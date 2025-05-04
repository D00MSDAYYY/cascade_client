#include "sensors_creator.hpp"

#include "page.hpp"
#include "ui_toolkit.hpp"

#include <QComboBox>
#include <QFile>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QTreeView>
#include <QVBoxLayout>


Q_DECLARE_METATYPE( sol::table )

sensors_creator::sensors_creator( const scripting::engine::ptr ngn_ptr, QWidget* parent )
	: scripting::object{ ngn_ptr }
	, QWidget( parent )
{
	Q_INIT_RESOURCE( sensors_creator );
	qRegisterMetaType< sol::table >( "sol::table" );
	//
	sensor::register_in_lua( _ngn_ptr.value() );
	// Main layout
	auto main_layout{ new QVBoxLayout( this ) };
	auto splitter{ new QSplitter( this ) };

	// Left side
	auto left_side{ new QWidget( this ) };
	auto left_layout{ new QVBoxLayout( left_side ) };

	// Right side
	auto right_side{ new QWidget( this ) };
	auto right_layout{ new QVBoxLayout( right_side ) };

	// 1. Templates Group with ComboBox containing TreeView
	auto templates_group{ new QGroupBox( "Templates", this ) };
	auto templates_layout{ new QVBoxLayout() };

	// Create ComboBox with TreeView
	auto templates_combo{ new QComboBox( this ) };
	auto tree_view{ new QTreeView( this ) };
	tree_view->setSelectionMode( QAbstractItemView::SingleSelection );

	auto combo_model{ new QStandardItemModel( this ) };

	// Configure TreeView
	tree_view->setHeaderHidden( true );
	tree_view->setRootIsDecorated( true );
	tree_view->setSelectionBehavior( QTreeView::SelectRows );
	tree_view->setColumnWidth( 0, 200 );
	tree_view->setIndentation( 20 );

	// Set TreeView as view for ComboBox
	templates_combo->setView( tree_view );
	templates_combo->setModel( combo_model );

	enum TEMPLATES_ITEM
	{
		TABLE = Qt::UserRole + 1
	};

	// Load data from LUA
	if ( QFile file{ QString{ ":/sensors_creator/scripts/sensors_templates_json.lua" } };
		 file.open( QIODevice::ReadOnly ) )
		{
			auto file_data{ _ngn_ptr.value()->script( file.readAll().constData() ) };
			file.close();

			if ( file_data.valid() )
				{
					auto templates{ file_data.get< sol::table >() };

					std::function< void( const sol::table&, QStandardItem* ) > parse_lua_table;
					parse_lua_table = [ &parse_lua_table ]( const sol::table& tbl, QStandardItem* parent ) {
						for ( const auto& [ key, value ] : tbl )
							{
								if ( key.is< int >() )
									{
										auto	item{ value.as< sol::table >() };
										QString name{
											item [ "name" ].get_or< std::string >( "Unnamed" ).c_str()
										};

										auto tree_item = new QStandardItem( name );

										if ( item [ "children" ].valid() )
											{
												tree_item->setIcon( QIcon{ ":/icons/folder.png" } );
												sol::table children{ item [ "children" ] };
												parse_lua_table( children, tree_item );
											}
										else
											{
												tree_item->setIcon( QIcon{ ":/icons/blueprint.png" } );
												tree_item->setData( QVariant::fromValue( item ),
																	TEMPLATES_ITEM::TABLE );
											}
										parent->appendRow( tree_item );
									}
							}
					};
					parse_lua_table( templates, combo_model->invisibleRootItem() );
					tree_view->expandAll();
				}
		}
	templates_layout->addWidget( templates_combo );

	// Buttons under ComboBox
	auto templates_btns_layout = new QHBoxLayout();
	templates_btns_layout->setContentsMargins( 0, 0, 0, 0 );

	_nd_t templates_actions_tree{
		{ .name		   = "_root_node",
		  .children
		  = { _nd_t{ { .name = "derive",
					   .data = { ._qaction = page::_bind_qaction_with_func( new QAction{ this },
																			[ this ]( auto derive_action ) {

																			} ) } } },
			_nd_t{ { .name = "edit",
					   .data = { ._qaction = page::_bind_qaction_with_func( new QAction{ this },
																			[ this ]( auto edit_action ) {

																			} ) } } },
			_nd_t{ { .name = "remove",
					   .data = { ._qaction = page::_bind_qaction_with_func( new QAction{ this },
																			[ this ]( auto remove_action ) {

																			} ) } } },
																		
																		
																		} }
	};

	auto fill_lyt{ [ this ]( _nd_t& node, auto* lyt ) {
		for ( auto& group : node._children )
			{
				if ( group._name == "|" ) { lyt->addStretch( 1 ); }
				else
					{
						auto btn{ new QPushButton(
							QIcon( ":/sensors_creator/icons/" + QString{ group._name.c_str() } + ".png" ),
							"",
							this ) };
						connect( btn, &QPushButton::clicked, [ action = group._data._qaction ]() {
							action->trigger();
						} );
						btn->setFixedSize( 32, 32 );
						lyt->addWidget( btn );
					}
			}
	} };
	fill_lyt( templates_actions_tree, templates_btns_layout );
	templates_btns_layout->addStretch( 1 );

	templates_layout->addLayout( templates_btns_layout );
	templates_group->setLayout( templates_layout );
	left_layout->addWidget( templates_group );

	// 2. Preview Group
	auto preview_group{ new QGroupBox {"Preview", this}  };
	auto preview_layout{ new QVBoxLayout{} };
	auto preview_window{ new QWidget {this}  };
	auto pr_win_lyt{ new QVBoxLayout{} };
	preview_window->setMinimumSize( 100, 100 );
	preview_window->setMaximumSize( 300, 300 );
	preview_window->setLayout( pr_win_lyt );
	preview_layout->addWidget( preview_window );
	preview_group->setLayout( preview_layout );
	left_layout->addWidget( preview_group );

	// 3. Parameters Group
	auto parameters_group  = new QGroupBox{ "Parameters", this} ;
	auto parameters_layout = new QVBoxLayout();
	auto parameters_window = new QWidget( this );
	parameters_window->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	parameters_layout->addWidget( parameters_window );
	parameters_group->setLayout( parameters_layout );
	left_layout->addWidget( parameters_group );

	// Right side - Edit Group
	auto edit_group{ new QGroupBox( "Edit", this ) };
	auto edit_layout{ new QVBoxLayout() };
	auto edit_area{ new QTextEdit( this ) };
	edit_area->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	edit_layout->addWidget( edit_area );

	auto  edit_btns_layout{ new QHBoxLayout() };

	_nd_t edit_actions_tree{
		{ .name = "_root_node",
		  .children
		  = { _nd_t{
				{ .name = "preview",
				  .data
				  = { ._qaction = page::_bind_qaction_with_func(
						  new QAction{ this },
						  [ this, edit_area, pr_win_lyt ]( auto preview_action ) {
							  auto text{ edit_area->toPlainText() };

							  _ngn_ptr.value()->set_function( "_steal_ownership", []( QWidget* ptr ) {
								  ui_toolkit::_steal_ownership< QWidget >( ptr );
							  } );

							  auto sns_lua{ _ngn_ptr.value()->script(
								  " ;  local sensor = {} ; " + text.toStdString()
								  + "; _steal_ownership(sensor) ; return sensor ; " ) };

							  if ( sns_lua.valid() )
								  {
									  if ( auto wgt_opt{ sns_lua.get< std::optional< QWidget* > >() };
										   wgt_opt )
										  {
											  if ( auto item{ pr_win_lyt->itemAt( 0 ) }; item )
												  {
													  auto old_wgt{ item->widget() };
													  pr_win_lyt->removeWidget( old_wgt );
													  old_wgt->deleteLater();
												  }
											  pr_win_lyt->addWidget( *wgt_opt );


											  _ngn_ptr.value()->script( " ; sensor = nil ; " );
											  sns_lua.abandon();

											  _ngn_ptr.value()->collect_garbage();
											  _ngn_ptr.value()->collect_garbage();

											  std::cout << "success" << std::endl;
										  }
									  else
										  {
											  std::cout
												  << "can't convert sensor from lua to widget. it's type is"
												  << sol::type_name( _ngn_ptr.value()->lua_state(),
																	 sns_lua.get_type() )
												  << std::endl;
										  }
								  }
							  else { std::cout << "sensor widget result is not valid" << std::endl; }
							  sol::state_view sv{ _ngn_ptr.value()->lua_state() };

							  _ngn_ptr.value()->collect_garbage();
							  _ngn_ptr.value()->collect_garbage();
							  sv.stack_clear();
							  _ngn_ptr.value()->collect_garbage();
							  _ngn_ptr.value()->collect_garbage();
						  } ) } } },
			  _nd_t{ { .name = "save",
					   .data
					   = { ._qaction = page::_bind_qaction_with_func( new QAction{ this },
																	  [ this ]( auto save_action ) {} ) } } },
			  _nd_t{ { .name = "|" } },
			  _nd_t{ { .name = "to default",
					   .data = { ._qaction = page::_bind_qaction_with_func(
									 new QAction{ this },
									 [ this ]( auto to_default_action ) {} ) } } } } }
	};
	fill_lyt( edit_actions_tree, edit_btns_layout );

	edit_layout->addLayout( edit_btns_layout );
	edit_group->setLayout( edit_layout );
	right_layout->addWidget( edit_group );

	// Assemble the interface
	splitter->addWidget( left_side );
	splitter->addWidget( right_side );
	main_layout->addWidget( splitter );

	// Set initial splitter sizes
	splitter->setSizes( { 300, 500 } );

	connect( tree_view, &QTreeView::pressed, [ edit_area, tree_view ]( const QModelIndex& index ) {
		if ( index.isValid() )
			{
				if ( not tree_view->model()->hasChildren( index ) )
					{
						auto table_variant{ index.data( TEMPLATES_ITEM::TABLE ) };

						if ( table_variant.canConvert< sol::table >() )
							{
								auto data_table{ table_variant.value< sol::table >() };

								auto text{ data_table [ "script" ].get_or< std::string >(
									"empty or error" ) };

								edit_area->setText( text.c_str() );
							}
					}
				else { edit_area->clear(); }
			}
	} );
}

sensors_creator::~sensors_creator() { Q_CLEANUP_RESOURCE( sensors_creator ); }

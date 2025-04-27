#include "sensors_creator.hpp"

#include <QComboBox>
#include <QFile>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPushButton>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QTreeView>
#include <QVBoxLayout>

sensors_creator::sensors_creator( QWidget* parent )
	: QWidget( parent )
{
	Q_INIT_RESOURCE( sensors_creator );

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

	// Load data from JSON
	if ( QFile file( ":/sensors_creator/sensors_templates.json" );
		 file.open( QIODevice::ReadOnly ) )
		{
			auto json_data = file.readAll();
			file.close();

			QJsonParseError error;
			auto			doc = QJsonDocument::fromJson( json_data, &error );
			if ( error.error == QJsonParseError::NoError && doc.isObject() )
				{
					auto root	   = doc.object();
					auto templates = root [ "templates" ].toArray();

					std::function< void( const QJsonObject&, QStandardItem* ) >
						parse_json;
					parse_json = [ &parse_json ]( const QJsonObject& obj,
												  QStandardItem* parent ) {
						auto item	   = new QStandardItem( obj [ "name" ].toString() );

						bool is_folder = obj.contains( "children" )
									  && !obj [ "children" ].toArray().isEmpty();
						item->setIcon( QIcon( is_folder ? ":/icons/folder.png"
														: ":/icons/blueprint.png" ) );

						if ( is_folder )
							{
								auto children = obj [ "children" ].toArray();
								for ( const auto& child : children )
									{
										parse_json( child.toObject(), item );
									}
							}
						parent->appendRow( item );
					};

					for ( const auto& t : templates )
						{
							parse_json( t.toObject(), combo_model->invisibleRootItem() );
						}
					tree_view->expandAll();
				}
		}

	templates_layout->addWidget( templates_combo );

	// Buttons under ComboBox
	auto templates_btns_layout = new QHBoxLayout();
	templates_btns_layout->setContentsMargins( 0, 0, 0, 0 );

	for ( const QString& str : { "derive", "edit", "remove" } )
		{
			auto btn
				= new QPushButton( QIcon( ":/sensors_creator/icons/" + str + ".png" ),
								   "",
								   this );
			btn->setFixedSize( 32, 32 );
			templates_btns_layout->addWidget( btn );
		}
	templates_btns_layout->addStretch( 1 );

	templates_layout->addLayout( templates_btns_layout );
	templates_group->setLayout( templates_layout );
	left_layout->addWidget( templates_group );

	// 2. Preview Group
	auto preview_group	= new QGroupBox( "Preview", this );
	auto preview_layout = new QVBoxLayout();
	auto preview_window = new QWidget( this );
	preview_window->setMinimumSize( 100, 100 );
	preview_window->setStyleSheet( "background-color: red;" );
	preview_layout->addWidget( preview_window );
	preview_group->setLayout( preview_layout );
	left_layout->addWidget( preview_group );

	// 3. Parameters Group
	auto parameters_group  = new QGroupBox( "Parameters", this );
	auto parameters_layout = new QVBoxLayout();
	auto parameters_window = new QWidget( this );
	parameters_window->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	parameters_layout->addWidget( parameters_window );
	parameters_group->setLayout( parameters_layout );
	left_layout->addWidget( parameters_group );

	// Right side - Edit Group
	auto edit_group	 = new QGroupBox( "Edit", this );
	auto edit_layout = new QVBoxLayout();
	auto edit_area	 = new QTextEdit( this );
	edit_area->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	edit_layout->addWidget( edit_area );

	auto edit_btns_layout = new QHBoxLayout();
	for ( const QString& str : { "refresh", "save", "|", "to default" } )
		{
			if ( str == "|" ) { edit_btns_layout->addStretch( 1 ); }
			else
				{
					auto btn = new QPushButton(
						QIcon( ":/sensors_creator/icons/" + str + ".png" ),
						"",
						this );
					btn->setFixedSize( 32, 32 );
					edit_btns_layout->addWidget( btn );
				}
		}
	edit_layout->addLayout( edit_btns_layout );
	edit_group->setLayout( edit_layout );
	right_layout->addWidget( edit_group );

	// Assemble the interface
	splitter->addWidget( left_side );
	splitter->addWidget( right_side );
	main_layout->addWidget( splitter );

	// Set initial splitter sizes
	splitter->setSizes( { 300, 500 } );
}

sensors_creator::~sensors_creator() { Q_CLEANUP_RESOURCE( sensors_creator ); }

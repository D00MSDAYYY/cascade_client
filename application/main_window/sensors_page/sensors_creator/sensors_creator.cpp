#include "sensors_creator.hpp"

#include <QComboBox>
#include <QFile>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPushButton>
#include <QRadioButton>
#include <QSplitter>
#include <QStandardItem>
#include <QTextEdit>
#include <QTreeView>
#include <QVBoxLayout>

sensors_creator::sensors_creator( QWidget* parent )
	: QWidget( parent )
{
	Q_INIT_RESOURCE( sensors_creator );

	// start templates group //

	auto templates_group_layout{ new QVBoxLayout{} };

	if ( QFile file( ":/sensors_creator/sensors_templates.json" );
		 file.open( QIODevice::ReadOnly ) )
		{
			auto json_data = file.readAll();
			file.close(); // Всегда закрывайте файл после чтения

			QJsonParseError error;
			auto			doc = QJsonDocument::fromJson( json_data, &error );
			if ( error.error != QJsonParseError::NoError )
				{
					std::cerr << "JSON parse error: " << error.errorString().toStdString()
							  << " at offset: " << error.offset << std::endl;
					return;
				}

			if ( !doc.isObject() )
				{
					std::cerr << "Document is not a JSON object" << std::endl;
					return;
				}

			// Выводим сырые данные для отладки
			std::cout << "Raw JSON:\n" << json_data.constData() << std::endl;

			auto root{ doc.object() };
			auto templates = root [ "templates" ]
								 .toArray(); //! don't change to auto templates{ ... } coz
											 //! it will coz a bug with templates.size()

			std::cout << "Correct size = " << templates.size() << std::endl;

			enum TEMPLATE_FIELDS
			{
				IS_FOLDER = 0,
				IS_MODIFIABLE,
				SCRIPT
			};

			std::function< void( const QJsonObject&, QStandardItem* ) > parse_json;
			parse_json = [ &parse_json ]( const QJsonObject& obj,
										  QStandardItem* parent ) {
				auto item{ new QStandardItem( obj [ "name" ].toString() ) };

				auto is_folder{ obj.contains( "children" )
								&& !obj [ "children" ].toArray().isEmpty() };

				item->setIcon(
					QIcon( is_folder ? ":/icons/folder.png" : ":/icons/blueprint.png" ) );
				item->setText( obj [ "name" ].toString() );
					item->setData( is_folder, TEMPLATE_FIELDS::IS_FOLDER );
				item->setData( obj [ "modifiable" ].toBool( false ),
							   TEMPLATE_FIELDS::IS_MODIFIABLE );
				item->setData( obj [ "script" ].toString(), TEMPLATE_FIELDS::SCRIPT );
				// TODO! should i add item->setData( obj [ "children" ].toArray(),
				// TEMPLATE_FIELDS::CHILDREN );

				if ( is_folder )
					{
						auto children{ obj [ "children" ].toArray() };
						for ( const auto& child : children )
							{
								parse_json( child.toObject(), item );
							}
					}

				parent->appendRow( item );
			};


			auto model{ new QStandardItemModel() };
			model->setHorizontalHeaderLabels( { "Templates" } );

			for ( const auto& t : templates )
				{
					parse_json( t.toObject(), model->invisibleRootItem() );
				}

			auto tree_view{ new QTreeView() };
			tree_view->setModel( model );
			tree_view->setHeaderHidden( true );
			tree_view->expandAll();

			// Добавьте эти строки:
			tree_view->setStyleSheet( "QTreeView { color: black; font: 12px; }" );
			tree_view->setColumnWidth( 0, 200 ); // Ширина колонки
			tree_view->setIndentation( 20 );

			templates_group_layout->addWidget( tree_view );
			std::cout << "ALL IS OK" << std::endl;
			std::cout << "Model row count:" << model->rowCount() << std::endl;
			for ( int i = 0; i < model->rowCount(); ++i )
				{
					auto item = model->item( i );
					std::cout << "Top level item:" << item->text().toStdString();
					if ( item->hasChildren() )
						{
							std::cout << "Has children:" << item->rowCount();
						}
				}
		}
	else
		{
			std::cout << "can't open json file for tree-view " << std::endl;
			file.close();
		}

	auto templates_btns_layout{ new QHBoxLayout{} };
	templates_btns_layout->setContentsMargins( 0, 0, 0, 0 );

	for ( const QString& str : { "derive", "edit", "remove" } )
		{
			auto path_str{ ( ":/sensors_creator/icons/" + str ) + ".png" };
			auto templates_btn{
				new QPushButton{ QIcon{ QPixmap{ path_str } }, "", this }
			};
			templates_btn->setFixedSize( 32, 32 );
			templates_btns_layout->addWidget( templates_btn );
		}
	templates_btns_layout->addStretch( 1 );


	auto templates_group{
		new QGroupBox{ "Templates", this }
	};


	templates_group_layout->addLayout( templates_btns_layout );
	templates_group->setLayout( templates_group_layout );
	// end templates group //

	// start preview group //
	auto preview_window{ new QWidget{ this } };
	preview_window->setMinimumSize( 100, 100 );
	preview_window->setStyleSheet( "background-color: red ;" );

	auto preview_group_layout{ new QVBoxLayout{} };
	preview_group_layout->addWidget( preview_window );

	auto preview_group{
		new QGroupBox{ "Preview", this }
	};
	preview_group->setLayout( preview_group_layout );
	// end preview group //

	// start parameters group //
	auto parameters_group{
		new QGroupBox{ "Parameters", this }
	};
	auto parameters_window{ new QWidget{ this } };
	parameters_window->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

	auto parameters_group_layout{ new QVBoxLayout{} };
	parameters_group_layout->addWidget( parameters_window );
	parameters_group->setLayout( parameters_group_layout );
	// end parameters group //

	// start left layout //
	auto left_layout{ new QVBoxLayout{} };
	left_layout->addWidget( templates_group );
	left_layout->addWidget( preview_group );
	left_layout->addWidget( parameters_group );
	// end left layout //

	// start edit group //
	auto edit_area{ new QTextEdit{ this } };
	edit_area->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

	auto edit_btns_layout{ new QHBoxLayout{} };
	for ( const QString& str : { "refresh", "save", "|", "to default" } )
		{
			if ( str == "|" ) { edit_btns_layout->addStretch( 1 ); }
			else
				{
					auto path_str{ ( ":/sensors_creator/icons/" + str ) + ".png" };
					auto edit_btn{
						new QPushButton{ QIcon{ QPixmap{ path_str } }, "", this }
					};
					edit_btn->setFixedSize( 32, 32 );
					edit_btns_layout->addWidget( edit_btn );
				}
		}

	auto edit_group_layout{ new QVBoxLayout{} };
	edit_group_layout->addWidget( edit_area );
	edit_group_layout->addLayout( edit_btns_layout );

	auto edit_group{
		new QGroupBox{ "Edit", this }
	};

	edit_group->setLayout( edit_group_layout );
	// end edit group //

	// start right layout //
	auto right_layout{ new QVBoxLayout{} };
	right_layout->addWidget( edit_group );
	// end right layout //

	auto left_side{ new QWidget{ this } };
	left_side->setLayout( left_layout );

	auto right_side{ new QWidget{ this } };
	right_side->setLayout( right_layout );

	auto central_splitter{ new QSplitter{ this } };
	central_splitter->addWidget( left_side );
	central_splitter->addWidget( right_side );

	auto main_layout{ new QVBoxLayout{} };
	main_layout->addWidget( central_splitter );

	setLayout( main_layout );
}

sensors_creator::~sensors_creator() { Q_CLEANUP_RESOURCE( sensors_creator ); }

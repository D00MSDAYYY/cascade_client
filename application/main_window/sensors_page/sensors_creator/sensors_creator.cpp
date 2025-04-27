#include "sensors_creator.hpp"

#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>

sensors_creator::sensors_creator( QWidget* parent )
	: QWidget( parent )
{
	Q_INIT_RESOURCE( sensors_creator );

	// start templates group //
	auto templates_combobox{ new QComboBox{ this } }; // TODO! change to tree-like view
	templates_combobox->addItem( "BLANK" );
	templates_combobox->addItem( "CO2" );
	templates_combobox->addItem( "Light" );
	templates_combobox->addItem( "Air" );
	templates_combobox->addItem( "Video" );

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
	auto templates_group_layout{ new QVBoxLayout{} };
	templates_group_layout->addWidget( templates_combobox );
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
	for ( const QString& str : { "refresh","save", "|", "to default" } )
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

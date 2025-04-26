#include "sensors_creator.hpp"

#include <QButtonGroup>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QSplitter>
#include <QVBoxLayout>

sensors_creator::sensors_creator( QWidget* parent )
	: QDialog( parent )
{
	Q_INIT_RESOURCE( sensors_creator );

	auto main_lyt{ new QHBoxLayout{} };
	auto main_splttr{ new QSplitter{ this } };

	auto lft_grp{
		new QGroupBox{ "Templates", this }
	};
	auto lft_lyt{ new QVBoxLayout{ this } };

	auto lft_up_grp{
		new QGroupBox{ "Standard", this }
	};
	auto lft_up_lyt{ new QVBoxLayout{} };
	auto stndrd_tmplts_cmb{ new QComboBox{ this } };
	// /////////////////////////////////////////////////
	stndrd_tmplts_cmb->addItem(
		"Temperature" ); // TODO change qcombobox to tree-like (directory) structure
	stndrd_tmplts_cmb->addItem( "CO2" );
	stndrd_tmplts_cmb->addItem( "Light" );
	stndrd_tmplts_cmb->addItem( "Air" );
	stndrd_tmplts_cmb->addItem( "Video" );
	stndrd_tmplts_cmb->addItem( "Audio" );
	stndrd_tmplts_cmb->addItem( "Analog" );
	stndrd_tmplts_cmb->addItem( "Discrete" );
	stndrd_tmplts_cmb->addItem( "Bool Flag" );
	// /////////////////////////////////////////////////
	auto stndrd_btns_grp{ new QGroupBox{ this } };
	auto stndrd_btns_lyt{ new QHBoxLayout{} };
	auto stndrd_derive_btn{ new QPushButton{ this } };
	stndrd_derive_btn->setFixedSize( 32, 32 );
	stndrd_derive_btn->setIcon( QIcon( QPixmap( ":/icons/derive.png" ) ) );
	stndrd_btns_lyt->addWidget( stndrd_derive_btn );
	stndrd_btns_lyt->addStretch( 1 );
	stndrd_btns_lyt->setContentsMargins( 0, 0, 0, 0 );
	stndrd_btns_grp->setLayout( stndrd_btns_lyt );
	stndrd_btns_grp->setFlat( true );

	lft_up_lyt->addWidget( stndrd_tmplts_cmb );
	lft_up_lyt->addWidget( stndrd_btns_grp );
	lft_up_lyt->addStretch( 1 );
	lft_up_grp->setLayout( lft_up_lyt );
	// ///////////////////////////////////////////////
	auto lft_btm_grp{
		new QGroupBox{ "User-defined", this }
	};
	auto lft_btm_lyt{ new QVBoxLayout{} };
	auto usr_tmplts_cmb{ new QComboBox{ this } };

	auto usr_btns_grp{ new QGroupBox{ this } };
	auto usr_btns_lyt{ new QHBoxLayout{} };

	for ( const auto& [ str, func ] :
		  std::vector< std::pair< std::string, std::function< void() > > >{
			{ "add",	 []() { return; } },
			{ "remove", []() { return; } },
			{ "edit",	  []() { return; } },
			{ "derive", []() { return; } }
	   } )
		{
			auto usr_btn{ new QPushButton{ this } };
			usr_btn->setFixedSize( 32, 32 );
			auto path{ ":/sensors_creator/icons/" + str + ".png" };
			usr_btn->setIcon( QIcon( QPixmap( path.c_str() ) ) );
			usr_btns_lyt->addWidget( usr_btn );
		}
	// /////
	usr_btns_lyt->addStretch( 1 );
	usr_btns_lyt->setContentsMargins( 0, 0, 0, 0 );
	usr_btns_grp->setLayout( usr_btns_lyt );
	usr_btns_grp->setFlat( true );
	lft_btm_lyt->addWidget( usr_tmplts_cmb );
	lft_btm_lyt->addWidget( usr_btns_grp );
	lft_btm_lyt->addStretch( 1 );
	lft_btm_grp->setLayout( lft_btm_lyt );

	lft_lyt->addWidget( lft_up_grp );
	lft_lyt->addWidget( lft_btm_grp );
	lft_grp->setLayout( lft_lyt );

	auto rght_pln{ new QWidget{ this } };
	auto rght_lyt{ new QVBoxLayout{} };
	auto prvw_grp{
		new QGroupBox{ "Preview", this }
	};
	auto prvw_lyt{ new QVBoxLayout{} };

	auto rght_cntr_lyt{ new QVBoxLayout{} };
	auto prvw_wndw{ new QWidget{ this } };
	prvw_wndw->setStyleSheet( "background-color: red ;" );
	prvw_wndw->setMinimumSize( 100, 100 );
	prvw_wndw->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

	auto prvw_swtchr_grp{
		new QGroupBox{ "Mode", this }
	};
	auto prvw_swtchr_lyt{ new QVBoxLayout{} };
	auto txt_md_btn{
		new QRadioButton{ "Text", this }
	}; // TODO replace preview widget for sensor visualization by qscroll area for text
	   // mode

	auto vsl_md_btn{
		new QRadioButton{ "Visual", this }
	};

	auto fnsh_btns_lyt{ new QHBoxLayout{} };
	auto crt_btn{
		new QPushButton{ "Create", this }
	};
	connect( crt_btn, &QPushButton::clicked, this, [ this ]() {
		emit sensor_created( new QWidget{ this } );
		close();
	} );
	auto cncl_btn{
		new QPushButton{ "Cancel", this }
	};
	connect( cncl_btn, &QPushButton::clicked, this, &QWidget::close );

	fnsh_btns_lyt->addStretch( 1 );
	fnsh_btns_lyt->addWidget( cncl_btn );
	fnsh_btns_lyt->addWidget( crt_btn );

	prvw_swtchr_lyt->addWidget( vsl_md_btn );
	prvw_swtchr_lyt->addWidget( txt_md_btn );
	prvw_swtchr_lyt->addStretch( 1 );
	prvw_swtchr_grp->setLayout( prvw_swtchr_lyt );
	rght_cntr_lyt->addWidget( prvw_wndw );
	rght_cntr_lyt->addWidget( prvw_swtchr_grp );

	prvw_lyt->addStretch( 1 );
	prvw_lyt->addLayout( rght_cntr_lyt );

	prvw_grp->setLayout( prvw_lyt );
	rght_lyt->addWidget( prvw_grp );
	rght_lyt->addLayout( fnsh_btns_lyt );
	rght_lyt->setContentsMargins( 0, 0, 0, 0 );
	rght_pln->setLayout( rght_lyt );

	main_splttr->addWidget( lft_grp );
	main_splttr->addWidget( rght_pln );
	main_lyt->addWidget( main_splttr );
	setLayout( main_lyt );
	setFixedSize( 1'024 * 2 / 3, 600 * 2 / 3 );
}

sensors_creator::~sensors_creator() { Q_CLEANUP_RESOURCE( sensors_creator ); }

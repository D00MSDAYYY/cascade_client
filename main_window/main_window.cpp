#include "main_window.hpp"

#include "ui_main_window.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>

main_window::main_window(QWidget* parent)
	: QWidget(parent),
	  ui(new Ui::main_window)
{
	Q_INIT_RESOURCE(icons);
	/////////////////////////////////////////////
	// clang-format off
	auto tb_layout{new QHBoxLayout{}};

	auto left_btn{new QPushButton{}};
		 left_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		 left_btn->setMinimumSize(1, 1);
		 left_btn->setIcon(QIcon{":/icons/arrow_left.png"});
	auto scroll_layout{new QHBoxLayout{}};
		 scroll_layout->setContentsMargins(0, 0, 0, 0);
		 scroll_layout->setSpacing(1);
		//  scroll_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
		//  for(auto elem : {"1","2","3","4","5"})
		//  {
		// 	auto tmp_btn{new QPushButton{elem}};
		// 	auto scroll_size{scroll_layout->geometry()};
		// 	tmp_btn->setFixedSize({40,40});
        //     scroll_layout->addWidget(tmp_btn);
		//  }
		


	auto right_btn{new QPushButton{}};
	     right_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		 right_btn->setMinimumSize(1, 1);
		 right_btn->setIcon(QIcon{":/icons/arrow_right.png"});

	tb_layout->addWidget(left_btn);
	tb_layout->addLayout(scroll_layout);
	tb_layout->addWidget(right_btn);

	tb_layout->setStretch(0, 1);
	tb_layout->setStretch(1, 40);
	tb_layout->setStretch(2, 1);

	tb_layout->setContentsMargins(1, 1, 1, 1);
	tb_layout->setSpacing(1);

	/////////////////////////////////////////////
	auto mw_layout{new QVBoxLayout{}};
	resize(600, 400);
	setLayout(mw_layout);

	

	mw_layout->addLayout(tb_layout);

	auto tmp{new QWidget{}};
	     tmp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Растягиваем кнопку

	// tmp->setMinimumSize({100,100});
	mw_layout->addWidget(tmp);

	
	mw_layout->setContentsMargins(1, 1, 1, 1);
	mw_layout->setSpacing(1);

	mw_layout->setStretch(0, 1);
	mw_layout->setStretch(1, 20);

	
	// clang-format off
}

main_window::~main_window() { delete ui; }

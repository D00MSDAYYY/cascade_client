#include "main_window.hpp"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>

main_window::main_window(QWidget* parent)
	: QWidget(parent)
{
	Q_INIT_RESOURCE(icons);
	/////////////////////////////////////////////
	left_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	left_btn->setMinimumSize(12, 12);
	left_btn->setIcon(QIcon{":/icons/arrow_left.png"});
	left_btn->setIconSize(left_btn->size());

	scroll_layout->setContentsMargins(15, 0, 15, 0);
	scroll_layout->setSpacing(0);
	for(auto title: {"connection.png", "flash.png", "network.png", "eject.png"})
	{
		auto tmp_btn{new QPushButton{}};
		// tmp_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tmp_btn->setIcon(QIcon{":/icons/" + QString{title}});
		scroll_layout->addWidget(tmp_btn);
		tmp_btn->setIconSize(left_btn->size());
	}
	scroll_layout->addSpacerItem(
		new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

	right_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	right_btn->setMinimumSize(12, 12);
	right_btn->setIcon(QIcon{":/icons/arrow_right.png"});
	right_btn->setIconSize(right_btn->size());

	tb_layout->addWidget(left_btn);
	tb_layout->addLayout(scroll_layout);
	tb_layout->addWidget(right_btn);

	tb_layout->setStretch(0, 1);
	tb_layout->setStretch(1, 25);
	tb_layout->setStretch(2, 1);

	tb_layout->setContentsMargins(0, 0, 0, 0);
	tb_layout->setSpacing(0);

	/////////////////////////////////////////////
	auto mw_layout{new QVBoxLayout{}};
	resize(600, 400);
	setLayout(mw_layout);

	mw_layout->addLayout(tb_layout);

	auto tmp{new QPushButton{}};
	tmp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);	 // Растягиваем кнопку

	// tmp->setMinimumSize({100,100});
	mw_layout->addWidget(tmp);

	mw_layout->setContentsMargins(1, 1, 1, 1);
	mw_layout->setSpacing(1);

	mw_layout->setStretch(0, 1);
	mw_layout->setStretch(1, 12);
}

main_window::~main_window() {}

void
main_window::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);

	int buttonSize = scroll_layout->geometry().height();
	for(int i = 0; i < scroll_layout->count() - 1; ++i)
	{
		auto btn = qobject_cast<QPushButton*>(scroll_layout->itemAt(i)->widget());
		if(btn)
		{
			btn->setFixedSize(buttonSize, buttonSize);
			btn->setIconSize(btn->size());
		}
	}
}

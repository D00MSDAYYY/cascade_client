#include "sensors_page.hpp"

sensors_page::sensors_page(QWidget* parent)
	: QMainWindow{parent}
{
	_snsrs_grd->setSpacing(5);
	_snsrs_grd->setContentsMargins(5, 5, 5, 5);

	_snsrs_pln->setLayout(_snsrs_grd);

	_scrl_area->setWidgetResizable(true);
	_scrl_area->setWidget(_snsrs_pln);

	setCentralWidget(_scrl_area);

	// _pg_lyt->addWidget(_scrl_area);

	// connect(_add_btn, &QPushButton::clicked, this, &sensors_page::addWidget);

	// setLayout(_pg_lyt);

}

void
sensors_page::addWidget()
{
	auto newWidget{new QPushButton(_snsrs_pln)};
	auto		 count{_snsrs_grd->count()};
	newWidget->setText("Виджет " + QString::number(count));
	newWidget->setFixedSize(100, 50);

	int row{count / 2};
	int col{count % 2};

	// Добавляем виджет в сетку
	_snsrs_grd->addWidget(newWidget, row, col);
}

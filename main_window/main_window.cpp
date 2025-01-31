#include "main_window.hpp"

#include "./ui_main_window.h"

#include <QPushButton>
#include <iostream>

main_window::main_window(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::main_window)
{
    ui->setupUi(this);

    ui->btns_list->setSelectionMode(QListWidget::NoSelection);

    auto strs = {"Button 1", "Button 2", "Button 3", "Button 4"};

    for(const QString& str: strs)
    {
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint({90, 10});
        QPushButton* btn = new QPushButton(str);
        connect(btn,
                &QPushButton::pressed,
                [=]()
                {
                    btn->setText("pressed");
                });
        connect(btn,
                &QPushButton::released,
                [=]()
                {
                    btn->setText("released");
                });
        ui->btns_list->addItem(item);
        ui->btns_list->setItemWidget(item, btn);
    }
    // ui->btns_list->addItem({"hello"});
}

main_window::~main_window() { delete ui; }

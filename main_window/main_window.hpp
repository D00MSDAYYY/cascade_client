#pragma once

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>

class main_window : public QWidget
{
	Q_OBJECT

public:
	main_window(QWidget* parent = nullptr);
	~main_window();

protected:
	void
	resizeEvent(QResizeEvent* event);

private:
	QHBoxLayout* tb_layout{new QHBoxLayout{}};
	QPushButton* left_btn{new QPushButton{}};
	QHBoxLayout* scroll_layout{new QHBoxLayout{}};
	QPushButton* right_btn{new QPushButton{}};
};

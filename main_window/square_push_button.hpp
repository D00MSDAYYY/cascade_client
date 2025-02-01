#pragma once
#include <QPushButton>

class SquareButton : public QPushButton
{
	Q_OBJECT

public:
	SquareButton(const QString& text, QWidget* parent = nullptr)
		: QPushButton(text, parent)
	{
	}

protected:
	void
	resizeEvent(QResizeEvent* event) override
	{
		setIconSize(event->size());
		QPushButton::resizeEvent(event);
	}
};

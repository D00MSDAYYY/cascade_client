#pragma once
#include <QListWidget>

class square_list_widget : public QListWidget
{
	Q_OBJECT

public:
	square_list_widget(QWidget* parent = nullptr)
		: QListWidget{parent}
	{
	}

protected:
	void
	resizeEvent(QResizeEvent* event) override
	{
		for(int i{0}; i < count(); ++i)
		{
			auto item{this->item(i)};
			int	 min_size{qMin(event->size().width(), event->size().height())};
			item->setSizeHint({min_size, min_size});

			auto widget{itemWidget(item)};
			if(widget) { widget->resize(min_size, min_size); }
		}
		QListWidget::resizeEvent(event);
	}
};
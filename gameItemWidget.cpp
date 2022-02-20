#include "gameItemWidget.h"

#include <QGridLayout>
#include <QMimeData>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QDataStream>
#include <QByteArray>

#include "gameDB.h"

gameItemWidget::gameItemWidget(QWidget* parent, int row_, int column_, QJsonArray item_) :
	QWidget(parent),
	isInfinite(false),
	row(row_),
	column(column_),
	item(item_)
{
	count = new QLabel(this);
	count->setText(QString::number(item[COUNT].toInt()));

	image = new QLabel(this);
	QPixmap iconImage(gameDB::getImage(item[IMAGE].toString()));
	iconImage = iconImage.scaled(QSize(90, 90));
	image->setPixmap(iconImage);

	QGridLayout* layout = new QGridLayout();
	layout->addWidget(image, 0, 0);
	layout->addWidget(count, 1, 1);
	setLayout(layout);

	setAcceptDrops(true);
}

void gameItemWidget::setItem(const QJsonArray& item_)
{
	item = item_;
	update();
}

QJsonArray gameItemWidget::getItem()
{
	return item;
}

void gameItemWidget::setInfinite(bool b)
{
	isInfinite = b;
}

bool gameItemWidget::getInfinite()
{
	return isInfinite;
}

void gameItemWidget::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasFormat("QJsonArray") && !isInfinite)
		event->acceptProposedAction();
}

void gameItemWidget::dropEvent(QDropEvent* event)
{
	QByteArray encodedData = event->mimeData()->data("QJsonArray");
	QDataStream stream(&encodedData, QIODevice::ReadOnly);
	QVariant data;
	stream >> data;
	QJsonArray recivedItem = data.toJsonArray();

	gameItemWidget* sender = static_cast<gameItemWidget*>(event->source());

	if (recivedItem[NAME] == item[NAME])
	{
		item[COUNT] = recivedItem[COUNT].toInt() + item[COUNT].toInt();
		gameDB::set(item,row, column);
		if(!sender->getInfinite())
			sender->setEmpty();
	}
	else if (item[NAME].toString() == QString(""))
	{
		count->show();
		item = recivedItem;
		gameDB::set(item, row, column);
		if (!sender->getInfinite())
			 sender->setEmpty();
	}
	else
	{
		///if name not equal make swap
	}

	emit update();
}

void gameItemWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		QDrag* drag = new QDrag(this);
		QMimeData* mimeData = new QMimeData;

		QByteArray encodedData;
		QDataStream stream(&encodedData, QIODevice::WriteOnly);
		stream << QVariant(item);

		mimeData->setData("QJsonArray", encodedData);
		drag->setMimeData(mimeData);

		Qt::DropAction dropAction = drag->exec();
	}
	else if (event->button() == Qt::RightButton)
	{
		int count = item.at(COUNT).toInt();
		if (count > 1 && !isInfinite) 
			item[COUNT] = --count;
		else if(!isInfinite)
		{
			setEmpty();
		}
		emit update();
	}
}

void gameItemWidget::update()
{
	count->setText(QString::number(item[COUNT].toInt()));

	QPixmap iconImage(gameDB::getImage(item[IMAGE].toString()));
	iconImage = iconImage.scaled(QSize(90, 90));
	image->setPixmap(iconImage);
}

void gameItemWidget::setEmpty()
{
	count->hide();
	item[COUNT] = 0;
	item[IMAGE] = QString("empty-icon.png");
	item[NAME] = QString("");
	update();
	gameDB::set(item, row, column);
}
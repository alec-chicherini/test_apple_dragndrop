#pragma once
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QJsonArray>

#include "enums.h"

class gameItemWidget : public QWidget
{
	
public:
	gameItemWidget(QWidget* parent);

private:
	QLabel * count;
	QLabel * image;
	QJsonArray item;
	bool isInfinite;

private slots:
	void update();

public slots:
	void setEmpty();
	void setItem(const QJsonArray& item);
	QJsonArray getItem();
	void setInfinite(bool);
	bool getInfinite();

protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dropEvent(QDropEvent* event);
	void mousePressEvent(QMouseEvent* event);
};
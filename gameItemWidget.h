#pragma once
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QJsonArray>

#include "enums.h"

class gameItemWidget : public QWidget
{
	
public:
	gameItemWidget(QWidget* parent,int row, int column, QJsonArray item);

private:
	QLabel * count;
	QLabel * image;
	QJsonArray item;
	bool isInfinite;
	int column;
	int row;

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
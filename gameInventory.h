#pragma once
#include <QTableWidget>
#include <QWidget>

#include "gameItemWidget.h"

class gameInventory : public QTableWidget
{
	
public:
	gameInventory() = delete;
	gameInventory(int countRows_, int countColumns_, QWidget * parent = nullptr);
	void fillInventory(QJsonArray item,int row, int column);
	void fillInventory(QJsonArray item);
	void fillInventory();
	gameItemWidget* getItem(int row, int column);
	void setItem(const QJsonArray & item, int row, int column);
};
#pragma once
#include <QWidget>
#include "gameInventory.h"

class gameWidget : public QWidget
{
	
public:
	gameWidget(QWidget* parent = nullptr);

private:
	gameInventory * table;
	gameInventory * single;
};
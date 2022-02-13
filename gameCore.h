#pragma once
#include <QObject>

#include "gameMainMenu.h"
#include "gameWidget.h"

class gameCore : public QObject
{
	
public:
	static gameWidget* takeGameWidget();
	static gameMainMenu* takeMainMenu();
	static gameCore* instance();

private:
	gameCore(QObject * parent = nullptr);
	static gameWidget* game;
	static gameMainMenu* menu;
};
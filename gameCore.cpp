#include "gameCore.h"
#include <QDebug>
gameWidget*   gameCore::game = nullptr;
gameMainMenu* gameCore::menu = nullptr;

gameCore::gameCore(QObject* parent) :
	QObject(parent)
{
	menu = new gameMainMenu();
	menu->show();
}
gameWidget* gameCore::takeGameWidget()
{
	return (game == nullptr)?new gameWidget() : game;
}
gameMainMenu* gameCore::takeMainMenu()
{
	return (menu == nullptr) ? new gameMainMenu() : menu;
}
gameCore* gameCore::instance()
{	
	static gameCore gameCore_;
	return &gameCore_;
}
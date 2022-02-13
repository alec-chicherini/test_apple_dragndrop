#include <QApplication>
#include "gameCore.h"
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	gameCore::instance();
	return app.exec();
}
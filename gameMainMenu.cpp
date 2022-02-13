#include "gameMainMenu.h"

#include "gameWidget.h"
#include "gameCore.h"

#include <QVBoxLayout>
#include <QPushButton>

#include "gameItemWidget.h"

gameMainMenu::gameMainMenu(QWidget* parent) :
									     QWidget(parent)
{
	QVBoxLayout * layout = new QVBoxLayout();
	QPushButton * btnNewGame = new QPushButton(tr("Новая игра"), this);
	QPushButton * btnExit = new QPushButton(tr("Выход"), this);
	layout->addWidget(btnNewGame);
	layout->addWidget(btnExit);
	setLayout(layout);

	connect(btnNewGame, &QPushButton::clicked, this, [&] {
		gameWidget* game = gameCore::takeGameWidget();
		this->setHidden(true);
		game->show();
		});

	connect(btnExit, &QPushButton::clicked, this, &QWidget::close);
};
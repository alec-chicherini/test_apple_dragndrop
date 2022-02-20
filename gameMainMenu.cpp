#include "gameMainMenu.h"

#include "gameWidget.h"
#include "gameCore.h"

#include <QVBoxLayout>
#include <QPushButton>

#include "gameItemWidget.h"

gameMainMenu::gameMainMenu(QWidget* parent) :
									     QWidget(parent)
{
	
	QPushButton * btnNewGame = new QPushButton(tr("Игра"), this);
	btnNewGame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPushButton * btnExit = new QPushButton(tr("Выход"), this);
	btnExit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(btnNewGame);
	layout->addWidget(btnExit);
	setLayout(layout);

	connect(btnNewGame, &QPushButton::clicked, this, [&] {
		gameWidget* game = gameCore::takeGameWidget();
		this->setHidden(true);
		game->show();
		});

	connect(btnExit, &QPushButton::clicked, this, &QWidget::close);
	setFixedSize(400, 200);
};
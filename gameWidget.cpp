﻿#include "gameWidget.h"

#include "gameMainMenu.h"
#include "gameCore.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QJsonArray>

#include "enums.h"
#include "gameDB.h"

gameWidget::gameWidget(QWidget* parent) :
	QWidget(parent),
	table(new gameInventory(3, 3, this)),
	single(new gameInventory(1, 1, this))
{
	gameDB db;
	qDebug() << "db.checkDBTables() = " << db.checkDBTables();

	/// TODO::refactor access to DB in model-view style
	if  ( db.checkDBTables())
	{
		for (int row = 0; row < table->rowCount(); row++)
			for (int column = 0; column < table->columnCount(); column++)
				table->setItem(db.get(row, column), row, column);
			
	}
	else
	{
		db.initDBTables();
		table->fillInventory();
		for (int row = 0; row < table->rowCount(); row++)
			for (int column = 0; column < table->columnCount(); column++)
				db.set(table->getItem(row, column)->getItem(), row, column);
	}
	QJsonArray test_item;
	
	test_item.insert(NAME, QString("Apple"));
	test_item.insert(IMAGE, QString("S:/Code/test_apple_dragndrop/images/apple-icon.png"));
	test_item.insert(COUNT, 1);

	single->fillInventory(test_item);
	single->getItem(0, 0)->setInfinite(true);
	
	QPushButton* btnMainMenu = new QPushButton(tr("Главное меню"), this);
	QGridLayout* layout = new QGridLayout();
	layout->addWidget(table, 0, 0);
	layout->addWidget(single, 0, 1);
	layout->addWidget(btnMainMenu, 1, 0, 1, -1);
	setLayout(layout);

	connect(btnMainMenu, &QPushButton::clicked, this, [&] {
		gameCore::takeMainMenu()->show();
		this->close();
		});

	setFixedSize(size());
};
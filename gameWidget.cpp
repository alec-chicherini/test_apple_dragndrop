#include "gameWidget.h"

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

	for (int row = 0; row < table->rowCount(); row++)
		for (int column = 0; column < table->columnCount(); column++)
			table->setItem(gameDB::get(row, column), row, column);

	/// init single 
	QJsonArray test_item;
	
	test_item.insert(NAME, QString("Apple"));
	test_item.insert(IMAGE, QString("apple-icon.png"));
	test_item.insert(COUNT, 1);

	single->fillInventory(test_item);
	single->getItem(0, 0)->setInfinite(true);
	///
	
	QPushButton* btnMainMenu = new QPushButton(tr("Главное меню"), this);
	QGridLayout* layout = new QGridLayout();
	layout->addWidget(table, 1, 0);
	layout->addWidget(single, 1, 1);
	layout->addWidget(btnMainMenu, 0, 0, 1, -1);
	setLayout(layout);

	connect(btnMainMenu, &QPushButton::clicked, this, [&] {
		gameCore::takeMainMenu()->show();
		this->close();
		});

	setFixedSize(size());
};
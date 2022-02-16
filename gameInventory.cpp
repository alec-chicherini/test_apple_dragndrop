#include "gameInventory.h"

#include <QHeaderView>

gameInventory::gameInventory(int countRows_, int countColumns_, QWidget * parent) :
	QTableWidget(countRows_, countColumns_,parent)
{
	for(int row=0; row<countRows_; row++)
		for(int column=0; column <countColumns_; column++)
	{
			QJsonArray item;
			item.insert(NAME, QString(""));
			item.insert(IMAGE, QString("S:/Code/test_apple_dragndrop/images/empty-icon.png"));
			item.insert(COUNT, 0);

			setCellWidget(row, column, new gameItemWidget(this,row,column,item));
			setSelectionMode(QAbstractItemView::SingleSelection);
	}
	resizeColumnsToContents();
	resizeRowsToContents();
	horizontalHeader()->hide();
	verticalHeader()->hide();
	setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}

void gameInventory::fillInventory(QJsonArray item, int row, int column)
{
	static_cast<gameItemWidget*>(cellWidget(row,column))->setItem(item);
}

void gameInventory::fillInventory(QJsonArray item)
{
	for (int row = 0; row < rowCount(); row++)
		for (int column = 0; column < columnCount(); column++)
		{
			fillInventory(item, row, column);
		}
}

void gameInventory::fillInventory()
{
	for (int row = 0; row < rowCount(); row++)
		for (int column = 0; column < columnCount(); column++)
		{
			static_cast<gameItemWidget*>(cellWidget(row, column))->setEmpty();
		}
}

gameItemWidget* gameInventory::getItem(int row, int column)
{
	if(row>=0 && row<rowCount() && column>=0 && column<columnCount())
		return static_cast<gameItemWidget*>(cellWidget(row, column));
	qDebug() << "ERROR:" << Q_FUNC_INFO << " return nullptr";
	return nullptr;
}

void gameInventory::setItem(const QJsonArray& item, int row, int column)
{
	static_cast<gameItemWidget*>(cellWidget(row, column))->setItem(item);
}

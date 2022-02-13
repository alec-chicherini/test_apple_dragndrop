#include "gameDB.h"
#include "enums.h"
gameDB::gameDB()
{
    addDatabase("QSQLITE");
    setDatabaseName("test_apple_dragndrop_db");
    if (!open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                "lastError().databaseText() = "+ lastError().databaseText() +
                "\nlastError().driverText() = " + lastError().driverText() +
                "\n\nClick Cancel to exit.", QMessageBox::Cancel);
    }
}

bool gameDB::checkDBTables()
{
    open();
    return tables().contains(QLatin1String("game_table"))
          /* &&
           tables().contains(QLatin1String("game_resource"))*/;
}

void gameDB::initDBTables()
{
    open();
    qDebug() << Q_FUNC_INFO;
    QSqlQuery query;
    query.exec("create table game_table ("
        "row int, "
        "column int, "
        "name varchar(30), "
        "image varchar (100), "
        "count int ");

    //query.exec("create table game_resource (uid varchar(30) primary key,"
    //    "varchar name(30), "
    //    "BLOB image, "
    //    "int count ");
}

QJsonArray gameDB::get(int row, int column)
{
    open();
    QSqlQuery query("select * from game_table");

    while (query.next())
    {
        if (query.value("row").toInt() == row &&
            query.value("column").toInt() == column)
        {
            QJsonArray item;
            item.insert(NAME, query.value("name").toString());
            item.insert(IMAGE, query.value("image").toString());
            item.insert(COUNT, query.value("name").toInt());
            return item;
        }
    }

    return QJsonArray();
}

void gameDB::set(const QJsonArray& item, int row, int column)
{
    open();
    QSqlQuery query;
    query.exec("insert into game_table values(?,?,?,?,?)");

    query.prepare("insert into game_table (row, column, name, image, count) "
        "VALUES (:row, :column, :name, :image, :count)");
    query.bindValue(":row", row);
    query.bindValue(":column", column);
    query.bindValue(":name", item[NAME].toString());
    query.bindValue(":image", item[IMAGE].toString());
    query.bindValue(":count", item[COUNT].toInt());
    query.exec();


}

#include "gameDB.h"
#include "enums.h"
QSqlDatabase gameDB::db = {};

void gameDB::initDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test_apple_dragndrop.db");
    db.setHostName("localhost");

    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            "lastError().databaseText() = " + db.lastError().databaseText() +
            "\nlastError().driverText() = " + db.lastError().driverText() +
            "\n\nClick Cancel to exit.", QMessageBox::Cancel);
    }
    else
    {
        qDebug() << "db oppened";
    }
}

bool gameDB::checkDBTables()
{
    return db.tables().contains(QLatin1String("game_table"))
          /* &&
           tables().contains(QLatin1String("game_resource"))*/;
}

void gameDB::initDBTables()
{
    QSqlQuery query;
    query.exec(QLatin1String("create table game_table ( row_column varchar(10) primary key, name varchar(30), image varchar (100), count int) "));
    qDebug() << "query.lastError() = " << query.lastError();
    qDebug() << "DB initialised";

    //query.exec("create table game_resource (uid varchar(30) primary key,"
    //    "varchar name(30), "
    //    "BLOB image, "
    //    "int count ");
}

void gameDB::fillDBTables()
{
    QJsonArray item;
    item.insert(NAME, QString(""));
    item.insert(IMAGE, QString("S:/Code/test_apple_dragndrop/images/empty-icon.png"));
    item.insert(COUNT, 0);

    for (int row = 0; row < 3; row++)
        for (int column = 0; column < 3; column++)
            set(item, row, column);
    qDebug() << "DB filled";
}

QJsonArray gameDB::get(int row, int column)
{
    QSqlQuery query(QString("select * from game_table where row_column  = '%1'").arg(to_r_c(row, column)));
    query.first();

    QJsonArray item;
    item.insert(NAME, query.value("name").toString());
    item.insert(IMAGE, query.value("image").toString());
    item.insert(COUNT, query.value("count").toInt());
    qDebug() << Q_FUNC_INFO << "item=" << item;
    return item;
}

void gameDB::set(const QJsonArray& item, int row, int column)
{
    QSqlQuery query;
    query.exec(QString("delete from game_table where row_column = '%1'").arg(to_r_c(row,column)));
    
    query.prepare("insert into game_table (row_column, name, image, count) "
                                  "VALUES (:row_column, :name, :image, :count)");
    query.bindValue(":row_column", to_r_c(row,column));
    query.bindValue(":name", item[NAME].toString());
    query.bindValue(":image", item[IMAGE].toString());
    query.bindValue(":count", item[COUNT].toInt());
    query.exec();
}

QString gameDB::to_r_c(int r, int c)
{
    return QString::number(r) + QChar('_') + QString::number(c);
}

int gameDB::row_from_r_c(QString s)
{
    s.section('_', 0, 0).toInt();
    return 0;
}

int gameDB::column_from_r_c(QString s)
{
    s.section('_', 1, 1).toInt();
    return 0;
}

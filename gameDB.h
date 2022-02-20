#pragma once

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPixmap>

class gameDB : public QObject
{
public:
    gameDB() = delete;
    static void initDB();
    static bool checkDBTables();
    static void initDBTables();
    static void fill_game_table();
    static void fill_resource_table();
    static QJsonArray get(int row, int column);
    static QPixmap getImage(const QString & name);
    static void set(const QJsonArray& item, int row, int column);
    static QString to_r_c(int r, int c);
    static int row_from_r_c(QString s);
    static int column_from_r_c(QString s);

private:
    static QSqlDatabase db;
};

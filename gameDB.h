#pragma once

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

class gameDB : public QSqlDatabase
{
public:
    gameDB();
    bool checkDBTables();
    void initDBTables();
    QJsonArray get(int row, int column);
    void set(const QJsonArray& item, int row, int column);
};

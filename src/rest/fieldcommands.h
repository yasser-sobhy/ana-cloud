#ifndef FIELDCOMMANDS_H
#define FIELDCOMMANDS_H

#include <QDate>
#include "commandsbase.h"

class IntFieldCommands
{
public:
    IntFieldCommands(CommandsBase *commands, QString field){
        this->commands = commands;
        this->field = field;

        // prepare sql statements to speed-up excution

        get_statement = QString("SELECT %1 FROM %2 WHERE %3 < %4").arg(field, commands->tableName, field);
//        list_statement = QString("SELECT %1 FROM %2 WHERE %3 < %4").arg(field, commands->tableName, field);
//        distinct_statement = QString("SELECT %1 FROM %2 WHERE %3 < %4").arg(field, commands->tableName, field);
        lt_statement = QString("SELECT %1 FROM %2 WHERE %3 < %4").arg(field, commands->tableName, field);
        lt_statement = QString("SELECT %1 FROM %2 WHERE %3 < %4").arg(field, commands->tableName, field);
        lt_statement = QString("SELECT %1 FROM %2 WHERE %3 < %4").arg(field, commands->tableName, field);
        lt_statement = QString("SELECT %1 FROM %2 WHERE %3 < %4").arg(field, commands->tableName, field);
        lt_statement = QString("SELECT %1 FROM %2 WHERE %3 < %4").arg(field, commands->tableName, field);
    }

    int get(int value){
        return commands->_getValue(get_statement.arg(value)).toInt();
    }

    QList<int> list();
    QList<int> list(int value);

    int distinct(int value);
    QList<int> distinct();

    int lt(int value){
        return commands->_getValue(lt_statement.arg(value)).toInt();
    }

    int gt(int value);
    int eq(int value);

    int lt_eq(int value);
    int gt_eq(int value);
    int nt_eq(int value);
    int mod(int value);

    int between(int value);
    int not_between(int value);
    int mod(int value);

    int in(QList<int> values);
    int not_in(QList<int> values);
    int exists(QList<int> values);
    int not_exists(QList<int> values);

    QList<int> lt(int value);
    QList<int> gt(int value);
    QList<int> eq(int value);

    int min();
    int max();
    int sum();
    int count();
private:
    CommandsBase *commands;
    QString field;

    QString get_statement;
    QString lt_statement;
};


class SqlQuery
{
public:
    SqlQuery();

    SqlQuery *_and(QString query) {
        statement += " AND " + query;
        return this;
    }

    SqlQuery *where(QString query) {
        statement += " WHERE " + query;
        return this;
    }

    QString limit();
private:
    QString statement;
};

class IntFieldQuery
{
public:

    IntFieldQuery(QString field);

    int get(int value);

    int distinct(int value);
    QList<int> distinct();

    QString lt(int value){
        return QString("%1 < %2").arg(field_name, value);
    }

    QString gt(int value){
        return QString("%1 > %2").arg(field_name, value);
    }

    QString eq(int value){
        return QString("%1 = %2").arg(field_name, value);
    }

    QString min(){
        return QString("MAX %1").append(field_name);
    }

    int max();
    int sum();
    int count();
private:
    QString field_name;
};


class TableCommands
{
public:
    TableCommands();

    void drop();
    void truncate();
};

class DatabaseCommands
{
public:
    DatabaseCommands();
};

class DateFieldCommands
{
public:
    DateFieldCommands();

    QDate get(QDate value);
    QList<QDate> list();
    QList<QDate> list(QDate value);

    int distinct(QDate value);
    QList<QDate> distinct();

    int lt(QDate value);
    int gt(QDate value);
    int eq(QDate value);

    QDate before(QDate);
    QDate after(QDate);
    QDate since(QDate);
    QDate last(int days);
    QDate today();
    QDate thisWeek();
    QDate thisMonth();
    QDate thisYear();

    QList<QDate> lt(QDate value);
    QList<QDate> gt(QDate value);
    QList<QDate> eq(QDate value);

    QDate min();
    QDate max();
    QDate sum();
    QDate count();
};

#endif // FIELDCOMMANDS_H

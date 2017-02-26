#ifndef COMMANDSBASE_H
#define COMMANDSBASE_H


#include <QObject>
#include <QVariant>
#include <QString>
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QByteArray>
#include <QList>
#include <QSqlError>
#include <QtSql/qsqlquery.h>
#include <AnaCloud/utility/databaseconnectionpool.h>

#include "entitybase.h"
#include "entityreader.h"

class CommandsBase
{
public:
    CommandsBase(QString tableName, QString idFiled);
    ~CommandsBase();

public:
    bool insert(EntityBase* entity);
    bool update(EntityBase* entity);

    EntityBase* get(QByteArray entity_id);
    QList<EntityBase *>* getList();
    QList<EntityBase *>* getList(int from, int to);

    bool doDelete(int entity_id);

    QVariant value(QByteArray valueName, int entity_id);
    EntityBase* byValue(QByteArray valueName, QByteArray value);
    QList<EntityBase *>* byValueList(QByteArray valueName, QByteArray value, int from, int to);

    int count();
    int countByID(QByteArray valueName, int entity_id);
    int countValue(QByteArray what, QByteArray valueName, QByteArray value);

    double sum();
    double sumByID(QByteArray valueName, int entity_id);
    double sumValue(QByteArray what, QByteArray valueName, QByteArray value);

    double avg();
    double avgByID(QByteArray valueName, int entity_id);
    double avgValue(QByteArray what, QByteArray valueName, QByteArray value);

    double min();
    double minByID(QByteArray valueName, int entity_id);
    double minValue(QByteArray what, QByteArray valueName, QByteArray value);

    double max();
    double maxByID(QByteArray valueName, int entity_id);
    double maxValue(QByteArray what, QByteArray valueName, QByteArray value);

    QString lastErrorText();

protected:
    bool _exec(QSqlQuery &query);
    bool _exec(QString sql);

    EntityBase* _get(QSqlQuery &query);
    EntityBase* _get(QString sql);

    QList<EntityBase *>* _getList(QSqlQuery &query);
    QList<EntityBase *>* _getList(QString sql);

    QVariant _getValue(QSqlQuery &query);
    QVariant _getValue(QString sql);

    QVariantList _getValueList(QSqlQuery &query);
    QVariantList _getValueList(QString sql);

    QString tableName;
    QString idFiled;

    EntityReader *reader;
    QString m_lastErrorText;
};

#endif // COMMANDSBASE_H

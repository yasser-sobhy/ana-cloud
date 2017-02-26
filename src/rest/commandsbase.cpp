#include "commandsbase.h"




CommandsBase::CommandsBase(QString tableName, QString idFiled){

    this->tableName = tableName;
    this->idFiled = idFiled;
}

CommandsBase::~CommandsBase(){

}

bool CommandsBase::insert(EntityBase* entity)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare("INSERT INTO bids (listing_id, seller_id, buyer_id, bid_value, accepted, created_at, updated_at)"
                  " VALUES (:listing_idValue, :seller_idValue, :buyer_idValue, :bid_valueValue, :acceptedValue, :created_atValue, :updated_atValue)");

    reader->write(entity, query);

    if(_exec(query)){
        QByteArray lastid = query.lastInsertId().toByteArray();
        entity->setID(lastid);
        return true;
    }

    return false;
}

bool CommandsBase::update(EntityBase* entity)
{
    DatabaseConnection *connection = DatabaseConnectionPool::getConnection();
    QSqlQuery query(connection->database);

    query.prepare("UPDATE bids SET listing_id = :listing_idValue, seller_id = :seller_idValue, buyer_id = :buyer_idValue, bid_value = :bid_valueValue, accepted = :acceptedValue, created_at = :created_atValue, updated_at = :updated_atValue"
                  " WHERE bid_id = :bid_idValue");

    reader->write(entity, query);
    return _exec(query);
}

EntityBase* CommandsBase::get(QByteArray entity_id)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare("SELECT * FROM bids WHERE bid_id = :bid_idValue");
    query.bindValue(":bid_idValue", entity_id);

    return _get(query);
}

QList<EntityBase *>* CommandsBase::getList()
{
    return _getList("SELECT * FROM bids ORDER BY bid_id DESC");
}

QList<EntityBase *>* CommandsBase::getList(int from, int to)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare("SELECT * FROM bids ORDER BY bid_id DESC LIMIT :fromValue,:toValue");

    query.bindValue(":fromValue", from);
    query.bindValue(":toValue", to);

    return _getList(query);
}


QVariant CommandsBase::value(QByteArray valueName, int bid_id)
{
    DatabaseConnection *connection = DatabaseConnectionPool::getConnection();
    QSqlQuery query(connection->database);

    query.prepare(QString("SELECT %1 FROM bids WHERE bid_id = :bid_idValue")
                  .arg(QString().append(valueName))
                  );

    query.bindValue(":bid_idValue", bid_id);

    if (!query.exec())
    {
        m_lastErrorText = query.lastError().databaseText();
        DatabaseConnectionPool::releaseDatabase(connection->uuid);
        return QVariant();
    }

    if (query.next()){

        DatabaseConnectionPool::releaseDatabase(connection->uuid);
        return query.value(0);
    }

    DatabaseConnectionPool::releaseDatabase(connection->uuid);

    return QVariant();
}

EntityBase* CommandsBase::byValue(QByteArray valueName, QByteArray value)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT * FROM bids WHERE %1 = :value")
                  .arg(QString().append(valueName))
                  );

    query.bindValue(":value", value);

    return _get(query);
}

QList<EntityBase *>* CommandsBase::byValueList(QByteArray valueName, QByteArray value, int from, int to)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT * FROM bids WHERE %1 = :value ORDER BY bid_id DESC")
                  .arg(QString().append(valueName))
                  );

    query.bindValue(":value", value);
    query.bindValue(":fromValue", from);
    query.bindValue(":toValue", to);

    return _getList(query);
}



int CommandsBase::count()
{
    return _getValue("SELECT COUNT(*) FROM bids ").toInt();
}

int CommandsBase::countByID(QByteArray valueName, int bid_id)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT COUNT(%1) FROM bids WHERE bid_id = :bid_idValue")
                  .arg(QString().append(valueName))
                  );

    query.bindValue(":bid_idValue", bid_id);

    return _getValue(query).toInt();
}

int CommandsBase::countValue(QByteArray what, QByteArray valueName, QByteArray value)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT COUNT(%1) FROM bids WHERE %2 = :value")
                  .arg(QString().append(what), QString().append(valueName))
                  );

    query.bindValue(":value", value);

    return _getValue(query).toInt();
}

double CommandsBase::sum()
{
    return _getValue("SELECT SUM(*) FROM bids ").toDouble();
}

double CommandsBase::sumByID(QByteArray valueName, int bid_id)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT SUM(%1) FROM bids WHERE bid_id = :bid_idValue")
                  .arg(QString().append(valueName))
                  );

    query.bindValue(":bid_idValue", bid_id);

    return _getValue(query).toDouble();
}

double CommandsBase::sumValue(QByteArray what, QByteArray valueName, QByteArray value)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT SUM(%1) FROM bids WHERE %2 = :value")
                  .arg(QString().append(what), QString().append(valueName))
                  );

    query.bindValue(":value", value);

    return _getValue(query).toDouble();
}

double CommandsBase::avg()
{
    return _getValue("SELECT AVG(*) FROM bids ").toDouble();
}

double CommandsBase::avgByID(QByteArray valueName, int bid_id)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT AVG(%1) FROM bids WHERE bid_id = :bid_idValue")
                  .arg(QString().append(valueName))
                  );

    query.bindValue(":bid_idValue", bid_id);

    return _getValue(query).toDouble();
}

double CommandsBase::avgValue(QByteArray what, QByteArray valueName, QByteArray value)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT AVG(%1) FROM bids WHERE %2 = :value")
                  .arg(QString().append(what), QString().append(valueName))
                  );

    query.bindValue(":value", value);

    return _getValue(query).toDouble();
}

double CommandsBase::min()
{
    return _getValue("SELECT MIN(*) FROM bids ").toDouble();
}

double CommandsBase::minByID(QByteArray valueName, int bid_id)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT MIN(%1) FROM bids WHERE bid_id = :bid_idValue")
                  .arg(QString().append(valueName))
                  );

    query.bindValue(":bid_idValue", bid_id);

    return _getValue(query).toDouble();
}

double CommandsBase::minValue(QByteArray what, QByteArray valueName, QByteArray value)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT MIN(%1) FROM bids WHERE %2 = :value")
                  .arg(QString().append(what), QString().append(valueName))
                  );

    query.bindValue(":value", value);

    return _getValue(query).toDouble();
}

double CommandsBase::max()
{
    return _getValue("SELECT MAX(*) FROM bids ").toDouble();
}

double CommandsBase::maxByID(QByteArray valueName, int bid_id)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT MAX(%1) FROM bids WHERE bid_id = :bid_idValue")
                  .arg(QString().append(valueName))
                  );

    query.bindValue(":bid_idValue", bid_id);

    return _getValue(query).toDouble();
}

double CommandsBase::maxValue(QByteArray what, QByteArray valueName, QByteArray value)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(QString("SELECT MAX(%1) FROM bids WHERE %2 = :value")
                  .arg(QString().append(what), QString().append(valueName))
                  );

    query.bindValue(":value", value);

    return _getValue(query).toDouble();
}

bool CommandsBase::doDelete(int bid_id)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare("DELETE FROM bids WHERE bid_id = :bid_idValue");
    query.bindValue(":bid_idValue", bid_id);

    return _exec(query);
}

QString CommandsBase::lastErrorText(){ return m_lastErrorText; }



bool CommandsBase::_exec(QSqlQuery &query){

    if(! query.exec()) {
        m_lastErrorText = query.lastError().databaseText();
        return false;
    }

    return true;
}

bool CommandsBase::_exec(QString sql){

    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(sql);
    return _exec(query);
}

EntityBase* CommandsBase::_get(QSqlQuery &query)
{
    if (!query.exec())
    {
        m_lastErrorText = query.lastError().databaseText();
        return nullptr;
    }

    if (query.next()) {
        return reader->read(query);
    }

    return nullptr;
}

EntityBase* CommandsBase::_get(QString sql)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(sql);
    return _get(query);
}

QList<EntityBase *>* CommandsBase::_getList(QSqlQuery &query)
{
    QList<EntityBase *>* entityList = nullptr ;
    EntityBase *entity;

    if (!query.exec())
    {
        m_lastErrorText = query.lastError().databaseText();
        return nullptr;
    }

    while (query.next()) {

        if(!entityList) entityList = new QList<EntityBase *>;

        entity = reader->read(query);
        if(entity) entityList->append(entity);
    }

    return entityList;
}

QList<EntityBase *>* CommandsBase::_getList(QString sql)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(sql);
    return _getList(query);
}

QVariant CommandsBase::_getValue(QSqlQuery &query)
{
    if (!query.exec())
    {
        m_lastErrorText = query.lastError().databaseText();
        return QVariant();
    }

    if (query.next()){
        return query.value(0);
    }

    return QVariant();
}

QVariant CommandsBase::_getValue(QString sql)
{
    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(sql);
    return _getValue(query);
}

QVariantList CommandsBase::_getValueList(QSqlQuery &query){

    if (!query.exec())
    {
        m_lastErrorText = query.lastError().databaseText();
        return QVariantList();
    }

    QVariantList list;
    while (query.next()) {
        list.append(query.value(0));
    }

    return list;
}

QVariantList CommandsBase::_getValueList(QString sql){

    ConnectionLocker locker;
    QSqlQuery query(locker.connection->database);

    query.prepare(sql);
    return _getValueList(query);
}

#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QUuid>
#include <QHash>
#include <QTimer>
#include <QMutex>
#include <QSettings>
#include <QDebug>

#include "configi.h"

struct DB
{
    QString type;
    QString host;
    QString name;
    QString user;
    QString password;
};

struct DatabaseConnection
{

    DatabaseConnection(DB &db){

        uuid = QUuid::createUuid().toString();
        database = QSqlDatabase::addDatabase(db.type, uuid);

        database.setHostName(db.host);
        database.setDatabaseName(db.name);
        database.setUserName(db.user);
        database.setPassword(db.password);
        database.open();
    }

    ~DatabaseConnection();

    QSqlDatabase database;
    QString uuid;
    bool isBusy = false;
};

class DatabaseConnectionPool : QObject
{
    Q_OBJECT

public:

    DatabaseConnectionPool(){

        qDebug("DatabaseConnection: Starting...");

        configi.read("etc/app.ini");
        db.type = configi.get("Database", "type").toString();
        db.host = configi.get("Database", "host").toString();
        db.name = configi.get("Database", "name").toString();
        db.user = configi.get("Database", "user").toString();
        db.password = configi.get("Database", "password").toString();

        configi.close();

        connect(&cleanupTimer, SIGNAL(timeout()), this,SLOT(cleanup()));
        cleanupTimer.start(1*1000);
    }

    static DatabaseConnection *getConnection(){

        mutex.lock();

        for(DatabaseConnection *con : connections.values()){

            if(!con->isBusy){

                con->isBusy = true;
                qDebug() << "`Using Existing Connection: " << con->uuid;
                mutex.unlock();
                return con;
            }
        }

        qDebug() << "Creating new database connection: " << connections.size();

        DatabaseConnection *newcon = new DatabaseConnection(db);
        newcon->isBusy = true;
        connections.insert(newcon->uuid, newcon);

        mutex.unlock();
        return newcon;
    }

    static void releaseDatabase(QString uuid){

        qDebug() << "Releasing Database:" << uuid;

        mutex.lock();
        DatabaseConnection *con = connections.value(uuid);

        if(con)
            con->isBusy = false;

        else qDebug() << "invalid datapase uuid:" << uuid;

        mutex.unlock();
    }

private slots:

    void cleanup(){

        //qDebug("DatabaseConnection: cleaning up...");

        int maxIdleDatabases= 0;
        int idleCounter=0;
        mutex.lock();

        foreach(DatabaseConnection* con, connections.values()) {

            if (!con->isBusy) {
                if (++idleCounter > maxIdleDatabases) {
                    connections.remove(con->uuid);
                    con->database.close();
                    delete con;
                    qDebug("DatabaseConnection: Removed database, pool size is now %i",  connections.size());
                    break; // remove only one databases in each interval
                }
            }
        }

        mutex.unlock();
    }

private:

    static QHash<QString, DatabaseConnection*> connections;
    QTimer cleanupTimer;
    static QMutex mutex;
    static Configi configi;
    static DB db;
};


struct ConnectionLocker {

    ConnectionLocker(){
        connection = DatabaseConnectionPool::getConnection();
    }

    ~ConnectionLocker(){
        DatabaseConnectionPool::releaseDatabase(connection->uuid);
    }

    DatabaseConnection *connection = nullptr;
};

#endif // CONNECTIONPOOL_H

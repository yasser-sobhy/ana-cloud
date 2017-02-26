#include "databaseconnectionpool.h"


QHash<QString, DatabaseConnection*> DatabaseConnectionPool::connections;
Configi DatabaseConnectionPool::configi;
DB DatabaseConnectionPool::db;

//QTimer DatabaseConnectionPool::cleanupTimer;

QMutex DatabaseConnectionPool::mutex;


DatabaseConnection::~DatabaseConnection(){}

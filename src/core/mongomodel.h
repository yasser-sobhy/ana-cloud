#ifndef MONGOMODEL_H
#define MONGOMODEL_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QByteArray>

#include "AnaCloud/http/httprequesthandler.h"
#include "AnaCloud/rest/restfulhandler.h"

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
#include "AnaCloud/utility/databaseconnectionpool.h"

#include <mongocxx/exception/authentication_exception.hpp>
#include <mongocxx/exception/bulk_write_exception.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/exception/operation_exception.hpp>
#include <mongocxx/exception/query_exception.hpp>
#include <mongocxx/exception/write_exception.hpp>

#include<bsoncxx/stdx/optional.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>



class MongoModel : public HttpRequestHandler, public RestfulHandler
{

public:
    MongoModel();

    QByteArray insert(QJsonDocument &json);
    QList<QByteArray>* insert_many(QList<QJsonDocument> &json);

    int update(QByteArray oid, QJsonDocument &json);
    int update(QJsonDocument &filter, QJsonDocument &json);
    int update_many(QJsonDocument &filter, QJsonDocument &json);

    QJsonDocument find(QByteArray oid);
    QJsonDocument find(QJsonDocument &filter);
    QList<QJsonDocument> find_many(QJsonDocument &filter);

    bool doDelete(QByteArray oid);
    bool doDelete(QJsonDocument &filter);
    bool doDelete_many(QJsonDocument &filter);

    QVariant value(QByteArray valueName, QByteArray oid);
    QJsonDocument* byValue(QByteArray valueName, QByteArray value);
    QList<QJsonDocument>* byValueList(QByteArray valueName, QByteArray value, int from, int to);

    QList<QJsonDocument>* distinct(QByteArray name, QJsonDocument &filter);

    int count();
    int countByID(QByteArray valueName, QByteArray oid);
    int countValue(QByteArray what, QByteArray valueName, QByteArray value);

    double sum();
    double sumByID(QByteArray valueName, QByteArray oid);
    double sumValue(QByteArray what, QByteArray valueName, QByteArray value);

    double avg();
    double avgByID(QByteArray valueName, QByteArray oid);
    double avgValue(QByteArray what, QByteArray valueName, QByteArray value);

    double min();
    double minByID(QByteArray valueName, QByteArray oid);
    double minValue(QByteArray what, QByteArray valueName, QByteArray value);

    double max();
    double maxByID(QByteArray valueName, int oid);
    double maxValue(QByteArray what, QByteArray valueName, QByteArray value);

    QString lastErrorText();

    void addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway) {}
    void removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway) {}

protected:
    QString db_name = "testdb";
    QString col_name = "testcollection";

    mongocxx::database db;
    mongocxx::collection col;
    mongocxx::client conn{mongocxx::uri{}};

private:
    QString m_lastErrorText;

};

//int main(int, char**) {

//    bsoncxx::builder::stream::document document{};

//    QByteArray ar ("{\"name\":\"ali\", \"age\":32}");

//    auto cb = bsoncxx::from_json(ar.toStdString());

//    auto collection = conn["testdb"]["testcollection"];
//    document << "hello" << "world";

//    collection.insert_one(document.view());
//    collection.insert_one(std::move(cb));

//    auto cursor = collection.find({});

//    for (auto&& doc : cursor) {
//        std::cout << bsoncxx::to_json(doc) << std::endl;
//    }
//}


#endif // MONGOMODEL_H

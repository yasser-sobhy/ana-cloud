#include "mongomodel.h"
#include <iostream>

MongoModel::MongoModel()
{
    bsoncxx::string::view_or_value _db_name (db_name.toStdString());
    bsoncxx::string::view_or_value _col_name (col_name.toStdString());

    db = conn[_db_name];
    col = db[_col_name];
}

QByteArray MongoModel::insert(QJsonDocument &json){

    bsoncxx::document::value data = bsoncxx::from_json(json.toJson().toStdString());
    bsoncxx::stdx::optional<mongocxx::result::insert_one> result;

    try {
        result = col.insert_one(std::move(data));
    }
    catch(const mongocxx::write_exception &e){
        return QByteArray();
    }

    if(result) {
        qDebug() << QByteArray::fromStdString( result.value().inserted_id().get_oid().value.to_string() );
        return QByteArray::fromStdString( result.value().inserted_id().get_oid().value.to_string() );
    }
    else return QByteArray();
}

QList<QByteArray> *MongoModel::insert_many(QList<QJsonDocument> &json){

    std::vector<bsoncxx::document::value> data;

    for(QJsonDocument d : json){
        data.push_back( bsoncxx::from_json(d.toJson().toStdString()) );
    }

    bsoncxx::stdx::optional<mongocxx::result::insert_many> result;

    try {
        result = col.insert_many(std::move(data));
    }
    catch(const mongocxx::write_exception &e){
        return nullptr;
    }

    if(result) {

        for(auto e : result->inserted_ids()){
            qDebug() << e.first;
        }
        return nullptr;
    }
    else return nullptr;
}

int MongoModel::update(QByteArray oid, QJsonDocument &json){

    bsoncxx::document::value data = bsoncxx::from_json(json.toJson().toStdString());
    bsoncxx::document::value filter = bsoncxx::from_json( "{ \"_id\":\"" + oid.toStdString() + "\"}" );

    bsoncxx::stdx::optional<mongocxx::result::update> result;

    try {
        result = col.update_one( std::move(filter), std::move(data));
    }
    catch(const mongocxx::write_exception &e){
        return -1;
    }

    if(result) {
        return result->modified_count();
    }
    else return -1;
}

int MongoModel::update(QJsonDocument &filter, QJsonDocument &json){

    bsoncxx::document::value data = bsoncxx::from_json(json.toJson().toStdString());
    bsoncxx::document::value filter_data = bsoncxx::from_json(filter.toJson().toStdString());

    bsoncxx::stdx::optional<mongocxx::result::update> result;

    try {
        result = col.update_one( std::move(filter_data), std::move(data));
    }
    catch(const mongocxx::write_exception &e){
        return -1;
    }

    if(result) {
        qDebug() << result->modified_count();
        return result->modified_count();
    }
    else return -1;
}

int MongoModel::update_many(QJsonDocument &filter, QJsonDocument &json){

    bsoncxx::document::value data = bsoncxx::from_json(json.toJson().toStdString());
    bsoncxx::document::value filter_data = bsoncxx::from_json(filter.toJson().toStdString());

    bsoncxx::stdx::optional<mongocxx::result::update> result;


    try {
        result = col.update_many( std::move(filter_data), std::move(data));
    }
    catch (const mongocxx::write_exception &e){
        return -1;
    }

    if(result) {
        return result->modified_count();
    }
    else return -1;
}

QJsonDocument MongoModel::find(QByteArray oid){

    bsoncxx::document::value filter = bsoncxx::from_json( ""); //QString().append( "{\"_id\":\"").append( bsoncxx::oid( oid.toStdString()).to_string() ).append("\"}").toStdString() );

    try {

        std::cout << bsoncxx::to_json(filter);
        bsoncxx::stdx::optional<bsoncxx::document::value> result = col.find_one(filter.view());

        if(result) {
            qDebug() << QJsonDocument::fromJson( QByteArray::fromStdString( bsoncxx::to_json(*result) ));
            return std::move( QJsonDocument::fromJson( QByteArray::fromStdString( bsoncxx::to_json(*result) )));
        }
        else qDebug("error"); //return QJsonDocument();
    }
    catch(const mongocxx::write_exception &e){
        qDebug("error");
        return QJsonDocument();
    }
}

QJsonDocument MongoModel::find(QJsonDocument &filter){

    bsoncxx::document::value filter_data = bsoncxx::from_json(filter.toJson().toStdString());

    try {
        bsoncxx::stdx::optional<bsoncxx::document::value> result = col.find_one(filter_data.view());

        if(result) {
            return std::move( QJsonDocument::fromJson( QByteArray::fromStdString( bsoncxx::to_json(*result) )));
        }
        else return QJsonDocument();
    }
    catch(const mongocxx::write_exception &e){
        return QJsonDocument();
    }

}

QList<QJsonDocument> MongoModel::find_many(QJsonDocument &filter){

    bsoncxx::document::value filter_data = bsoncxx::from_json(filter.toJson().toStdString());

    try {

        mongocxx::cursor result = col.find( std::move( filter_data ));

        QList<QJsonDocument> lst;

        for(auto doc : result) {
            QByteArray doc_ = QByteArray::fromStdString( bsoncxx::to_json(doc) );
            lst.append(QJsonDocument::fromJson(doc_));

            return std::move(lst);
        }
    }
    catch(const mongocxx::write_exception &e){
        return  QList<QJsonDocument>();
    }

}

bool MongoModel::doDelete(QByteArray oid){}
bool MongoModel::doDelete(QJsonDocument &filter){}
bool MongoModel::doDelete_many(QJsonDocument &filter){}

QVariant MongoModel::value(QByteArray valueName, QByteArray oid){}
QJsonDocument* MongoModel::byValue(QByteArray valueName, QByteArray value){}
QList<QJsonDocument>* MongoModel::byValueList(QByteArray valueName, QByteArray value, int from, int to){}

QList<QJsonDocument>* MongoModel::distinct(QByteArray name, QJsonDocument &filter){}

int MongoModel::count(){}
int MongoModel::countByID(QByteArray valueName, QByteArray oid){}
int MongoModel::countValue(QByteArray what, QByteArray valueName, QByteArray value){}

double MongoModel::sum(){}
double MongoModel::sumByID(QByteArray valueName, QByteArray oid){}
double MongoModel::sumValue(QByteArray what, QByteArray valueName, QByteArray value){}

double MongoModel::avg(){}
double MongoModel::avgByID(QByteArray valueName, QByteArray oid){}
double MongoModel::avgValue(QByteArray what, QByteArray valueName, QByteArray value){}

double MongoModel::min(){}
double MongoModel::minByID(QByteArray valueName, QByteArray oid){}
double MongoModel::minValue(QByteArray what, QByteArray valueName, QByteArray value){}

double MongoModel::max(){}
double MongoModel::maxByID(QByteArray valueName, int oid){}
double MongoModel::maxValue(QByteArray what, QByteArray valueName, QByteArray value){}

QString MongoModel::lastErrorText(){}


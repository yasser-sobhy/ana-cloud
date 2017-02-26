#include "pushdata.h"

PushData::PushData()
{
}

PushData::PushData(PushData &other)
{
    m_service = other.service();
    m_data = other.dataObject();
}

PushData::PushData(QJsonDocument other)
{
    m_service = other.object().value("service").toString();
    m_data = other.object().value("data").toObject();
}

PushData::~PushData()
{

}

QByteArray PushData::toJson(){

    PushDataObject docObject;
    docObject.insert("service", PushDataValue(m_service));
    docObject.insert("data", PushDataValue(m_data));
    setObject(docObject);

    return QJsonDocument::toJson();
}

PushData PushData::fromJson(const QByteArray &json, PushDataError *error){
    return QJsonDocument::fromJson(json, error);
}

QString PushData::service(){
    return m_service;
}

PushDataObject PushData::dataObject(){
    return m_data;
}

void PushData::setService(QString name){
    m_service = name;
}

void PushData::setDataObject(PushDataObject obj){
    m_data = obj;
}



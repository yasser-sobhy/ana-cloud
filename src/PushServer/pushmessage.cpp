#include "pushmessage.h"


PushMessage::PushMessage()
{
}

PushMessage::PushMessage(QByteArray message){

    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(message,&err);

    if(err.error == QJsonParseError::NoError)
    {
        QJsonObject obj = json.object();
        m_service = QByteArray().append(obj.value("service").toString());
        m_data = QByteArray().append(obj.value("data").toString());
    }
}

PushMessage::PushMessage(QByteArray service, QByteArray data){
    m_service = service;
    m_data = data;
}

//PushMessage::PushMessage(PushMessage &other)
//{
//    m_service = other.service();
//    m_data = other.data();
//}

//PushMessage::PushMessage(QJsonDocument &other)
//{
//    m_service = QByteArray().append(other.object().value("service").toString());
//    m_data = QByteArray().append(other.object().value("data").toString());
//}

PushMessage::~PushMessage()
{

}

QByteArray PushMessage::toJson(){

    QJsonObject docObject;
    docObject.insert("service", QJsonValue(QString(m_service)));
    docObject.insert("data", QJsonValue(QString(m_data)));
    setObject(docObject);

    return QJsonDocument::toJson();
}


QByteArray PushMessage::service(){
    return m_service;
}

QByteArray PushMessage::data(){
    return m_data;
}

void PushMessage::setService(QByteArray name){
    m_service = name;
}

void PushMessage::setData(QByteArray obj){
    m_data = obj;
}

PushMessage PushMessage::fromJson(const QByteArray &json, QJsonParseError *error){

    QJsonDocument doc = QJsonDocument::fromJson(json, error);

    if(error->error == QJsonParseError::NoError)
    {
        QJsonObject obj = doc.object();
        QByteArray service = QByteArray().append(obj.value("service").toString());
        QByteArray data = QByteArray().append(obj.value("data").toString());

        if(service.isEmpty() || data.isEmpty()) return PushMessage();

        return PushMessage(service, data);
    }

    return PushMessage();
}



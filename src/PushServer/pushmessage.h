#ifndef PUSHCLIENTDATA_H
#define PUSHCLIENTDATA_H

#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class PushMessage : private QJsonDocument
{
public:
    PushMessage();
    PushMessage(QByteArray message);
    PushMessage(QByteArray service, QByteArray data);
//    PushMessage(PushMessage &other);
//    PushMessage(QJsonDocument &other);
    ~PushMessage();

    QByteArray toJson();

    QByteArray service();
    QByteArray data();

    void setService(QByteArray name);
    void setData(QByteArray obj);

    static PushMessage fromJson(const QByteArray &json, QJsonParseError *error);

private:
    QByteArray m_service;
    QByteArray m_data;
};

#endif // PUSHCLIENTDATA_H

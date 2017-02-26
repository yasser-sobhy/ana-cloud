#ifndef PUSHDATA_H
#define PUSHDATA_H

#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

typedef QJsonObject PushDataObject;
typedef QJsonArray PushDataArray;
typedef QJsonValue PushDataValue;
typedef QJsonParseError PushDataError;

class PushData : private QJsonDocument
{
public:
    PushData();
    PushData(PushData &other);
    PushData(QJsonDocument other);
    ~PushData();

    QByteArray toJson();
    PushData fromJson(const QByteArray &json, PushDataError *error);

    QString service();
    PushDataObject dataObject();

    void setService(QString name);
    void setDataObject(PushDataObject obj);

private:
    QString m_service;
    PushDataObject m_data;
};

#endif // PUSHDATA_H

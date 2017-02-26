#ifndef APPCONFIGURATIONS_H
#define APPCONFIGURATIONS_H

#include <QByteArray>
#include <QSettings>

class AppConfigurations
{
public:
    AppConfigurations(){

        qDebug("Reading app configurations");

        QSettings settings ("etc/app.ini",QSettings::IniFormat);
        settings.beginGroup("app");

        responseContentType = settings.value("Response-Content-Type").toByteArray();
        requestContentType = settings.value("Request-Content-Type").toByteArray();
        queryStringMode = settings.value("Query-String-Mode").toByteArray();

        settings.endGroup();

        settings.beginGroup("Gateway");

        userGroups = settings.value("userGroups").toByteArray().split(',');
    }

    ~AppConfigurations(){}

    QByteArray responseContentType;
    QByteArray requestContentType;
    QByteArray queryStringMode;

    QByteArray userGroupSessionVariable;

    QList<QByteArray> userGroups;
};

#endif // APPCONFIGURATIONS_H

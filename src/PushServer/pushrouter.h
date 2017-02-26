#ifndef PUSHROUTER_H
#define PUSHROUTER_H

#include <QByteArray>
#include <QHash>
#include <QString>

#include "pushmessageHandler.h"
#include "pushmessage.h"

class PushConnection;

class PushRouter
{
public:
    PushRouter();
    ~PushRouter();

    void service(PushConnection *connection, PushMessage message);
   // void serviceText(PushConnection *connection, QByteArray service, QString data);

    void addHandler(QByteArray service, PushMessageHandler *handler);
    void removeHandler(QByteArray service);

private:
    QHash<QByteArray, PushMessageHandler *> m_handlers;
};

#endif // PUSHROUTER_H

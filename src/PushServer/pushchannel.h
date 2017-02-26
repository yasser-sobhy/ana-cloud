#ifndef PUSHCHANNEL_H
#define PUSHCHANNEL_H

#include <QByteArray>
#include <QHash>
#include <QQueue>
#include <QDebug>

#include "pushmessage.h"

class PushServer;
class PushConnection;
class Pusher;

class PushChannel
{
public:
    PushChannel();
    PushChannel(PushServer *server, QByteArray name);
    PushChannel(PushServer *server, QByteArray name, bool publc);

    ~PushChannel();

    QByteArray name();
    int count();

    void push(PushMessage &message);

    void subscribe(QByteArray key);
    void unsubscribe(QByteArray key);

    bool isPublic();

    Pusher *pusher = nullptr;

private:

    void doPush();
    QByteArray m_name;
    bool m_public;

    QList<QByteArray> m_connections; // list of subscribed connections keys

    QQueue<QByteArray> messages;
};

#endif // PUSHCHANNEL_H

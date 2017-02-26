#ifndef PUSHBROADCASTER_H
#define PUSHBROADCASTER_H

#include <QByteArray>

#include "pushconnection.h"
#include "pushchannel.h"

class PushServer;

class PushBroadcaster
{
public:
    PushBroadcaster();
    PushBroadcaster(PushServer *pServer);

    ~PushBroadcaster();

    void newChannel(QByteArray name, bool publc = false);
    void removeChannel(QByteArray name);

    void push(QByteArray channel, PushMessage &message);

    void subscribe(QByteArray channel, QByteArray key);
    void unsubscribe(QByteArray channel, QByteArray key);

    int subscribersCount(QByteArray channel);

    PushChannel *getChannel(QByteArray name);

    QByteArrayList channelsNames();
    QList<PushChannel *> channels();

    QByteArrayList publicChannelsNames();
    QList<PushChannel *> publicChannels();

    void clientConnected(PushConnection *con);
    void clientDisconnected(PushConnection *con);

    void setPushServer(PushServer *pServer);
private:
    PushServer *pushServer = nullptr;
    QHash<QByteArray, PushChannel *> m_channels;
    QHash<QByteArray, PushChannel *> m_publicChannels;
};

#endif // PUSHBROADCASTER_H

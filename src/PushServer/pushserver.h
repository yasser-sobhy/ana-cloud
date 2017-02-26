#ifndef PUSHSERVER_H
#define PUSHSERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>
#include <QHash>
#include <QReadWriteLock>

#include "pushconnectionhandler.h"
#include "pushbroadcaster.h"
#include "pushblacklist.h"
#include "pushrouter.h"

class PushConnection;
class PushChannel;
class Pusher;

class PushServer : public QObject
{
    Q_OBJECT

    friend class PushConnection;
    friend class PushChannel;
    friend class Pusher;

public:
    PushServer();
    ~PushServer();

    Pusher *newPusher();
    PushBroadcaster *newBroadcaster();
    PushBlackList *newBlackList();

    PushRouter &router();

    PushConnection *connection(QByteArray key);
    void setConnectionHandler(PushConnectionHandler *connectionHandler);

    void connectionClosed(PushConnection *connection);
    void connected(PushConnection *connection);
    QWebSocketServer *m_websocketServer;

private slots:
    void onNewConnection();
    void onSslErrors(const QList<QSslError> &);

private:
    // connections are accepted by PushConnectionHandler derived class'
    // PushConnectionHandler must set PushConnection.key or connection will be aborted
    void connectionAccepted(PushConnection *con);

    //change this
    int port = 5803;

    QHash<QByteArray, PushConnection *> m_connections;
    QList<PushConnection *> m_pendingConnections;

    QList<Pusher *> pushers;
    QList<PushBroadcaster *> broadcasters;
    QList<PushBlackList *> blackLists;

    PushRouter m_router;

    PushConnectionHandler *m_connectionHandler = nullptr;
};

#endif // PUSHSERVER_H

#include "pushserver.h"

#include "pusher.h"

PushServer::PushServer()
{
    qDebug() << "**************** PushServer Starting...";

    m_websocketServer = new QWebSocketServer(QStringLiteral("Easysocket Server"),
                                             QWebSocketServer::NonSecureMode);

    if (m_websocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "**************** PushServer listening on port" << port;
        connect(m_websocketServer, &QWebSocketServer::newConnection,
                this, &PushServer::onNewConnection);
        connect(m_websocketServer, &QWebSocketServer::sslErrors,
                this, &PushServer::onSslErrors);
    }
    else qDebug() << "**************** PushServer Error" << m_websocketServer->errorString();

    qDebug() << "**************** PushServer uri:" << m_websocketServer->serverUrl().toString();
}

PushServer::~PushServer()
{
    m_websocketServer->close();
    qDeleteAll(m_connections.begin(), m_connections.end());

    qDeleteAll(pushers);
    qDeleteAll(broadcasters);
    qDeleteAll(blackLists);
}

Pusher *PushServer::newPusher()
{
    Pusher *pusher = new Pusher(this);
    pushers.append(pusher);

    return pusher;
}

PushBroadcaster *PushServer::newBroadcaster(){

    PushBroadcaster *broadcaster = new PushBroadcaster(this);
    broadcasters.append(broadcaster);

    return broadcaster;
}

PushBlackList *PushServer::newBlackList()
{
    PushBlackList *blackList = new PushBlackList();
    blackLists.append(blackList);

    return blackList;
}

PushConnection *PushServer::connection(QByteArray key){
    return m_connections.value(key);
}

void PushServer::setConnectionHandler(PushConnectionHandler *connectionHandler){

    m_connectionHandler = connectionHandler;
}

void PushServer::onNewConnection()
{
    qDebug("PushServer, new PushConnection");
    QWebSocket *socket = m_websocketServer->nextPendingConnection();

    if(!socket) return;

    for(PushBlackList *blacklist : blackLists){
        if(blacklist->contains(socket->peerAddress())){
            socket->abort();
            delete socket;
            return;
        }
    }

    PushConnection *con = new PushConnection(socket);
    con->connectionHandler = m_connectionHandler;
    con->pushServer = this;
    con->router = &m_router;

    m_pendingConnections.append(con);
}

void PushServer::connectionClosed(PushConnection *connection)
{
    m_connections.remove(connection->key);
    m_pendingConnections.removeAll(connection); // for rejected connections

    m_connectionHandler->onClientDisconected(connection);

    for(PushBroadcaster *broadcaster : broadcasters){
        broadcaster->clientDisconnected(connection);
    }

    delete connection;
}

void PushServer::onSslErrors(const QList<QSslError> &)
{
    qDebug() << "Ssl errors occurred";
}

PushRouter &PushServer::router(){
    return m_router;
}

void PushServer::connectionAccepted(PushConnection *con)
{
    if(!con->key.isEmpty())
    {
        m_connections.insert(con->key, con);
        m_pendingConnections.removeAll(con);

        for(PushBroadcaster *broadcaster : broadcasters){
            broadcaster->clientConnected(con);
        }
    }
    else
    {
        m_pendingConnections.removeAll(con);
        con->disconnect();

        // will be deleted by PushServer::connectionClosed
        //delete con;
    }
}

#ifndef PUSHCONNECTION_H
#define PUSHCONNECTION_H

#include <QtWebSockets/QWebSocket>

#include "pushmessageHandler.h"
#include "pushconnectionhandler.h"
#include "pushrouter.h"
#include "pushmessage.h"

class PushServer;
class PushConnectionHandler;

class PushConnection : public QObject
{
    Q_OBJECT

public:
    PushConnection(QWebSocket *sockt);
    ~PushConnection();

    void push(PushMessage &message);

    void accept();
    void reject();
    void disconnect();

    QByteArray key;
    QWebSocket *socket = nullptr;

    PushServer *pushServer = nullptr;
    PushRouter *router = nullptr; // the main message handler, it routes messages to connections by service URI
    PushMessageHandler *messageHandler = nullptr;
    PushConnectionHandler *connectionHandler = nullptr;

    bool useMessageHandlerOnly = false;

signals:
    void pushReceived(PushConnection *connection, PushMessage &message);
    void disconnected();
    void closing();

private slots:
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    bool m_accepted = false;
    bool m_firstMessageReceived = false;
};

#endif // PUSHCONNECTION_H

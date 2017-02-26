#include "pushconnection.h"
#include "pushserver.h"

PushConnection::PushConnection(QWebSocket *sockt)
{
    if(sockt){
        socket = sockt;
        connect(socket, &QWebSocket::binaryMessageReceived, this, &PushConnection::processBinaryMessage);

        connect(socket, &QWebSocket::aboutToClose, this, &PushConnection::closing);
        connect(socket, &QWebSocket::disconnected, this, &PushConnection::disconnect);

        connect(socket, &QWebSocket::disconnected, this, &PushConnection::socketDisconnected);
    }
}

PushConnection::~PushConnection()
{
    if(socket) delete socket;
   // if(messageHandler) delete messageHandler;
}

void PushConnection::push(PushMessage &message){

    if(socket)
        socket->sendBinaryMessage(message.toJson());
}

void PushConnection::accept()
{
    pushServer->connectionAccepted(this);
}

void PushConnection::reject()
{
    disconnect();
}

void PushConnection::disconnect()
{
    if(socket)
        socket->close();
}

void PushConnection::processBinaryMessage(QByteArray message)
{
    // if no key was set after receiving the first message, close connection.
    if(m_firstMessageReceived && key.isEmpty()){
        qDebug() << "PushConnection aborting invalid Connection";
        socket->abort();
        return;
    }
    else if (!m_firstMessageReceived)
    {
        qDebug() << "PushConnection processing first message";
        m_firstMessageReceived = true;
        connectionHandler->processFirstMessage(this, message);
        return;
    }

    PushMessage msg(message);

    if(router && !useMessageHandlerOnly){
        // qDebug() << "PushConnection routing message";
        router->service(this, msg);
    }

    if (messageHandler) {
        //  qDebug() << "PushConnection handling message";
        messageHandler->process(this, msg);
    }

    pushReceived(this, msg);
}

void PushConnection::socketDisconnected(){
    qDebug() << "PushConnection socketDisconnected";

    delete socket;
    socket = nullptr;
    pushServer->connectionClosed(this);
}


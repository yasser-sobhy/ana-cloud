#include "pushclient.h"

PushClient::PushClient()
{
    m_socket = new QWebSocket();

    connect(m_socket, &QWebSocket::binaryMessageReceived, this, &PushClient::processBinaryMessage);
    connect(m_socket, &QWebSocket::textMessageReceived, this, &PushClient::processTextMessage);
    //connect(m_socket, &QWebSocket::disconnected, this, &PushClient::socketDisconnected);

    connect(m_socket, &QWebSocket::binaryMessageReceived, this, &PushClient::pushReceivd);
    connect(m_socket, &QWebSocket::textMessageReceived, this, &PushClient::TextPushReceivd);

    connect(m_socket, &QWebSocket::connected, this, &PushClient::connected);
    connect(m_socket, &QWebSocket::disconnected, this, &PushClient::disconnected);
    connect(m_socket, &QWebSocket::aboutToClose, this, &PushClient::closing);

    connect(m_socket, &QWebSocket::pong, this, &PushClient::pong);

}

PushClient::~PushClient()
{
    delete m_socket;
}

void PushClient::open(){
    m_socket->open(QUrl(m_serverUrl.toString()));
}

void PushClient::close(){
    m_socket->close();
}

void PushClient::push(PushMessage message){

    m_socket->sendBinaryMessage(message.toJson());
}

void PushClient::push(QByteArray service, QByteArray data){

    PushMessage message(service, data);
    m_socket->sendBinaryMessage(message.toJson());
}

void PushClient::setUrl(const QByteArray url){
    m_serverUrl = url;
}

void PushClient::ping(const QByteArray & payload){
    m_socket->ping(payload);
}

QWebSocket *PushClient::socket(){
    return m_socket;
}

void PushClient::processBinaryMessage(QByteArray message)
{
    qDebug() << "PushClient, binary message received:" << message;
}

void PushClient::processTextMessage(QString message)
{
    qDebug() << "PushClient, text message received:" << message;
}

void PushClient::socketDisconnected()
{
}

#ifndef PUSHCLIENT_H
#define PUSHCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

#include "pushmessage.h"

class PushClient : public QObject
{
    Q_OBJECT

public:
    PushClient();
    PushClient(QUrl serverUrl);
    ~PushClient();

public slots:
    void open();
    void close();

    void push(PushMessage message);
    void push(QByteArray service, QByteArray data);

    void setUrl(const QByteArray url);

    void ping(const QByteArray & payload = QByteArray());

    QWebSocket *socket();

signals:
    void pushReceivd(QByteArray message);
    void TextPushReceivd(QString message);

    void connected();
    void disconnected();
    void closing();

    void pong(quint64 elapsedTime, const QByteArray & payload);

private slots:
    void processBinaryMessage(QByteArray message);
    void processTextMessage(QString message);
    void socketDisconnected();

private:
    QWebSocket *m_socket = nullptr;
    QUrl m_serverUrl;
};

#endif // PUSHCLIENT_H

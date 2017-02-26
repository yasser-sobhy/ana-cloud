#include "pusher.h"

Pusher::Pusher(){}

Pusher::Pusher(PushServer *pServer)
{
    pushServer = pServer;
}

void Pusher::push(QByteArray key, PushMessage &message)
{
    PushConnection *con = pushServer->m_connections[key];

    if(con) con->push(message);
    else qDebug() << "Pusher: no PushConnection found for key" << key;
}

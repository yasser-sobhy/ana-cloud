#include "pushrouter.h"

PushRouter::PushRouter()
{

}

PushRouter::~PushRouter()
{

}

void PushRouter::service(PushConnection *connection, PushMessage message)
{
    if(m_handlers.contains(message.service()))
    {
        PushMessageHandler *handler = m_handlers[message.service()];
        if(handler) handler->process(connection, message);
    }
}

//void PushRouter::serviceText(PushConnection *connection, QByteArray service, QString data)
//{
//    if(m_handlers.contains(service))
//    {
//        MessageHandler *handler = m_handlers[service];
//        if(handler) handler->processTextMessage(connection, data);
//    }
//}

void PushRouter::addHandler(QByteArray service, PushMessageHandler *handler)
{
    m_handlers.insert(service, handler);
}

void PushRouter::removeHandler(QByteArray service)
{
    m_handlers.remove(service);
}

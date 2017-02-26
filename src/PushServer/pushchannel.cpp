#include "pushchannel.h"
#include "pushserver.h"
#include "pushconnection.h"
#include "pusher.h"

PushChannel::PushChannel()
{

}

PushChannel::PushChannel(PushServer *server, QByteArray name)
{
    m_name = name;
    this->pusher = server->newPusher();
}

PushChannel::PushChannel(PushServer *server, QByteArray name, bool publc)
{
    m_name = name;
    m_public = publc;
    this->pusher = server->newPusher();
}

PushChannel::~PushChannel()
{

}

QByteArray PushChannel::name(){
    return m_name;
}

int PushChannel::count(){
    return m_connections.count();
}

void PushChannel::push(PushMessage &message){

    if(!pusher) {
        qDebug() << "PushBroadcastChannel: no pusher assigned!";
        return;
    }

    for(QByteArray key : m_connections){
        pusher->push(key, message);
    }
}

void PushChannel::subscribe(QByteArray key){

    qDebug() << "PushChannel::subscribe "<< m_name << key;

    if(key.isEmpty()) return;

    if(!m_connections.contains(key))
        m_connections.append(key);
}

void PushChannel::unsubscribe(QByteArray key){
    m_connections.removeAll(key);
}

bool PushChannel::isPublic(){
    return m_public;
}

void PushChannel::doPush(){

//    int c =  messages.count();
//    for(QByteArray m : messages){
//        for(QByteArray key : m_connections){
//            con->push(m);
//        }
//    }
}

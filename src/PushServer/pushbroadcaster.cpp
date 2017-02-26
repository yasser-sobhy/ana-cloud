#include "pushbroadcaster.h"
#include "pushserver.h"

PushBroadcaster::PushBroadcaster()
{
}

PushBroadcaster::PushBroadcaster(PushServer *pServer){

    pushServer = pServer;
}

PushBroadcaster::~PushBroadcaster()
{
    qDeleteAll(m_channels.values());
    qDeleteAll(m_publicChannels.values());
}

void PushBroadcaster::newChannel(QByteArray name, bool publc){

    if(publc) m_publicChannels.insert(name, new PushChannel(pushServer, name, true));
    else m_channels.insert(name, new PushChannel(pushServer, name, false));
}

void PushBroadcaster::removeChannel(QByteArray name){

    PushChannel *channel = m_channels[name];

    if(channel){
        m_channels.remove(name);
        delete channel;
    }

    channel = m_channels[name];

    if(channel){
        m_publicChannels.remove(name);
        delete channel;
    }
}

void PushBroadcaster::push(QByteArray channel, PushMessage &message){

    if(m_channels.contains(channel)){
        m_channels[channel]->push(message);
        return;
    }

    if(m_publicChannels.contains(channel)){
        m_publicChannels[channel]->push(message);
        return;
    }

}

void PushBroadcaster::subscribe(QByteArray channel, QByteArray key){

    if(m_channels.contains(channel)){

        m_channels[channel]->subscribe(key);
        return;
    }

    if(m_publicChannels.contains(channel)){

        m_publicChannels[channel]->subscribe(key);
        return;
    }
}

void PushBroadcaster::unsubscribe(QByteArray channel, QByteArray key){

    if(m_channels.contains(channel)){
        m_channels[channel]->unsubscribe(key);
        return;
    }

    if(m_publicChannels.contains(channel)){

        m_publicChannels[channel]->unsubscribe(key);
        return;
    }
}

int PushBroadcaster::subscribersCount(QByteArray channel){

    if(m_channels.contains(channel)) return m_channels[channel]->count();
    if(m_publicChannels.contains(channel)) return m_channels[channel]->count();

    return -1;
}

PushChannel *PushBroadcaster::getChannel(QByteArray name){

    if(m_channels.contains(name)) return m_channels[name];

    if(m_publicChannels.contains(name)) return m_publicChannels[name];

    return nullptr;
}

QByteArrayList PushBroadcaster::channelsNames(){
    return m_channels.keys();
}

QList<PushChannel *> PushBroadcaster::channels(){
    return m_channels.values();
}

QByteArrayList PushBroadcaster::publicChannelsNames(){
    return m_publicChannels.keys();
}

QList<PushChannel *> PushBroadcaster::publicChannels(){
    return m_publicChannels.values();
}

void PushBroadcaster::clientConnected(PushConnection *con){
    for(PushChannel *ch : m_publicChannels) ch->subscribe(con->key);
}

void PushBroadcaster::clientDisconnected(PushConnection *con){
    for(PushChannel *ch : m_publicChannels) ch->unsubscribe(con->key);
}

void PushBroadcaster::setPushServer(PushServer *pServer)
{
    pushServer = pServer;
}

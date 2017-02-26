#ifndef PUSHCONNECTIONHANDLER_H
#define PUSHCONNECTIONHANDLER_H

#include <QByteArray>
#include "pushconnection.h"

class PushConnection;

class PushConnectionHandler
{
public:
    PushConnectionHandler();
    ~PushConnectionHandler();

    virtual void onClientConected(PushConnection *connection) = 0;
    virtual void onClientReConected(PushConnection *connection) = 0;
    virtual void onClientDisconected(PushConnection *connection) = 0;

    virtual void processFirstMessage(PushConnection *connection, QByteArray message) = 0;
    virtual void processFirstMessage(PushConnection *connection, QString message) = 0;

};

#endif // PUSHCONNECTIONHANDLER_H

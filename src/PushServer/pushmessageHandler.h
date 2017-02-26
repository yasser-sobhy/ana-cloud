#ifndef PUSHMESSAGEHANDLER_H
#define PUSHMESSAGEHANDLER_H

#include <QByteArray>
#include "pushmessage.h"

class PushConnection;

class PushMessageHandler
{
public:
    PushMessageHandler(){}

    virtual void process(PushConnection *connection, PushMessage message) = 0;

//    virtual void processBinaryMessage(PushConnection *connection, QByteArray message) = 0;
//    virtual void processTextMessage(PushConnection *connection, QString message) = 0;
};

#endif // PUSHMESSAGEHANDLER_H

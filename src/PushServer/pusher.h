#ifndef PUSHER_H
#define PUSHER_H

#include "pushmessage.h"
#include "pushserver.h"

class Pusher
{
public:
    Pusher();
    Pusher(PushServer *pServer);

    void push(QByteArray key, PushMessage &message);

private:
    PushServer *pushServer = nullptr;

};

#endif // PUSHER_H

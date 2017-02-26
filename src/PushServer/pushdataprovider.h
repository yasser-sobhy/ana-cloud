#ifndef PUSHDATAPROVIDER_H
#define PUSHDATAPROVIDER_H

#include "pushdata.h"

class PushDataProvider
{
public:
    PushDataProvider();
    ~PushDataProvider();

    virtual PushData service(PushData data) = 0;
    QString serviceName() {return m_service;}

protected:
    QString m_service; // service name

};

#endif // PUSHDATAPROVIDER_H

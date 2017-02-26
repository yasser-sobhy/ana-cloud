#ifndef CORS_H
#define CORS_H

#include <QList>
#include <QByteArray>
#include <QByteArrayList>

#include "middleware.h"
#include <AnaCloud/http/utility/httpstatuscodes.h>

class Cors: public Middleware
{
public:
    Cors();

    virtual void process(HttpRequest& request, HttpResponse& response);

    bool allowAllOrigins = true;
    QByteArrayList allowedOrigins {};
    QByteArrayList allowedMethods {"GET","HEAD","PUT","PATCH","POST","DELETE"};
    QByteArrayList allowedHeaders {};
    QByteArrayList exposeHeaders {};
    QByteArray maxAge;

    bool preflightContinue = false;
    HttpStatusCode successStatus = HttpStatusCodes::NoContent;
    bool credentials = false;
};

#endif // CORS_H

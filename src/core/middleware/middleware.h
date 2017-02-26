#ifndef MIDDLEWARE
#define MIDDLEWARE

#include <AnaCloud/http/httprequesthandler.h>

class Middleware
{
public:
    Middleware(){}

    virtual void process(HttpRequest& , HttpResponse&){
        qDebug() << "using an abstract middleware";
        return;
    }

    QByteArray name; //middleare name, may be used for debugging
    QByteArray path; // url to apply this middleare on, empty for all
    QByteArray method; // HTTP method to apply this middleare on, empty for all

    bool next = true; //should pursue processing request or not, ignored for post middlewares
    bool post = false; // should this middleware be excuted after processing request?

    bool notfound = false; // special middleware run if no handler found to handle a request
};

#endif // MIDDLEWARE

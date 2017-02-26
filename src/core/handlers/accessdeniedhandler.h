#ifndef ACCESSDENIEDHANDLER_H
#define ACCESSDENIEDHANDLER_H

#include "AnaCloud/rest/restfulhandler.h"
#include "AnaCloud/http/httprequesthandler.h"
#include "AnaCloud/http/utility/httpstatuscodes.h"
#include "AnaCloud/utility/globals.h"

class AccessDeniedHandler : public HttpRequestHandler , public RestfulHandler
{
public:
    AccessDeniedHandler(){}
    ~AccessDeniedHandler(){}

    virtual void addRoutes(Router<RequestHandler, QByteArray> *, Gateway<RequestHandler, QByteArray> *) {}
    virtual void removeRoutes(Router<RequestHandler, QByteArray> *, Gateway<RequestHandler, QByteArray> *) {}

    void service(HttpRequest& , HttpResponse& response){
        anasErrors.Unauthorized.response(response);
    }

private:
    AnasErrors anasErrors;
};

#endif // ACCESSDENIEDHANDLER_H

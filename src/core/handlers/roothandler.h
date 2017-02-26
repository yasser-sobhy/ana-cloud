#ifndef ROOTHANDLER_H
#define ROOTHANDLER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include <AnaCloud/http/httprequesthandler.h>
#include "AnaCloud/core/handlerfunctor.h"
#include "AnaCloud/router/router.h"
#include "AnaCloud/router/gateway.h"

#include "AnaCloud/http/utility/httprequestheaders.h"
#include "AnaCloud/http/utility/httpresponseheaders.h"
#include "AnaCloud/core/errors/anaclouderror.h"
#include "AnaCloud/core/errors/anaclouderrors.h"
#include "AnaCloud/http/utility/httpstatuscodes.h"
#include "AnaCloud/utility/resourcelink.h"

#include "AnaCloud/core/app.h"

class RootHandler : public HttpRequestHandler , public RestfulHandler{

public:
    RootHandler();
    ~RootHandler();

public:

    /**
* The GET function list Classes
*
* ****************************************************************************
* URL:          ** /                                       *
* ****************************************************************************
* Method:       ** GET                                                       *
* ****************************************************************************
* Returns:                                                                   *
*               ** 401 Unauthorized                                          *
*               ** 406 NotAcceptable                                         *
*               ** 415 UnsupportedMediaType                                  *
*               ** 400 badRequest                                            *
*               ** 200 OK + JSON Object                                      *
*               ** 404 Not Found                                             *
* ****************************************************************************
*/
    void GET(HttpRequest& request, HttpResponse& response);

    void addLink(QByteArray resource, QJsonArray p_links);

    void addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway);

    void removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway);

private:

    bool checkRequest(HttpRequest& request, HttpResponse& response);

private:

    QByteArray path;// service URI for this handler

    //indicate whether handler was added to router and gateway or not
    bool addedRoutes = false;

    RequestHandler *get = nullptr;

    QByteArray links;
    QJsonObject linksObject;
    QJsonArray linksArray;
    QByteArray version;

    AnasErrors anasErrors;
    HttpRequestHeaders httpRequestHeaders;
    HttpResponseHeaders httpResponseHeaders;

};

#endif // ROOTHANDLER_H

#ifndef RESTFULHANDLER_H
#define RESTFULHANDLER_H

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
#include "AnaCloud/utility/uuid/uuid.hpp"
#include "AnaCloud/utility/configi.h"

#include "AnaCloud/core/handlerfunctor.h"
#include "AnaCloud/http/utility/httprequestheaders.h"
#include "AnaCloud/http/utility/httpresponseheaders.h"
#include "AnaCloud/core/errors/anaclouderror.h"
#include "AnaCloud/core/errors/anaclouderrors.h"
#include "AnaCloud/http/utility/httpstatuscodes.h"
#include "AnaCloud/utility/resourcelink.h"
#include "AnaCloud/utility/uuid/uuid.hpp"
#include "AnaCloud/utility/configi.h"


template <class T, class M> class Router;
template <class T, class M> class Gateway;

class RestfulHandler
{
public:
    RestfulHandler();

    virtual void addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway) = 0;
    virtual void removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway) = 0;

    virtual bool checkRequest(HttpRequest&, HttpResponse&) {}
    virtual QByteArray createUuid() {}


//    void GET(HttpRequest& request, HttpResponse& response);

//    void PUT(HttpRequest& request, HttpResponse& response);

//    void POST(HttpRequest& request, HttpResponse& response);

//    void DELETE(HttpRequest& request, HttpResponse& response);

//    void idGET(HttpRequest& request, HttpResponse& response);

//    void idPUT(HttpRequest& request, HttpResponse& response);

//    void idPOST(HttpRequest& request, HttpResponse& response);


//    void idDELETE(HttpRequest& request, HttpResponse& response);

//    void value(HttpRequest& request, HttpResponse& response);

//    void byValue(HttpRequest& request, HttpResponse& response);

//    void byValueList(HttpRequest& request, HttpResponse& response);

//    void count(HttpRequest& request, HttpResponse& response);

//    void countByID(HttpRequest& request, HttpResponse& response);

//    void countValue(HttpRequest& request, HttpResponse& response);

//    void sum(HttpRequest& request, HttpResponse& response);

//    void sumByID(HttpRequest& request, HttpResponse& response);

//    void sumValue(HttpRequest& request, HttpResponse& response);

//    void avg(HttpRequest& request, HttpResponse& response);

//    void avgByID(HttpRequest& request, HttpResponse& response);

//    void avgValue(HttpRequest& request, HttpResponse& response);

//    void min(HttpRequest& request, HttpResponse& response);

//    void minByID(HttpRequest& request, HttpResponse& response);

//    void minValue(HttpRequest& request, HttpResponse& response);

//    void max(HttpRequest& request, HttpResponse& response);

//    void maxByID(HttpRequest& request, HttpResponse& response);

//    void maxValue(HttpRequest& request, HttpResponse& response);


//private:
//    RequestHandler *get = nullptr;
//    RequestHandler *post = nullptr;

//    RequestHandler *idget = nullptr;
//    RequestHandler *idput = nullptr;
//    RequestHandler *iddelete = nullptr;

//    RequestHandler *valueGET = nullptr;
//    RequestHandler *byValueGET = nullptr;
//    RequestHandler *byValueListGET = nullptr;

//    RequestHandler *countGET = nullptr;
//    RequestHandler *countByIDGET = nullptr;
//    RequestHandler *countValueGET = nullptr;

//    RequestHandler *sumGET = nullptr;
//    RequestHandler *sumByIDGET = nullptr;
//    RequestHandler *sumValueGET = nullptr;

//    RequestHandler *avgGET = nullptr;
//    RequestHandler *avgByIDGET = nullptr;
//    RequestHandler *avgValueGET = nullptr;

//    RequestHandler *minGET = nullptr;
//    RequestHandler *minByIDGET = nullptr;
//    RequestHandler *minValueGET = nullptr;

//    RequestHandler *maxGET = nullptr;
//    RequestHandler *maxByIDGET = nullptr;
//    RequestHandler *maxValueGET = nullptr;



//    Configi configi;
//   // RidesCommands m_ridesCommands;

//    AnasErrors anasErrors;
//    HttpRequestHeaders httpRequestHeaders;
//    HttpResponseHeaders httpResponseHeaders;

//    QByteArray path;// service URI for this handler
//    bool routesAdded = false; //indicate whether handler was added to router and gateway or not

//    QByteArray requestContentType;
//    QByteArray responseContentType;
//    QByteArray queryStringMode;
};

#endif // RESTFULHANDLER_H

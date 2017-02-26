//#ifndef MONGOHANDLER_H
//#define MONGOHANDLER_H

//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonArray>

//#include "Anas/core/app.h"

//#include <Anas/http/httprequesthandler.h>
//#include "Anas/core/handlerfunctor.h"
//#include "Anas/router/router.h"
//#include "Anas/router/gateway.h"

//#include "Anas/http/utility/httprequestheaders.h"
//#include "Anas/http/utility/httpresponseheaders.h"
//#include "Anas/core/errors/anaserror.h"
//#include "Anas/core/errors/anaserrors.h"
//#include "Anas/http/utility/httpstatuscodes.h"
//#include "Anas/utility/resourcelink.h"
//#include "Anas/utility/uuid/uuid.hpp"
//#include "Anas/utility/configi.h"


//class MongoHandler
//{
//public:
//    MongoHandler();


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

//    void addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway);
//    void removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway);

//private:

//    bool checkRequest(HttpRequest& request, HttpResponse& response);
//    QByteArray createUuid();

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

//    AnasErrors anasErrors;
//    HttpRequestHeaders httpRequestHeaders;
//    HttpResponseHeaders httpResponseHeaders;

//    QByteArray path;// service URI for this handler
//    bool routesAdded = false; //indicate whether handler was added to router and gateway or not

//    QByteArray requestContentType;
//    QByteArray responseContentType;
//    QByteArray queryStringMode;

//};

//#endif // MONGOHANDLER_H

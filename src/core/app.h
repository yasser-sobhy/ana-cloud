#ifndef APP_H
#define APP_H


#include <QObject>

#include <AnaCloud/rest/restfulhandler.h>
#include <AnaCloud/core/middleware/middleware.h>

#include <AnaCloud/http/httprequesthandler.h>
#include <AnaCloud/http/staticfilecontroller.h>
#include <AnaCloud/http/httpsessionstore.h>

//#include "Anas/core/handlerfunctor.h"
#include "AnaCloud/router/router.h"
#include "AnaCloud/router/gateway.h"
#include "AnaCloud/core/configurations.h"
#include "AnaCloud/utility/globals.h"

#include "AnaCloud/core/handlers/accessdeniedhandler.h"
#include "AnaCloud/utility/databaseconnectionpool.h"

//#include "handlers/basicfileshandler.h"


class App : public HttpRequestHandler
{
    Q_OBJECT

public:
    App();
    ~App();

    void service(HttpRequest& request, HttpResponse& response);

    void use(RestfulHandler * handler);
    void unuse(RestfulHandler * handler);

    void use(Middleware *middleware);
    void unuse(Middleware *middleware);

    static StaticFileController *filesHandler;
    static HttpSessionStore *sessionStore;
    static AppConfigurations configurations;

    static BasicAuthenticator basicAuthenticator;

    bool production = false;

private:
    bool runMiddleare(QByteArray method, QByteArray path, HttpRequest &request, HttpResponse &response, bool post = false);
    bool runNotFoundMiddleare(HttpRequest &request, HttpResponse &response);

    Router<RequestHandler, QByteArray> *router;
    Gateway<RequestHandler, QByteArray> *gateway;

    AnasErrors anasErrors;
    AccessDeniedHandler *accessDeniedHandler;

    QList < RestfulHandler *> handlers;

    // method --> [path --> middlewares]
    // * for any method, * for any path
    QHash <QByteArray, QHash<QByteArray, QList<Middleware*>>> pre_middleware;
    QHash <QByteArray, QHash<QByteArray, QList<Middleware*>>> post_middleware;
    // special middleware run if no handler found to handle a request
    QHash <QByteArray, QHash<QByteArray, QList<Middleware*>>> notFound_middleware;

    // just declare it to connect timer to slots and start cleanup
    DatabaseConnectionPool conpool;
};

#endif // APP_H


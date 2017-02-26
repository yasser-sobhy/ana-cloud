#include "app.h"

#include <AnaCloud/core/errors/anaclouderrors.h>

#include <QDebug>

StaticFileController* App::filesHandler = 0;
HttpSessionStore* App::sessionStore = 0;
AppConfigurations App::configurations;

BasicAuthenticator App::basicAuthenticator;


App::App()
{
    basicAuthenticator.setTestMode(!production);

    accessDeniedHandler = new AccessDeniedHandler();
    RequestHandler *ad = new RequestHandler(accessDeniedHandler, (serviceFun)&AccessDeniedHandler::service);

    router = new Router<RequestHandler, QByteArray>();
    gateway = new Gateway<RequestHandler, QByteArray>(router);

    // setup gateway
    gateway->setAccessDeniedHandler(ad);
    gateway->setBasicAuthenticator(&basicAuthenticator);
}

App::~App()
{
    for(RestfulHandler * handler : handlers){
        delete handler;
    }

    delete accessDeniedHandler;

//    for(Middleware * middleware : post_middleware){
//        delete middleware;
//    }

//    for(Middleware * middleware : pre_middleware){
//        delete middleware;
//    }
}

void App::use(RestfulHandler *handler)
{
    handler->addRoutes(router, gateway);
    handlers.append(handler);
}

void App::unuse(RestfulHandler *handler)
{
    handler->removeRoutes(router, gateway);
    handlers.removeAll(handler);
}

void App::use(Middleware *middleware)
{
    QByteArray method = middleware->method, path = middleware->path;

    if(middleware->method.isEmpty()) method = "*";
    if(middleware->path.isEmpty()) path = "*";

    if(middleware->notfound)
        notFound_middleware[method][path].append(middleware);
    else if(middleware->post)
        post_middleware[method][path].append(middleware);
    else
        pre_middleware[method][path].append(middleware);
}

void App::unuse(Middleware *middleware)
{
//    post_middleware.removeAll(middleware);
//    pre_middleware.removeAll(middleware);
}

bool App::runMiddleare(QByteArray method, QByteArray path, HttpRequest &request, HttpResponse &response, bool post){

    QList<Middleware *> middlewares;

    if(post) middlewares = post_middleware[method][path];
    else middlewares = pre_middleware[method][path];

    for(Middleware *middleware : middlewares){
        middleware->process(request, response);
        if(!middleware->next) return false;
    }

    return true;
}

bool App::runNotFoundMiddleare(HttpRequest &request, HttpResponse &response){

    // not found middleware have no path
    QList<Middleware *> any_middlewares = notFound_middleware["*"]["*"];

    for(Middleware *middleware : any_middlewares){
        middleware->process(request, response);
        if(!middleware->next) return false;
    }

    QList<Middleware *> middlewares = notFound_middleware[request.getMethod()]["*"];

    for(Middleware *middleware : middlewares){
        middleware->process(request, response);
        if(!middleware->next) return false;
    }

    return true;
}

void App::service(HttpRequest &request, HttpResponse &response)
{
    qDebug() << "directing to router";

    if(! runMiddleare("*", "*", request, response)) return;
    if(! runMiddleare( request.getMethod(), "*", request, response)) return;

    Routed<HandlerFunctor<HttpRequestHandler>> *routed = gateway->route(request, response);

    // routed will be null if no notFoundHandler was set
    if(routed){

        //if(routed->handler()->handler()->path = )
        qDebug("Handler found for method: %s, and path: %s", request.getMethod().data(), request.getPath().data());
        HandlerFunctor<HttpRequestHandler> *handler = routed->handler;

        // tokens are associated with request not handler
        // because handler can handle multiple requests synchronously
        // while there is only one request per connection
        request.setTokens(routed->params);

        if(! runMiddleare("*", routed->path, request, response)) return;
        if(! runMiddleare(routed->method, routed->path, request, response)) return;

        handler->service(request, response);

        if(! runMiddleare("*", routed->path, request, response, true)) return;
        if(! runMiddleare(routed->method, routed->path, request, response, true)) return;

        delete routed;
        return;
    }
    else
    {
        qDebug("No handler found for method: %s, and path: %s", request.getMethod().data(), request.getPath().data());

        if(! runNotFoundMiddleare(request, response)) return;

        anasErrors.NotFound.response(response);
        return;
    }

    if(! runMiddleare("*", "*", request, response, true)) return;
    if(! runMiddleare(request.getMethod(), "*", request, response, true)) return;
}


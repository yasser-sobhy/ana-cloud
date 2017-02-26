#include "roothandler.h"


RootHandler::RootHandler(){

    QSettings handlerSettings("etc/handlers/RootHandler.ini", QSettings::IniFormat);
    //get handler path
    handlerSettings.beginGroup("RootHandler");
    path = handlerSettings.value("urlPath").toByteArray();
    version = handlerSettings.value("APIversion").toByteArray();
}

RootHandler::~RootHandler(){

}

bool RootHandler::checkRequest(HttpRequest &request, HttpResponse &response){

    // check for media type required by client
    if(request.getHeader(httpRequestHeaders.Accept) != App::configurations.responseContentType ){

        anasErrors.NotAcceptable.response(response);
        return false;
    }

    // check for media type required by handler
    if(request.getHeader(httpRequestHeaders.ContentType) != App::configurations.requestContentType){

        anasErrors.UnsupportedMediaType.response(response);
        return false;
    }

    return true;
}

void RootHandler::GET(HttpRequest &request, HttpResponse &response){

    if( !checkRequest(request, response)){
        // just return because checkRequest writes an error ,if any, before returning false
        return;
    }

    response.write(links, true);
}

void RootHandler::addLink(QByteArray resource, QJsonArray p_links){

    linksObject.insert(resource, QJsonValue(p_links));

    QJsonObject o;
    o.insert("version", QJsonValue( QString(version)));
    o.insert("links", QJsonValue(linksObject));

    QJsonDocument json;
    json.setObject(o);

    links = json.toJson();

}

void RootHandler::addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway){

    if(addedRoutes) {
        qWarning("RootHandler %p: routes already added", this);
        return;
    }

    qDebug("RootHandler %p: registering handlers...", this);

    get = new RequestHandler (this, (serviceFun)&RootHandler::GET);
    router->addHandler("GET", path, get);
    gateway->addGate(get, "GET"); // onlu GET method is allowed on root handler

    addedRoutes = true;
}

void RootHandler::removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway){

    if(!addedRoutes){
        qWarning("RootHandler %p: no handlers to remove", this);
        return;
    }

    qDebug("RootHandler %p: un-registering RootHandler...", this);

    qDebug("RootHandler %p: removing handlers...", this);
    router->removeHandler(get);

    qDebug("RootHandler %p: removing gateways...", this);
    gateway->removeGate(get);

    qDebug("RootHandler %p: deleting handlers...", this);
    delete get ;

    addedRoutes = false;

}





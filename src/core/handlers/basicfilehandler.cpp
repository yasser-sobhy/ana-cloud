#include "basicfilehandler.h"

QByteArray FileJson::path;


BasicFileHandler::BasicFileHandler()
{
    QSettings handlerSettings("etc/handlers/BasicFileHandler.ini", QSettings::IniFormat);
    //get handler path
    handlerSettings.beginGroup("BasicFileHandler");
    path = handlerSettings.value("urlPath").toByteArray();
    docRoot = handlerSettings.value("dataDir").toByteArray();

    FileJson::setPath(path);

    QSettings *ssets = new QSettings("etc/handlers/StaticFileController.ini",  QSettings::IniFormat);
    ssets->beginGroup("files");
    staticFileController = new StaticFileController(ssets);
}

BasicFileHandler::~BasicFileHandler()
{
    delete staticFileController;
}

bool BasicFileHandler::checkRequest(HttpRequest &request, HttpResponse &response){

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

void BasicFileHandler::GET(HttpRequest &request, HttpResponse &response){

    //no need to check request, no specific request or response content-type required for a file handler
//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }


    //which file or dir to serve
    QByteArray path = request.getPath();
    QFileInfo info(docRoot+path);

    if(info.exists()){

        // if it's a file, serve it
        if(info.isFile()){
            staticFileController->service(request,response);
            return;
        }

        QDir dir(info.absoluteFilePath());

        // get all dirs and files
        QFileInfoList entries = dir.entryInfoList(QDir::AllEntries);

        // if list is not empty
        if(!entries.isEmpty()){

            QJsonDocument json;
            QJsonObject o;
            QJsonArray array;

            for (QFileInfo e: entries) {

                QJsonValue value(FileJson::toJsonObject(path, &e));
                array.append(value);
            }

            o.insert("files", QJsonValue(array));
            o.insert("links", QJsonValue(FileJson::links()));
            json.setObject(o);

            response.setHeader(httpResponseHeaders.ContentType, App::configurations.responseContentType);
            response.write(json.toJson(), true);

            return;
        }
        else
        {
            // if no entries found
            anasErrors.NotFound.response(response);
            return;
        }
    }
    // file not found
    else{
        anasErrors.NotFound.response(response);
        return;
    }
}

void BasicFileHandler::addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway){

    if(addedRoutes) {
        qWarning("BasicFileHandler %p: routes already added", this);
        return;
    }
    qDebug("BasicFileHandler %p: registering handlers...", this);

    get = new RequestHandler (this, (serviceFun)&BasicFileHandler::GET);

    // add handler for different methods with handler path
    router->addHandler("GET",path, get); //to list root dir contents
    router->addHandler("GET",path+"/:*", get);//to list and service inner dir/files contents
    router->addHandler("GET","favicon.ico", get); //specially for favicon.ico
    gateway->addGate(get, "GET"); // only GET method is allowed on BasicFileHandler

    addedRoutes = true;
}

void BasicFileHandler::removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway){

    if(!addedRoutes){
        qWarning("BasicFileHandler %p: no routes to remove", this);
        return;
    }

    qDebug("BasicFileHandler %p: un-registering handlers...", this);

    qDebug("BasicFileHandler %p: removing handlers...", this);
    router->removeHandler(get);

    qDebug("BasicFileHandler %p: removing gateways...", this);
    gateway->removeGate(get);

    qDebug("BasicFileHandler %p: deleting handlers...", this);
    delete get ;

    addedRoutes = false;

}

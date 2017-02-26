#ifndef BASICFILEHANDLER_H
#define BASICFILEHANDLER_H

#include "AnaCloud/core/app.h"

#include "AnaCloud/http/httprequesthandler.h"
#include "../../http/staticfilecontroller.h"

#include "AnaCloud/router/router.h"
#include "AnaCloud/router/gateway.h"
#include "AnaCloud/core/handlerfunctor.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QDir>

#include "AnaCloud/utility/globals.h"
#include "AnaCloud/core/errors/anaclouderror.h"
#include "AnaCloud/core/errors/anaclouderrors.h"
#include "AnaCloud/http/utility/httpstatuscodes.h"
#include "AnaCloud/utility/resourcelink.h"

// just a wrapper for StaticFileController to insure that:
// 1- the user is using the right http method
// 2- will get the proper error message if he used a wrong http method
// or requested file was not found
// 3- is using the correct response/request content type
// 4- get proper error if anonymous users are denied to access the service
// 5- to list files and folders on server, because StaticFileController only serve files

class FileJson
{

public:

    static QJsonDocument toJson(QString path, QFileInfo *p_info){

        QJsonDocument json;
        QJsonObject o;
        QJsonObject maino;

        o.insert("name", QJsonValue(p_info->fileName()));
        o.insert("links", QJsonValue(links(path, p_info)));

        maino.insert("file",o);
        json.setObject(maino);

        return json;
    }

    static QJsonObject toJsonObject(QString path, QFileInfo *p_info){

        QJsonObject o;

        o.insert("name", QJsonValue(p_info->fileName()));
        o.insert("links", QJsonValue(links(path, p_info)));

        return o;
    }

    //creates links for a resource
    static QJsonArray links(QString path, QFileInfo *info){

        ResourceLink self;
        if(info->isDir())
            self = ResourceLink(QByteArray().append(path + info->fileName()) , "list", "GET");
        else
            self = ResourceLink(QByteArray().append(path + info->fileName()) , "self", "GET");

        QJsonArray array;
        array.append(QJsonValue(self.jsonObject()));

        return array;
    }

    // collection links
    static QJsonArray links(){

        // only for collections not resources
        ResourceLink list(path + "/" , "list", "GET");

        QJsonArray array;
        array.append(QJsonValue(list.jsonObject()));

        return array;
    }

    static void setPath(QByteArray pth){
        path = pth;
    }

private:
    static QByteArray path;

};

/**
* @brief The FreeAccessHandler class is used to list titles and packages that has a free access to the public
*/
class BasicFileHandler : public HttpRequestHandler
{
public:
    BasicFileHandler();
    ~BasicFileHandler();

    /**
    * @brief The GET function list both titles and packages with free access to the public
    *
    * ****************************************************************************
    * URL:          ** /freeaccess                                               *
    * ****************************************************************************
    * Method:       ** GET                                                       *
    * ****************************************************************************
    * Query Params:                                                              *
    *               ** from : the number of the first FreeAccess to return       *
    *               ** to   : the number of the first FreeAccess to return       *
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

    void addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway);
    void removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway);

private:

    bool checkRequest(HttpRequest& request, HttpResponse& response);

    QByteArray path;// handler url path
    QByteArray docRoot;// service data dir

    //indicate wither handler was added to router and gateway or not
    bool addedRoutes = false;

    RequestHandler *get = nullptr; // list all files and dirs

    StaticFileController *staticFileController;

    AnasErrors anasErrors;
    HttpRequestHeaders httpRequestHeaders;
    HttpResponseHeaders httpResponseHeaders;
};


#endif // BASICFILEHANDLER_H

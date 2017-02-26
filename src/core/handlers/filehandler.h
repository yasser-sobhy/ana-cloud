#ifndef FILESERVER_H
#define FILESERVER_H

#include "AnaCloud/core/app.h"

#include "AnaCloud/http/httprequesthandler.h"
#include "AnaCloud/http/staticfilecontroller.h"

#include "../../router/router.h"
#include "../../router/gateway.h"
#include "../handlerfunctor.h"
#include "AnaCloud/utility/configi.h"

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

struct ServerFile
{
    QString name;
    QString path;

    bool valid() {
        return !name.isEmpty() && !path.isEmpty();
    }
};

class FileServerJson
{

public:

    // collection links
    static QJsonArray links(){

        // only for collections not resources
        ResourceLink list(path + "/" , "list", "GET");
        ResourceLink create(path + "/" , "create", "POST");

        QJsonArray array;
        array.append(QJsonValue(list.jsonObject()));
        array.append(QJsonValue(create.jsonObject()));

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
class FileServer : public HttpRequestHandler , public RestfulHandler
{
public:
    FileServer();
    ~FileServer();

    //list files, not implemented. No need to list files on server due to it's folder structure
    void GET(HttpRequest&, HttpResponse&);
    //eplace list of files, not implemented.
    void PUT(HttpRequest&, HttpResponse&);
    // post a new file
    void POST(HttpRequest& request, HttpResponse& response);
    //delete all files, not supported
    void DELETE(HttpRequest& request, HttpResponse&);

    // get a file by it's name
    void idGET(HttpRequest& request, HttpResponse& response);
    // replace a file
    void idPUT(HttpRequest& request, HttpResponse& response);
    //post a file as a child of another file, not implemented. Not possible
    void idPOST(HttpRequest& request, HttpResponse&);
    // delete a file
    void idDELETE(HttpRequest& request, HttpResponse& response);

    void addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway);
    void removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway);

private:

    bool checkRequest(HttpRequest& request, HttpResponse& response);
    ServerFile createFilePath(QString filename);
    ServerFile makeFilePath(QString filename);

    QByteArray path;// handler url path
    QByteArray docRoot;// service data dir

    //indicate wither handler was added to router and gateway or not
    bool addedRoutes = false;

    Configi configi;

    RequestHandler *post = nullptr;

    RequestHandler *idget = nullptr;
    RequestHandler *idput = nullptr;
    RequestHandler *iddelete = nullptr;

    StaticFileController *staticFileController;

    AnasErrors anasErrors;
    HttpRequestHeaders httpRequestHeaders;
    HttpResponseHeaders httpResponseHeaders;
};


#endif // FILESERVER_H

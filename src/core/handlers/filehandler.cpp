#include "filehandler.h"

QByteArray FileServerJson::path;


FileServer::FileServer()
{
    configi.read("etc/handlers/FileServer.ini");

    path = configi.get("FileServer", "urlPath").toByteArray();
    docRoot = configi.get("FileServer", "dataDir").toByteArray();

    FileServerJson::setPath(path);

    QSettings ssets("etc/handlers/FileServerStaticFileController.ini",  QSettings::IniFormat);
    ssets.beginGroup("files");
    staticFileController = new StaticFileController(&ssets);
}

FileServer::~FileServer()
{
    delete staticFileController;
}

bool FileServer::checkRequest(HttpRequest &request, HttpResponse &response){

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
//--
void FileServer::GET(HttpRequest &, HttpResponse &){
}
//--
void FileServer::PUT(HttpRequest &, HttpResponse &){
}

void FileServer::POST(HttpRequest &request, HttpResponse &response){

    QByteArray uploadedfilename = request.getParameter("uploadedfile");
    ServerFile serverfile = createFilePath(uploadedfilename);

    if(!serverfile.valid()){
        anasErrors.badRequest.response(response);
        return;
    }

    QTemporaryFile *uploadedFile = request.getUploadedFile("uploadedfile");

    if(uploadedFile)
    {
        // upload new file
        if(uploadedFile->rename(serverfile.path)){

            uploadedFile->setAutoRemove(false); // don't delete newly created file

            response.setHeader(httpResponseHeaders.ContentType, "text/plain");
            // return the name of the uploaded file on the server
            response.write(QByteArray().append( serverfile.name ), true);
            // Http status is 200 OK by default, so just return
            return;
        }
        else
        {
            anasErrors.InternalServerError.response(response);
            return;
        }
    }
    else
    {
        anasErrors.badRequest.response(response);
        return;
    }
}
//--
void FileServer::DELETE(HttpRequest &, HttpResponse &){
}

void FileServer::idGET(HttpRequest &request, HttpResponse &response){

    ServerFile serverfile = makeFilePath(request.getTokenValue("filename"));

    if(!serverfile.valid()){
        anasErrors.badRequest.response(response);
        return;
    }

    QFileInfo info(serverfile.path);

    qDebug() << info.absoluteFilePath() << info.exists() << info.isFile();

    if(info.exists() && info.isFile())
    {
        request.setPath(serverfile.path);
        staticFileController->service(request, response);

        // Http status is 200 OK by default, so just return
        return;
    }
    else // file not found
    {
        anasErrors.NotFound.response(response);
    }

}

void FileServer::idPUT(HttpRequest &request, HttpResponse &response){

    // file to be edited
    QByteArray filename = request.getTokenValue("filename");
    QTemporaryFile *uploadedFile = request.getUploadedFile("uploadedfile");

    ServerFile oldserverfile = makeFilePath(filename);
    ServerFile newserverfile = createFilePath("");

    if(!oldserverfile.valid() || !newserverfile.valid()){
        anasErrors.badRequest.response(response);
        return;
    }

    QFileInfo info(oldserverfile.path);

    if(info.exists() && info.isFile() && uploadedFile) // we need to replace file, so it must be already on the server
    {
        QFile file(info.absoluteFilePath());

        if(!file.remove()) // delete old file
        {
            // if old file not removed, response an error
            anasErrors.InternalServerError.response(response);
            return;
        }

        qDebug() << "removed file" << oldserverfile.path;

        // upload new file
        qDebug() << "copying to" << newserverfile.path;
        if(uploadedFile->rename(newserverfile.path)){

            uploadedFile->setAutoRemove(false); // don't delete newly created file

            response.setHeader(httpResponseHeaders.ContentType, "text/plain");
            // return the name of the uploaded file on the server
            response.write(QByteArray().append( newserverfile.name ), true);
            // Http status is 200 OK by default, so just return
            qDebug() << "renamed file";
            return;
        }
        else
        {
            qDebug() << "rename error" << uploadedFile->errorString();
            anasErrors.InternalServerError.response(response);
            return;
        }
    }
    else // file not found on server
    {
        anasErrors.badRequest.response(response);
        return;
    }

}

//--
void FileServer::idPOST(HttpRequest &, HttpResponse &){
}

void FileServer::idDELETE(HttpRequest &request, HttpResponse &response){

    QFileInfo info( makeFilePath(request.getTokenValue("filename")).path );

    if(info.exists() && info.isFile())
    {
        QFile file(info.absoluteFilePath());

        if(file.remove())
            return;
        else anasErrors.InternalServerError.response(response);
    }
    else
    {
        anasErrors.badRequest.response(response);
    }
}

ServerFile FileServer::createFilePath(QString filename)
{
    // create uuid for file name
    QFileInfo info(filename);
    filename = QUuid::createUuid().toString();
    filename.remove('{').remove('}').remove('-');

    if(!info.suffix().isEmpty())
        filename.append(".").append(info.suffix());

    qDebug() << "created file name::" << filename;

    QString pth;
    int depth = 4; // should be read from a config file
    if(filename.length() < depth) return {};

    for(int i = 0; i < depth; i++)
    {
        pth += "/" + filename[i];
    }

    pth = docRoot + pth + "/"; // file dir

    qDebug() << "making path:" << pth;

    QDir dir(pth);
    if(!dir.exists()) dir.mkpath(pth);

    qDebug() << "created server file" << pth + filename;

    return {filename, pth + filename};
}

ServerFile FileServer::makeFilePath(QString filename)
{
    qDebug() << "making path" << filename;

    QString pth;
    int depth = 4; // should be read from a config file
    if(filename.length() < depth) return {};

    for(int i = 0; i < depth; i++)
    {
        pth += "/" + filename[i];
    }

    pth = docRoot + pth + "/"; // file dir

    qDebug() << "generated server file" << pth + filename;

    return {filename, pth + filename};
}

void FileServer::addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway){

    if(addedRoutes) {
        qWarning("FileServer %p: routes already added", this);
        return;
    }

    qDebug("FileServer %p: registering handlers...", this);

    post = new RequestHandler (this, (serviceFun)&FileServer::POST);

    idget = new RequestHandler(this, (serviceFun)&FileServer::idGET);
    idput = new RequestHandler(this, (serviceFun)&FileServer::idPUT);
    iddelete = new RequestHandler(this, (serviceFun)&FileServer::idDELETE);

    // add handler for different methods with handler path
    router->addHandler("POST",path, post);

    router->addHandler("GET",path+"/:filename", idget);
    router->addHandler("PUT",path+"/:filename",idput);
    router->addHandler("DELETE",path+"/:filename",iddelete);

    gateway->addGate(post, configi.get("FileServer.POST", "userGroups").toByteArray());

    gateway->addGate(idget, configi.get("FileServer.idGET", "userGroups").toByteArray());
    gateway->addGate(idput, configi.get("FileServer.idPUT", "userGroups").toByteArray());
    gateway->addGate(iddelete, configi.get("FileServer.idDELETE", "userGroups").toByteArray());

    //    EasyTaxiRequestMapper::basicAuthenticator.addPublicHandler(post);

    App::basicAuthenticator.addPublicHandler(idget);
    //    EasyTaxiRequestMapper::basicAuthenticator.addPublicHandler(idput);
    //    EasyTaxiRequestMapper::basicAuthenticator.addPublicHandler(iddelete);

    addedRoutes = true;
}
void FileServer::removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway){

    if(!addedRoutes){
        qWarning("FileServer %p: no handlers to remove", this);
        return;
    }

    qDebug("FileServer %p: un-registering FileServer...", this);

    qDebug("FileServer %p: removing handlers...", this);
    router->removeHandler(post);

    router->removeHandler(idget);
    router->removeHandler(idput);
    router->removeHandler(iddelete);


    qDebug("FileServer %p: removing gateways...", this);
    gateway->removeGate(post);

    gateway->removeGate(idget);
    gateway->removeGate(idput);
    gateway->removeGate(iddelete);

    qDebug("FileServer %p: deleting handlers...", this);
    delete post;

    delete idget;
    delete idput;
    delete iddelete ;

    addedRoutes = false;

}


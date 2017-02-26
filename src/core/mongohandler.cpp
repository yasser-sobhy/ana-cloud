//#include "mongohandler.h"


//MongoHandler::MongoHandler(){
//    configi.read("etc/handlers/MongoHandler.ini");

//    path = configi.get("MongoHandler", "urlPath").toByteArray();
//  //  ClientLocationsJson::setPath(path);

//    requestContentType = configi.get("MongoHandler", "requestContentType").toByteArray();
//    responseContentType = configi.get("MongoHandler", "responseContentType").toByteArray();
//    queryStringMode = configi.get("MongoHandler", "queryStringMode").toByteArray();
//}

//bool MongoHandler::checkRequest(HttpRequest &request, HttpResponse &response){

//    // check for media type required by client
//    if(request.getHeader(httpRequestHeaders.Accept) != responseContentType ){

//        anasErrors.NotAcceptable.response(response);
//        return false;
//    }

//    // check for media type required by handler
//    if(request.getHeader(httpRequestHeaders.ContentType) != requestContentType){

//        anasErrors.UnsupportedMediaType.response(response);
//        return false;
//    }

//    return true;
//}

//QByteArray MongoHandler::createUuid(){

//    uuid::Uuid uid = uuid::uuid1(0x19432987, 0x33);
//    QByteArray hexuuid = QByteArray().append( QString::fromStdString(uid.hex()));

//    //https://www.percona.com/blog/2014/12/19/store-uuid-optimized-way/
//    QByteArray retuuid = hexuuid.mid(14,4);
//    retuuid += hexuuid.mid(9,4);
//    retuuid += hexuuid.mid(0,8);
//    retuuid += hexuuid.mid(19,4);
//    retuuid += hexuuid.mid(24);

//    return retuuid;
//}
//void MongoHandler::GET(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    bool toOK, fromOK;
//    int from = request.getParameter("from").toInt(&fromOK);
//    int to = request.getParameter("to").toInt(&toOK);

//    // if any query params are wrong
//    if( fromOK == false || toOK == false)
//    {
//        // if mode == Restrict response with error
//        if( queryStringMode == "Restrict")
//        {
//            anasErrors.badRequest.response(response);
//            return;
//        }
//        else{
//            // if mode != Restrict use default values
//            from = 0;
//            to = 9;
//        }
//    }

//    QList<ClientLocations*> *clientLocationslist = m_clientLocationsCommands.getList(from, to);

//    // if fetched data
//    if(clientLocationslist){

//        QJsonDocument json;
//        QJsonObject o;
//        QJsonArray array;

//        // if list is not empty
//        if(!clientLocationslist->isEmpty()){

//            for (ClientLocations *clientLocations: *clientLocationslist) {

//                QJsonValue value(ClientLocationsJson::jsonObject(clientLocations));
//                array.append(value);
//            }

//            o.insert("ClientLocations", QJsonValue(array));
//            o.insert("links", QJsonValue(ClientLocationsJson::links()));
//            json.setObject(o);

//            response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//            response.write(json.toJson(), true);

//            qDeleteAll(*clientLocationslist);
//            delete clientLocationslist;
//            return;
//        }
//        else
//        {
//            // if no data fetched
//            anasErrors.NotFound.response(response);
//            return;
//        }
//    }
//    else
//    {
//        // if no data fetched; a null pointer returned
//        anasErrors.NotFound.response(response);
//        return;
//    }
//}
//// not implemented
//void MongoHandler::PUT(HttpRequest &request, HttpResponse &response){

//    anasErrors.NotImplemented.response(response);
//}
//void MongoHandler::POST(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    // parse request
//    ClientLocations *clientLocations = ClientLocationsJson::fromJson(request.getBody());

//    // if successfully parsed request
//    if(clientLocations)
//    {
//        // validate() method is supported by all entities
//        // and is used to validate an object values
//        if(clientLocations->validate(true))
//        {


//            if(m_clientLocationsCommands.insert(clientLocations))
//            {
//                QJsonDocument json;
//                QJsonObject o;

//                o.insert("clientLocations", QJsonValue(ClientLocationsJson::jsonObject(clientLocations)));
//                o.insert("links", QJsonValue(ClientLocationsJson::links()));
//                json.setObject(o);

//                //return newly created object
//                response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//                response.write(json.toJson(), true);

//                delete clientLocations;
//                return;
//            }
//            else{
//                // successfully parsed request, but couldn't insert object
//                anasErrors.InternalServerError.response(response);
//                delete clientLocations;
//                return;
//            }
//        }
//        else {
//            // successfully parsed request, but it contains invalid values
//            anasErrors.badRequest.response(response);
//            delete clientLocations;
//            return;
//        }
//    }
//    // if failed to parse request
//    else anasErrors.badRequest.response(response);

//}
//// not implemented
//void MongoHandler::DELETE(HttpRequest &request, HttpResponse &response){

//    anasErrors.NotImplemented.response(response);
//}
//void MongoHandler::idGET(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get locationID of resource from URI
//    int locationID = request.getTokenValue("locationID").toInt();



//    // if locationID is zero
//   if( locationID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }

//    ClientLocations *clientLocations = m_clientLocationsCommands.get(locationID);

//    // if fetched data
//    if(clientLocations){

//        QJsonDocument json;
//        QJsonObject o;

//        o.insert("clientLocations", QJsonValue(ClientLocationsJson::jsonObject(clientLocations)));
//        o.insert("links", QJsonValue(ClientLocationsJson::links()));
//        json.setObject(o);

//        response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//        response.write(json.toJson(), true);

//        delete clientLocations;
//        return;
//    }
//    else
//    {
//        // if error fetching data; a null pointer returned
//        anasErrors.NotFound.response(response);
//        return;
//    }
//}
//void MongoHandler::idPUT(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get locationID of resource from URI
//    int locationID = request.getTokenValue("locationID").toInt();



//    // if locationID is zero
//   if( locationID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }

//    // parse request
//    ClientLocations *clientLocations = ClientLocationsJson::fromJson(request.getBody());

//    // if successfully parsed request object
//    if(clientLocations)
//    {
//        // set locationID found in URI
//        clientLocations->setLocationID(locationID);

//        // validate() method is supported by all entities
//        // and is used to validate an object values
//        if(clientLocations->validate(false))
//        {
//            if(m_clientLocationsCommands.update(clientLocations))
//            {
//                QJsonDocument json;
//                QJsonObject o;

//                o.insert("clientLocations", QJsonValue(ClientLocationsJson::jsonObject(clientLocations)));
//                o.insert("links", QJsonValue(ClientLocationsJson::links()));
//                json.setObject(o);

//                //return newly updated object
//                response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//                response.write(json.toJson(), true);

//                delete clientLocations;
//                return;
//            }
//            else{
//                // successfully parsed request, but couldn't update object
//                anasErrors.InternalServerError.response(response);

//                delete clientLocations;
//                return;
//            }
//        }
//        else {
//            // successfully parsed request, but it contains invalid values
//            anasErrors.badRequest.response(response);
//            delete clientLocations;
//            return;
//        }
//    }
//    // if failed to parse request
//    else {
//        anasErrors.badRequest.response(response);
//        return;
//    }
//}
//// not implemented
//void MongoHandler::idPOST(HttpRequest &request, HttpResponse &response){

//    anasErrors.NotImplemented.response(response);
//}
//void MongoHandler::idDELETE(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get locationID of resource from URI
//    int locationID = request.getTokenValue("locationID").toInt();



//    // if locationID is zero
//   if( locationID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }


//    if(m_clientLocationsCommands.doDelete(locationID))
//    {
//        // Http status is 200 OK by default, so just return
//        return;
//    }
//    else{
//        // successfully parsed request, but couldn't delete it
//        anasErrors.InternalServerError.response(response);
//        return;
//    }

//}
//void MongoHandler::value(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get locationID of resource from URI
//    int locationID = request.getTokenValue("locationID").toInt();



//    // if locationID is zero
//   if( locationID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }


//    //get value name from resource from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    if(valuename.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    QVariant value = m_clientLocationsCommands.value(valuename, locationID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(value.toByteArray(), true);
//}

//void MongoHandler::byValue(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    //get value name from resource from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    //get value from resource from URI
//    QByteArray value = request.getTokenValue("value");

//    if(valuename.isEmpty() || value.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    ClientLocations *clientLocations = m_clientLocationsCommands.byValue(valuename,value);

//    // if fetched data
//    if(clientLocations){

//        QJsonDocument json;
//        QJsonObject o;

//        o.insert("clientLocations", QJsonValue(ClientLocationsJson::jsonObject(clientLocations)));
//        o.insert("links", QJsonValue(ClientLocationsJson::links()));
//        json.setObject(o);

//        response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//        response.write(json.toJson(), true);

//        delete clientLocations;
//        return;
//    }
//    else
//    {
//        // if error fetching data; a null pointer returned
//        anasErrors.NotFound.response(response);
//        return;
//    }
//}

//void MongoHandler::byValueList(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    bool toOK, fromOK;
//    int from = request.getParameter("from").toInt(&fromOK);
//    int to = request.getParameter("to").toInt(&toOK);

//    //get value name from resource from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    //get value from resource from URI
//    QByteArray value = request.getTokenValue("value");

//    // if any query params are wrong
//    if( fromOK == false|| toOK == false)
//    {
//        // if mode == Restrict response with error
//        if( queryStringMode == "Restrict")
//        {
//            anasErrors.badRequest.response(response);
//            return;
//        }
//        else{
//            // if mode != Restrict use default values
//            from = 0;
//            to = 9;
//        }
//    }

//    if(valuename.isEmpty() || value.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }


//    QList<ClientLocations*> *clientLocationslist = m_clientLocationsCommands.byValueList(valuename,value, from, to);

//    // if fetched data
//    if(clientLocationslist){

//        QJsonDocument json;
//        QJsonObject o;
//        QJsonArray array;

//        // if list is not empty
//        if(!clientLocationslist->isEmpty()){

//            for (ClientLocations *clientLocations: *clientLocationslist) {

//                QJsonValue value(ClientLocationsJson::jsonObject(clientLocations));
//                array.append(value);
//            }

//            o.insert("clientLocations", QJsonValue(array));
//            o.insert("links", QJsonValue(ClientLocationsJson::links()));
//            json.setObject(o);

//            response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//            response.write(json.toJson(), true);

//            qDeleteAll(*clientLocationslist);
//            delete clientLocationslist;
//            return;
//        }
//        else
//        {
//            // if no data fetched
//            anasErrors.NotFound.response(response);
//            return;
//        }
//    }
//    else
//    {
//        // if no data fetched; a null pointer returned
//        anasErrors.NotFound.response(response);
//        return;
//    }
//}

//void MongoHandler::count(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    double ret = m_clientLocationsCommands.count();

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}
//void MongoHandler::countByID(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get locationID of resource from URI
//    int locationID = request.getTokenValue("locationID").toInt();



//    // if locationID is zero
//   if( locationID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }


//    //get value name from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    if(valuename.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    double ret = m_clientLocationsCommands.countByID(valuename, locationID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void MongoHandler::countValue(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    //get value name from URI
//    QByteArray what = request.getTokenValue("what");

//    //get value name from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    //get value from URI
//    QByteArray value = request.getTokenValue("value");

//    if(valuename.isEmpty() || value.isEmpty() || what.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    double ret = m_clientLocationsCommands.countValue(what, valuename,value);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void MongoHandler::sum(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    double ret = m_clientLocationsCommands.sum();

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}
//void MongoHandler::sumByID(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get locationID of resource from URI
//    int locationID = request.getTokenValue("locationID").toInt();



//    // if locationID is zero
//   if( locationID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }


//    //get value name from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    if(valuename.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    double ret = m_clientLocationsCommands.sumByID(valuename, locationID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void MongoHandler::sumValue(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    //get value name from URI
//    QByteArray what = request.getTokenValue("what");

//    //get value name from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    //get value from URI
//    QByteArray value = request.getTokenValue("value");

//    if(valuename.isEmpty() || value.isEmpty() || what.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    double ret = m_clientLocationsCommands.sumValue(what, valuename,value);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void MongoHandler::avg(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    double ret = m_clientLocationsCommands.avg();

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}
//void MongoHandler::avgByID(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get locationID of resource from URI
//    int locationID = request.getTokenValue("locationID").toInt();



//    // if locationID is zero
//   if( locationID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }


//    //get value name from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    if(valuename.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    double ret = m_clientLocationsCommands.avgByID(valuename, locationID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void MongoHandler::avgValue(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    //get value name from URI
//    QByteArray what = request.getTokenValue("what");

//    //get value name from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    //get value from URI
//    QByteArray value = request.getTokenValue("value");

//    if(valuename.isEmpty() || value.isEmpty() || what.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    double ret = m_clientLocationsCommands.avgValue(what, valuename,value);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void MongoHandler::min(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    double ret = m_clientLocationsCommands.min();

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}
//void MongoHandler::minByID(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get locationID of resource from URI
//    int locationID = request.getTokenValue("locationID").toInt();



//    // if locationID is zero
//   if( locationID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }


//    //get value name from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    if(valuename.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    double ret = m_clientLocationsCommands.minByID(valuename, locationID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void MongoHandler::minValue(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    //get value name from URI
//    QByteArray what = request.getTokenValue("what");

//    //get value name from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    //get value from URI
//    QByteArray value = request.getTokenValue("value");

//    if(valuename.isEmpty() || value.isEmpty() || what.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    double ret = m_clientLocationsCommands.minValue(what, valuename,value);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void MongoHandler::max(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    double ret = m_clientLocationsCommands.max();

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}
//void MongoHandler::maxByID(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get locationID of resource from URI
//    int locationID = request.getTokenValue("locationID").toInt();



//    // if locationID is zero
//   if( locationID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }


//    //get value name from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    if(valuename.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    double ret = m_clientLocationsCommands.maxByID(valuename, locationID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void MongoHandler::maxValue(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    //get value name from URI
//    QByteArray what = request.getTokenValue("what");

//    //get value name from URI
//    QByteArray valuename = request.getTokenValue("valuename");

//    //get value from URI
//    QByteArray value = request.getTokenValue("value");

//    if(valuename.isEmpty() || value.isEmpty() || what.isEmpty())
//    {
//        anasErrors.badRequest.response(response);
//        return;
//    }

//    double ret = m_clientLocationsCommands.maxValue(what, valuename,value);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void MongoHandler::addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway){

//    if(routesAdded) {
//        qWarning("MongoHandler %p: routes already added", this);
//        return;
//    }

//    qDebug("MongoHandler %p: registering handlers...", this);

//    get = new RequestHandler (this, (serviceFun)&MongoHandler::GET);
//    post = new RequestHandler (this, (serviceFun)&MongoHandler::POST);

//    idget = new RequestHandler(this, (serviceFun)&MongoHandler::idGET);
//    idput = new RequestHandler(this, (serviceFun)&MongoHandler::idPUT);
//    iddelete = new RequestHandler(this, (serviceFun)&MongoHandler::idDELETE);

//    valueGET = new RequestHandler(this, (serviceFun)&MongoHandler::value);
//    byValueGET = new RequestHandler(this, (serviceFun)&MongoHandler::byValue);
//    byValueListGET = new RequestHandler(this, (serviceFun)&MongoHandler::byValueList);

//    countGET = new RequestHandler(this, (serviceFun)&MongoHandler::count);
//    countByIDGET = new RequestHandler(this, (serviceFun)&MongoHandler::countByID);
//    countValueGET = new RequestHandler(this, (serviceFun)&MongoHandler::countValue);

//    sumGET = new RequestHandler(this, (serviceFun)&MongoHandler::sum);
//    sumByIDGET = new RequestHandler(this, (serviceFun)&MongoHandler::sumByID);
//    sumValueGET = new RequestHandler(this, (serviceFun)&MongoHandler::sumValue);

//    avgGET = new RequestHandler(this, (serviceFun)&MongoHandler::avg);
//    avgByIDGET = new RequestHandler(this, (serviceFun)&MongoHandler::avgByID);
//    avgValueGET = new RequestHandler(this, (serviceFun)&MongoHandler::avgValue);

//    minGET = new RequestHandler(this, (serviceFun)&MongoHandler::min);
//    minByIDGET = new RequestHandler(this, (serviceFun)&MongoHandler::minByID);
//    minValueGET = new RequestHandler(this, (serviceFun)&MongoHandler::minValue);

//    maxGET = new RequestHandler(this, (serviceFun)&MongoHandler::max);
//    maxByIDGET = new RequestHandler(this, (serviceFun)&MongoHandler::maxByID);
//    maxValueGET = new RequestHandler(this, (serviceFun)&MongoHandler::maxValue);




//    // add handler for different methods with handler path
//    router->addHandler("GET",path, get);
//    router->addHandler("POST",path, post);

//    router->addHandler("GET",path+"/:locationID", idget);
//    router->addHandler("PUT",path+"/:locationID",idput);
//    router->addHandler("DELETE",path+"/:locationID",iddelete);

//    router->addHandler("GET",path+"/:locationID/:valuename", valueGET);
//    router->addHandler("GET",path+"/by/:valuename/:value",byValueGET);
//    router->addHandler("GET",path+"/list/by/:valuename/:value",byValueListGET);

//    router->addHandler("GET",path+"/:locationID/fn/count/:valuename", countByIDGET);
//    router->addHandler("GET",path+"/fn/count/:valuename",countGET);
//    router->addHandler("GET",path+"/fn/count/:what/:valuename/:value",countValueGET);

//    router->addHandler("GET",path+"/:locationID/fn/sum/:valuename", sumByIDGET);
//    router->addHandler("GET",path+"/fn/sum/:valuename",sumGET);
//    router->addHandler("GET",path+"/fn/sum/:what/:valuename/:value",sumValueGET);

//    router->addHandler("GET",path+"/:locationID/fn/avg/:valuename", avgByIDGET);
//    router->addHandler("GET",path+"/fn/avg/:valuename",avgGET);
//    router->addHandler("GET",path+"/fn/avg/:what/:valuename/:value",avgValueGET);

//    router->addHandler("GET",path+"/:locationID/fn/min/:valuename", minByIDGET);
//    router->addHandler("GET",path+"/fn/min/:valuename",minGET);
//    router->addHandler("GET",path+"/fn/min/:what/:valuename/:value",minValueGET);

//    router->addHandler("GET",path+"/:locationID/fn/max/:valuename", maxByIDGET);
//    router->addHandler("GET",path+"/fn/max/:valuename",maxGET);
//    router->addHandler("GET",path+"/fn/max/:what/:valuename/:value",maxValueGET);




//    gateway->addGate(get, configi.get("MongoHandler.GET", "userGroups").toByteArray());
//    gateway->addGate(post, configi.get("MongoHandler.POST", "userGroups").toByteArray());

//    gateway->addGate(idget, configi.get("MongoHandler.idGET", "userGroups").toByteArray());
//    gateway->addGate(idput, configi.get("MongoHandler.idPUT", "userGroups").toByteArray());
//    gateway->addGate(iddelete, configi.get("MongoHandler.idDELETE", "userGroups").toByteArray());

//    gateway->addGate(valueGET, configi.get("MongoHandler.valueGET", "userGroups").toByteArray());
//    gateway->addGate(byValueGET, configi.get("MongoHandler.byValueGET", "userGroups").toByteArray());
//    gateway->addGate(byValueListGET, configi.get("MongoHandler.byValueListGET", "userGroups").toByteArray());

//    gateway->addGate(countGET, configi.get("MongoHandler.countGET", "userGroups").toByteArray());
//    gateway->addGate(countByIDGET, configi.get("MongoHandler.countByIDGET", "userGroups").toByteArray());
//    gateway->addGate(countValueGET, configi.get("MongoHandler.countValueGET", "userGroups").toByteArray());

//    gateway->addGate(sumGET, configi.get("MongoHandler.sumGET", "userGroups").toByteArray());
//    gateway->addGate(sumByIDGET, configi.get("MongoHandler.sumByIDGET", "userGroups").toByteArray());
//    gateway->addGate(sumValueGET, configi.get("MongoHandler.sumValueGET", "userGroups").toByteArray());

//    gateway->addGate(avgGET, configi.get("MongoHandler.avgGET", "userGroups").toByteArray());
//    gateway->addGate(avgByIDGET, configi.get("MongoHandler.avgByIDGET", "userGroups").toByteArray());
//    gateway->addGate(avgValueGET, configi.get("MongoHandler.avgValueGET", "userGroups").toByteArray());

//    gateway->addGate(minGET, configi.get("MongoHandler.minGET", "userGroups").toByteArray());
//    gateway->addGate(minByIDGET, configi.get("MongoHandler.minByIDGET", "userGroups").toByteArray());
//    gateway->addGate(minValueGET, configi.get("MongoHandler.minValueGET", "userGroups").toByteArray());

//    gateway->addGate(maxGET, configi.get("MongoHandler.maxGET", "userGroups").toByteArray());
//    gateway->addGate(maxByIDGET, configi.get("MongoHandler.maxByIDGET", "userGroups").toByteArray());
//    gateway->addGate(maxValueGET, configi.get("MongoHandler.maxValueGET", "userGroups").toByteArray());


//    routesAdded = true;
//}
//void MongoHandler::removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway){

//    if(!routesAdded){
//        qWarning("MongoHandler %p: no handlers to remove", this);
//        return;
//    }

//    qDebug("MongoHandler %p: un-registering MongoHandler...", this);

//    qDebug("MongoHandler %p: removing handlers...", this);
//    router->removeHandler(get);
//    router->removeHandler(post);

//    router->removeHandler(idget);
//    router->removeHandler(idput);
//    router->removeHandler(iddelete);

//    router->removeHandler(valueGET);
//    router->removeHandler(byValueGET);
//    router->removeHandler(byValueListGET);




//    qDebug("MongoHandler %p: removing gateways...", this);
//    gateway->removeGate(get);
//    gateway->removeGate(post);

//    gateway->removeGate(idget);
//    gateway->removeGate(idput);
//    gateway->removeGate(iddelete);

//    gateway->removeGate(valueGET);
//    gateway->removeGate(byValueGET);
//    gateway->removeGate(byValueListGET);




//    qDebug("MongoHandler %p: deleting handlers...", this);
//    delete get ;
//    delete post;

//    delete idget;
//    delete idput;
//    delete iddelete ;

//    delete valueGET;
//    delete byValueGET;
//    delete byValueListGET ;




//    routesAdded = false;

//}

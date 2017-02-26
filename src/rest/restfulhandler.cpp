#include "restfulhandler.h"

RestfulHandler::RestfulHandler()
{
//    configi.read("etc/handlers/RestfulHandler.ini");

//    path = configi.get("RestfulHandler", "urlPath").toByteArray();

//    requestContentType = configi.get("RestfulHandler", "requestContentType").toByteArray();
//    responseContentType = configi.get("RestfulHandler", "responseContentType").toByteArray();
//    queryStringMode = configi.get("RestfulHandler", "queryStringMode").toByteArray();
}


//bool RestfulHandler::checkRequest(HttpRequest &request, HttpResponse &response){

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

//QByteArray RestfulHandler::createUuid(){

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

//void RestfulHandler::GET(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    bool toOK, fromOK;
//    int from = request.getParameter("from").toInt(&fromOK);
//    int to = request.getParameter("to").toInt(&toOK);

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

//    QList<Rides*> *rideslist = m_ridesCommands.getList(from, to);

//    // if fetched data
//    if(rideslist){

//        QJsonDocument json;
//        QJsonObject o;
//        QJsonArray array;

//        // if list is not empty
//        if(!rideslist->isEmpty()){

//            for (Rides *rides: *rideslist) {

//                QJsonValue value(RidesJson::jsonObject(rides));
//                array.append(value);
//            }

//            o.insert("Rides", QJsonValue(array));
//            o.insert("links", QJsonValue(RidesJson::links()));
//            json.setObject(o);

//            response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//            response.write(json.toJson(), true);

//            qDeleteAll(*rideslist);
//            delete rideslist;
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
//void RestfulHandler::PUT(HttpRequest &request, HttpResponse &response){

//    anasErrors.NotImplemented.response(response);
//}
//void RestfulHandler::POST(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    // parse request
//    Rides *rides = RidesJson::fromJson(request.getBody());

//    // if successfully parsed request
//    if(rides)
//    {
//        // validate() method is supported by all entities
//        // and is used to validate an object values
//        if(rides->validate(true))
//        {


//            if(m_ridesCommands.insert(rides))
//            {
//                QJsonDocument json;
//                QJsonObject o;

//                o.insert("rides", QJsonValue(RidesJson::jsonObject(rides)));
//                o.insert("links", QJsonValue(RidesJson::links()));
//                json.setObject(o);

//                //return newly created object
//                response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//                response.write(json.toJson(), true);

//                delete rides;
//                return;
//            }
//            else{
//                // successfully parsed request, but couldn't insert object
//                anasErrors.InternalServerError.response(response);
//                delete rides;
//                return;
//            }
//        }
//        else {
//            // successfully parsed request, but it contains invalid values
//            anasErrors.badRequest.response(response);
//            delete rides;
//            return;
//        }
//    }
//    // if failed to parse request
//    else anasErrors.badRequest.response(response);

//}
//// not implemented
//void RestfulHandler::DELETE(HttpRequest &request, HttpResponse &response){

//    anasErrors.NotImplemented.response(response);
//}
//void RestfulHandler::idGET(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get rideID of resource from URI
//    int rideID = request.getTokenValue("rideID").toInt();



//    // if rideID is zero
//   if( rideID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }

//    Rides *rides = m_ridesCommands.get(rideID);

//    // if fetched data
//    if(rides){

//        QJsonDocument json;
//        QJsonObject o;

//        o.insert("rides", QJsonValue(RidesJson::jsonObject(rides)));
//        o.insert("links", QJsonValue(RidesJson::links()));
//        json.setObject(o);

//        response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//        response.write(json.toJson(), true);

//        delete rides;
//        return;
//    }
//    else
//    {
//        // if error fetching data; a null pointer returned
//        anasErrors.NotFound.response(response);
//        return;
//    }
//}
//void RestfulHandler::idPUT(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get rideID of resource from URI
//    int rideID = request.getTokenValue("rideID").toInt();



//    // if rideID is zero
//   if( rideID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }

//    // parse request
//    Rides *rides = RidesJson::fromJson(request.getBody());

//    // if successfully parsed request object
//    if(rides)
//    {
//        // set rideID found in URI
//        rides->setRideID(rideID);

//        // validate() method is supported by all entities
//        // and is used to validate an object values
//        if(rides->validate(false))
//        {
//            if(m_ridesCommands.update(rides))
//            {
//                QJsonDocument json;
//                QJsonObject o;

//                o.insert("rides", QJsonValue(RidesJson::jsonObject(rides)));
//                o.insert("links", QJsonValue(RidesJson::links()));
//                json.setObject(o);

//                //return newly updated object
//                response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//                response.write(json.toJson(), true);

//                delete rides;
//                return;
//            }
//            else{
//                // successfully parsed request, but couldn't update object
//                anasErrors.InternalServerError.response(response);

//                delete rides;
//                return;
//            }
//        }
//        else {
//            // successfully parsed request, but it contains invalid values
//            anasErrors.badRequest.response(response);
//            delete rides;
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
//void RestfulHandler::idPOST(HttpRequest &request, HttpResponse &response){

//    anasErrors.NotImplemented.response(response);
//}
//void RestfulHandler::idDELETE(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get rideID of resource from URI
//    int rideID = request.getTokenValue("rideID").toInt();



//    // if rideID is zero
//   if( rideID == 0){

//        anasErrors.NotFound.response(response);
//        return;
//    }


//    if(m_ridesCommands.doDelete(rideID))
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
//void RestfulHandler::value(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get rideID of resource from URI
//    int rideID = request.getTokenValue("rideID").toInt();



//    // if rideID is zero
//   if( rideID == 0){

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

//    QVariant value = m_ridesCommands.value(valuename, rideID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(value.toByteArray(), true);
//}

//void RestfulHandler::byValue(HttpRequest &request, HttpResponse &response){

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

//    Rides *rides = m_ridesCommands.byValue(valuename,value);

//    // if fetched data
//    if(rides){

//        QJsonDocument json;
//        QJsonObject o;

//        o.insert("rides", QJsonValue(RidesJson::jsonObject(rides)));
//        o.insert("links", QJsonValue(RidesJson::links()));
//        json.setObject(o);

//        response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//        response.write(json.toJson(), true);

//        delete rides;
//        return;
//    }
//    else
//    {
//        // if error fetching data; a null pointer returned
//        anasErrors.NotFound.response(response);
//        return;
//    }
//}

//void RestfulHandler::byValueList(HttpRequest &request, HttpResponse &response){

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


//    QList<Rides*> *rideslist = m_ridesCommands.byValueList(valuename,value, from, to);

//    // if fetched data
//    if(rideslist){

//        QJsonDocument json;
//        QJsonObject o;
//        QJsonArray array;

//        // if list is not empty
//        if(!rideslist->isEmpty()){

//            for (Rides *rides: *rideslist) {

//                QJsonValue value(RidesJson::jsonObject(rides));
//                array.append(value);
//            }

//            o.insert("rides", QJsonValue(array));
//            o.insert("links", QJsonValue(RidesJson::links()));
//            json.setObject(o);

//            response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//            response.write(json.toJson(), true);

//            qDeleteAll(*rideslist);
//            delete rideslist;
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

//void RestfulHandler::count(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    double ret = m_ridesCommands.count();

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}
//void RestfulHandler::countByID(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get rideID of resource from URI
//    int rideID = request.getTokenValue("rideID").toInt();



//    // if rideID is zero
//   if( rideID == 0){

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

//    double ret = m_ridesCommands.countByID(valuename, rideID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void RestfulHandler::countValue(HttpRequest &request, HttpResponse &response){

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

//    double ret = m_ridesCommands.countValue(what, valuename,value);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void RestfulHandler::sum(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    double ret = m_ridesCommands.sum();

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}
//void RestfulHandler::sumByID(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get rideID of resource from URI
//    int rideID = request.getTokenValue("rideID").toInt();



//    // if rideID is zero
//   if( rideID == 0){

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

//    double ret = m_ridesCommands.sumByID(valuename, rideID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void RestfulHandler::sumValue(HttpRequest &request, HttpResponse &response){

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

//    double ret = m_ridesCommands.sumValue(what, valuename,value);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void RestfulHandler::avg(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    double ret = m_ridesCommands.avg();

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}
//void RestfulHandler::avgByID(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get rideID of resource from URI
//    int rideID = request.getTokenValue("rideID").toInt();



//    // if rideID is zero
//   if( rideID == 0){

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

//    double ret = m_ridesCommands.avgByID(valuename, rideID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void RestfulHandler::avgValue(HttpRequest &request, HttpResponse &response){

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

//    double ret = m_ridesCommands.avgValue(what, valuename,value);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void RestfulHandler::min(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    double ret = m_ridesCommands.min();

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}
//void RestfulHandler::minByID(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get rideID of resource from URI
//    int rideID = request.getTokenValue("rideID").toInt();



//    // if rideID is zero
//   if( rideID == 0){

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

//    double ret = m_ridesCommands.minByID(valuename, rideID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void RestfulHandler::minValue(HttpRequest &request, HttpResponse &response){

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

//    double ret = m_ridesCommands.minValue(what, valuename,value);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void RestfulHandler::max(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//    double ret = m_ridesCommands.max();

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}
//void RestfulHandler::maxByID(HttpRequest &request, HttpResponse &response){

//    if( !checkRequest(request, response)){
//        // just return because checkRequest writes an error ,if any, before returning false
//        return;
//    }

//        //get rideID of resource from URI
//    int rideID = request.getTokenValue("rideID").toInt();



//    // if rideID is zero
//   if( rideID == 0){

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

//    double ret = m_ridesCommands.maxByID(valuename, rideID);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void RestfulHandler::maxValue(HttpRequest &request, HttpResponse &response){

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

//    double ret = m_ridesCommands.maxValue(what, valuename,value);

//    response.setHeader(httpResponseHeaders.ContentType, responseContentType);
//    response.write(QByteArray::number(ret), true);
//}

//void RestfulHandler::addRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway){

//    if(routesAdded) {
//        qWarning("RestfulHandler %p: routes already added", this);
//        return;
//    }

//    qDebug("RestfulHandler %p: registering handlers...", this);

//    get = new RequestHandler (this, (serviceFun)&RestfulHandler::GET);
//    post = new RequestHandler (this, (serviceFun)&RestfulHandler::POST);

//    idget = new RequestHandler(this, (serviceFun)&RestfulHandler::idGET);
//    idput = new RequestHandler(this, (serviceFun)&RestfulHandler::idPUT);
//    iddelete = new RequestHandler(this, (serviceFun)&RestfulHandler::idDELETE);

//    valueGET = new RequestHandler(this, (serviceFun)&RestfulHandler::value);
//    byValueGET = new RequestHandler(this, (serviceFun)&RestfulHandler::byValue);
//    byValueListGET = new RequestHandler(this, (serviceFun)&RestfulHandler::byValueList);

//    countGET = new RequestHandler(this, (serviceFun)&RestfulHandler::count);
//    countByIDGET = new RequestHandler(this, (serviceFun)&RestfulHandler::countByID);
//    countValueGET = new RequestHandler(this, (serviceFun)&RestfulHandler::countValue);

//    sumGET = new RequestHandler(this, (serviceFun)&RestfulHandler::sum);
//    sumByIDGET = new RequestHandler(this, (serviceFun)&RestfulHandler::sumByID);
//    sumValueGET = new RequestHandler(this, (serviceFun)&RestfulHandler::sumValue);

//    avgGET = new RequestHandler(this, (serviceFun)&RestfulHandler::avg);
//    avgByIDGET = new RequestHandler(this, (serviceFun)&RestfulHandler::avgByID);
//    avgValueGET = new RequestHandler(this, (serviceFun)&RestfulHandler::avgValue);

//    minGET = new RequestHandler(this, (serviceFun)&RestfulHandler::min);
//    minByIDGET = new RequestHandler(this, (serviceFun)&RestfulHandler::minByID);
//    minValueGET = new RequestHandler(this, (serviceFun)&RestfulHandler::minValue);

//    maxGET = new RequestHandler(this, (serviceFun)&RestfulHandler::max);
//    maxByIDGET = new RequestHandler(this, (serviceFun)&RestfulHandler::maxByID);
//    maxValueGET = new RequestHandler(this, (serviceFun)&RestfulHandler::maxValue);




//    // add handler for different methods with handler path
//    router->addHandler("GET",path, get);
//    router->addHandler("POST",path, post);

//    router->addHandler("GET",path+"/:rideID", idget);
//    router->addHandler("PUT",path+"/:rideID",idput);
//    router->addHandler("DELETE",path+"/:rideID",iddelete);

//    router->addHandler("GET",path+"/:rideID/:valuename", valueGET);
//    router->addHandler("GET",path+"/by/:valuename/:value",byValueGET);
//    router->addHandler("GET",path+"/list/by/:valuename/:value",byValueListGET);

//    router->addHandler("GET",path+"/:rideID/fn/count/:valuename", countByIDGET);
//    router->addHandler("GET",path+"/fn/count/:valuename",countGET);
//    router->addHandler("GET",path+"/fn/count/:what/:valuename/:value",countValueGET);

//    router->addHandler("GET",path+"/:rideID/fn/sum/:valuename", sumByIDGET);
//    router->addHandler("GET",path+"/fn/sum/:valuename",sumGET);
//    router->addHandler("GET",path+"/fn/sum/:what/:valuename/:value",sumValueGET);

//    router->addHandler("GET",path+"/:rideID/fn/avg/:valuename", avgByIDGET);
//    router->addHandler("GET",path+"/fn/avg/:valuename",avgGET);
//    router->addHandler("GET",path+"/fn/avg/:what/:valuename/:value",avgValueGET);

//    router->addHandler("GET",path+"/:rideID/fn/min/:valuename", minByIDGET);
//    router->addHandler("GET",path+"/fn/min/:valuename",minGET);
//    router->addHandler("GET",path+"/fn/min/:what/:valuename/:value",minValueGET);

//    router->addHandler("GET",path+"/:rideID/fn/max/:valuename", maxByIDGET);
//    router->addHandler("GET",path+"/fn/max/:valuename",maxGET);
//    router->addHandler("GET",path+"/fn/max/:what/:valuename/:value",maxValueGET);




//    gateway->addGate(get, configi.get("RestfulHandler.GET", "userGroups").toByteArray());
//    gateway->addGate(post, configi.get("RestfulHandler.POST", "userGroups").toByteArray());

//    gateway->addGate(idget, configi.get("RestfulHandler.idGET", "userGroups").toByteArray());
//    gateway->addGate(idput, configi.get("RestfulHandler.idPUT", "userGroups").toByteArray());
//    gateway->addGate(iddelete, configi.get("RestfulHandler.idDELETE", "userGroups").toByteArray());

//    gateway->addGate(valueGET, configi.get("RestfulHandler.valueGET", "userGroups").toByteArray());
//    gateway->addGate(byValueGET, configi.get("RestfulHandler.byValueGET", "userGroups").toByteArray());
//    gateway->addGate(byValueListGET, configi.get("RestfulHandler.byValueListGET", "userGroups").toByteArray());

//    gateway->addGate(countGET, configi.get("RestfulHandler.countGET", "userGroups").toByteArray());
//    gateway->addGate(countByIDGET, configi.get("RestfulHandler.countByIDGET", "userGroups").toByteArray());
//    gateway->addGate(countValueGET, configi.get("RestfulHandler.countValueGET", "userGroups").toByteArray());

//    gateway->addGate(sumGET, configi.get("RestfulHandler.sumGET", "userGroups").toByteArray());
//    gateway->addGate(sumByIDGET, configi.get("RestfulHandler.sumByIDGET", "userGroups").toByteArray());
//    gateway->addGate(sumValueGET, configi.get("RestfulHandler.sumValueGET", "userGroups").toByteArray());

//    gateway->addGate(avgGET, configi.get("RestfulHandler.avgGET", "userGroups").toByteArray());
//    gateway->addGate(avgByIDGET, configi.get("RestfulHandler.avgByIDGET", "userGroups").toByteArray());
//    gateway->addGate(avgValueGET, configi.get("RestfulHandler.avgValueGET", "userGroups").toByteArray());

//    gateway->addGate(minGET, configi.get("RestfulHandler.minGET", "userGroups").toByteArray());
//    gateway->addGate(minByIDGET, configi.get("RestfulHandler.minByIDGET", "userGroups").toByteArray());
//    gateway->addGate(minValueGET, configi.get("RestfulHandler.minValueGET", "userGroups").toByteArray());

//    gateway->addGate(maxGET, configi.get("RestfulHandler.maxGET", "userGroups").toByteArray());
//    gateway->addGate(maxByIDGET, configi.get("RestfulHandler.maxByIDGET", "userGroups").toByteArray());
//    gateway->addGate(maxValueGET, configi.get("RestfulHandler.maxValueGET", "userGroups").toByteArray());


//    routesAdded = true;
//}
//void RestfulHandler::removeRoutes(Router<RequestHandler, QByteArray> *router, Gateway<RequestHandler, QByteArray> *gateway){

//    if(!routesAdded){
//        qWarning("RestfulHandler %p: no handlers to remove", this);
//        return;
//    }

//    qDebug("RestfulHandler %p: un-registering RestfulHandler...", this);

//    qDebug("RestfulHandler %p: removing handlers...", this);
//    router->removeHandler(get);
//    router->removeHandler(post);

//    router->removeHandler(idget);
//    router->removeHandler(idput);
//    router->removeHandler(iddelete);

//    router->removeHandler(valueGET);
//    router->removeHandler(byValueGET);
//    router->removeHandler(byValueListGET);




//    qDebug("RestfulHandler %p: removing gateways...", this);
//    gateway->removeGate(get);
//    gateway->removeGate(post);

//    gateway->removeGate(idget);
//    gateway->removeGate(idput);
//    gateway->removeGate(iddelete);

//    gateway->removeGate(valueGET);
//    gateway->removeGate(byValueGET);
//    gateway->removeGate(byValueListGET);




//    qDebug("RestfulHandler %p: deleting handlers...", this);
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





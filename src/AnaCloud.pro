#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T10:06:29
#
#-------------------------------------------------

QT       += network sql testlib

QT       -= gui

TARGET = anacloud
TEMPLATE = lib
VERSION = 1.1

CONFIG += c++11

DEFINES += ANACLOUD_LIBRARY

INCLUDEPATH += /home/yasser/Downloads/AnaCloud

#LIBS += -L/usr/local/lib/ -lbsoncxx
#LIBS += -L/usr/local/lib/ -lmongocxx

#INCLUDEPATH += /usr/local/include/bsoncxx/v_noabi
#DEPENDPATH += /usr/local/include/bsoncxx/v_noabi
#INCLUDEPATH += /usr/local/include/mongocxx/v_noabi
#DEPENDPATH += /usr/local/include/mongocxx/v_noabi


SOURCES += \
    core/authintication/basicauthinticator.cpp \
    core/handlers/basicfilehandler.cpp \
    core/handlers/filehandler.cpp \
    core/handlers/roothandler.cpp \
    core/app.cpp \
#    core/mongohandler.cpp \
#    core/mongomodel.cpp \
    http/utility/httpstatuscodes.cpp \
    http/httpconnectionhandler.cpp \
    http/httpconnectionhandlerpool.cpp \
    http/httpcookie.cpp \
    http/httpglobal.cpp \
    http/httplistener.cpp \
    http/httprequest.cpp \
    http/httprequesthandler.cpp \
    http/httpresponse.cpp \
    http/httpsession.cpp \
    http/httpsessionstore.cpp \
    http/staticfilecontroller.cpp \
    PushServer/pushblacklist.cpp \
    PushServer/pushbroadcaster.cpp \
    PushServer/pushclient.cpp \
    PushServer/pushconnection.cpp \
    PushServer/pushconnectionhandler.cpp \
    PushServer/pushdata.cpp \
    PushServer/pushdataprovider.cpp \
    PushServer/pushmessage.cpp \
    PushServer/pushmonitor.cpp \
    PushServer/pushrouter.cpp \
    PushServer/pushserver.cpp \
    rest/restfulhandler.cpp \
#    utility/chance/chance.cpp \
#    utility/chance/chancedata.cpp \
    utility/uuid/uuid.cpp \
    utility/configi.cpp \
    utility/databaseconnectionpool.cpp \
    PushServer/pusher.cpp \
    PushServer/pushchannel.cpp \
    core/middleware/cors.cpp \
    utility/jwt.cpp \
    core/authintication/tokenauthenticator.cpp \
    utility/jws.cpp \
    core/authintication/jwtauthenticator.cpp \
    core/modules/user.cpp \
    rest/commandsbase.cpp \
    rest/entityreader.cpp \
    rest/fieldcommands.cpp \
    rest/paginationoptions.cpp \
    rest/searchoptions.cpp

HEADERS +=\
        anacloud_global.h \
    core/authintication/authenticatorbase.h \
    core/authintication/basicauthinticator.h \
    core/errors/anaclouderror.h \
    core/errors/anaclouderrors.h \
    core/handlers/accessdeniedhandler.h \
    core/handlers/basicfilehandler.h \
    core/handlers/filehandler.h \
    core/handlers/roothandler.h \
    core/schema/rule.h \
    core/schema/rules.h \
    core/schema/schema.h \
    core/schema/schemaerror.h \
    core/schema/typerules.h \
    core/app.h \
    core/configurations.h \
    core/handlerfunctor.h \
#    core/mongohandler.h \
#    core/mongomodel.h \
    http/utility/httprequestheaders.h \
    http/utility/httpresponseheaders.h \
    http/utility/httpstatuscodes.h \
    http/httpconnectionhandler.h \
    http/httpconnectionhandlerpool.h \
    http/httpcookie.h \
    http/httpglobal.h \
    http/httplistener.h \
    http/httprequest.h \
    http/httprequesthandler.h \
    http/httpresponse.h \
    http/httpsession.h \
    http/httpsessionstore.h \
    http/staticfilecontroller.h \
    PushServer/pushblacklist.h \
    PushServer/pushbroadcaster.h \
    PushServer/pushclient.h \
    PushServer/pushconnection.h \
    PushServer/pushconnectionhandler.h \
    PushServer/pushdata.h \
    PushServer/pushdataprovider.h \
    PushServer/pushmessage.h \
    PushServer/pushmessageHandler.h \
    PushServer/pushmonitor.h \
    PushServer/pushrouter.h \
    PushServer/pushserver.h \
    rest/commandsbase.h \
    rest/entitybase.h \
    rest/entityjsonbase.h \
    rest/restfulhandler.h \
    router/gateway.h \
    router/internalrouter.h \
    router/pattern.h \
    router/routed.h \
    router/router.h \
#    utility/chance/chance.h \
#    utility/chance/chancedata.h \
    utility/uuid/uuid.hpp \
    utility/configi.h \
    utility/databaseconnectionpool.h \
    utility/globals.h \
    utility/resourcelink.h \
    PushServer/pushhandshake.h \
    PushServer/pusher.h \
    PushServer/pushchannel.h \
    core/middleware/middleware.h \
    core/middleware/cors.h \
    utility/jwt.h \
    core/authintication/tokenauthenticator.h \
    utility/jws.h \
    core/authintication/jwtauthenticator.h \
    core/modules/user.h \
    rest/entityreader.h \
    rest/fieldcommands.h \
    rest/paginationoptions.h \
    rest/searchoptions.h \
    router/route.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

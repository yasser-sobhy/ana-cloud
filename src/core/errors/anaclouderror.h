#ifndef ANASERROR_H
#define ANASERROR_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "AnaCloud/http/httpresponse.h"
#include "AnaCloud/http/utility/httpstatuscodes.h"

// every error is recommended to be associated with an HTTP status code to be compatible with it
class AnasError
{

public:

    AnasError(){}
    AnasError(QByteArray message, QByteArray type, QByteArray code, HttpStatusCode httpCode){

        m_message = message;
        m_type = type;
        m_code = code;
        m_httpcode = httpCode;
    }
    ~AnasError(){}

    void setMessage(QByteArray p_message){
        m_message = p_message;
    }

    void setCode(QByteArray p_code){
        m_code = p_code;
    }

    void setType(QByteArray p_type){
        m_type = p_type;
    }

    void setHttpCode(HttpStatusCode p_code){
        m_httpcode = p_code;
    }

    QByteArray message(){return m_message;}
    QByteArray type(){return m_type;}
    QByteArray code(){return m_code;}
    HttpStatusCode httpCode(){return m_httpcode;}

    QJsonDocument json(){

        QJsonDocument json;
        QJsonObject maino;
        QJsonObject o;

        // if errors are categorized and this error has a type, add it to error
        if(!m_type.isEmpty()) o.insert("type",QJsonValue(m_type.data()));
        o.insert("code", QJsonValue(m_code.data()));
        o.insert("message", QJsonValue(m_message.data()));

        maino.insert("error", QJsonValue(o));

        json.setObject(maino);

        return json;
    }

    void response(HttpResponse& p_response){

        p_response.setHeader("Content-Type", "");
        p_response.setStatus(m_httpcode.code, m_httpcode.message);
        p_response.write(json().toJson(), true);
        return;
    }

private:
    QByteArray m_message;
    QByteArray m_code; // application specific code, usually used in app docs
    QByteArray m_type; // used if you are going to put your errors into categories
    HttpStatusCode m_httpcode = HttpStatusCodes::OK;

    QByteArray m_docLink;
};

#endif // ANASERROR_H

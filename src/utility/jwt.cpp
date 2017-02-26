#include "jwt.h"
#include <QDebug>

QJsonObject Jwt::m_defaultHeader;

Jwt::Jwt()
{
    // create the header with default algorithm
    m_header.insert("typ", QJsonValue("JWT") );
    m_header.insert("alg", QJsonValue(m_options.algorithm));

    m_defaultHeader = m_header;
}

Jwt::Jwt(const Jwt &other)
{
    this->m_options = other.m_options;
    this->m_header  = other.m_header;
    this->m_payload = other.m_payload;
}

bool Jwt::verify(QByteArray token, QByteArray secret, JwtVerifyOptions options){

    if(token.isEmpty()) return false;

    if(! Jws::verify(token, secret, options.algorithm) ) return false;

    Jws jws;
    jws.decode(token);

    QJsonParseError header_error, payload_error;

    QJsonDocument header = QJsonDocument::fromJson(jws.header(), &header_error);
    QJsonDocument payload = QJsonDocument::fromJson(jws.payload(), &payload_error);

    if(header_error.error != QJsonParseError::NoError || payload_error.error != QJsonParseError::NoError) return false;
    if(!header.isObject() || !payload.isObject()) return false;

    QJsonObject header_obj = header.object(), payload_obj = payload.object();

    if(!validatePayload( &header_obj, &options)) return false;
    if(!validateHeader( &payload_obj, &options)) return false;

    // success
    return true;
}

QByteArray Jwt::sign(QByteArray header, QByteArray payload, QByteArray secret, JwtOptions &options){

    // all options are ignored expect for options.algorithm
    return Jws::sign(header, payload, secret, options.algorithm);
}

QByteArray Jwt::sign(QByteArray payload, QByteArray secret, JwtOptions options){

    // all options are ignored expect for options.algorithm
    QByteArray header = QJsonDocument(m_defaultHeader).toJson(QJsonDocument::Compact);
    return Jws::sign(header, payload, secret, options.algorithm);
}

QByteArray Jwt::sign(QJsonObject header, QJsonObject payload, QByteArray secret, JwtOptions &options){

    preparePayload(&payload, &options);
    QByteArray _header = QJsonDocument(header).toJson(QJsonDocument::Compact);
    QByteArray _payload = QJsonDocument(payload).toJson(QJsonDocument::Compact);

    return Jws::sign(_header, _payload, secret, options.algorithm);
}

QByteArray Jwt::sign(QJsonObject payload, QByteArray secret, JwtOptions &options){

    preparePayload(&payload, &options);
    QByteArray _header = QJsonDocument(m_defaultHeader).toJson(QJsonDocument::Compact);
    QByteArray _payload = QJsonDocument(payload).toJson(QJsonDocument::Compact);

    return Jws::sign(_header, _payload, secret, options.algorithm);
}

QByteArray Jwt::sign(QByteArray secret, JwtOptions options){

    preparePayload(&m_payload, &m_options);
    QByteArray header = QJsonDocument(m_header).toJson(QJsonDocument::Compact);
    QByteArray payload = QJsonDocument(m_payload).toJson(QJsonDocument::Compact);

    return Jws::sign(header, payload, secret, options.algorithm);
}


QJsonObject &Jwt::header()
{
    return m_header;
}

bool Jwt::setHeader(QJsonObject header)
{
    if (header.isEmpty()) return false;

    // check if supported algorithm
    QString algorithm = header.value("alg").toString();
    if (!supportedAlgorithms().contains(algorithm)) return false;

    m_header = header;
    return true;
}

bool Jwt::setHeader(QByteArray header)
{
    QJsonParseError error;
    QJsonDocument tmpHeader = QJsonDocument::fromJson(header, &error);

    // validate and set header
    if (error.error != QJsonParseError::NoError || !tmpHeader.isObject() || !setHeader(tmpHeader.object())) return false;

    return true;
}


QJsonObject &Jwt::payload()
{
    return m_payload;
}

bool Jwt::setPayload(QJsonObject &payload)
{
    //allow empty payloads
   // if (payload.isEmpty()) return false;

    m_payload = payload;
    return true;
}

bool Jwt::setPayload(QByteArray payload)
{
    QJsonParseError error;
    QJsonDocument tmpPayload = QJsonDocument::fromJson(payload, &error);

    // validate and set payload
    if (error.error != QJsonParseError::NoError || !tmpPayload.isObject()) return false;

    QJsonObject obj = tmpPayload.object();
    if(!setPayload(obj)) return false;

    return true;
}


void Jwt::appendClaim(QString claimType, QString value)
{
    m_payload.insert(claimType, value);
}

void Jwt::removeClaim(QString claimType)
{
    m_payload.remove(claimType);
}

void Jwt::preparePayload(QJsonObject *payload, JwtOptions *options){

    if(!payload || !options) return;

    if( !options->issuer.isEmpty() )
        payload->insert("iss", QJsonValue(options->issuer));
    if( !options->subject.isEmpty() )
        payload->insert("sub", QJsonValue(options->subject));
    if( !options->audience.isEmpty() )
        payload->insert("aud", QJsonValue(options->audience));

    if(!options->noTimestamp){

        if(options->issuedAt.isValid())
            payload->insert("iat", QJsonValue(options->issuedAt.toMSecsSinceEpoch()));
        else
            payload->insert("iat", QJsonValue(QDateTime::currentDateTime().toMSecsSinceEpoch()));
    }
    else payload->remove("iat");

    if(options->expiresIn.isValid())
        payload->insert("exp", QJsonValue(options->expiresIn.toMSecsSinceEpoch()));

    if(options->notBefore.isValid())
        payload->insert("nbf", QJsonValue(options->notBefore.toMSecsSinceEpoch()));

    if(!options->jwtid.isEmpty())
        payload->insert("jti", QJsonValue(options->jwtid));
}

bool Jwt::validatePayload(QJsonObject *payload, JwtVerifyOptions *options){

    if(!payload || !options) return false;

    if( !options->issuer.isEmpty() ) if( payload->value("iss").toString() != options->issuer) return false;
    if( !options->subject.isEmpty() ) if( payload->value("sub").toString() != options->subject) return false;
    if( !options->audience.isEmpty() ) if( payload->value("aud").toString() != options->audience) return false;
    if( !options->jwtid.isEmpty() ) if( payload->value("jti").toString() != options->jwtid) return false;

    if(options->maxAge > 0){

        if(!payload->contains("iat")) return false;

        qint64 iat = payload->value("iat").toInt();
        QDateTime iat_time = QDateTime::fromMSecsSinceEpoch(iat);

        if(iat_time > QDateTime::currentDateTime()) return false;

        if(QDateTime::currentDateTime().msecsTo(iat_time) < -options->maxAge) return false;
    }

    if(options->notBefore.isValid()){

        if(!payload->contains("nbf")) return false;

        qint64 nbf = payload->value("nbf").toInt();
        QDateTime nbf_time = QDateTime::fromMSecsSinceEpoch(nbf);

        if(nbf_time < QDateTime::currentDateTime()) return false;
    }

    if(options->expiresIn.isValid()){

        if(!payload->contains("exp")) return false;

        qint64 exp = payload->value("exp").toInt();
        QDateTime exp_time = QDateTime::fromMSecsSinceEpoch(exp);

        if(exp_time < QDateTime::currentDateTime()) return false;
    }

    return true;
}

bool Jwt::validateHeader(QJsonObject *header, JwtVerifyOptions *options){

    if(!header || !options) return false;

    if(!header->contains("typ") || header->value("typ").toString() != "JWT") return false;
    if(!header->contains("alg") || header->value("alg").toString() != options->algorithm) return false;

    return true;
}

QStringList Jwt::supportedAlgorithms()
{
    return Jws::supportedAlgorithms();
}


#ifndef JWT_H
#define JWT_H

#include <QObject>
#include <QMessageAuthenticationCode>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

#include "jws.h"

// Note: when using sign() method with header or payload of QByteArray type
// all options are ignored, if you  would like to include options in the payload
// use the QJsonDocument alternatives or QByteArray &sign(QByteArray secret) to use local header and payload

// Note: for the sake of speed QJsonWebToken doesn't validate options, so make sure to validate options yourself before passing it


struct JwtOptions {

    QString issuer;      //The issuer of the token
    QString subject;     // The subject of the token
    QString audience;    //The audience of the token

    QDateTime expiresIn;   //This will probably be the registered claim most often used. This will define the expiration in NumericDate value. The expiration MUST be after the current date/time.
    QDateTime notBefore;   //Defines the time before which the JWT MUST NOT be accepted for processing
    QDateTime issuedAt;    //The time the JWT was issued. Can be used to determine the age of the JWT

    QString jwtid;       //Unique

    QString algorithm = "HS256";
    bool noTimestamp = false;
};

struct JwtVerifyOptions : public JwtOptions {

    bool ignoreExpiration = false;
    bool ignoreNotBefore = false;
    qint64 maxAge = 0; // in millseconds
};

class Jwt
{
public:
    Jwt();

    Jwt(const Jwt &other);
    Jwt(QByteArray token, QByteArray secret, JwtOptions &options);

    static bool verify(QByteArray token, QByteArray secret, JwtVerifyOptions options = JwtVerifyOptions());

    static QByteArray sign(QByteArray header, QByteArray payload, QByteArray secret, JwtOptions &options);
    static QByteArray sign(QByteArray payload, QByteArray secret, JwtOptions options = JwtOptions()); // sign using local header

    static QByteArray sign(QJsonObject header, QJsonObject payload, QByteArray secret, JwtOptions &options);
    static QByteArray sign(QJsonObject payload, QByteArray secret, JwtOptions &options); // sign using local header

    QByteArray sign(QByteArray secret, JwtOptions options = JwtOptions()); // sign using local header and payload  && default options if not specified

    void appendClaim(QString claimType, QString value);
    void removeClaim(QString claimType);

    QJsonObject &header();
    bool setHeader(QJsonObject header);
    bool setHeader(QByteArray header);

    QJsonObject &payload();
    bool setPayload(QJsonObject &payload);
    bool setPayload(QByteArray payload);

    bool validateOptions(JwtOptions &options);
    static QStringList supportedAlgorithms();

private:
    // important: options' values replaces payload's values;
    static void preparePayload(QJsonObject *payload = nullptr, JwtOptions *options = nullptr);
    static bool validatePayload(QJsonObject *payload = nullptr, JwtVerifyOptions *options = nullptr);
    static bool validateHeader(QJsonObject *header = nullptr, JwtVerifyOptions *options = nullptr);

    JwtOptions  m_options;
    JwtVerifyOptions m_verify_options;

    QJsonObject m_header;
    QJsonObject m_payload;

    static QJsonObject m_defaultHeader;
};

#endif // JWT_H

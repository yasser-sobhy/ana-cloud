#ifndef JWTAUTHENTICATOR_H
#define JWTAUTHENTICATOR_H

#include <AnaCloud/utility/jwt.h>
#include <AnaCloud/core/middleware/middleware.h>
#include <AnaCloud/core/errors/anaclouderrors.h>
#include <QString>

typedef QByteArray (*GetTokenFunction)(HttpRequest& request);

class JwtAuthenticator : public Middleware
{

public:

    JwtAuthenticator(QByteArray secret, JwtVerifyOptions options);

    virtual void process(HttpRequest& request , HttpResponse& response);

    void setGetToken(GetTokenFunction function);

    static QByteArray fromHeader(HttpRequest& request);
    static QByteArray fromUrlQueryParameter(HttpRequest& request);
    static QByteArray fromUrlToken(HttpRequest& request);
    static QByteArray fromAuthHeader(HttpRequest& request);

private:
    QByteArray m_secret;
    JwtVerifyOptions m_options;
    GetTokenFunction getToken = &JwtAuthenticator::fromAuthHeader;
    AnasErrors anaError;
};

#endif // JWTAUTHENTICATOR_H

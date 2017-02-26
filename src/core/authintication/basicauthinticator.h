#ifndef BASICAUTHENTICATOR_H
#define BASICAUTHENTICATOR_H

#include <QByteArray>
#include <QString>

#include <AnaCloud/core/handlerfunctor.h>
#include "authenticatorbase.h"

class BasicAuthenticator
{
public:
    BasicAuthenticator();

    void addAuthenticator(AuthenticatorBase *authenticator);
    void removeAuthenticator(AuthenticatorBase *authenticator);

    void addPublicHandler(RequestHandler *handler);
    void removePublicHandler(RequestHandler *handler);

    void setTestMode(bool value);

    static QByteArrayList grapUser(QByteArray data);

    AuthUser *get(QByteArray credents, RequestHandler *handler);

private:
    QList<AuthenticatorBase *> authenticators;
    QList<RequestHandler *> publicHandlers;
    bool m_testMode;
};

#endif // BASICAUTHINTICATOR_H

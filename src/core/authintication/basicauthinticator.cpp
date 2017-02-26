#include "basicauthinticator.h"

BasicAuthenticator::BasicAuthenticator()
{

}

AuthUser *BasicAuthenticator::get(QByteArray credents, RequestHandler *handler){

    if(m_testMode)
    {
        AuthUser *user = new AuthUser();
        user->group = "*"; // set user group to public group
        return user;
    }

    // if the requested handler is a public handler
    // return an AuthUser with group set to *; which means a public group
    if(publicHandlers.contains(handler))
    {
        AuthUser *user = new AuthUser();
        user->group = "*"; // set user group to public group
        return user;
    }

    QByteArrayList d =  grapUser(credents);
    if(d.isEmpty()) return nullptr;

    // loop for all authenticators to find a user with provided credintials
    for(AuthenticatorBase *auth: authenticators)
    {
        AuthUser * user = auth->get(d[0], d[1]);

        // if found a user retun it, no need to lookup other authenticators
        if(user) return user;
    }

    // if no user found
    return nullptr;
}

void BasicAuthenticator::addAuthenticator(AuthenticatorBase *authenticator){

    if(authenticator) authenticators.append(authenticator);
}

void BasicAuthenticator::removeAuthenticator(AuthenticatorBase *authenticator){

    if(authenticator) authenticators.removeAll(authenticator);
}

void BasicAuthenticator::addPublicHandler(RequestHandler *handler){

    if(handler) publicHandlers.append(handler);
}

void BasicAuthenticator::removePublicHandler(RequestHandler *handler){

    if(handler) publicHandlers.removeAll(handler);
}


QByteArrayList BasicAuthenticator::grapUser(QByteArray data)
{
    data = data.trimmed().remove(0,6); // remove Basic

    // convert data from base64, then split username and password
    QByteArrayList d =  QByteArray::fromBase64(data).split(':');

    // there must be a username and a password
    if(d.length() != 2) return QByteArrayList();

    return d;
}

void BasicAuthenticator::setTestMode(bool value)
{
    m_testMode = value;
}

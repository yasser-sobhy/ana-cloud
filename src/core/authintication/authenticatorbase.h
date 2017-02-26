#ifndef AUTHENTICATORBASE_H
#define AUTHENTICATORBASE_H

#include <QByteArray>
#include <QList>

struct AuthUser
{
    QByteArray name;
    QByteArray password;
    QByteArray group;
};

class AuthenticatorBase
{
public:
    AuthenticatorBase(){}

    virtual AuthUser* get(QByteArray username, QByteArray password) = 0;
};

#endif // AUTHENTICATORBASE_H

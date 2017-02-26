#ifndef USER_H
#define USER_H

#include <QByteArray>

class User
{
public:
    User();

    virtual bool create(QByteArray data);
    virtual bool login(QByteArray data);
    virtual bool logout(QByteArray data);
    virtual bool isFound(QByteArray data);
    virtual bool resetPassword(QByteArray data);
};

#endif // USER_H

#ifndef ENTITYBASE_H
#define ENTITYBASE_H

#include <QByteArray>

class EntityBase
{
public:
    EntityBase(){}

public:

    virtual void setID(int id) = 0; // int based ID's
    virtual void setID(QByteArray uuid) = 0; // UUID based ID's

    virtual bool validate(bool /*isNew*/) {return true;}
};

#endif // ENTITYBASE_H

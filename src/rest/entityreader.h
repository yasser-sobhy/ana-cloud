#ifndef ENTITYREADER_H
#define ENTITYREADER_H

#include "entitybase.h"
#include <QSqlQuery>

class EntityReader
{
public:
    EntityReader();

    EntityBase *read(QSqlQuery &query);
    EntityBase *write(EntityBase *entity, QSqlQuery &query);
};

#endif // ENTITYREADER_H

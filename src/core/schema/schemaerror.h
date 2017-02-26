#ifndef SCHEMAERROR_H
#define SCHEMAERROR_H

#include <QString>

struct SchemaError
{
    enum Errors { NoError, Error };

    SchemaError(QString _valuename, QString _message, Errors _error = Error)
        : error(_error), valuename (_valuename), message (_message) {}


    Errors error = Error;

    QString valuename; // json value name
    QString message;
};

#endif // SCHEMAERROR_H

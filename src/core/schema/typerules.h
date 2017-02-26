#ifndef TYPERULES_H
#define TYPERULES_H

#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "../rule.h"

template <T>
class TypeRule : public Rule
{
public:

    TypeRule(QString tname){

        _tname = tname;
        errorMessage = QString("%1 must be of type %2");
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == T )
            return true;

        error = new SchemaError(valuename, errorMessage.arg(valuename, _tname));
        return false;
    }

private:
    QString _tname;
};

typedef TypeRule <QJsonValue::Null> Null("Null");
typedef TypeRule <QJsonValue::Double> Double("Double");
typedef TypeRule <QJsonValue::Bool> Boolean("Boolean");
typedef TypeRule <QJsonValue::String> String("String");
typedef TypeRule <QJsonValue::Object> Object("Object");
typedef TypeRule <QJsonValue::Array> Array("Array");
typedef TypeRule <QJsonValue::Undefined> Undefined("Undefined");


class Integer : public Rule
{
    Integer(){
        errorMessage = "%1 must be of integer";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() > 0 )
            return true;

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

#endif // TYPERULES_H

/****************************************************************************
**
** Copyright (C) 2016 Yasser Sobhy Saleh.
** Contact: yasser.sobhy.net@gmail.com
**          www.yasser-sobhy.com
**
** This file is part of the Core module of AnaCloud.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
****************************************************************************/

#ifndef RULES_H
#define RULES_H

#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QUuid>
#include <QUrl>
#include <QHostAddress>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimeZone>
#include <QRegularExpression>
#include <QLocale>
#include <QDebug>

#include "../rule.h"

class Required : public Rule
{
public:

    Required(){
        errorMessage = "%1 is required";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double || value.type() == QJsonValue::Bool )
            return true;

        if( value.type() == QJsonValue::String && !value.toString().isEmpty() )
            return true;

        if( value.type() == QJsonValue::Array && !value.toArray().isEmpty() )
            return true;

        if( value.type() == QJsonValue::Object && !value.toObject().isEmpty() )
            return true;

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

class Present : public Rule
{
public:

    Present(){
        errorMessage = "%1 is required";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() != QJsonValue::Undefined )
            return true;

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

class Max : public Rule
{
public:

    Max(int value) : max(value){}
    Max(double value) : max_double(value){}

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        // return true if the Rule is optional. i.e. bypass Rule if this value in not provided
        if( value.type() == QJsonValue::Undefined && optional )
            return true;

        if( value.type() == QJsonValue::Double && value.toInt() <= max )
            return true;

        if( value.type() == QJsonValue::Double && value.toDouble() <= max_double )
            return true;

        if( value.type() == QJsonValue::String && value.toString().size() <= max )
            return true;

        if( value.type() == QJsonValue::Array && value.toArray().size() <= max )
            return true;

        if( value.type() == QJsonValue::Object && value.toObject().keys().size() <= max )
            return true;

        errorMessage = messages[value.type()].arg(valuename, max);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    int max = 0;
    double max_double = 0.0;

    // error messages for every JSON type
    QHash <int, QString> messages[] = {
        QJsonValue::Null, QString(""),                                          /* null     N/A */
        QJsonValue::Bool, QString(""),                                          /* bool     N/A */
        QJsonValue::Double, QString("%1 must be less than %2"),              /* double       */
        QJsonValue::String, QString("%1 length must be less than %2"),          /* string       */
        QJsonValue::Object, QString("%1 keys count must be less than %2"),      /* object       */
        QJsonValue::Array, QString("%1 size must be less than %2"),             /* array        */
        QJsonValue::Undefined, QString("")                                      /* undefined N/A*/
    };
};

class Min : public Rule
{
public:

    Min(int value) : min(value){}
    Min(double value) : min_double(value){}

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() >= min )
            return true;

        if( value.type() == QJsonValue::Double && value.toDouble() >= min_double )
            return true;

        if( value.type() == QJsonValue::String && value.toString().size() >= min )
            return true;

        if( value.type() == QJsonValue::Array && value.toArray().size() >= min )
            return true;

        if( value.type() == QJsonValue::Object && value.toObject().keys().size() >= min )
            return true;

        errorMessage = messages[value.type()].arg(valuename, min);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    int min = 0;
    double min_double = 0.0;

    // error messages for every JSON type
    QHash <int, QString> messages[] = {
        QJsonValue::Null, QString(""),                                                  /* null     N/A */
        QJsonValue::Bool, QString(""),                                                  /* bool     N/A */
        QJsonValue::Double, QString("%1 must be greater than %2"),                   /* double       */
        QJsonValue::String, QString("%1 length must be greater than %2"),               /* string       */
        QJsonValue::Object, QString("%1 keys count must be greater than %2"),           /* object       */
        QJsonValue::Array, QString("%1 size must be greater than %2"),                  /* array        */
        QJsonValue::Undefined, QString("")                                              /* undefined N/A*/
    };
};

class Accepted : public Rule
{
public:

    Accepted(){}

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        bool success =  ((value.type() == QJsonValue::Double && value.toInt() == 1 )
                         || (value.type() == QJsonValue::Double && value.toDouble() == 1.0 )
                         || (value.type() == QJsonValue::Bool && value.toBool() == true )
                         || (value.type() == QJsonValue::String && truelist.contains(value.toString()))
                         );

        if(success) return true;

        errorMessage = messages[value.type()].arg(valuename, min);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:

    QStringList truelist = {"yes", "on", "1", "true"};

    // error messages for every JSON type
    QHash <int, QString> messages[] = {
        QJsonValue::Null, QString(),                                                    /* null     N/A */
        QJsonValue::Bool, QString("%1 must be true"),                                   /* bool         */
        QJsonValue::Double, QString("%1 is must be 1"),                                 /* double       */
        QJsonValue::String, QString("%1 length must be yes, on, true, or 1"),           /* string       */
        QJsonValue::Object, QString(),                                                  /* object   N/A */
        QJsonValue::Array, QString(),                                                   /* array    N/A */
        QJsonValue::Undefined, QString()                                                /* undefined N/A*/
    };
};

class Length : public Rule
{
public:

    Length(int value) : length(value){}

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String && value.toString().size()  == length )
            return true;

        if( value.type() == QJsonValue::Array && value.toArray().size()  == length )
            return true;

        if( value.type() == QJsonValue::Object && value.toObject().keys().size()  == length )
            return true;

        errorMessage = messages[value.type()].arg(valuename, length);

        error = new SchemaError(valuename, errorMessage);

        return false;
    }

private:
    int length = 0;

    // error messages for every JSON type
    QHash <int, QString> messages[] = {
        QJsonValue::Null, QString(""),                                                  /* null     N/A */
        QJsonValue::Bool, QString(""),                                                  /* bool     N/A */
        QJsonValue::Double, QString(),                                                  /* double       */
        QJsonValue::String, QString("%1 length must be %2"),                            /* string       */
        QJsonValue::Object, QString("%1 keys count must %2"),                           /* object       */
        QJsonValue::Array, QString("%1 size must be %2"),                               /* array        */
        QJsonValue::Undefined, QString("")                                              /* undefined N/A*/
    };
};

class LessThan : public Rule
{
public:

    LessThan(int value) : value_(value){}
    LessThan(double value) : value_double(value){}

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() < value_ )
            return true;

        if( value.type() == QJsonValue::Double && value.toDouble() < value_double )
            return true;

        if( value.type() == QJsonValue::String && value.toString().size() < value_ )
            return true;

        if( value.type() == QJsonValue::Array && value.toArray().size() < value_ )
            return true;

        if( value.type() == QJsonValue::Object && value.toObject().keys().size() < value_ )
            return true;

        errorMessage = messages[value.type()].arg(valuename, value_);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    int value_ = 0;
    double value_double = 0.0;

    // error messages for every JSON type
    QHash <int, QString> messages[] = {
        QJsonValue::Null, QString(""),                                                  /* null     N/A */
        QJsonValue::Bool, QString(""),                                                  /* bool     N/A */
        QJsonValue::Double, QString("%1 must be less than %2"),                   /* double       */
        QJsonValue::String, QString("%1 length must be less than %2"),               /* string       */
        QJsonValue::Object, QString("%1 keys count must be less than %2"),           /* object       */
        QJsonValue::Array, QString("%1 size must be less than %2"),                  /* array        */
        QJsonValue::Undefined, QString("")                                              /* undefined N/A*/
    };
};

class GreaterThan : public Rule
{
public:

    GreaterThan(int value) : value_(value){}
    GreaterThan(double value) : value_double(value){}

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() > value_ )
            return true;

        if( value.type() == QJsonValue::Double && value.toDouble() > value_double )
            return true;

        if( value.type() == QJsonValue::String && value.toString().size() > value_ )
            return true;

        if( value.type() == QJsonValue::Array && value.toArray().size() > value_ )
            return true;

        if( value.type() == QJsonValue::Object && value.toObject().keys().size() > value_ )
            return true;

        errorMessage = messages[value.type()].arg(valuename, value_);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    int value_ = 0;
    double value_double = 0.0;

    // error messages for every JSON type
    QHash <int, QString> messages[] = {
        QJsonValue::Null, QString(""),                                                  /* null     N/A */
        QJsonValue::Bool, QString(""),                                                  /* bool     N/A */
        QJsonValue::Double, QString("%1 must be greater than %2"),                   /* double       */
        QJsonValue::String, QString("%1 length must be greater than %2"),               /* string       */
        QJsonValue::Object, QString("%1 keys count must be greater than %2"),           /* object       */
        QJsonValue::Array, QString("%1 size must be greater than %2"),                  /* array        */
        QJsonValue::Undefined, QString("")                                              /* undefined N/A*/
    };
};

class Positive : public Rule
{
public:

    Positive(){
        errorMessage = "%1 must be positive";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() >= 0 )
            return true;

        if( value.type() == QJsonValue::Double && value.toDouble() >= 0.0 )
            return true;

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

class Negative : public Rule
{
public:

    Negative(){
        errorMessage = "%1 must be negative";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() < 0 )
            return true;

        if( value.type() == QJsonValue::Double && value.toDouble() < 0.0 )
            return true;

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

class Between : public Rule
{
public:

    Between(int min, int max) : min_(min), max_(max){}
    Between(double min, double max) : min_double(min), max_double(max){}

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() >= min_ && value.toInt() <= max_ )
            return true;

        if( value.type() == QJsonValue::Double && value.toDouble() >= min_double && value.toDouble() <= max_double  )
            return true;

        if( value.type() == QJsonValue::String && value.toString().size() >= min_ && value.toString().size() <= max_  )
            return true;

        if( value.type() == QJsonValue::Array && value.toArray().size() >= min_ && value.toArray().size() <= max_  )
            return true;

        if( value.type() == QJsonValue::Object && value.toObject().keys().size() >= min_ && value.toObject().keys().size() <= max_  )
            return true;

        errorMessage = messages[value.type()].arg(valuename, min, max);

        error = new SchemaError(valuename, errorMessage);

        return false;
    }

private:
    int min_, max_ = 0;
    double min_double, max_double = 0.0;

    // error messages for every JSON type
    QHash <int, QString> messages[] = {
        QJsonValue::Null, QString(""),                                                        /* null     N/A */
        QJsonValue::Bool, QString(""),                                                        /* bool     N/A */
        QJsonValue::Double, QString("%1 is must be between %2 and %3"),                       /* double       */
        QJsonValue::String, QString("%1 length must be between %2 and %3"),                   /* string       */
        QJsonValue::Object, QString("%1 keys count must be between %2 and %3"),               /* object       */
        QJsonValue::Array, QString("%1 size must be between %2 and %3"),                      /* array        */
        QJsonValue::Undefined, QString("")                                                    /* undefined N/A*/
    };
};

// Object and Array types aren't supported
class Equals : public Rule
{
public:

    Equals(QString other) : other_(other){
        errorMessage = "%1 and %2 must be equall";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        QJsonValue other_value = obj.value(other_);

        if(value.type() == other_value.type()){

            // both values are null or undefined, so they are equal
            if( value.type() == QJsonValue::Null || value.type() == QJsonValue::Undefined) return true;

            if( value.type() == QJsonValue::Double ){

                if(value.toDouble() == other_value.toDouble())
                    return true;
            }

            if( value.type() == QJsonValue::Bool ){

                if(value.toBool() == other_value.toBool())
                    return true;
            }

            if( value.type() == QJsonValue::String ){

                if(value.toString() == other_value.toString())
                    return true;
            }
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename, other_));
        return false;
    }

private:
    QString other_;
};

// Object and Array types aren't supported
class NotEquals : public Rule
{
public:

    NotEquals(QString other) : other_(other){
        errorMessage = "%1 and %2 must be different";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        QJsonValue other_value = obj.value(other_);

        // types are different, return true
        if(value.type() != other_value.type())
            return true;

        if( value.type() == QJsonValue::Double ){

            if(value.toDouble() != other_value.toDouble())
                return true;
        }

        if( value.type() == QJsonValue::Bool ){

            if(value.toBool() != other_value.toBool())
                return true;
        }

        if( value.type() == QJsonValue::String ){

            if(value.toString() != other_value.toString())
                return true;
        }


        error = new SchemaError(valuename, errorMessage.arg(valuename, other_));
        return false;
    }

private:
    QString other_;
};

class Uuid : public Rule
{
public:

    Uuid(){
        errorMessage = "%1 is not a valid uuid";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if(value.type() == QJsonValue::String){
            QUuid uuid(value.toString());
            if(!uuid.isNull()) return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

class Url : public Rule
{
public:

    Url(){
        errorMessage = "%1 is not a valid url";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if(value.type() == QJsonValue::String){
            QUrl url(value.toString(), QUrl::StrictMode);
            if(url.isValid()) return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

class IP : public Rule
{
public:

    IP(){
        errorMessage = "%1 is not a valid IP address";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if(value.type() == QJsonValue::String){
            QHostAddress addr(value.toString());
            if(!addr.isNull()) return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

class Date : public Rule
{
public:

    Date(QString format = "dd/MM/yyyy"): format_(format){
        errorMessage = "%1 is not a valid date";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if(value.type() == QJsonValue::String){
            QDate date =  QDate::fromString(value.toString(),format_);
            if(date.isValid()) return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QString format_;
};

class Time : public Rule
{
public:

    Time(QString format = "hh:mm:ss"): format_(format){
        errorMessage = "%1 is not a valid time";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if(value.type() == QJsonValue::String){
            QTime time =  QTime::fromString(value.toString(),format_);
            if(time.isValid()) return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QString format_;
};

class DateTime : public Rule
{
public:

    DateTime(QString format = "dd/MM/yyyy hh:mm:ss"): format_(format){
        errorMessage = "%1 is not a valid datetime";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if(value.type() == QJsonValue::String){
            QDateTime dt =  QDateTime::fromString(value.toString(),format_);
            if(dt.isValid()) return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QString format_;
};

class TimeZone : public Rule
{
public:

    TimeZone(){
        errorMessage = "%1 is not a valid time zone";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if(value.type() == QJsonValue::String){
            QTimeZone tz(value.toString());
            if(tz.isValid()) return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

class After : public Rule
{
public:

    After(QString datetime, QString format = "dd/MM/yyyy hh:mm:ss"): format_(format), dt(QDateTime(datetime)){

        if(!dt.isValid()) qCritical() << "AnaSchema, invalid date/time was provided to After rule:" << datetime;
        errorMessage = "%1 must be after %2";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if(value.type() == QJsonValue::String){
            QDateTime value_dt =  QDateTime::fromString(value.toString(),format_);

            if( value_dt > dt) return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename, dt.toString(format_)));
        return false;
    }

private:
    QDateTime dt;
    QString format_;
};

class Before : public Rule
{
public:

    Before(QString datetime, QString format = "dd/MM/yyyy hh:mm:ss"): format_(format), dt(QDateTime(datetime)){

        if(!dt.isValid()) qCritical() << "AnaSchema, invalid date/time was provided to Before rule:" << datetime;
        errorMessage = "%1 must be before %2";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if(value.type() == QJsonValue::String){
            QDateTime value_dt =  QDateTime::fromString(value.toString(),format_);

            if( value_dt < dt) return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename, dt.toString(format_)));
        return false;
    }

private:
    QDateTime dt;
    QString format_;
};

class Numeric : public Rule
{
public:

    Numeric(){
        errorMessage = "%1 must be numeric";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if(value.type() == QJsonValue::Double)
            return true;

        if(value.type() == QJsonValue::String){

            bool ok;
            QLocale().toDouble(value.toString(), &ok); // using system locale
            if(ok) return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

class Pattern : public Rule
{
public:

    Pattern(QString pattern, QRegularExpression::PatternOptions opt = QRegularExpression::NoPatternOption,
            QRegularExpression::MatchType mtype = QRegularExpression::NormalMatch,
            QRegularExpression::MatchOptions moptions = QRegularExpression::NoMatchOption){

        ptrn = QRegularExpression( QRegularExpression::escape(pattern), opt );

        if(!ptrn.isValid()) qCritical() << "invalid pattern was provided to Pattern rule" << pattern;

        mopt = moptions;
        mtyp = mtype;
        ptrn.optimize();

        errorMessage = "%1 is invalid";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String ){

            if(ptrn.match(value.toString(), 0, mtyp, mopt).hasMatch())
                return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QRegularExpression ptrn;
    QRegularExpression::MatchOptions mopt;
    QRegularExpression::MatchType mtyp;
};

template<class T>
class In : public Rule
{
public:

    In(QVector<T> values) : values_(values){
        errorMessage = "%1 is not valid";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && values_.contains(value.toInt()))
            return true;

        if( value.type() == QJsonValue::Double && values_.contains(value.toDouble()) )
            return true;

        if( value.type() == QJsonValue::String && values_.contains(value.toString()) )
            return true;

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QVector<T> values_;
};

template<class T>
class NotIn : public Rule
{
public:

    In(QVector<T> values) : values_(values){
        errorMessage = "%1 is not valid";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && !values_.contains(value.toInt()))
            return true;

        if( value.type() == QJsonValue::Double && !values_.contains(value.toDouble()) )
            return true;

        if( value.type() == QJsonValue::String && !values_.contains(value.toString()) )
            return true;

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QVector<T> values_;
};

class Contains : public Rule
{
public:

    Contains(QString value) : value_(value){

        if(value.isEmpty()) qCritical() << "empty string provided to Contains rule";
        errorMessage = "%1 must contain %2";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String && value.toString().contains(value_) )
            return true;

        if( value.type() == QJsonValue::Array && value.toArray().contains(QJsonValue(value_)) )
            return true;

        if( value.type() == QJsonValue::Object && value.toObject().contains(value_) )
            return true;

        errorMessage = messages[value.type()].arg(valuename, value_);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    QString value_;
};

class NotContains : public Rule
{
public:

    NotContains(QString value) : value_(value){

        if(value.isEmpty()) qCritical() << "empty string provided to Contains rule";
        errorMessage = "%1 must not contain %2";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String && !value.toString().contains(value_) )
            return true;

        if( value.type() == QJsonValue::Array && !value.toArray().contains(QJsonValue(value_)) )
            return true;

        if( value.type() == QJsonValue::Object && !value.toObject().contains(value_) )
            return true;

        errorMessage = messages[value.type()].arg(valuename, value_);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    QString value_ = 0;
};

class NotEmpty : public Rule
{
public:

    NotEmpty(){
        errorMessage = "%1 can't be empty";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String && !value.toString().isEmpty() )
            return true;

        if( value.type() == QJsonValue::Array && !value.toArray().isEmpty() )
            return true;

        if( value.type() == QJsonValue::Object && !value.toObject().isEmpty() )
            return true;

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }
};

class Digits : public Rule
{
public:

    Digits(int value) : value_(value){

        if(value <= 0) qCritical() << "invalid argument was provided to Digits rule" << value;

        errorMessage = "%1 must be %2 digits";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() > 0 )
        {
            int len = 0;
            for(;i; i/=10 ) len++;

            if(len == value )
                return true;
        }

        errorMessage = errorMessage.arg(valuename, value);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    int value = 0;
};

class MinDigits : public Rule
{
public:

    MinDigits(int min) : min_(min){

        if(min <= 0) qCritical() << "invalid argument was provided to MinDigits rule" << min;

        errorMessage = "%1 must be %2 digits min";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() > 0 )
        {
            int len = 0;
            for(;i; i/=10 ) len++;

            if(len > min_ )
                return true;
        }

        errorMessage = errorMessage.arg(valuename, min_);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    int min_ = 0;
};

class MaxDigits : public Rule
{
public:

    MaxDigits(int max) : max_(max){

        if(max <= 0) qCritical() << "invalid argument was provided to MaxDigits rule" << max;

        errorMessage = "%1 must be %2 digits max";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() > 0 )
        {
            int len = 0;
            for(;i; i/=10 ) len++;

            if(len < max_ )
                return true;
        }

        errorMessage = errorMessage.arg(valuename, max_);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    int max_ = 0;
};

class DigitsBetween : public Rule
{
public:

    DigitsBetween(int min, int max) : max_(max){

        if(min <=0 || max <= 0) qCritical() << "invalid argument was provided to DigitsBetween rule" << min << max;

        errorMessage = "%1 must be between %2 and %3";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::Double && value.toInt() > 0 )
        {
            int len = 0;
            for(;i; i/=10 ) len++;

            if(len >  min_ && len < max_ )
                return true;
        }

        errorMessage = errorMessage.arg(valuename, min_, max_);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    int min_, max_;
};

class EMail : public Rule
{
public:

    EMail(){

        ptrn = QRegularExpression(QRegularExpression::escape("[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])"),
                                  QRegularExpression::CaseInsensitiveOption);
        ptrn.optimize();

        errorMessage = "%1 is not a valid email";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String ){

            if(ptrn.match(value.toString()).hasMatch())
                return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QRegularExpression ptrn;
};

class Phone : public Rule
{
    Phone(){

        ptrn = QRegularExpression(QRegularExpression::escape("\+(9[976]\d|8[987530]\d|6[987]\d|5[90]\d|42\d|3[875]\d|"
                                                             "2[98654321]\d|9[8543210]|8[6421]|6[6543210]|5[87654321]|"
                                                             "4[987654310]|3[9643210]|2[70]|7|1)\d{1,14}$"),
                                  QRegularExpression::CaseInsensitiveOption);
        ptrn.optimize();

        errorMessage = "%1 is not a valid phone number";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String ){

            if(ptrn.match(value.toString()).hasMatch())
                return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QRegularExpression ptrn;
};

// cards may not be OR'ed
class CreditCard : public Rule
{
public:
    enum CreditCardType {
        AmexCard, BCGlobal, CarteBlancheCard, DinersClubCard,
        DiscoverCard, InstaPaymentCard, JCBCard, KoreanLocalCard,
        LaserCard,MaestroCard, Mastercard, SoloCard, SwitchCard,
        UnionPayCard, VisaCard, Any
    };

    CreditCard(CreditCardType type = Any){

        type_ = type;

        if(type != Any){

            ptrn = QRegularExpression(QRegularExpression::escape(cards[type]),
                                      QRegularExpression::CaseInsensitiveOption);
            ptrn.optimize();
        }

        errorMessage = "%1 is not a valid credit card";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String ){

            if(type_ != Any){
                if(ptrn.match(value.toString()).hasMatch())
                    return true;
            }
            else { // if Any, try to find a valid card
                for(CreditCardType t : cards){

                    ptrn = QRegularExpression(QRegularExpression::escape(cards[t]), QRegularExpression::CaseInsensitiveOption);
                    if(ptrn.match(value.toString()).hasMatch())
                        return true;
                }
            }
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QRegularExpression ptrn;
    CreditCardType type_;

    QHash<CreditCardType, QString> cards = {
        AmexCard , "^3[47][0-9]{13}$",
        BCGlobal , "^(6541|6556)[0-9]{12}$",
        CarteBlancheCard , "^389[0-9]{11}$",
        DinersClubCard , "^3(?:0[0-5]|[68][0-9])[0-9]{11}$",
        DiscoverCard , "^65[4-9][0-9]{13}|64[4-9][0-9]{13}|6011[0-9]{12}|(622(?:12[6-9]|1[3-9][0-9]|[2-8][0-9][0-9]|9[01][0-9]|92[0-5])[0-9]{10})$",
        InstaPaymentCard , "^63[7-9][0-9]{13}$",
        JCBCard , "^(?:2131|1800|35\d{3})\d{11}$",
        KoreanLocalCard , "^9[0-9]{15}$",
        LaserCard , "^(6304|6706|6709|6771)[0-9]{12,15}$",
        MaestroCard = "^(5018|5020|5038|6304|6759|6761|6763)[0-9]{8,15}$",
        Mastercard , "^5[1-5][0-9]{14}$",
        SoloCard , "^(6334|6767)[0-9]{12}|(6334|6767)[0-9]{14}|(6334|6767)[0-9]{15}$",
        SwitchCard , "^(4903|4905|4911|4936|6333|6759)[0-9]{12}|(4903|4905|4911|4936|6333|6759)[0-9]{14}|(4903|4905|4911|4936|6333|6759)[0-9]{15}|564182[0-9]{10}|564182[0-9]{12}|564182[0-9]{13}|633110[0-9]{10}|633110[0-9]{12}|633110[0-9]{13}$",
        UnionPayCard , "^(62[0-9]{14,17})$",
        VisaCard , "^4[0-9]{12}(?:[0-9]{3})?$"};
};

class Alpha : public Rule
{
public:

    Alpha(bool en_only){

        if(en_only)
            ptrn = QRegularExpression(QRegularExpression::escape("/^[A-Za-z]+$/"), QRegularExpression::CaseInsensitiveOption);
        else
            ptrn = QRegularExpression(QRegularExpression::escape("\A\pL+\z"), QRegularExpression::CaseInsensitiveOption);

        ptrn.optimize();

        errorMessage = "%1 can only contain alphabetic characters";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String ){

            if(ptrn.match(value.toString()).hasMatch())
                return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QRegularExpression ptrn;
};

class AlphaNumeric : public Rule
{
public:

    AlphaNumeric(bool en_only){

        if(en_only)
            ptrn = QRegularExpression(QRegularExpression::escape("^[a-zA-Z0-9]*$"), QRegularExpression::CaseInsensitiveOption);
        else /////********************??
            ptrn = QRegularExpression(QRegularExpression::escape("\A\pL+\z"), QRegularExpression::CaseInsensitiveOption);

        ptrn.optimize();

        errorMessage = "%1 can only contain alpha-numeric characters";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String ){

            if(ptrn.match(value.toString()).hasMatch())
                return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QRegularExpression ptrn;
};

class Slug : public Rule
{
public:

    Slug(bool en_only){

        if(en_only)
            ptrn = QRegularExpression(QRegularExpression::escape("/^[a-z0-9](-?[a-z0-9_]+)*$/i"), QRegularExpression::CaseInsensitiveOption);
        else /////********************??
            ptrn = QRegularExpression(QRegularExpression::escape("\A\pL+\z"), QRegularExpression::CaseInsensitiveOption);

        ptrn.optimize();

        errorMessage = "%1 can only contain alpha-numeric, - or _ characters";
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String ){

            if(ptrn.match(value.toString()).hasMatch())
                return true;
        }

        error = new SchemaError(valuename, errorMessage.arg(valuename));
        return false;
    }

private:
    QRegularExpression ptrn;
};

class Password : public Rule
{
public:
    enum PasswordStrength{
        _8_num, // Minimum 8 characters at least 1 Alphabet and 1 Number
        _8_num_special, // Minimum 8 characters at least 1 Alphabet, 1 Number and 1 Special Character
        _8_upper_lower_num, // Minimum 8 characters at least 1 Uppercase Alphabet, 1 Lowercase Alphabet and 1 Number
        _8_upper_lower_num_special // Minimum 8 characters at least 1 Uppercase Alphabet, 1 Lowercase Alphabet, 1 Number and 1 Special Character
    };

    Password(PasswordStrength strength = _8_num){

        strength_ = strength;
        ptrn = QRegularExpression(QRegularExpression::escape(strengths[strength]), QRegularExpression::CaseInsensitiveOption);
        ptrn.optimize();
    }

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString &valuename, SchemaError *error){

        if( value.type() == QJsonValue::String ){

            if(ptrn.match(value.toString()).hasMatch())
                return true;
        }

        errorMessage = messages[strength_].arg(valuename);
        error = new SchemaError(valuename, errorMessage);
        return false;
    }

private:
    QRegularExpression ptrn;
    PasswordStrength strength_;

    QHash<int, QString> strengths = {
        _8_num, "^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$",
        _8_num_special, "^(?=.*[A-Za-z])(?=.*\d)(?=.*[$@$!%*#?&])[A-Za-z\d$@$!%*#?&]{8,}$",
        _8_upper_lower_num, "^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d]{8,}$",
        _8_upper_lower_num_special,"^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[$@$!%*?&])[A-Za-z\d$@$!%*?&]{8,}"
    };

    QHash<int, QString> messages = {
        _8_num, "%1 can only contain alpha-numeric characters",
        _8_num_special, "%1 can only contain alpha-numeric, and any of [$ @ $ ! % * # ? &] characters",
        _8_upper_lower_num, "%1 can only contain alpha-numeric characters, and must contain at least one uppercase letter and one lowercase letter",
        _8_upper_lower_num_special,"%1 can only contain alpha-numeric characters, and any of [$ @ $ ! % * # ? &], and must contain at least one uppercase letter and one lowercase letter"
    };
};

typedef Length Size;
typedef Equals Same;
typedef Between Range;

#endif // RULES_H

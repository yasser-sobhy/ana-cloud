#ifndef RESOURCELINK_H
#define RESOURCELINK_H

#include <QByteArray>
#include <QJsonObject>
#include <QJsonValue>

class ResourceLink
{
public:

    ResourceLink(){}

    ResourceLink(QByteArray href, QByteArray rel, QByteArray method){
        m_href = href;
        m_rel = rel;
        m_method =  method;
    }

    ~ResourceLink(){}

    QByteArray href(){
        return m_href;
    }

    QByteArray rel(){
        return m_rel;
    }

    QByteArray method(){
        return m_method;
    }

    QJsonObject jsonObject(){

        QJsonObject o;
        o.insert("href", QJsonValue(m_href.data()));
        o.insert("rel", QJsonValue(m_rel.data()));
        o.insert("method", QJsonValue(m_method.data()));

        return o;
    }

private:
    QByteArray m_href; //link to resource
    QByteArray m_rel; //relation to resource
    QByteArray m_method; //supported method
};

#endif // RESOURCELINK_H

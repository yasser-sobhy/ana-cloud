#ifndef ROUTED_H
#define ROUTED_H

#include <QHash>

template <class T>
class Routed
{
public:
    Routed(T *p_handler, QHash<QByteArray, QByteArray> *p_params, QByteArray p_path, bool p_notFound, QByteArrayList p_roles = {} ){
        handler = p_handler;
        params = p_params;
        notFound = p_notFound;
        path = p_path;
        roles = p_roles;
    }

    Routed(T *p_handler, QHash<QByteArray, QByteArray> *p_params, bool p_notFound, QByteArray p_tokensPath){
        handler = p_handler;
        params = p_params;
        notFound = p_notFound;
        tokensPath = p_tokensPath;
    }

    ~Routed(){
        // don't delete hanlder, managing handlers is done outside Router
        // only delete params associated with this Routed
        if(params) delete params;
    }

    T *handler = nullptr;
    QHash<QByteArray, QByteArray> *params;
    bool notFound = false;
    QByteArray path; // original non-routed path
    QByteArray method;
    QByteArray tokensPath;
    QByteArrayList roles; // list of user roles allowed om this route
};

#endif // ROUTED_H

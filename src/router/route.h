#ifndef ROUTE_H
#define ROUTE_H


class Route
{
public:
    Route();

    Route(T *p_handler, QByteArray p_method, QByteArray p_path, QByteArrayList p_roles = {} ){
        handler = p_handler;
        method = p_method;
        path = p_path;
        roles = p_roles;
    }

    ~Route(){
    }

    T *handler = nullptr;
    QByteArray path; // original non-routed path
    QByteArray method;
    QByteArrayList roles; // list of user roles allowed om this route
};

#endif // ROUTE_H

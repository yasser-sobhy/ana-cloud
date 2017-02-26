#ifndef HANDLERFUNCTOR_H
#define HANDLERFUNCTOR_H

#include "AnaCloud/http/httprequesthandler.h"

class HttpRequestHandler;

template <class T> class HandlerFunctor : public HttpRequestHandler
{
    typedef void (T::*ServiceFunction)(HttpRequest& request, HttpResponse& response);

public:
    HandlerFunctor(T *ptr2object, ServiceFunction func){
        m_ptr2object = ptr2object;
        m_ptr2func = func;
    }

    void service(HttpRequest &request, HttpResponse &response){
        (*m_ptr2object.*m_ptr2func)(request, response);
    }

private:
    T *m_ptr2object; // pointer to handler
    void (T::*m_ptr2func)(HttpRequest &request, HttpResponse &response); // pointer to service function
};

// to make code more readable
typedef HandlerFunctor<HttpRequestHandler> RequestHandler;
//serviceFun used to cast function pointer
typedef void (HttpRequestHandler::*serviceFun)(HttpRequest& request, HttpResponse& response);


#endif // HANDLERFUNCTOR_H

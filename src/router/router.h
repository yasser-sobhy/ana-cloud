#ifndef ROUTER_H
#define ROUTER_H

#include "routed.h"
#include "pattern.h"
#include "internalrouter.h"

#include <QList>
#include <QHash>

/**
  Router is a C++ library that can route paths to handlers and create paths from a handler

  <p>
  Router paths can use only two tokens:
    :tokenname : where <i>tokenname</i> is any meaningful and URL compatible name
        examples: "/articles/:id" -> "/articles/123"
                 "/articles/users/:username" -> "/articles/users/yasser-sobhy"
                 "/articles/:cat/list" -> "/articles/tech/list"

    :* : matches any values; and must be the last token in path
        examples: "/download/:*" matches "/download/file1.tar"
                  "/download/:*" matches "/download/files/foo/bar.tar"
  </p>

  <p>
  methods: can be any thing, but usually these are  HTTP methods (GET, PUT, POST, DELETE) and so on, you can use HttpRequest.getMethod()
  </p>

  <p>
  handlers: can be of any type but usually these are pointer to a handler that can service HTTP requests
  </p>

  <p>
  handler priority: a handler can have one of three priorities
                    1- High: which is matched first, use addFirstHandler(...) to a handler with high priority
                    1- Medium: (default) which is matched if no high priority handler found for a path, use addHandler(...) to a handler with medium priority
                    1- Low: which is matched if no high nor medium priority handler found for a path , use addLastHandler(...) to a handler with low priority
 </p>

  <p>
  Router is a C++ version of Jauter: a Java Router that has all functionality supported by Router
  </p>

  <p>
  Jauter is a Java library that can route paths to targets and create paths from targets and params (reverse routing).

  This library is tiny, without additional dependencies, and is intended for use together with an HTTP server side library. If you want to use with Netty, see Netty-Router and Sinetja.
  </p>

*/

template <class T, class M> class Router
{
public:

    /** Constructor */
    Router(){
        m_notFoundHandler = 0;
        m_anyMethodFirstRouter = new InternalRouter<T>();
        m_anyMethodMiddleRouter = new InternalRouter<T>();
        m_anyMethodLastRouter = new InternalRouter<T>();
    }

    /** destructor */
    ~Router(){}

    /**
     * add a middle handler to Router
     * @param p_method which method should p_handler assigned to, this usually will be a HTTP method e.g GET. If p_method is empty, p_handler will be a generic handler that handle all requests with empty methods
     * @param p_path the path p_handler will be assigned to, example: "/articles/users/:username" -> "/articles/users/yasser-sobhy"
     * @param p_handler a T type handler that services requests on p_path
     * @warning if p_handler is a pointer, Router only removes it from it's internal handlers , it doesn't delete them, it's your responsibility to delete it
*/
    void addHandler(M p_method, QByteArray p_path, T * p_handler){

        getMiddleRouter(p_method)->addHandler(p_path, p_handler);
    }

    /**
     * add a first handler to Router
     * @param p_method which method should p_handler assigned to, this usually will be a HTTP method e.g GET. If p_method is empty, p_handler will be a generic handler that handle all requests with empty methods
     * @param p_path the path p_handler will be assigned to, example: "/articles/users/:username" -> "/articles/users/yasser-sobhy"
     * @param p_handler a T type handler that services requests on p_path
     * @warning if p_handler is a pointer, Router only removes it from it's internal handlers , it doesn't delete them, it's your responsibility to delete it
*/
    void addFirstHandler(M p_method, QByteArray p_path, T * p_handler){

        getFirstRouter(p_method)->addHandler(p_path, p_handler);
    }

    /**
     * add a last handler to Router
     * @param p_method which method should p_handler assigned to, this usually will be a HTTP methid e.g GET. If p_method is empty, p_handler will be a generic handler that handle all requests with empty methods
     * @param p_path the path p_handler will be assigned to, example: "/articles/users/:username" -> "/articles/users/yasser-sobhy"
     * @param p_handler a T type handler that services requests on p_path
     * @warning if p_handler is a pointer, Router only removes it from it's internal handlers , it doesn't delete them, it's your responsibility to delete it
*/
    void addLastHandler(M p_method, QByteArray p_path, T * p_handler){

        getLastRouter(p_method)->addHandler(p_path, p_handler);
    }

    /**
     * add a handler to Router, p_handler will service requests with wrong path, path that is not found in Router
     * @param p_handler a T type handler that services requests on p_path
*/
    void setNotFoundHandler(T * p_handler){

        if(p_handler) m_notFoundHandler = p_handler;
    }

    /**
     * routes a path to a handler and returns a Routed object with a proper handler and params found in p_path
     * @param p_method method of this path, usually a HTTP method e.g GET
     * @param p_path a path to parse, extract : and :* tokens, and pass to a handler
*/
    Routed<T> * route(M p_method, QByteArray p_path){

        qDebug("routing: %s", p_path.data());

        Routed<T> *routed =  getFirstRouter(p_method)->route(p_path);
        if(routed) return routed;

        routed =  getMiddleRouter(p_method)->route(p_path);
        if(routed) return routed;

        routed =  getLastRouter(p_method)->route(p_path);
        if(routed) return routed;

        if(m_notFoundHandler)return new Routed<T>(m_notFoundHandler, new QHash<QByteArray, QByteArray>(), "", true);

        return 0;
    }

    /**
     * @overload
     * creates a path from handler with : and :* tokens replaced by values in params
     * @param p_method method of this handler, usually a HTTP method e.g GET
     * @param p_handler a handler to create path from
     * @param params params to be included in path, params are separated by "," colon
     * @see path
*/
    QByteArray path(M p_method, T *p_handler, QByteArray params){

        // only one delimiter to speed up splitting and parsing
        QList<QByteArray> itemsList = params.split(',');
        QHash<QByteArray,QByteArray> prms;

        if(itemsList.length() < 2) return QByteArray();
        if(itemsList.length() % 2  != 0) return QByteArray();

        for(int i = 0; i < itemsList.size(); i += 2){
            prms.insert(itemsList[i], itemsList[i+1]);
        }

        return path(p_method, p_handler, prms);
    }

    /**
     * @overload
     * creates a path from handler with : and :* tokens replaced by values in params
     * @param p_method method of this handler, usually a HTTP method e.g GET
     * @param p_handler a handler to create path from
     * @param params params to be included in path
*/
    QByteArray path(M p_method, T *p_handler, QHash<QByteArray, QByteArray> params){

        QByteArray path =  getFirstRouter(p_method)->path(p_handler, params);
        if(!path.isEmpty()) return path;

        path =  getMiddleRouter(p_method)->path(p_handler, params);
        if(!path.isEmpty()) return path;

        return  getLastRouter(p_method)->path(p_handler, params);
    }

    /**
     * removes a handler from Router, be careful, Router only removes handler from it's internal handlers , it doesn't delete them, if p_handler is a pointer it's your responsibility to delete it
     * @param p_handler a handler to remove
*/
    void removeHandler(T * p_handler){

        if(!p_handler) return;

        for (InternalRouter<T> * rtr: m_firstRouters.values()) {
            rtr->removeHandler(p_handler);
        }

        for (InternalRouter<T> * rtr: m_middleRouters.values()) {
            rtr->removeHandler(p_handler);
        }

        for (InternalRouter<T> * rtr: m_lastRouters.values()) {
            rtr->removeHandler(p_handler);
        }

        m_anyMethodFirstRouter->removeHandler(p_handler);
        m_anyMethodMiddleRouter->removeHandler(p_handler);
        m_anyMethodLastRouter->removeHandler(p_handler);
    }

    /**
     * removes a path from Router
     * @param p_path a path to remove
*/
    void removePath(QByteArray p_path){

        for (InternalRouter<T> * rtr: m_firstRouters.values()) {
            rtr->removePath(p_path);
        }

        for (InternalRouter<T> * rtr: m_middleRouters.values()) {
            rtr->removePath(p_path);
        }

        for (InternalRouter<T> * rtr: m_lastRouters.values()) {
            rtr->removePath(p_path);
        }

        m_anyMethodFirstRouter->removePath(p_path);
        m_anyMethodMiddleRouter->removePath(p_path);
        m_anyMethodLastRouter->removePath(p_path);
    }

private:
    InternalRouter<T> *getFirstRouter(M p_method){

        if(p_method.isEmpty()) return m_anyMethodFirstRouter;

        if(m_firstRouters.contains(p_method))
            return m_firstRouters.value(p_method);
        else {
            InternalRouter<T> *rtr = new InternalRouter<T>();
            m_firstRouters.insert(p_method, rtr);
            return rtr;
        }
    }

    InternalRouter<T> *getMiddleRouter(M p_method){

        if(p_method.isEmpty()) return m_anyMethodMiddleRouter;

        if(m_middleRouters.contains(p_method))
            return m_middleRouters.value(p_method);
        else {
            InternalRouter<T> *rtr = new InternalRouter<T>();
            m_middleRouters.insert(p_method, rtr);
            return rtr;
        }
    }

    InternalRouter<T> *getLastRouter(M p_method){

        if(p_method.isEmpty()) return m_anyMethodLastRouter;

        if(m_lastRouters.contains(p_method))
            return m_lastRouters.value(p_method);
        else {
            InternalRouter<T> *rtr = new InternalRouter<T>();
            m_lastRouters.insert(p_method, rtr);
            return rtr;
        }
    }

    // to create path from handler
    QHash<M, InternalRouter<T> *> m_firstRouters;
    QHash<M, InternalRouter<T> *> m_middleRouters;
    QHash<M, InternalRouter<T> *> m_lastRouters;

    InternalRouter<T>  *m_anyMethodFirstRouter;
    InternalRouter<T>  *m_anyMethodMiddleRouter;
    InternalRouter<T>  *m_anyMethodLastRouter;

    T *m_notFoundHandler;

};

#endif // ROUTER_H

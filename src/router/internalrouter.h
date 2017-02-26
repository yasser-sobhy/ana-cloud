#ifndef INTERNALROUTER_H
#define INTERNALROUTER_H

#include "pattern.h"
#include "routed.h"
#include <QList>
#include <QHash>

#include "route.h"

template <class T>
class InternalRouter
{
public:

    InternalRouter(){}
    ~InternalRouter(){}

    // every pattern is added to m_PatternList used in route() function to route a path
    // and to m_handlerPatterns used in path() function to create path for a handler
    void addRoute(Route route){

        if(!p_handler) return;

        QByteArray path = Pattern<T>::removeSlash(p_path);
        // add a new pattern to method's patterns
        Pattern<T> *newPattern = new Pattern<T>(path,p_handler);
        m_PatternList.append(newPattern);

        /*---------------------------------------------------*/
        // get pattern list for this handler to append a new pattern to
        QList<Pattern<T> *> *patternList;
        // map every handler to its own patterns
        //if p_handler already exist add pattern list to its pattern list
        if(m_handlerPatterns.contains(p_handler)){
            patternList = m_handlerPatterns.value(p_handler);
            patternList->append(newPattern);
        }
        // else add handler and its pattern to m_handlerPatterns
        else{
            patternList = new QList<Pattern<T> *>();
            patternList->append(newPattern);
            m_handlerPatterns.insert(p_handler, patternList);
        }


    }

    Routed<T> * route(QByteArray p_path){

        QList<QByteArray> pathTokens  = Pattern<T>::removeSlash(p_path).split('/');
        QHash<QByteArray, QByteArray> *params  = new QHash<QByteArray, QByteArray>();

        bool matched = true;

        foreach (Pattern<T> *ptrn, m_PatternList) {
            const QList<QByteArray> currTokens = ptrn->tokens();
            T *handler = ptrn->handler();

            matched = true;
            params->clear();

            // mach URI tokens and : tokens
            if (pathTokens.length() == currTokens.length()) {
                for (int i = 0; i < currTokens.length(); i++) {
                    const QByteArray token = pathTokens[i];
                    const QByteArray currToken = currTokens[i];

                    if (currToken.length() > 0 && currToken[0] == ':') {
                        params->insert(currToken.mid(1), token);
                    } else if (currToken != token) {
                        matched = false;
                        break;
                    }
                }
                // mach :* tokens
            } else if (currTokens.length() > 0 && currTokens[currTokens.length() - 1] == ":*" && pathTokens.length() >= currTokens.length()) {
                for (int i = 0; i < currTokens.length() - 1; i++) {
                    const QByteArray token = pathTokens[i];
                    const QByteArray currToken = currTokens[i];

                    if (currToken.length() > 0 && currToken[0] == ':') {
                        params->insert(currToken.mid(1), token);
                    } else if (token !=token ) {
                        matched = false;
                        break;
                    }
                }

                // add :* token to params
                if (matched) {
                    QByteArray t;
                    t.append(pathTokens[currTokens.length() - 1]);
                    for (int i = currTokens.length(); i < pathTokens.length(); i++) {
                        t.append('/');
                        t.append(pathTokens[i]);
                    }
                    params->insert("*", t);
                }
            } else {
                matched = false;
            }

            // if matched return the handler found and its params
            if (matched) {
                return new Routed<T>(handler, params, ptrn->path(), false);
            }

        }

        // if no mach found, return null pointer
        return 0;
    }

    QByteArray path(T *p_handler, QHash<QByteArray, QByteArray> params){

        if(!p_handler) return QByteArray();

        QList<Pattern<T> *> *ptrnList = m_handlerPatterns.value(p_handler);
        if (!ptrnList) return QByteArray();

        // The best one is the one with minimum number of params in the query
        QByteArray bestCandidate;
        int minQueryParams = 10000;

        bool matched = true;
        QList<QByteArray> usedKeys; // keys indicated as : tokens

        foreach (Pattern<T> *ptrn , *ptrnList) {
            matched = true;
            usedKeys.clear();

            QByteArray path;
            foreach (QByteArray token , ptrn->tokens()) {
                path.append('/');

                if (token.length() > 0 && token[0] == ':') {
                    QByteArray key   = token.mid(1);
                    QByteArray value = params.value(key);
                    // if token is not found in params, so it's a wrong pattern
                    if (value == "") {
                        matched = false;
                        break; // exit loop
                    }
                    // append key as : or :* tokens
                    usedKeys.append(key);
                    path.append(value); // append value of that token
                    // if not : token, then it's normal URI token
                } else {
                    path.append(token);
                }
            }

            // if a proper pattern was found
            if (matched) {
                int numQueryParams = params.size() - usedKeys.size(); // discard : tokens
                if (numQueryParams < minQueryParams) { // if query params is less than previous query params
                    if (numQueryParams > 0) { // if there is any params

                        bool firstQueryParam = true;
                        foreach (QByteArray key , params.keys()) {
                            if (!usedKeys.contains(key)) { // is this param isn't : or :* token
                                if (firstQueryParam) {
                                    path.append('?');
                                    firstQueryParam = false;
                                } else {
                                    path.append('&');
                                }

                                QByteArray value = params.value(key);
                                // no URL encode here, it's handled by HttpRequest & HttpResponse
                                path.append(key);
                                path.append('=');
                                path.append(value);
                            }
                        }
                    }

                    bestCandidate  = path;
                    minQueryParams = numQueryParams;
                }
            }
        }

        return bestCandidate;
    }

    void removeHandler(T * p_handler){

        if(!p_handler) return;

        // delete this handler from m_methodPatternMap
        typename QList<Pattern<T>*>::iterator begin = m_PatternList.begin();
        typename QList<Pattern<T>*>::iterator end =  m_PatternList.end();

        while(begin != end){
            if((*begin)->handler() == p_handler){

                // don't delete handler, managing handlers is done outside Router. Since API 1.2
                // delete handler pointer
                //if((*begin)->handler()) delete (*begin)->handler();

                // delete pattern itself
                if((*begin)) delete (*begin);

                //remove pattern from patternList
                m_PatternList.erase(begin);
            }

            begin++;
        }


        // don't delete handler, managing handlers is done outside Router. Since API 1.2
        // only remove it from m_handlerPatterns
        if(m_handlerPatterns.contains(p_handler)){
            m_handlerPatterns.remove(p_handler);
        }
    }

    void removePath(QByteArray p_path){

        QByteArray path = Pattern<T>::removeSlash(p_path);

        removePatternByPath(path, &m_PatternList);

        foreach (QList<Pattern<T>*> * plist, m_handlerPatterns.values()) {
            removePatternByPath(path, plist);
        }
    }


private:
    void removePatternByPath(QByteArray p_path, QList<Pattern<T> *> *p_patternList){
        if(!p_patternList) return;

        typename QList<Pattern<T> *>::iterator begin = p_patternList->begin();
        typename QList<Pattern<T> *>::iterator end =  p_patternList->end();

        while(begin != end){
            if((*begin)->path() == p_path){

                // don't delete handler, managing handlers is done outside Router. Since API 1.2
                // delete handler pointer
                //if((*begin)->handler()) delete (*begin)->handler();

                // delete pattern itself
                if((*begin)) delete (*begin);

                //remove pattern from patternList
                p_patternList->erase(begin);

            }

            begin++;
        }
    }

private:

    // to create path from handler
    QHash<T *, QList<Pattern<T> *>* > m_handlerPatterns;

    // to route paths to their handlers
    QList<Pattern<T> *> m_PatternList;

};

#endif // INTERNALROUTER_H

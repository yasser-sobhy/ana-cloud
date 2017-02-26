/* ************************************************************************
 * Copyright (c) 2016 Yasser Sobhy <yasser.sobhy.net@gmail.com> *
 *                                                                        *
 * This file is part of QtWebApp                                          *
 *                                                                        *
 * QtWebApp is free software: you can redistribute it and/or modify       *
 * it under the terms of the GNU Lesser General Public License as published by   *
 * the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                    *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                   *
 * See the GNU General Public License for more details.                   *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.   *
 * ********************************************************************** */

#ifndef GATEWAY_H
#define GATEWAY_H

#include <QByteArray>
#include <QHash>

#include "router.h"
#include "routed.h"
#include <AnaCloud/core/authintication/basicauthinticator.h>

template <class T, class M> class Gateway
{
public:
    Gateway(Router<T, M> *p_router){
        m_router = p_router;
    }

    ~Gateway(){}

    void addGate(T *p_handler, QByteArray p_userGroups){

        // user groups must be separated with colon, and must not contains any whitespaces before or after it
        if(p_handler) m_handlers.insert(p_handler, p_userGroups.split(','));
    }

    void removeGate(T *p_handler){

        if(p_handler) m_handlers.remove(p_handler);
    }

    Routed<T> *route(HttpRequest& request, HttpResponse& response){

        // we must route path first to make sure that the resource exists
        // before granting or revoking access to it, because we can't deny access
        // to something that doesn't exist
        Routed<T> *routed = m_router->route(request.getMethod(), request.getPath());

        // if path exists
        if(routed){

            routed->method = request.getMethod();

            AuthUser *user = basicAuthenticator->get(request.getHeader("Authorization"), routed->handler);

            if(!user){ // if no user found with provided credintials

                // if access denied handler was set, replace routed's handler
                if(m_accessdeniedhandler)
                    routed->handler = m_accessdeniedhandler;

                return routed;
            }

            qDebug() << "user found";

            // ***** manage permissions ****************
            // if m_handlers contaons routed handler
            if(m_handlers.contains(routed->handler)){

                // if user.group is in handler groups
                if(m_handlers[routed->handler].contains(user->group) || user->group == "*")
                {
                    delete user;
                    return routed; // return routed handler
                }
                else // user.group is not in handler groups
                {
                    qDebug() << "invalid user group found";

                    delete user;
                    // if access denied handler was set
                    if(m_accessdeniedhandler)
                        routed->handler = m_accessdeniedhandler;

                    return routed;
                }
            }
        }
        else //if no routed found
        {
            //Gateway will return nullptr in two cases:
            // 1- if no handler matched in router and no notFoundHandler was set
            // 2- if handler is matched but isn't added to gateway
            return nullptr;
        }
    }

    void setAccessDeniedHandler(T *p_handler){

        if(p_handler) m_accessdeniedhandler = p_handler;
    }
    void setBasicAuthenticator(BasicAuthenticator *authenticator){
        basicAuthenticator = authenticator;
    }

private:
    // map every handler to its user groups
    QHash<T *, QByteArrayList> m_handlers;

    BasicAuthenticator *basicAuthenticator;
    Router<T, M> *m_router = nullptr;
    T *m_accessdeniedhandler = nullptr;
};

#endif // GATEWAY_H

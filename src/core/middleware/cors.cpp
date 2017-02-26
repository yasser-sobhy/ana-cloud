#include "cors.h"

Cors::Cors()
{

}

void Cors::process(HttpRequest &request, HttpResponse &response){

    next = true; // continue by default

    // origin
    QByteArray origin = request.getHeader("Origin");
    if(allowedOrigins.contains(origin) || allowAllOrigins){

        if (allowAllOrigins)
            response.setHeader("Access-Control-Allow-Origin", "*");

        if(!allowedOrigins.isEmpty())
            response.setHeader("Access-Control-Allow-Origin", allowedOrigins.join(","));
    }

    // credentials
    if(credentials)
        response.setHeader("Access-Control-Allow-Credentials", "true");

    // expose headers
    if(!exposeHeaders.isEmpty())
        response.setHeader("Access-Control-Expose-Headers", exposeHeaders.join(","));

    if(request.getMethod() == "OPTIONS"){

        // methods
        if(!allowedMethods.isEmpty())
            response.setHeader("Access-Control-Allow-Methods", allowedMethods.join(","));

        //headers
        QByteArray newHeadrs;

        if(!allowedHeaders.isEmpty())
            newHeadrs = allowedHeaders.join(",");
        else  // if headers wasn't specified, re-write the request headers
            newHeadrs = request.getHeaders("Access-Control-Request-Headers").join(",");

        if(!newHeadrs.isEmpty())
            response.setHeader("Access-Control-Allow-Headers", newHeadrs);

        // max age
        if(!maxAge.isEmpty())
            response.setHeader("Access-Control-Max-Age", maxAge);

        response.setStatus(successStatus.code, successStatus.message);

        if(!preflightContinue) next = false;
    }
}

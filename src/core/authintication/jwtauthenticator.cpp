#include "jwtauthenticator.h"

JwtAuthenticator::JwtAuthenticator(QByteArray secret, JwtVerifyOptions options)
{
    name = "JwtAuthenticator";
    m_secret = secret;
    m_options = options;
}

void JwtAuthenticator::process(HttpRequest &request, HttpResponse &response){

    next = false; // by default don't preoceed

    QByteArray token  = getToken(request);

    if(token.isEmpty()) {
        anaError.Unauthorized.response(response);
        return;
    }

    if(!Jwt::verify(token, m_secret, m_options)){
        anaError.Unauthorized.response(response);
        return;
    }

    // token is valid, continue handling request
    next = true;
}

void JwtAuthenticator::setGetToken(GetTokenFunction function){

    getToken = function;
}

QByteArray JwtAuthenticator::fromHeader(HttpRequest& request){
    return request.getHeader("s");
}

QByteArray JwtAuthenticator::fromUrlQueryParameter(HttpRequest& request){
 return request.getParameter("");
}

QByteArray JwtAuthenticator::fromUrlToken(HttpRequest& request){
    return request.getTokenValue("sf");
}

QByteArray JwtAuthenticator::fromAuthHeader(HttpRequest& request){
    return request.getHeader("Authorization");
}

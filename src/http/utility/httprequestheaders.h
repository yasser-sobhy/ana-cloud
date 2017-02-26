#ifndef HTTPREQUESTHEADERS_H
#define HTTPREQUESTHEADERS_H

#include <QByteArray>

class HttpRequestHeaders
{
public:
    HttpRequestHeaders(){}
    ~HttpRequestHeaders(){}

    QByteArray Accept = "Accept";
    QByteArray AcceptCharset = "Accept-Charset";
    QByteArray AcceptEncoding = "Accept-Encoding";
    QByteArray AcceptLanguage = "Accept-Language";
    QByteArray AcceptDatetime = "Accept-Datetime";
    QByteArray Authorization = "Authorization";
    QByteArray CacheControl = "Cache-Control";
    QByteArray Connection = "Connection";
    QByteArray Cookie = "Cookie";
    QByteArray ContentLength = "Content-Length";
    QByteArray ContentMD5 = "Content-MD5";
    QByteArray ContentType = "Content-Type";
    QByteArray Date = "Date";
    QByteArray Expect = "Expect";
    QByteArray From = "From";
    QByteArray Host = "Host";
    QByteArray IfMatch = "If-Match";
    QByteArray IfModifiedSince = "If-Modified-Since";
    QByteArray IfNoneMatch = "If-None-Match";
    QByteArray IfRange = "If-Range";
    QByteArray IfUnmodifiedSince = "If-Unmodified-Since";
    QByteArray MaxForwards = "Max-Forwards";
    QByteArray Origin = "Origin";
    QByteArray Pragma = "Pragma";
    QByteArray ProxyAuthorization = "Proxy-Authorization";
    QByteArray Range = " Range";
    QByteArray Referer = "Referer";
    QByteArray TE = "TE";
    QByteArray UserAgent = "User-Agent";
    QByteArray Upgrade = "Upgrade";
    QByteArray Via = "Via";
    QByteArray Warning = "Warning";
};

#endif // HTTPREQUESTHEADERS_H

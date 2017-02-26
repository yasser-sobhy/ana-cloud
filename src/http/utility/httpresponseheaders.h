#ifndef HTTPRESPONSEHEADERS_H
#define HTTPRESPONSEHEADERS_H

#include <QByteArray>

class HttpResponseHeaders
{
public:
    HttpResponseHeaders(){}
    ~HttpResponseHeaders(){}

    QByteArray AccessControlAllowOrigin = "Access-Control-Allow-Origin";
    QByteArray AcceptPatch = "Accept-Patch";
    QByteArray AcceptRanges = "Accept-Ranges";
    QByteArray Age = "Age";
    QByteArray Allow = "Allow";
    QByteArray CacheControl = "Cache-Control";
    QByteArray Connection = "Connection";
    QByteArray ContentDisposition = "Content-Disposition";
    QByteArray ContentEncoding = "Content-Encoding";
    QByteArray ContentLanguage = "Content-Language";
    QByteArray ContentLength = "Content-Length";
    QByteArray ContentLocation = "Content-Location";
    QByteArray ContentMD5 = "Content-MD5";
    QByteArray ContentRange = "Content-Range";
    QByteArray ContentType = "Content-Type";
    QByteArray Date = "Date";
    QByteArray ETag = "ETag";
    QByteArray Expires = "Expires";
    QByteArray LastModified = "Last-Modified";
    QByteArray Link = "Link";
    QByteArray P3P = "P3P";
    QByteArray Pragma = "Pragma";
    QByteArray ProxyAuthenticate = "Proxy-Authenticate";
    QByteArray PublicKeyPins = "Public-Key-Pins";
    QByteArray Refresh = "Refresh";
    QByteArray RetryAfter = "Retry-After";
    QByteArray Server = "Server";
    QByteArray SetCookie = "Set-Cookie";
    QByteArray Status = "Status";
    QByteArray StrictTransportSecurity = "Strict-Transport-Security";
    QByteArray Trailer = "Trailer";
    QByteArray TransferEncoding = "Transfer-Encoding";
    QByteArray Upgrade = "Upgrade";
    QByteArray Vary = "Vary";
    QByteArray Via = "Via";
    QByteArray Warning = "Warning";
    QByteArray WWWAuthenticate = "WWW-Authenticate";
    QByteArray XFrameOptions = "X-Frame-Options";
};

#endif // HTTPRESPONSEHEADERS_H

#ifndef HTTPSTATUSCODES
#define HTTPSTATUSCODES

#include <QByteArray>

struct HttpStatusCode{

    HttpStatusCode(){}
    HttpStatusCode(int p_code, QByteArray p_message){

       code = p_code;
       message = p_message;
    }
    int code = 0;
    QByteArray message = "zTest Message";
};

class HttpStatusCodes{

public:

    HttpStatusCodes(){}
    ~HttpStatusCodes(){}

    // *** 1xx Informational *** //
    static HttpStatusCode Continue ;
    static HttpStatusCode SwitchingProtocols;
    static HttpStatusCode Processing;
    // *** 2xx Success *** //
    static HttpStatusCode OK ;
    static HttpStatusCode Created;
    static HttpStatusCode Accepted;
    static HttpStatusCode NonAuthoritativeInformation;
    static HttpStatusCode NoContent;
    static HttpStatusCode ResetContent;
    static HttpStatusCode PartialContent;
    static HttpStatusCode MultiStatus;
    static HttpStatusCode AlreadyReported;
    static HttpStatusCode IMUsed;

    // *** 3xx Redirection *** //
    static HttpStatusCode MultipleChoices;
    static HttpStatusCode MovedPermanently;
    static HttpStatusCode Found;
    static HttpStatusCode SeeOther;
    static HttpStatusCode NotModified;
    static HttpStatusCode UseProxy;
    static HttpStatusCode SwitchProxy;
    static HttpStatusCode TemporaryRedirect;
    static HttpStatusCode PermanentRedirect;
    static HttpStatusCode ResumeIncomplete;

    // *** 4xx Client Error *** //
    static HttpStatusCode BadRequest;
    static HttpStatusCode Unauthorized;
    static HttpStatusCode PaymentRequired;
    static HttpStatusCode Forbidden;
    static HttpStatusCode NotFound;
    static HttpStatusCode MethodNotAllowed;
    static HttpStatusCode NotAcceptable;
    static HttpStatusCode ProxyAuthenticationRequired;
    static HttpStatusCode RequestTimeout;
    static HttpStatusCode Conflict;
    static HttpStatusCode Gone;
    static HttpStatusCode LengthRequired;
    static HttpStatusCode PreconditionFailed;
    static HttpStatusCode PayloadTooLarge;
    static HttpStatusCode RequestURITooLong;
    static HttpStatusCode UnsupportedMediaType;
    static HttpStatusCode RequestedRangeNotSatisfiable;
    static HttpStatusCode ExpectationFailed;
    static HttpStatusCode ImTeapot;
    static HttpStatusCode AuthenticatioTimeout;
    //static HttpStatusCode MethodFailure;
    //static HttpStatusCode EnhanceYourCalm;
    static HttpStatusCode MisdirectedRequest;
    static HttpStatusCode UnprocessableEntity;
    static HttpStatusCode Locked;
    static HttpStatusCode FailedDependency;
    static HttpStatusCode UpgradeRequired;
    static HttpStatusCode PreconditionRequired;
    static HttpStatusCode TooManyRequests;
    static HttpStatusCode RequestHeaderFieldsTooLarge;
    static HttpStatusCode LoginTimeout;
    static HttpStatusCode NoResponse;
    static HttpStatusCode RetryWith;
    static HttpStatusCode BlockedByWindowsParentalControls;
    static HttpStatusCode UnavailableForLegalReasons;
    //static HttpStatusCode Redirect;
    static HttpStatusCode RequestHeaderTooLarge;
    static HttpStatusCode CertError;
    static HttpStatusCode NoCert;
    static HttpStatusCode HTTPToHTTPS;
    static HttpStatusCode TokenExpired;
    static HttpStatusCode ClientClosedRequest;
    //static HttpStatusCode TokenRequired;

    // *** 5xx Server Error *** //
    static HttpStatusCode InternalServerError;
    static HttpStatusCode NotImplemented;
    static HttpStatusCode BadGateway;
    static HttpStatusCode ServiceUnavailable;
    static HttpStatusCode GatewayTimeout;
    static HttpStatusCode HTTPVersionNotSupported;
    static HttpStatusCode VariantAlsoNegotiates;
    static HttpStatusCode InsufficientStorage;
    static HttpStatusCode LoopDetected;
    static HttpStatusCode BandwidthLimitExceeded;
    static HttpStatusCode NotExtended;
    static HttpStatusCode NetworkAuthenticationRequired;
    static HttpStatusCode UnknownError;
    static HttpStatusCode OriginConnectionTimeout;
    static HttpStatusCode NetworkReadTimeout;
    static HttpStatusCode NetworkConnectTimeout;
};

#endif // HTTPSTATUSCODES


#ifndef ANASERRORS_H
#define ANASERRORS_H


#include "anaclouderror.h"
#include "AnaCloud/http/utility/httpstatuscodes.h"

class AnasErrors
{

public:
    AnasErrors(){}
    ~AnasErrors(){}

    // error codes that is compatible with HTTP must have the same error code of the HTTP status code

    //******** 2xx Success ********

    AnasError NoContent = AnasError(
                "NoContent","HTTP", "5",HttpStatusCodes::NoContent);

    //******** 3xx Redirection *********

    AnasError MovedPermanently = AnasError(
                "NoContent","HTTP", "301",HttpStatusCodes::MovedPermanently);

    AnasError SeeOther = AnasError(
                "SeeOther","HTTP", "303",HttpStatusCodes::SeeOther);

    //******** 4xx Client Error **********

    AnasError badRequest = AnasError(
                "you have wrong values in you request","bad request", "400",HttpStatusCodes::BadRequest);

    AnasError Unauthorized = AnasError(
                "your method is'nt allowed on the resource","method not allowed", "401",HttpStatusCodes::Unauthorized);

    AnasError PaymentRequired = AnasError(
                "your method is'nt allowed on the resource","method not allowed", "402",HttpStatusCodes::PaymentRequired);

    AnasError Forbidden = AnasError(
                "your method is'nt allowed on the resource","method not allowed", "403",HttpStatusCodes::Forbidden);

    AnasError NotFound = AnasError(
                "Not Found","HTTP", "404",HttpStatusCodes::NotFound);

    AnasError methodNotAllowed = AnasError(
                "your method is'nt allowed on the resource","method not allowed", "405",HttpStatusCodes::MethodNotAllowed);

    AnasError NotAcceptable = AnasError(
                "NotAcceptable","HTTP", "406",HttpStatusCodes::NotAcceptable);

    AnasError ProxyAuthenticationRequired  = AnasError(
                "XXX","HTTP", "407",HttpStatusCodes::ProxyAuthenticationRequired);

    AnasError RequestTimeout = AnasError(
                "XXX","HTTP", "408",HttpStatusCodes::RequestTimeout);

    AnasError Conflict = AnasError(
                "XXX","HTTP", "409",HttpStatusCodes::Conflict);

    AnasError Gone = AnasError(
                "XXX","HTTP", "410",HttpStatusCodes::Gone);

    AnasError LengthRequired = AnasError(
                "XXX","HTTP", "411",HttpStatusCodes::LengthRequired);

    AnasError PreconditionFailed = AnasError(
                "XXX","HTTP", "412",HttpStatusCodes::PreconditionFailed);

    AnasError PayloadTooLarge = AnasError(
                "XXX","HTTP", "413",HttpStatusCodes::PayloadTooLarge);

    AnasError RequestURITooLong = AnasError(
                "XXX","HTTP", "414",HttpStatusCodes::RequestURITooLong);

    AnasError UnsupportedMediaType = AnasError(
                "UnsupportedMediaType","HTTP", "415",HttpStatusCodes::UnsupportedMediaType);

    AnasError AuthenticationTimeout = AnasError(
                "XXX","HTTP", "419",HttpStatusCodes::AuthenticatioTimeout);

    AnasError TooManyRequests = AnasError(
                "XXX","HTTP", "429",HttpStatusCodes::TooManyRequests);

    AnasError RequestHeaderFieldsTooLarge = AnasError(
                "XXX","HTTP", "431",HttpStatusCodes::RequestHeaderFieldsTooLarge);

    //************** 5xx Server Error **************

    AnasError InternalServerError = AnasError(
                "Internal Server Error","HTTP", "500",HttpStatusCodes::InternalServerError);

    AnasError NotImplemented = AnasError(
                "XXX","HTTP", "501",HttpStatusCodes::NotImplemented);

    AnasError BadGateway = AnasError(
                "XXX","HTTP", "502",HttpStatusCodes::BadGateway);

    AnasError ServiceUnavailable = AnasError(
                "XXX","HTTP", "503",HttpStatusCodes::ServiceUnavailable);

    AnasError GatewayTimeout = AnasError(
                "XXX","HTTP", "504",HttpStatusCodes::GatewayTimeout);

    AnasError HTTPVersionNotSupported = AnasError(
                "XXX","HTTP", "505",HttpStatusCodes::HTTPVersionNotSupported);
};

#endif // ANASERRORS_H

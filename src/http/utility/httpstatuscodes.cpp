#include "httpstatuscodes.h"

    // *** 1xx Informational *** //
    HttpStatusCode HttpStatusCodes::Continue = HttpStatusCode(100,"Continue");
    HttpStatusCode HttpStatusCodes::SwitchingProtocols = HttpStatusCode (101, "SwitchingProtocols");
    HttpStatusCode HttpStatusCodes::Processing = HttpStatusCode (102, "Processing");  // (WebDAV; RFC 2518)
    // *** 2xx Success *** //
    HttpStatusCode HttpStatusCodes::OK = HttpStatusCode  (200, "OK");
    HttpStatusCode HttpStatusCodes::Created = HttpStatusCode  (201, "Created");
    HttpStatusCode HttpStatusCodes::Accepted = HttpStatusCode  (202, "Accepted");
    HttpStatusCode HttpStatusCodes::NonAuthoritativeInformation = HttpStatusCode  (203, "NonAuthoritativeInformation");
    HttpStatusCode HttpStatusCodes::NoContent = HttpStatusCode  (204, "NoContent");
    HttpStatusCode HttpStatusCodes::ResetContent = HttpStatusCode  (205, "ResetContent");
    HttpStatusCode HttpStatusCodes::PartialContent = HttpStatusCode  (206, "PartialContent");
    HttpStatusCode HttpStatusCodes::MultiStatus = HttpStatusCode  (207, "MultiStatus");
    HttpStatusCode HttpStatusCodes::AlreadyReported = HttpStatusCode  (208, "AlreadyReported");
    HttpStatusCode HttpStatusCodes::IMUsed = HttpStatusCode  (226, "IMUsed");

    // *** 3xx Redirection *** //
    HttpStatusCode HttpStatusCodes::MultipleChoices = HttpStatusCode  (300, "MultipleChoices");
    HttpStatusCode HttpStatusCodes::MovedPermanently = HttpStatusCode  (301, "MovedPermanently");
    HttpStatusCode HttpStatusCodes::Found = HttpStatusCode  (302, "Found");
    HttpStatusCode HttpStatusCodes::SeeOther = HttpStatusCode  (303, "SeeOther");
    HttpStatusCode HttpStatusCodes::NotModified = HttpStatusCode  (304, "NotModified");
    HttpStatusCode HttpStatusCodes::UseProxy = HttpStatusCode  (305, "UseProxy");
    HttpStatusCode HttpStatusCodes::SwitchProxy = HttpStatusCode  (306, "SwitchProxy");
    HttpStatusCode HttpStatusCodes::TemporaryRedirect = HttpStatusCode  (307, "TemporaryRedirect");
    HttpStatusCode HttpStatusCodes::PermanentRedirect = HttpStatusCode  (308, "PermanentRedirect");
    HttpStatusCode HttpStatusCodes::ResumeIncomplete = HttpStatusCode  (309, "ResumeIncomplete");

    // *** 4xx Client Error *** //
    HttpStatusCode HttpStatusCodes::BadRequest = HttpStatusCode  (400, "BadRequest");
    HttpStatusCode HttpStatusCodes::Unauthorized = HttpStatusCode  (401, "Unauthorized");
    HttpStatusCode HttpStatusCodes::PaymentRequired = HttpStatusCode  (402, "PaymentRequired");
    HttpStatusCode HttpStatusCodes::Forbidden = HttpStatusCode  (403, "Forbidden");
    HttpStatusCode HttpStatusCodes::NotFound = HttpStatusCode  (404, "NotFound");
    HttpStatusCode HttpStatusCodes::MethodNotAllowed = HttpStatusCode  (405, "MethodNotAllowed");
    HttpStatusCode HttpStatusCodes::NotAcceptable = HttpStatusCode  (406, "NotAcceptable");
    HttpStatusCode HttpStatusCodes::ProxyAuthenticationRequired = HttpStatusCode  (407, "ProxyAuthenticationRequired");
    HttpStatusCode HttpStatusCodes::RequestTimeout = HttpStatusCode  (408, "RequestTimeout");
    HttpStatusCode HttpStatusCodes::Conflict = HttpStatusCode  (409, "Conflict");
    HttpStatusCode HttpStatusCodes::Gone = HttpStatusCode  (410, "Gone");
    HttpStatusCode HttpStatusCodes::LengthRequired = HttpStatusCode  (411, "LengthRequired");
    HttpStatusCode HttpStatusCodes::PreconditionFailed = HttpStatusCode  (412, "PreconditionFailed");
    HttpStatusCode HttpStatusCodes::PayloadTooLarge = HttpStatusCode  (413, "PayloadTooLarge");
    HttpStatusCode HttpStatusCodes::RequestURITooLong = HttpStatusCode  (414, "RequestURITooLong");
    HttpStatusCode HttpStatusCodes::UnsupportedMediaType = HttpStatusCode  (415, "UnsupportedMediaType");
    HttpStatusCode HttpStatusCodes::RequestedRangeNotSatisfiable = HttpStatusCode   (416, "RequestedRangeNotSatisfiable");
    HttpStatusCode HttpStatusCodes::ExpectationFailed = HttpStatusCode  (417, "ExpectationFailed");
    HttpStatusCode HttpStatusCodes::ImTeapot = HttpStatusCode  (418, "ImTeapot");
    HttpStatusCode HttpStatusCodes::AuthenticatioTimeout = HttpStatusCode  (419, "AuthenticatioTimeout");
    //HttpStatusCode HttpStatusCodes::MethodFailure = HttpStatusCode  (420, "MethodFailure");
    //HttpStatusCode HttpStatusCodes::EnhanceYourCalm = HttpStatusCode  (420, "EnhanceYourCalm");
    HttpStatusCode HttpStatusCodes::MisdirectedRequest = HttpStatusCode  (421, "MisdirectedRequest");
    HttpStatusCode HttpStatusCodes::UnprocessableEntity = HttpStatusCode  (422, "UnprocessableEntity");
    HttpStatusCode HttpStatusCodes::Locked = HttpStatusCode  (423, "Locked");
    HttpStatusCode HttpStatusCodes::FailedDependency = HttpStatusCode  (424, "FailedDependency");
    HttpStatusCode HttpStatusCodes::UpgradeRequired = HttpStatusCode  (426, "UpgradeRequired");
    HttpStatusCode HttpStatusCodes::PreconditionRequired = HttpStatusCode  (428, "PreconditionRequired");
    HttpStatusCode HttpStatusCodes::TooManyRequests = HttpStatusCode  (429, "TooManyRequests");
    HttpStatusCode HttpStatusCodes::RequestHeaderFieldsTooLarge = HttpStatusCode  (431, "RequestHeaderFieldsTooLarge");
    HttpStatusCode HttpStatusCodes::LoginTimeout = HttpStatusCode  (440, "LoginTimeout");
    HttpStatusCode HttpStatusCodes::NoResponse = HttpStatusCode  (444, "NoResponse");
    HttpStatusCode HttpStatusCodes::RetryWith = HttpStatusCode  (449, "RetryWith");
    HttpStatusCode HttpStatusCodes::BlockedByWindowsParentalControls = HttpStatusCode  (450, "BlockedByWindowsParentalControls");
    HttpStatusCode HttpStatusCodes::UnavailableForLegalReasons = HttpStatusCode   (451, "UnavailableForLegalReasons");
    //HttpStatusCode HttpStatusCodes::Redirect = HttpStatusCode  (451, "Redirect");
    HttpStatusCode HttpStatusCodes::RequestHeaderTooLarge = HttpStatusCode  (494, "RequestHeaderTooLarge");
    HttpStatusCode HttpStatusCodes::CertError = HttpStatusCode  (495, "CertError");
    HttpStatusCode HttpStatusCodes::NoCert = HttpStatusCode  (496, "NoCert");
    HttpStatusCode HttpStatusCodes::HTTPToHTTPS = HttpStatusCode  (497, "HTTPToHTTPS");
    HttpStatusCode HttpStatusCodes::TokenExpired = HttpStatusCode  (498, "TokenExpired");
    HttpStatusCode HttpStatusCodes::ClientClosedRequest = HttpStatusCode  (499, "ClientClosedRequest");
    //HttpStatusCode HttpStatusCodes::TokenRequired = HttpStatusCode  (499, "TokenRequired");

    // *** 5xx Server Error *** //
    HttpStatusCode HttpStatusCodes::InternalServerError = HttpStatusCode  (500, "InternalServerError");
    HttpStatusCode HttpStatusCodes::NotImplemented = HttpStatusCode  (501, "NotImplemented");
    HttpStatusCode HttpStatusCodes::BadGateway = HttpStatusCode  (502, "BadGateway");
    HttpStatusCode HttpStatusCodes::ServiceUnavailable = HttpStatusCode  (503, "ServiceUnavailable");
    HttpStatusCode HttpStatusCodes::GatewayTimeout = HttpStatusCode  (504, "GatewayTimeout");
    HttpStatusCode HttpStatusCodes::HTTPVersionNotSupported = HttpStatusCode  (505, "HTTPVersionNotSupported");
    HttpStatusCode HttpStatusCodes::VariantAlsoNegotiates = HttpStatusCode  (506, "VariantAlsoNegotiates");
    HttpStatusCode HttpStatusCodes::InsufficientStorage = HttpStatusCode  (507, "InsufficientStorage");
    HttpStatusCode HttpStatusCodes::LoopDetected = HttpStatusCode  (508, "LoopDetected");
    HttpStatusCode HttpStatusCodes::BandwidthLimitExceeded = HttpStatusCode  (509, "BandwidthLimitExceeded");
    HttpStatusCode HttpStatusCodes::NotExtended = HttpStatusCode  (510, "NotExtended");
    HttpStatusCode HttpStatusCodes::NetworkAuthenticationRequired = HttpStatusCode  (511, "NetworkAuthenticationRequired");
    HttpStatusCode HttpStatusCodes::UnknownError = HttpStatusCode  (520, "UnknownError");
    HttpStatusCode HttpStatusCodes::OriginConnectionTimeout = HttpStatusCode  (522, "OriginConnectionTimeout");
    HttpStatusCode HttpStatusCodes::NetworkReadTimeout = HttpStatusCode  (598, "NetworkReadTimeout");
    HttpStatusCode HttpStatusCodes::NetworkConnectTimeout = HttpStatusCode  (599, "NetworkConnectTimeout");



/**
 *
 *  CorsMiddleware.cc
 *
 */

#include "CorsMiddleware.h"
#include <drogon/HttpResponse.h>

using namespace drogon;

void CorsMiddleware::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    std::cout << "Middleware called. Path: " << req->path() << ", Method: " << req->methodString() << std::endl;

    if (req->method() == Options) {
        std::cout << "CORS preflight OPTIONS request caught" << std::endl;

        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "*");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "*");
        resp->addHeader("Access-Control-Max-Age", "86400");
        resp->setStatusCode(k200OK);
        fcb(resp);
        return;
    }

    // Allow normal requests through with CORS headers
    req->attributes()->insert("CorsMatched", true); // optional debugging
    fccb();
}
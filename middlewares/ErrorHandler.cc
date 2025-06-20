/**
 *
 *  ErrorHandler.cc
 *
 */

#include "ErrorHandler.h"
#include <drogon/HttpResponse.h>
#include"../utils/AppError.h"
#include<jsoncpp/json/json.h>

using namespace drogon;

void ErrorHandler::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    try{
        fccb();
    }
    catch(const AppError &e){
        Json::Value jsonResponse;
        jsonResponse["success"]=false;
        jsonResponse["message"] = e.what();
        jsonResponse["data"]=NULL;
        auto res= drogon::HttpResponse::newHttpJsonResponse(jsonResponse);
        res->setStatusCode(e.statusCode);
    }
    catch (const std::exception &e)
    {
        Json::Value jsonResponse;
        jsonResponse["success"]=false;
        jsonResponse["message"] = e.what();
        jsonResponse["data"]=NULL;
        auto res = drogon::HttpResponse::newHttpJsonResponse(jsonResponse);
        res->setStatusCode(k500InternalServerError);
        fcb(res);
    }
}

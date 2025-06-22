/**
 *
 *  auth.cc
 *
 */

#include "auth.h"
#include<jsoncpp/json/json.h>
#include"../utils/AppError.h"
#include"../utils/token.h"

using namespace drogon;

void auth::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    try
    {
        auto authHeader=req->getHeader("Authorization");
        if(authHeader.empty()) throw AppError("token not found!",k401Unauthorized);
        if(authHeader.rfind("Bearer ",0)!=0) throw AppError("Bearer token not found!",k401Unauthorized);
        std::string token=authHeader.substr(7);
        auto [userId,email]=Auth::decodeAndverifyToken(token);
        if(!userId){
            throw AppError("Unauthorised",k401Unauthorized);
        }
        req->setParameter("userId",std::to_string(userId));
        req->setParameter("email",email);
        fccb();
    }
    catch(const AppError& e)
    {
        Json::Value res;
        res["success"]=false;
        res["message"]=e.what();
        res["data"]=Json::nullValue;
        auto resp=HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(e.statusCode);
        fcb(resp);
    }
    catch(const std::exception& e)
    {
        Json::Value res;
        res["success"]=false;
        res["message"]=e.what();
        res["data"]=Json::nullValue;
        auto resp=HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k500InternalServerError);
        fcb(resp);
    }
}

#include "health.h"

void health::health(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback){
    try
    {
        Json::Value res;
        res["sucess"]=true;
        res["message"]="healthy";
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k200OK);
        callback(resp);
        return;
    }
    catch(const std::exception& e)
    {
        Json::Value res;
        res["message"]=e.what();
        res["success"]=false;
        auto resp=HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
        return;
    }
    
}
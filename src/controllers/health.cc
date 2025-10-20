#include "health.h"
#include<jsoncpp/json/json.h>

using namespace std;

void health::healthCheck(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback){
    try {
        Json::Value res;
        res["success"] = true;
        res["message"] = "healthy";
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k200OK);
        callback(resp);
    } catch (const std::exception &e) {
        Json::Value res;
        res["success"] = false;
        res["message"] = e.what();
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    }
    
}
#pragma once
#include <drogon/HttpController.h>
#include <jsoncpp/json/json.h>

using namespace drogon;

namespace Response {
    void response(std::function<void (const HttpResponsePtr &)> &&callback,drogon::HttpStatusCode statusCode,std::string &message,const Json::Value &data) {
        Json::Value response;
        response["success"]=true;
        response["message"]=message;
        response["data"] = data;
        auto res = HttpResponse::newHttpJsonResponse(response);
        res->setStatusCode(statusCode);
        callback(res);
        return;
    }
}

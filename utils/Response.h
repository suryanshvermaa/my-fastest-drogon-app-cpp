#pragma once
#include <drogon/HttpController.h>
#include <jsoncpp/json/json.h>

using namespace drogon;

namespace ResponseHelper {

inline HttpResponsePtr success(const Json::Value &data = Json::Value{}) {
    Json::Value res;
    res["success"] = true;
    res["data"] = data;
    return HttpResponse::newHttpJsonResponse(res);
}

inline HttpResponsePtr error(const std::string &message, int code = 400) {
    Json::Value res;
    res["success"] = false;
    res["message"] = message;
    auto resp = HttpResponse::newHttpJsonResponse(res);
    resp->setStatusCode(static_cast<HttpStatusCode>(code));
    return resp;
}

}

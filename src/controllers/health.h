#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class health : public drogon::HttpController<health>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(health::health, "/", Get); // path is /health/{arg2}/{arg1}
    METHOD_LIST_END
    void health(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
};

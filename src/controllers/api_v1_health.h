#pragma once

#include <drogon/HttpController.h>

using namespace drogon;
namespace api
{
namespace v1
{
class health : public drogon::HttpController<health>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(health::healthCheck, "/", Get);
    METHOD_LIST_END
    void healthCheck(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
};
}
}
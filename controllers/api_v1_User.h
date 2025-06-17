#pragma once

#include <drogon/HttpController.h>
#include <drogon/orm/Mapper.h>
#include"../models/Users.h"

using namespace drogon;

namespace api
{
namespace v1
{
class User : public drogon::HttpController<User>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(User::signup, "/signup", Post); // path is /api/v1/User/signup
    METHOD_ADD(User::getUsers, "/getUsers", Get); // path is /api/v1/User/getUsers
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    void signup(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
    void getUsers(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
};
}
}

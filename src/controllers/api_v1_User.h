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
    METHOD_ADD(User::login, "/login", Post); // path is /api/v1/User/login
    METHOD_ADD(User::profile, "/profile", Get,"auth"); // path is /api/v1/User/profile
    METHOD_LIST_END
    
    void signup(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
    void login(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
    void profile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
};
}
}

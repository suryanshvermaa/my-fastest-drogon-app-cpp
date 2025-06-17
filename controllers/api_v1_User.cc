#include "api_v1_User.h"
#include<drogon/orm/DbClient.h>
#include"../models/Users.h"

using namespace api::v1;
using namespace drogon_model::userdb;
using namespace std;

void User::signup(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback){
    try
    {
        const auto json=req->getJsonObject();
        if(!json){
            Json::Value res;
            res["message"]="All fields are required";
            res["success"]=false;
            auto resp=HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
        string name=(json->get("name", "").asString());
        string email=(json->get("email", "").asString());
        string password=(json->get("password", "").asString()); 
        Json::Value errors;
        if (name.empty()) {
            errors["name"] = "Username is required";
        }
        if (email.empty()) {
            errors["email"] = "Email is required";
        }
        if (password.empty()) {
            errors["password"] = "Password is required";
        }
        if(!errors.empty()){
            Json::Value res;
            res["message"]="All fields are required";
            res["success"]=false;
            auto resp=HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
        Users user;
        user.setName(name);
        user.setEmail(email);
        user.setPassword(password);
        auto clientPtr = drogon::app().getDbClient();
        drogon::orm::Mapper<Users> mapper(clientPtr);
        mapper.insert(user, [callback](const Users &insertedUser) {
            Json::Value json;
            json["id"] = insertedUser.getValueOfId();
            json["name"] = insertedUser.getValueOfName();
            json["email"] = insertedUser.getValueOfEmail();
            json["password"] = insertedUser.getValueOfPassword();
            auto resp = HttpResponse::newHttpJsonResponse(json);
            resp->setStatusCode(k201Created);
            callback(resp);
        }, [callback](const drogon::orm::DrogonDbException &e) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k500InternalServerError);
            resp->setBody("Error: " + std::string(e.base().what()));
            callback(resp);
        });
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        Json::Value res;
        res["message"]=e.what();
        res["success"]=false;
        auto resp=HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
        
    }
    
}


void User::getUsers(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const{
    auto clientPtr = drogon::app().getDbClient();
    drogon::orm::Mapper<Users> mapper(clientPtr);
    mapper.findAll([callback](const std::vector<Users> &users) {
        Json::Value json;
        for (const auto &user : users) {
            Json::Value userJson;
            userJson["id"] = user.getValueOfId();
            userJson["name"] = user.getValueOfName();
            userJson["email"] = user.getValueOfEmail();
            userJson["password"] = user.getValueOfPassword();
            json.append(userJson);
        }
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(k200OK);
        callback(resp);
    },
    [callback](const drogon::orm::DrogonDbException &exception) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        resp->setBody("Error: " + std::string(exception.base().what()));
        callback(resp);
    });
}
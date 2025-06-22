#include "api_v1_User.h"
#include<drogon/orm/DbClient.h>
#include"../models/Users.h"
#include <iostream>
#include"bcrypt.h"
#include"../utils/AppError.h"
#include"../utils/token.h"
#include"../utils/AppError.h"

using namespace std;
using namespace api::v1;
using namespace drogon_model::userdb;

using namespace std;

void User::signup(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback){
    try
    {
        const auto json=req->getJsonObject();
        if(!json) throw AppError("All properties are required",k400BadRequest);
        if(!json->isMember("email")||!json->isMember("name")||!json->isMember("password")) throw AppError("All fields required");
        Users user;
        std::string name = (*json)["name"].asString();
        std::string email = (*json)["email"].asString();
        std::string password = (*json)["password"].asString();
        user.setName(name);
        user.setEmail(email);
        user.setPassword(bcrypt::generateHash(password,5));
        drogon::orm::Mapper<Users> mapper(app().getDbClient());
        mapper.insert(user, [callback](const Users &insertedUser) {
            Json::Value json;
            json["id"] = insertedUser.getValueOfId();
            json["name"] = insertedUser.getValueOfName();
            json["email"] = insertedUser.getValueOfEmail();
            json["password"] = insertedUser.getValueOfPassword();
            json["token"]=Auth::createToken(insertedUser.getValueOfId(),insertedUser.getValueOfEmail());
            Json::Value res;
            res["sucess"]=true;
            res["message"]="signup successful";
            res["data"]=json;
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k201Created);
            callback(resp);
            return;
        }, [callback](const drogon::orm::DrogonDbException &e) {
            Json::Value res;
            res["message"]=e.base().what();
            res["success"]=false;
            auto resp=HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k500InternalServerError);
            callback(resp);
            return;
        });
    }
    catch(const AppError &e){
        Json::Value res;
        res["message"]=e.what();
        res["success"]=false;
        auto resp=HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(e.statusCode);
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

void User::login(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) {
    try {
        auto json = req->getJsonObject();
        if(!json) throw AppError("All properties are required",k400BadRequest);
        if(!json->isMember("email")||!json->isMember("password")) throw AppError("Both fields are required");
        const std::string email=(*json)["email"].asString();
        const std::string password=(*json)["password"].asString();
        drogon::orm::Mapper<Users> mapper(app().getDbClient());
        
        mapper.findOne(drogon::orm::Criteria(Users::Cols::_email, email),
            [callback,password](const Users& user) {
                bool isCorrectPassword=bcrypt::validatePassword(password,user.getValueOfPassword());
                std::cout<<"l0"<<password<<" ";
                if(!isCorrectPassword){
                    Json::Value res;
                    res["message"]="Password is incorrect";
                    res["success"]=false;
                    auto resp=HttpResponse::newHttpJsonResponse(res);
                    resp->setStatusCode(k500InternalServerError);
                    callback(resp);
                    return;
                }
                Json::Value data;
                data["id"] = user.getValueOfId();
                data["email"] = user.getValueOfEmail();
                data["name"] = user.getValueOfName();
                data["token"] = Auth::createToken(user.getValueOfId(), user.getValueOfEmail());
                Json::Value res;
                res["sucess"]=true;
                res["message"]="login successful";
                res["data"]=data;
                auto resp=HttpResponse::newHttpJsonResponse(res);
                resp->setStatusCode(k200OK);
                callback(resp);
               return;
            },
            [callback](const drogon::orm::DrogonDbException &e) {
                Json::Value res;
                res["message"]=e.base().what();
                res["success"]=false;
                auto resp=HttpResponse::newHttpJsonResponse(res);
                resp->setStatusCode(k500InternalServerError);
                callback(resp);
                return;
            });
    } catch (const AppError &e) {
        Json::Value res;
        res["message"] = e.what();
        res["success"] = false;
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(e.statusCode);
        callback(resp);
        return;
    }
     catch (const std::exception &e) {
        Json::Value res;
        res["message"] = e.what();
        res["success"] = false;
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
        return;
    }
}

void User::profile(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) {
    try {
        auto json = req->getJsonObject();
        Json::Value res;
        res["message"] = "profile fetched successfully";
        res["success"] = true;
        Json::Value data;
        data["userId"]=req->getParameter("userId");
        res["data"] = data;
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k200OK);
        callback(resp);
        return;
    } catch (const AppError &e) {
        Json::Value res;
        res["message"] = e.what();
        res["success"] = false;
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(e.statusCode);
        callback(resp);
        return;
    } catch (const std::exception &e) {
        Json::Value res;
        res["message"] = e.what();
        res["success"] = false;
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
        return;
    }
}
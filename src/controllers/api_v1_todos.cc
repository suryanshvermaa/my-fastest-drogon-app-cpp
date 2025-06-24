#include "api_v1_todos.h"
#include <jsoncpp/json/json.h>
#include"../utils/AppError.h"
#include<drogon/orm/DbClient.h>
#include"../models/Todos.h"

using namespace drogon_model::userdb;

using namespace api::v1;

void todos::getTodo(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback,int id) const{
    try {
        drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());
        mapper.findByPrimaryKey(id,[callback](const Todos&todo){
            Json::Value res;
            res["message"] = "todo fectched successfully";
            res["success"] = true;
            Json::Value data;
            data["id"]=todo.getValueOfId();
            data["title"]=todo.getValueOfTitle();
            data["completed"]=todo.getValueOfCompleted();
            res["data"] = data;
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k200OK);
            callback(resp);
            return;
        },[callback](const drogon::orm::DrogonDbException &e){
            Json::Value res;
            res["message"] = "Todo not found";
            res["success"] = true;
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
    );
        
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

void todos::getAllTodos(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const{
    try {
        int userId = std::stoi(req->getParameter("userId"));
        drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());
        mapper.findBy(drogon::orm::Criteria(Todos::Cols::_user_id,userId),[callback](const std::vector<Todos>&todos){
            std::vector<Json::Value> arayOfJson;
            for(Todos t:todos){
                Json::Value data;
                data["id"]=t.getValueOfId();
                data["title"]=t.getValueOfTitle();
                data["completed"]=t.getValueOfCompleted();
                arayOfJson.push_back(data);
            }
            Json::Value res;
            res["message"] = "fetched";
            res["success"] = true;
            res["data"] = Json::Value(Json::arrayValue);
            for (const auto& item : arayOfJson) {
                res["data"].append(item);
            }
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k200OK);
            callback(resp);
            return;
        },[callback](const drogon::orm::DrogonDbException &e){
            Json::Value res;
            res["message"] = "Todos not found";
            res["success"] = false;
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
    );
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

void todos::getAllTodosByCompletion(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback,bool completion) const{
    try {
        int userId = std::stoi(req->getParameter("userId"));
        drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());
        mapper.findBy(drogon::orm::Criteria(Todos::Cols::_user_id,userId)&&drogon::orm::Criteria(Todos::Cols::_completed,completion),[callback](const std::vector<Todos>&todos){
            std::vector<Json::Value> arayOfJson;
            for(Todos t:todos){
                Json::Value data;
                data["id"]=t.getValueOfId();
                data["title"]=t.getValueOfTitle();
                data["completed"]=t.getValueOfCompleted();
                arayOfJson.push_back(data);
            }
            Json::Value res;
            res["message"] = "fetched";
            res["success"] = true;
            res["data"] = Json::Value(Json::arrayValue);
            for (const auto& item : arayOfJson) {
                res["data"].append(item);
            }
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k200OK);
            callback(resp);
            return;
        },[callback](const drogon::orm::DrogonDbException &e){
            Json::Value res;
            res["message"] = "Todos not found";
            res["success"] = false;
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
    );
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



void todos::createTodo(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) {
    try {
        auto json = req->getJsonObject();
        if(!json) throw AppError("All fields are required!",k400BadRequest);
        if(!json->isMember("title")||!json->isMember("completed")) throw AppError("All fields are required!",k400BadRequest);
        std::string titleReq=(*json)["title"].asString();
        bool completedReq=(*json)["completed"].asBool();
        Todos todo;
        todo.setTitle(titleReq);
        todo.setCompleted(completedReq);
        todo.setUserId(std::stoi(req->getParameter("userId")));

        drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());
        mapper.insert(todo,[callback](const Todos&todo){
            Json::Value res;
            res["message"] = "created todo";
            res["success"] = true;
            Json::Value data;
            data["id"]=todo.getValueOfId();
            data["title"]=todo.getValueOfTitle();
            data["completed"]=todo.getValueOfCompleted();
            res["data"] = data;
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k201Created);
            callback(resp);
            return;
        },[callback](const drogon::orm::DrogonDbException &e){
            Json::Value res;
            res["message"] = "Todos creation failed";
            res["success"] = false;
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
    );
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

void todos::updateTodo(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, int id) {
    try {
        // Validate JSON input
        auto json = req->getJsonObject();
        if (!json || !json->isMember("title") || !json->isMember("completed")) {
            throw AppError("All fields (title and completed) are required!", k400BadRequest);
        }

        // Extract JSON fields
        std::string titleReq = (*json)["title"].asString();
        bool completedReq = (*json)["completed"].asBool();

        // Initialize database mapper
        drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());

        // Find Todo by ID
        mapper.findByPrimaryKey(
            id,
            [callback, titleReq, completedReq](const Todos &todo) {
                // Create a copy to update
                auto updatedTodo = todo;
                updatedTodo.setTitle(titleReq);
                updatedTodo.setCompleted(completedReq);

                // Initialize mapper again for the update operation
                drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());

                // Update Todo in database
                mapper.update(
                    updatedTodo,
                    [callback, updatedTodo](size_t rows) {
                        if (rows == 0) {
                            Json::Value res;
                            res["message"] = "No Todo was updated";
                            res["success"] = false;
                            auto resp = HttpResponse::newHttpJsonResponse(res);
                            resp->setStatusCode(k400BadRequest);
                            callback(resp);
                            return;
                        }

                        // Prepare success response
                        Json::Value res;
                        res["message"] = "Updated successfully";
                        res["success"] = true;
                        Json::Value data;
                        data["id"] = updatedTodo.getValueOfId();
                        data["title"] = updatedTodo.getValueOfTitle();
                        data["completed"] = updatedTodo.getValueOfCompleted();
                        res["data"] = data;

                        auto resp = HttpResponse::newHttpJsonResponse(res);
                        resp->setStatusCode(k200OK);
                        callback(resp);
                    },
                    [callback](const drogon::orm::DrogonDbException &e) {
                        Json::Value res;
                        res["message"] = std::string("Todo update failed: ") + e.base().what();
                        res["success"] = false;
                        auto resp = HttpResponse::newHttpJsonResponse(res);
                        resp->setStatusCode(k500InternalServerError);
                        callback(resp);
                    });
            },
            [callback](const drogon::orm::DrogonDbException &e) {
                Json::Value res;
                res["message"] = std::string("Todo not found: ") + e.base().what();
                res["success"] = false;
                auto resp = HttpResponse::newHttpJsonResponse(res);
                resp->setStatusCode(k404NotFound);
                callback(resp);
            });

    } catch (const AppError &e) {
        Json::Value res;
        res["message"] = e.what();
        res["success"] = false;
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(e.statusCode);
        callback(resp);
    } catch (const std::exception &e) {
        Json::Value res;
        res["message"] = std::string("Server error: ") + e.what();
        res["success"] = false;
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    } catch (...) {
        Json::Value res;
        res["message"] = "Unknown server error";
        res["success"] = false;
        auto resp = HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    }
}
void todos::deleteTodo(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback,int id) {
    try {
        drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());
        mapper.deleteByPrimaryKey(id,[callback](const size_t count){
            if(count==1){
                Json::Value res;
                res["message"] = "todo deleted successfully";
                res["success"] = true;
                auto resp = HttpResponse::newHttpJsonResponse(res);
                resp->setStatusCode(k200OK);
                callback(resp);
                return;
            }else{
                Json::Value res;
                res["message"] = "Error in deletion";
                res["success"] = false;
                auto resp = HttpResponse::newHttpJsonResponse(res);
                resp->setStatusCode(k400BadRequest);
                callback(resp);
                return;
            }
            
        },[callback](const drogon::orm::DrogonDbException &e){
            Json::Value res;
            res["message"] = "Error in deletion";
            res["success"] = false;
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k400BadRequest);
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
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace api
{
namespace v1
{
class todos : public drogon::HttpController<todos>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(todos::getTodo, "/api/v1/todos/{id}", Get); // path is /api/v1/todos/:id
    METHOD_ADD(todos::createTodo, "/create", Post,"auth"); // path is /api/v1/todos/create
    METHOD_ADD(todos::getAllTodos, "/getAll", Get,"auth"); // path is /api/v1/todos/create
    ADD_METHOD_TO(todos::getAllTodosByCompletion, "/api/v1/todos/getAll/{completion}", Get,"auth"); // path is /api/v1/todos/create/:true/false
    ADD_METHOD_TO(todos::updateTodo, "/api/v1/todos/update/{id}", Put,"auth"); // path is /api/v1/todos/update/:id
    ADD_METHOD_TO(todos::deleteTodo, "/api/v1/todos/delete/{id}", Delete,"auth");// path is /api/v1/todos/delete/:id
    METHOD_LIST_END

    void getTodo(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback,int id)const;
    void createTodo(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
    void getAllTodos(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void getAllTodosByCompletion(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback,bool completion) const;
    void updateTodo(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback,int id);
    void deleteTodo(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback,int id);
};
}
}

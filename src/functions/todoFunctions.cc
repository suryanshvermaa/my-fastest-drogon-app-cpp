#include"./todoFunctions.h"
#include <drogon/HttpController.h>
#include<drogon/orm/DbClient.h>
#include"../models/Todos.h"

using drogon_model::userdb;

todoData Todo::createTodo(int userId,std::string &title,bool completed){
    
}

// todoData Todo::updateTodo(int todoId,std::string &title,bool completed){
//     Todos newTodo;
//     newTodo.setUserId(userId);
//     newTodo.setTitle(title);
//     newTodo.setCompleted(completed);
//     drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());
    // mapper.findByPrimaryKey(todoId,[callback](const Todos &insertedTodo) {
    //     todoData data;
    //     data.id = insertedTodo.getValueOfId();
    //     data.title = insertedTodo.getValueOfTitle();
    //     data.completed = insertedTodo.getValueOfCompleted();
    //     return json;
    // }, [](const drogon::orm::DrogonDbException &e) {
    //     todoData data{0,"",false};
    //     return json;
    // });
// }

todoData Todo::getTodo(int todoId){
    drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());
    try
    {
        auto todo=co_await mapper.findFutureByPrimaryKey(todoId);
        co_return {
            todo.getValueOfId(),
            todo.getValueOfTitle(),
            todo.getValueOfCompleted()
        }
    }
    catch(const drogon::orm::DrogonDbException &e)
    {
        co_return{0,"",false};
    }
    
    
}

std::vector<todoData> Todo::getAllTodos(int userId){
    drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());
    try
    {
        std::vector<Todos> todos=co_await mapper.findFutureAll(drogon::orm::Criteria(Todos::Cols::_user_id,userId));
        std::vector<todoData> res; 
        for(Todos t:todos){
            todoData data;
            data.title=t.getValueOfTitle();
            data.id=t.getValueOfId();
            data.completed=t.getValueOfCompleted();
            res.push_back(data);
        }
        co_return res;
    }
    catch(const std::exception& e)
    {
        co_return {};
    }
    

}

bool deleteTodo(int todoId){
    drogon::orm::Mapper<Todos> mapper(drogon::app().getDbClient());
    try
    {
        co_await mapper.deleteFutureByPrimaryKey(todoId);
        co_return true;
    }
    catch(const std::exception& e)
    {
        co_return false;
    }
    
}


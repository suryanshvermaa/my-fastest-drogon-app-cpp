#include<iostream>
#include"jsoncpp/json/json.h"

struct todoData
{
    int id;
    std::string title;
    bool completed;
};
namespace Todo{
    todoData createTodo(int userId,std::string &title,bool completed);
    // todoData updateTodo(int todoId,std::string &title,bool completed);
    todoData getTodo(int todoId);
    std::vector<todoData> getAllTodos(int userId);
    bool deleteTodo(int userId,int todoId);
}
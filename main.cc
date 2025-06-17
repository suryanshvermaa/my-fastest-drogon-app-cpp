#include<drogon/drogon.h>

int main(){
    std::cout<<"Server is running on port 3000!"<<std::endl;
    drogon::app().loadConfigFile("config.json").run();
    return 0;
}
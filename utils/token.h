#include<iostream>
struct data{
    int userId;
    std::string email;
};
namespace Auth {
    std::string createToken(const int userId,const std::string &email);
    data decodeAndverifyToken(const std::string &token);
}

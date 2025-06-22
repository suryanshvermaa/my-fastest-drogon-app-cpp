#include"jwt-cpp/jwt.h"
#include<iostream>
#include"./token.h"
#include<jsoncpp/json/json.h>


std::string Auth::createToken(const int userId,const std::string &email){
    std::string token=jwt::create()
    .set_issuer("suryansh")
    .set_type("JWS")
    .set_expires_at(std::chrono::system_clock::now()+std::chrono::hours{24})
    .set_payload_claim("userId",jwt::claim(std::to_string(userId)))
    .set_payload_claim("email",jwt::claim(email))
    .sign(jwt::algorithm::hs256{std::getenv("JWT_SECRET")});

    return token;
}

data Auth::decodeAndverifyToken(const std::string &token){
    try
    {
        auto decodedToken=jwt::decode(token);
        auto verifier = jwt::verify()
        .with_issuer("suryansh")
        .with_type("JWS")
        .allow_algorithm(jwt::algorithm::hs256{std::getenv("JWT_SECRET")});

        verifier.verify(decodedToken);
        auto mp = decodedToken.get_payload_json();
        const std::string email=mp["email"].get<std::string>();
        const std::string userId=mp["userId"].get<std::string>();
        return {std::stoi(userId),email};
    }
    catch(const std::exception& e)
    {
        return {0,""};
    }
    
}
#include "assistant.h"
#include<unordered_map>
#include<jsoncpp/json/json.h>
#include <sstream>
#include <iostream>
#include "../utils/token.h"

using namespace std;

unordered_map<WebSocketConnectionPtr,Json::Value> connections; //userId->chat

void assistant::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    const int userId=connections[wsConnPtr]["userId"].asInt();
    Json::Value userChat;
    userChat["role"]="user";
    userChat["message"]=message;

    Json::Value serverChat;
    serverChat["role"]="ai";
    serverChat["message"]="ai:"+message;

    connections[wsConnPtr]["chats"].append(userChat);
    connections[wsConnPtr]["chats"].append(serverChat);

    wsConnPtr->sendJson(connections[wsConnPtr]["chats"]);
}

void assistant::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    auto token=req->getHeader("token");
    auto [userId,email]=Auth::decodeAndverifyToken(token);
    if(!userId) {
        wsConnPtr->shutdown();
        return;
    }
    connections[wsConnPtr]["userId"]=userId;
    connections[wsConnPtr]["chats"]=Json::arrayValue;
}

void assistant::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    connections.erase(wsConnPtr);
}

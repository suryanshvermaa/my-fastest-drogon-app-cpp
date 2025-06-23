#include "./gemini.h"
#include <jsoncpp/json/json.h>
#include <cpr/cpr.h>
#include <sstream>
#include <iostream>

std::string sendPrompt(const std::string &prompt) {
    std::string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=AIzaSyBWh9NvXvur3k0cz7a8m-ok1ujEnJpFNfY";
    
    Json::Value requestBody;
    requestBody["contents"] = Json::arrayValue;
    Json::Value innerPart;
    innerPart["text"] = prompt;
    Json::Value innerContent;
    innerContent["parts"] = Json::arrayValue;
    innerContent["parts"].append(innerPart);
    requestBody["contents"].append(innerContent);
    
    Json::StreamWriterBuilder writer;
    std::string requestBodyStr = Json::writeString(writer, requestBody);

    cpr::Response res = cpr::Post(
        cpr::Url{url},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{requestBodyStr}
    );

    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    std::istringstream rawJson(res.text);
    if (!Json::parseFromStream(builder, rawJson, &root, &errs)) {
        std::cerr << "Error parsing JSON: " << errs << std::endl;
        return "";
    }

    if (
        root.isMember("candidates") &&
        root["candidates"].isArray() &&
        root["candidates"][0].isMember("content") &&
        root["candidates"][0]["content"].isMember("parts") &&
        root["candidates"][0]["content"]["parts"].isArray() &&
        root["candidates"][0]["content"]["parts"][0].isMember("text")
    ) {
        return root["candidates"][0]["content"]["parts"][0]["text"].asString();
    }

    return "";
}

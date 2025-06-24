#include<drogon/drogon.h>

int main(){
    // Register pre-routing advice for CORS
    drogon::app().registerPreRoutingAdvice([](
        const drogon::HttpRequestPtr &req, 
        std::function<void(const drogon::HttpResponsePtr &)> &&stop,
        std::function<void()> &&pass) {
        // Handle preflight OPTIONS requests
        if (req->method() == drogon::Options) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->addHeader("Access-Control-Allow-Origin", "*");
            resp->addHeader("Access-Control-Allow-Methods", "*");
            resp->addHeader("Access-Control-Allow-Headers", "*, Authorization");
            resp->addHeader("Access-Control-Max-Age", std::to_string(86400));
            stop(resp); // Send response and stop further processing
            return;
        }
        pass(); // Continue processing for non-OPTIONS requests
    });

    // Register post-handling advice to add CORS headers to all responses
    drogon::app().registerPostHandlingAdvice([](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
        resp->addHeader("Access-Control-Allow-Origin", "*");
    });
    std::cout<<"Server is running!"<<std::endl;
    drogon::app().loadConfigFile("config.json").run();
    return 0;
}
#pragma once

#include "Utils/Network.hpp"
#include "Utils/Logger.hpp"
#include "Utils/DataBase.hpp"
#include "Utils/JSON.hpp"
#include "SQLiteDataBase.hpp"

using namespace Utils::Network;
using namespace Utils::Network::HTTPS;
using namespace Utils::Logger;
using namespace Utils::DataBase;
using namespace Utils::JSON;

namespace Backend {

    class WebServer {
    public:
        WebServer(int port, SQLiteDataBase& db,
                  bool consoleLogger = false, const std::string &logFile = "log/WebServer.log");
        void Run();
        void Stop();
    private:
        HTTPServer server_;
        SQLiteDataBase& db_;
        Logger logger_;

        void ConfigureLogger(bool consoleLogger, const std::string &logFile);
        void AddRoutes();

        // 路由注册函数
        void HandleUserLogin(HTTPRequestString &request, HTTPResponseString &response);
        void HandleUserRegister(HTTPRequestString &request, HTTPResponseString &response);
        // TODO 重置密码
        void HandleDashboard(HTTPRequestString &request, HTTPResponseString &response);
        void HandleDeviceList(HTTPRequestString &request, HTTPResponseString &response);


        // 默认返回值
        std::string json_default_ = R"({"code": 0, "message": "failed", "data":{} })";

    };
}

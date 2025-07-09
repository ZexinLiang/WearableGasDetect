#include "Backend/WebServer.hpp"

namespace Backend {

    WebServer::WebServer(int port, SQLiteDataBase& db,
                         bool consoleLogger, const std::string &logFile) :
        server_(port),
        db_(db){
        ConfigureLogger(consoleLogger, logFile);
        AddRoutes();
        logger_.Info("WebServer Configure Successfully...");
    }

    void WebServer::Stop() {
        logger_.Info("Stopping WebServer...");
        server_.Stop();
    }


    void WebServer::ConfigureLogger(bool consoleLogger, const std::string &logFile) {
        if (consoleLogger) {
            auto console_logger = std::make_shared<ConsoleLogPolicy>();
            logger_.AddPolicy(console_logger);
        }
        if(!logFile.empty()) {
            auto file_logger = std::make_shared<FileLogPolicy>(logFile);
            logger_.AddPolicy(file_logger);
        }
        logger_.Info("Logger Configure Successfully");
    }

    void WebServer::Run() {
        logger_.Info("Starting Web Server");
        server_.Start();
    }

    void WebServer::AddRoutes() {
        server_.AddRoute("/api/login", "POST", std::bind(&WebServer::HandleUserLogin, this, std::placeholders::_1, std::placeholders::_2));
        server_.AddRoute("/api/register", "POST", std::bind(&WebServer::HandleUserRegister, this, std::placeholders::_1, std::placeholders::_2));

        server_.AddRoute("/api/dashboard", "GET", std::bind(&WebServer::HandleDashboard, this, std::placeholders::_1, std::placeholders::_2));
        server_.AddRoute("/api/device/list", "GET", std::bind(&WebServer::HandleDeviceList, this, std::placeholders::_1, std::placeholders::_2));
    }


    void WebServer::HandleUserLogin(HTTPRequestString &request, HTTPResponseString &response) {
        const std::string& req_body = request.body();
        JsonManager body_json = JsonManager::FromString(req_body);
        int status = 0; // 1：成功，0：密码错误，-1:用户不存在，-2：请求不正确
        std::string username;
        if(body_json.exists("message")) {
            auto message = body_json["message"].String();
            if(message == "login") {
                if(body_json.exists("data")) {
                    auto data = body_json["data"];
                    if(data.exists("username") && data.exists("password")) {
                        username = data["username"].String();
                        auto password = data["password"].String();
                        status = db_.QueryUserPassword(username, password);
                    }else status = -2; // data 错误
                }else status = -2; // 没有 data
            }else status = -2; // message 错误
        }else status = -2; // 没有 message

        JsonManager res_json = JsonManager::FromString(json_default_);
        switch (status) {
            case 1:
                res_json["code"] = 1;
                res_json["message"] = "success";
                res_json["data"]["token"] = "token";
                break;
            case 0:
                res_json["code"] = 0;
                res_json["message"] = "password incorrect";
                res_json["data"]["token"] = "";
                break;
            case -1:
                res_json["code"] = 0;
                res_json["message"] = "username not exist";
                res_json["data"]["token"] = "";
                break;
            default:
                res_json["code"] = 0;
                res_json["message"] = "unknown error";
                res_json["data"]["token"] = "";
                break;
        }
        // 设置CORS响应头
        // response.set(HTTP::field::access_control_allow_origin, "*"); // 允许所有来源
        // response.set(HTTP::field::access_control_allow_methods, "GET, POST, OPTIONS");
        // response.set(HTTP::field::access_control_allow_headers, "Content-Type, Authorization");

        response.set(HTTP::field::server, "Server");
        response.set(HTTP::field::content_type, "application/json");
        response.body() = res_json.toString();
        response.prepare_payload();

        if(status == 1) logger_.Info("<User Login> Success: User {} ", username);
        else if(status == 0) logger_.Error("<User Login> Failed: User {} , password incorrect", username);
        else if(status == -1) logger_.Error("<User Login> Failed: User {} , user not exist", username);
        else logger_.Error("<User Login> Failed: User {} , unknown request", username);
    }

    void WebServer::HandleUserRegister(HTTPRequestString &request, HTTPResponseString &response) {
        const std::string& req_body = request.body();
        JsonManager body_json = JsonManager::FromString(req_body);
        int status = 0; // 1：成功，0：用户已经存在，-1：验证码错误，-2：请求不正确，-3：数据库错误
        std::string username;
        if(body_json.exists("message")) {
            auto message = body_json["message"].String();
            if(message == "register") {
                if(body_json.exists("data")) {
                    auto data = body_json["data"];
                    if(data.exists("username") && data.exists("password") && data.exists("verifyCode")) {
                        username = data["username"].String();
                        auto password = data["password"].String();
                        auto verifyCode = data["verifyCode"].String();
                        if(verifyCode == "1037") {
                            status = db_.RegisterUser(username, password);
                        }else status = -1; // verifyCode 错误
                    }else status = -2; // data 错误
                }else status = -2; // 没有 data
            }else status = -2; // message 错误
        }else status = -2; // 没有 message

        JsonManager res_json = JsonManager::FromString(json_default_);
        switch (status) {
            case 1:
                res_json["code"] = 1;
                res_json["message"] = "success";
                res_json["data"]["token"] = "token";
                break;
            case 0:
                res_json["code"] = 0;
                res_json["message"] = "user has exist";
                res_json["data"]["token"] = "";
                break;
            case -1:
                res_json["code"] = 0;
                res_json["message"] = "verify code error";
                res_json["data"]["token"] = "";
                break;
            default:
                res_json["code"] = 0;
                res_json["message"] = "unknown error";
                res_json["data"]["token"] = "";
                break;
        }
        response.set(HTTP::field::server, "Server");
        response.set(HTTP::field::content_type, "application/json");
        response.body() = res_json.toString();
        response.prepare_payload();

        if(status == 1) logger_.Info("<User Register> Success: User {}", username);
        else if(status == 0) logger_.Error("<User Register> Failed: User {} has exist", username);
        else if(status == -1) logger_.Error("<User Register> Failed: Verify Code error", username);
        else if(status == -2) logger_.Error("<User Register> Failed: Unknown request", username);
        else if(status == -3) logger_.Error("<User Register> Failed: DataBase error", username);
    }

    void WebServer::HandleDashboard(HTTPRequestString &request, HTTPResponseString &response) {
        logger_.Info("<Dashboard> Request");
        JsonManager res_json = JsonManager::FromString(json_default_);
        res_json["code"] = 1;
        res_json["message"] = "success";
        DeviceCount device_count{};
        db_.QueryAllDevices(device_count);
        res_json["data"]["onlineDevices"] = device_count.onlineDevices;
        res_json["data"]["activeDevices"] = device_count.activeDevices;
        res_json["data"]["alarmDevices"] = device_count.alarmDevices;
        res_json["data"]["allDevices"] = device_count.allDevices;
        std::vector<DeviceActivity> device_activities;
        int count = db_.QueryDeviceActivities(device_activities);
        for(int i = 0; i < count; i++) {
            res_json["data"]["activities"][i]["time"] = device_activities[i].time;
            res_json["data"]["activities"][i]["deviceId"] = device_activities[i].id;
            res_json["data"]["activities"][i]["deviceName"] = device_activities[i].name;
            res_json["data"]["activities"][i]["eventType"] = device_activities[i].type;
            res_json["data"]["activities"][i]["description"] = device_activities[i].description;
        }

        response.set(HTTP::field::server, "Server");
        response.set(HTTP::field::content_type, "application/json");
        response.body() = res_json.toString();
        response.prepare_payload();

        logger_.Info("<DashBoard Query> Success: ");
    }

    void WebServer::HandleDeviceList(HTTPRequestString &request, HTTPResponseString &response) {
        logger_.Info("<Device List Query> Request");
        JsonManager res_json = JsonManager::FromString(json_default_);
        res_json["code"] = 1;
        res_json["message"] = "success";
        std::vector<DeviceBasicInformation> device_list;
        int count = db_.QueryDeviceList(device_list);
        std::cout << "Device Count: " << count << std::endl;
        for(int i = 0; i < count; i++) {
            res_json["data"]["deviceList"][i]["deviceID"] = device_list[i].id;
            res_json["data"]["deviceList"][i]["deviceName"] = device_list[i].name;
            res_json["data"]["deviceList"][i]["deviceStatus"] = device_list[i].status;
            res_json["data"]["deviceList"][i]["lastLoginTime"] = device_list[i].lastLoginTime;
            res_json["data"]["deviceList"][i]["temperature"] = device_list[i].temperature;
            res_json["data"]["deviceList"][i]["humidity"] = device_list[i].humidity;
        }

        response.set(HTTP::field::server, "Server");
        response.set(HTTP::field::content_type, "application/json");
        response.body() = res_json.toString();
        response.prepare_payload();

        logger_.Info("<Device List Query> Success:");
    }

}
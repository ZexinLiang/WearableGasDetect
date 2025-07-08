#include "Backend/WGDServer.hpp"

namespace Backend {

    WGDServer::WGDServer(int port, SQLiteDataBase& db) :
        server_(port, "$$"), db_(db){
        // 配置日志
        const std::string log_path = "./log/WGDServer.log";
        std::filesystem::path path(log_path);
        if (!path.parent_path().empty() && !std::filesystem::exists(path.parent_path())) {
            std::filesystem::create_directories(path.parent_path());
        }
        auto file_policy = std::make_shared<FileLogPolicy>("./cache/WGDServer.log");
        auto console_policy = std::make_shared<ConsoleLogPolicy>();
        logger_.AddPolicy(file_policy);
        logger_.AddPolicy(console_policy);
        logger_.Info("WGDServer started");
    }


    void WGDServer::Run() {
        server_.Start();
        StartHeartbeat();
        while (true) {
            TCPMessage message;
            server_.GetMessage(message);
            if(message.data.empty()) continue;
            // 处理转发的消息
            logger_.Info("Message from {}: {}", message.ip, message.port);
            logger_.Info("Message: {}", message.data);
            if(message.data == "exit") {
                continue;
            }
            JsonManager json = JsonManager::FromString(message.data);
            // 进行设备验证和注册
            if(!HandleVerify(json, message.sessionId)){
                 server_.Unicast(message.sessionId, "$Verify Failed*");
                 server_.CloseSession(message.sessionId);
                continue;
            }else RegisterDevice(message.sessionId);
            // 处理具体逻辑
            auto now_time = Time::now();
            if(json.exists("type")) {
                int id = sessionID_to_deviceID_[message.sessionId];
                if(json["type"].String() == "GPS" || json["type"].String() == "LBS") {
                    // 处理GPS信息
                    std::string now_latitude = json["data"]["Latitude"].String(), now_longitude = json["data"]["Longitude"].String();
                    HandleLocation(now_latitude, now_longitude, message.sessionId);
                    // 处理第一次登陆信息
                    auto it = isLoginPosition_.find(id);
                    DeviceLoginInformation loginInformation;
                    if(it != isLogin_.end() && it->second ) { // 已经登陆了
                        logger_.Info("<Device Login> : id {} has login",  id);
                        continue;
                    }
                    // 设备登陆
                    loginInformation.id = id;
                    loginInformation.time = Time::formatTime(Time::now());
                    loginInformation.status = 0;
                    loginInformation.latitude = now_latitude;
                    loginInformation.longitude = now_longitude;
                    loginInformation.location = lastReGeo_;
                    loginInformation.ip = message.ip;
                    db_.UpdateDeviceLoginData(loginInformation);
                    isLoginPosition_[id] = true;
                    logger_.Info("<Device Login> : id {}", id);
                }else if(json["type"].String() == "Sensor") {
                    HandleSensorData(json, message.sessionId);
                }
                db_.UpdateDeviceTime(id);
                {
                    std::lock_guard<std::mutex> lock(lastUpdateTimeMutex_);
                    lastUpdateTime_[id] = Time::formatTime(now_time);
                }
                auto it = isLogin_.find(id);
                DeviceLoginInformation loginInformation;
                if(it != isLogin_.end() && it->second ) { // 已经登陆了
                    logger_.Info("<Device Login> : id {} has login",  id);
                    continue;
                }
                db_.DeviceLogin(id);
                isLogin_[id] = true;
            }
        }
    }

//    void WGDServer::TransportRun() {
//        //server_.Start();
//        client_.ConnectToServer();
//        StartHeartbeat();
//        while (true) {
//            std::string message;
//            if(!client_.RecData(message)) {
//                std::this_thread::sleep_for(std::chrono::milliseconds(10));
//                continue;
//            }
//            // TCPMessage message;
//            // server_.GetMessage(message);
//            std::cout << message << std::endl;
//            JsonManager json_message = JsonManager::FromString(message);
//            // 处理转发的消息
//            std::string ip = json_message["ip"].String();
//            int port = json_message["port"].Int();
//            std::string data = json_message["data"].String();
//            int sessionId = json_message["sessionID"].Int();
//            logger_.Info("Message from {}: {}", ip, port);
//            logger_.Info("Message: {}", data);
//
//            send_json["sessionID"] = sessionId;
//            if(data == "exit") {
//                send_json["data"] = "exit";
//                continue;
//            }
//            JsonManager json = JsonManager::FromString(data);
//            // 进行设备验证和注册
//            if(!HandleVerify(json, sessionId)){
//                // server_.Unicast(sessionId, "$Verify Failed*");
//                // server_.CloseSession(sessionId);
//                send_json["data"] = "exit";
//                client_.SendData(send_json.toString() + "$$");
//                continue;
//            }else RegisterDevice(sessionId);
//            // 处理具体逻辑
//            auto now_time = Time::now();
//            if(json.exists("type")) {
//                int id = sessionID_to_deviceID_[sessionId];
//                if(json["type"].String() == "GPS" || json["type"].String() == "LBS") {
//                    // 处理GPS信息
//                    std::string now_latitude = json["data"]["Latitude"].String(), now_longitude = json["data"]["Longitude"].String();
//                    HandleLocation(now_latitude, now_longitude, sessionId);
//                    // 处理第一次登陆信息
//                    auto it = isLogin_.find(id);
//                    DeviceLoginInformation loginInformation;
//                    if(it != isLogin_.end() && it->second ) { // 已经登陆了
//                        logger_.Info("<Device Login> : id {} has login",  id);
//                        continue;
//                    }
//                    // 设备登陆
//                    loginInformation.id = id;
//                    loginInformation.time = Time::formatTime(Time::now());
//                    loginInformation.status = 0;
//                    loginInformation.latitude = now_latitude;
//                    loginInformation.longitude = now_longitude;
//                    loginInformation.location = lastReGeo_;
//                    loginInformation.ip = ip;
//                    db_.UpdateDeviceLoginData(loginInformation);
//                    isLogin_[id] = true;
//                    logger_.Info("<Device Login> : id {}", id);
//                }else if(json["type"].String() == "Sensor") {
//                    HandleSensorData(json, sessionId);
//                }
//                db_.UpdateDeviceTime(id);
//                {
//                    std::lock_guard<std::mutex> lock(lastUpdateTimeMutex_);
//                    lastUpdateTime_[id] = Time::formatTime(now_time);
//                }
//
//            }
//        }
//    }

    void WGDServer::Stop() {
        heartbeatRunning_ = false;
        if (heartbeatThread_.joinable()) {
            heartbeatThread_.join();
        }
        logger_.Info("Stop WGDServer ...");
        server_.Stop();
    }

    void WGDServer::RegisterDevice(int sessionId) {
        int id = sessionID_to_deviceID_[sessionId];
        auto it = isRegistered_.find(id);
        if(it == isRegistered_.end()) {
            db_.RegisterDevice(id);
            isRegistered_[id] = true;
        }
    }

    bool WGDServer::HandleVerify(JsonManager& json, int sessionId) {
        auto it = isVerified_.find(sessionId);
        if(it == isVerified_.end()) { // SessionID 第一次验证
            if(json.exists("type")) {
                if(json["type"].String() == "verify") {
                    if(json["data"]["VerifyCode"].String() == "1037") {
                        // 验证成功
                        isVerified_[sessionId] = true;
                        sessionID_to_deviceID_[sessionId] = json["data"]["DeviceID"].Int();
                        logger_.Info("SessionID {} Verify Success", sessionId);
                    }else{
                        // 验证失败
                        isVerified_[sessionId] = false;
                        logger_.Info("SessionID {} Verify Failed", sessionId);
                    }
                }
            }
        }
        // SessionID 之前验证过
        return isVerified_[sessionId];
    }

    void WGDServer::HandleLocation(std::string& latitude, std::string& longitude, int sessionId) {
        double latitude_double = std::stod(latitude), longitude_double = std::stod(longitude);
        // 判断GPS是否改变
        if(std::fabs(latitude_double - lastLatitude_) > delta_ ||
           std::fabs(longitude_double - lastLongitude_) > delta_) {
            logger_.Info("GPS has changed: {}, {}", latitude, longitude);
            lastLatitude_ = latitude_double;
            lastLongitude_ = longitude_double;
            lastReGeo_ = AmapAPI::ReGeo(aMapKey_, latitude, longitude);
        }else{
            logger_.Info("GPS has not changed: {}, {}", latitude, longitude);
        }
        server_.Unicast(sessionId, "$A" + lastReGeo_ + "*"); // 发送位置信息给客户端
        logger_.Info("Now Position: {}", lastReGeo_);
    }

    void WGDServer::HandleSensorData(JsonManager& json, int sessionID) {
        auto now_time = Time::now();
        DeviceSensorInformation sensorInformation;
        sensorInformation.id = sessionID_to_deviceID_[sessionID];
        sensorInformation.time = Time::formatTime(now_time);
        sensorInformation.temperature1 = json["data"]["Temperature1"].Float();
        sensorInformation.temperature2 = json["data"]["Temperature2"].Float();
        sensorInformation.humidity1 = json["data"]["Humidity1"].Float();
        sensorInformation.humidity2 = json["data"]["Humidity2"].Float();
        sensorInformation.pressure = json["data"]["Pressure"].Float();
        sensorInformation.GasRes = json["data"]["GasRes"].Float();
        sensorInformation.PGas = json["data"]["PGas"].Float();
        sensorInformation.CO2 = json["data"]["CO2"].Float();
        db_.UpdateDeviceSensorInformation(sensorInformation);
        //TODO 处理异常数据
        //uint8_t 0,0,0,0,GasRes,H2,CO2,T2
        std::uint8_t data = 0;
        if(sensorInformation.temperature2 > 35) data |= 0x01;
//        if(sensorInformation.CO2 > 3000) data |= 0x02;
        if(sensorInformation.humidity2 < 20) data |= 0x04;
        if(sensorInformation.GasRes < 20000) data |= 0x08;
//        data |= 0x01;
//        data |= 0x02;
//        data |= 0x04;
//        data |= 0x08;
        std::string payload = "b";
        payload += static_cast<char>(data);
        server_.Unicast(sessionID, "$b" + payload + "*");
    }

    void WGDServer::CheckOffline() {
        auto now_time = Time::now();
        for (auto& [id, lastUpdateTime] : lastUpdateTime_) {
            std::lock_guard<std::mutex> lock(lastUpdateTimeMutex_);
            if(!isLogin_[id]) continue;
            if (Time::duration(Time::parseTime(lastUpdateTime), now_time) > timeout_) {
                isLogin_[id] = false;
                isLoginPosition_[id] = false;
                db_.DeviceLogout(id);
                logger_.Info("<Device Logout> : id {}", id);
            }
        }
    }

    void WGDServer::StartHeartbeat() {
        heartbeatRunning_ = true;
        heartbeatThread_ = std::thread([this]() {
            while (heartbeatRunning_) {
                CheckOffline();
                std::this_thread::sleep_for(std::chrono::seconds(1));  // 每隔1s执行
            }
        });
    }

}

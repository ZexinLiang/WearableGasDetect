#pragma once

#include "Utils/TCP.hpp"
#include "Utils/Logger.hpp"
#include "Utils/DataBase.hpp"
#include "AmapAPI.hpp"
#include "SQLiteDataBase.hpp"
#include "Time.hpp"

using namespace Utils::TCP;
using namespace Utils::Logger;
using namespace Utils::DataBase;
using namespace Utils::JSON;

namespace Backend {

    class WGDServer {
    public:
        WGDServer(int port, SQLiteDataBase& db);
        void Run();
        void TransportRun();
        void Stop();

    private:
        Logger logger_;
         TCPServer server_;
//        TCPClient client_;
        SQLiteDataBase& db_;

        std::map<int, bool> isVerified_; // 检测SessionID是否是验证过的
        std::map<int, int> sessionID_to_deviceID_; // SessionID对应设备ID
        std::map<int, bool> isRegistered_; // 检测ID是不是注册过的
        std::map<int, bool> isLogin_; // 检测ID是不是登录的，已经登陆为 true，离线或异常为 false
        std::map<int, bool> isLoginPosition_;
        std::map<int, std::string> lastUpdateTime_; // 检测ID超时断连
        const int timeout_ = 3; // 超过 3s 没有响应则断开连接
        std::mutex lastUpdateTimeMutex_;

        std::string aMapKey_ = "1d29422ef95b36ae7348d311ff9c5e06";
        double lastLatitude_ = 39.9042, lastLongitude_ = 116.4074, delta_ = 0.01;
        std::string lastReGeo_ = "";

        void RegisterDevice(int sessionId);

        void HandleMessage(TCPMessage& message);
        bool HandleVerify(JsonManager& json, int sessionId);
        void HandleLocation(std::string& latitude, std::string& longitude, int sessionId);
        void HandleSensorData(JsonManager& json, int sessionId);

        // 离线检测
        void StartHeartbeat();
        void CheckOffline();

        std::thread heartbeatThread_;
        std::atomic<bool> heartbeatRunning_ = false;

        JsonManager send_json = JsonManager::FromString("{}");
    };

}

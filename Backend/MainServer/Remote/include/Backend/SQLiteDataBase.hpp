#pragma once

#include "BasicType.hpp"
#include "Utils/DataBase.hpp"
#include "Utils/Logger.hpp"
#include "Time.hpp"

using namespace Utils::DataBase;
using namespace Utils::Logger;

namespace Backend {

    using SQLiteWrapperPtr = std::shared_ptr<SQLiteWrapper>;
    using LoggerPtr = std::shared_ptr<Logger>;

    class SQLiteDataBase {
    public:
        SQLiteDataBase(const std::string& dbName, bool consoleLogger = false, const std::string &logFile = "log/SQLiteDataBase.log");

        // User
        int QueryUserPassword(const std::string& username, std::string& password);
        bool SetUserPassword(const std::string& username, const std::string& password);
        int RegisterUser(const std::string& username, const std::string& password);

        // Device
        int QueryAllDevices(DeviceCount& deviceCount);
        // int QueryOnlineDevices();
        // int QueryActiveDevices();
        // int QueryAlarmDevices();
        int QueryDeviceActivities(std::vector<DeviceActivity> &activities);
        int QueryDeviceList(std::vector<DeviceBasicInformation> &list);

        int RegisterDevice(int id);
        void UpdateDeviceSensorInformation(DeviceSensorInformation &sensorInformation);
        void UpdateDeviceLoginData(DeviceLoginInformation &loginInformation);
        void UpdateDeviceTime(int id); // 更新设备最后一次活动时间
        void DeviceLogin(int id); // 设备登录
        void DeviceLogout(int id); // 设备离线
        void DeviceError(int id); // 设备异常
    private:
        std::string dbName_;
        SQLiteWrapper dbWrapper_;
        Logger logger_;

        void ConfigureLogger(bool consoleLogger, const std::string &logFile);
        void InitTable();
    };
}

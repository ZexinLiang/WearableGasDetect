#include "Backend/SQLiteDataBase.hpp"
#include <algorithm>

using namespace Utils::DataBase;

namespace Backend {

    SQLiteDataBase::SQLiteDataBase(const std::string &dbName, bool consoleLogger, const std::string &logFile) :
        dbName_(dbName) , dbWrapper_(dbName_){
        ConfigureLogger(consoleLogger, logFile);
        InitTable();
    }

    void SQLiteDataBase::ConfigureLogger(bool consoleLogger, const std::string &logFile) {
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

    /*
     * 初始化数据库表结构，括用户表，设备基本信息表，设备登录信息表，设备传感器数据表，报警记录表
     */
    void SQLiteDataBase::InitTable() {
        {// 用户表
            SQLiteKeyType user_columns;
            user_columns["id"] = INTEGER;
            user_columns["username"] = TEXT;
            user_columns["password"] = TEXT;
            if(!dbWrapper_.CreateTable("user", user_columns)) {
                logger_.Error("Create Table user Failed");
                return;
            }
        }
        {// 设备基本信息表
            SQLiteKeyType device_columns;
            device_columns["id"] = INTEGER;
            device_columns["name"] = TEXT;
            device_columns["status"] = INTEGER;
            device_columns["last_update"] = TEXT;
            device_columns["last_login"] = TEXT;
            if(!dbWrapper_.CreateTable("device", device_columns)) {
                logger_.Error("Create Table device Failed");
                return;
            }
        }
        {// 设备登录信息表
            SQLiteKeyType device_login_columns;
            device_login_columns["id"] = INTEGER;
            device_login_columns["time"] = TEXT;
            device_login_columns["status"] = INTEGER;
            device_login_columns["latitude"] = TEXT;
            device_login_columns["longitude"] = TEXT;
            device_login_columns["location"] = TEXT;
            device_login_columns["ip"] = TEXT;
            if(!dbWrapper_.CreateTable("device_login", device_login_columns)) {
                logger_.Error("Create Table device_login Failed");
                return;
            }
        }
        {// 设备传感器数据表
            SQLiteKeyType device_sensor_columns;
            device_sensor_columns["id"] = INTEGER;
            device_sensor_columns["time"] = TEXT;
            device_sensor_columns["humidity1"] = REAL;
            device_sensor_columns["humidity2"] = REAL;
            device_sensor_columns["temperature1"] = REAL;
            device_sensor_columns["temperature2"] = REAL;
            device_sensor_columns["pressure"] = REAL;
            device_sensor_columns["GasRes"] = REAL;
            device_sensor_columns["PGas"] = REAL;
            device_sensor_columns["CO2"] = REAL;
            if(!dbWrapper_.CreateTable("device_sensor", device_sensor_columns)) {
                logger_.Error("Create Table device_sensor Failed");
                return;
            }
        }
        {// 报警记录表
            SQLiteKeyType device_alarm_columns;
            device_alarm_columns["id"] = INTEGER;
            device_alarm_columns["time"] = TEXT;
            device_alarm_columns["type"] = INTEGER;
            device_alarm_columns["status"] = INTEGER;
            device_alarm_columns["description"] = TEXT;
            device_alarm_columns["action"] = TEXT;
            if(!dbWrapper_.CreateTable("device_alarm", device_alarm_columns)) {
                logger_.Error("Create Table device_alarm Failed");
                return;
            }
        }
        {// 设备事件表
            SQLiteKeyType device_event_columns;
            device_event_columns["id"] = INTEGER;
            device_event_columns["time"] = TEXT;
            device_event_columns["type"] = INTEGER;
            device_event_columns["description"] = TEXT;
            if(!dbWrapper_.CreateTable("device_event", device_event_columns)) {
                logger_.Error("Create Table device_event Failed");
                return;
            }
        }
        logger_.Info("Init Table Successfully");
    }

    // 1：成功，0：密码错误，-1:用户不存在
    int SQLiteDataBase::QueryUserPassword(const std::string& username, std::string& password) {
        SQLiteQueryResult query_result = dbWrapper_.QueryDataCondition("user", "username = '" + username + "'");
        if(query_result.empty()) {
            logger_.Error("<Query Password> Failed: User {} not exist", username);
            return -1;
        }
        for(auto& row : query_result) {
            if(row["username"] == username) {
                if(password == row["password"]) {
                    logger_.Info("<Query Password> Successfully: User {} ", username);
                    return 1;
                }
            }
        }
        logger_.Error("<Query Password> Failed: User {} password incorrect", username);
        return false;
    }
    bool SQLiteDataBase::SetUserPassword(const std::string& username, const std::string& password) {
        SQLiteKeyValue data;
        data["password"] = password;
        std::string condition = "username = '" + username + "'";
        if(!dbWrapper_.UpdateData("user", data, condition)) {
            logger_.Error("<Set Password> Failed: User {} password update failed", username);
            return false;
        }
        logger_.Info("<Set Password> Success: User {} password updated", username);
        return true;
    }

    // 1：成功，0：用户已经存在, -3：注册失败
    int SQLiteDataBase::RegisterUser(const std::string& username, const std::string& password) {
        SQLiteKeyValue data;
        data["username"] = username;
        data["password"] = password;
        auto result = dbWrapper_.QueryDataCondition("user", "username = '" + username + "'");
        if(!result.empty()) {
            logger_.Error("<Register User> Failed: User {} already exists", username);
            return 0;
        }
        if(!dbWrapper_.InsertData("user", data)) {
            logger_.Info("<Register User> Failed: User {} already exists", username);
            return -3;
        }
        logger_.Info("<Register User> Success: User {} registered", username);
        return 1;
    }

    // 查询仪表板所需要的设备信息
    int SQLiteDataBase::QueryAllDevices(DeviceCount& deviceCount) {
        SQLiteQueryResult result = dbWrapper_.QueryData("device");
        deviceCount.allDevices = result.size();
        for(auto& row : result) {
            if(row["status"] == "1") {
                deviceCount.onlineDevices++;
                auto timestamp = Time::parseTime(row["last_login"]);
                auto now = Time::now();
                if(Time::duration(timestamp, now) > 60 * 60 * 1) {
                    // 连续在线1小时，认为是活跃设备
                    deviceCount.activeDevices++;
                }
            }else if(row["status"] == "2") {
                deviceCount.alarmDevices++;
            }
        }
        return true;
    }

    // 查询设备的活动情况
    int SQLiteDataBase::QueryDeviceActivities(std::vector<DeviceActivity>& activities) {
        SQLiteQueryResult result = dbWrapper_.QueryData("device_event");
        std::vector<DeviceActivity> all_activities;
        auto now = Time::now();
        for(auto row : result) {
            DeviceActivity activity;
            auto tp = Time::parseTime(row["time"]);
            activity.id = std::stoi(row["id"]);
            activity.name = "设备" + row["id"];
            activity.time = row["time"];
            activity.type = std::stoi(row["type"]);
            // 设备上线（1），设备离线（2），设备异常（3），配置更新（4）
            switch(activity.type) {
                case 1:
                    activity.description = "上线";break;
                case 2:
                    activity.description = "离线";break;
                case 3:
                    activity.description = "设备异常";break;
                case 4:
                    activity.description = "配置更新";break;
                default:
                    activity.description = "未知";break;
            }
            all_activities.push_back(activity);
        }
        // 按时间降序排列（最新的在前）
        std::sort(all_activities.begin(), all_activities.end(), CompareDeviceActivity());

        int count = 0;
        for (const auto& act : all_activities) {
            if (count >= 10) break;
            activities.push_back(act);
            ++count;
        }
        return count; // 返回实际添加的活动数量
    }

    // 查询设备的基本状态
    int SQLiteDataBase::QueryDeviceList(std::vector<DeviceBasicInformation> &list) {
        SQLiteQueryResult all_devices = dbWrapper_.QueryData("device");
        int device_count = all_devices.size();
        for(auto &device: all_devices) {
            DeviceBasicInformation device_info;
            int id = std::stoi(device["id"]);
            device_info.id = id;
            device_info.name = device["name"];
            device_info.status = std::stoi(device["status"]);
            device_info.lastLoginTime = device["last_login"];
            SQLiteQueryResult sensor_information = dbWrapper_.QueryDataCondition("device_sensor", "id="+device["id"]);
            if(!sensor_information.empty()) {
                auto last_time = Time::parseTime(sensor_information[0]["time"]);
                float temperature = std::stof(sensor_information[0]["temperature2"]);
                float humidity = std::stof(sensor_information[0]["humidity2"]);
                for (auto &sensor : sensor_information) {
                    auto time = Time::parseTime(sensor["time"]);
                    if(time > last_time) {
                        last_time = time;
                        temperature = std::stof(sensor["temperature2"]);
                        humidity = std::stof(sensor["humidity2"]);
                    }
                }
                device_info.temperature = temperature;
                device_info.humidity = humidity;
            }else {
                device_info.temperature = 0;
                device_info.humidity = 0;
            }
            list.emplace_back(device_info);
        }
        sort(list.begin(), list.end(), CompareDeviceBasicInformation());
        logger_.Info("<Query Device List> Success: {} devices queried", device_count);
        return device_count;
    }

    int SQLiteDataBase::RegisterDevice(int id) {
        auto result = dbWrapper_.QueryDataCondition("device", "id="+std::to_string(id));
        if(result.empty()) {
            SQLiteKeyValue data;
            data["id"] = std::to_string(id);
            data["name"] = "设备" + std::to_string(id);
            if(!dbWrapper_.InsertData("device", data)) {
                logger_.Error("<Register Device> Failed: Device {} already exists", id);
                return -1;
            }
            logger_.Info("<Register Device> Success: Device {} registered", id);
            return 1;
        }
        logger_.Info("<Register Device> Success: Device {} already exists", id);
        return 0;
    }

    // 更新设备传感器数据表 device_sensor
    void SQLiteDataBase::UpdateDeviceSensorInformation(DeviceSensorInformation &sensorInformation) {
        SQLiteKeyValue data;
        data["id"] = std::to_string(sensorInformation.id);
        data["time"] = sensorInformation.time;
        data["humidity1"] = std::to_string(sensorInformation.humidity1);
        data["humidity2"] = std::to_string(sensorInformation.humidity2);
        data["temperature1"] = std::to_string(sensorInformation.temperature1);
        data["temperature2"] = std::to_string(sensorInformation.temperature2);
        data["pressure"] = std::to_string(sensorInformation.pressure);
        data["GasRes"] = std::to_string(sensorInformation.GasRes);
        data["PGas"] = std::to_string(sensorInformation.PGas);
        data["CO2"] = std::to_string(sensorInformation.CO2);
        if(!dbWrapper_.InsertData("device_sensor", data)) {
            logger_.Error("<Update Device Sensor Information> Failed: id {}", sensorInformation.id);
            return;
        }
        logger_.Info("<Update Device Sensor Information> Success: id {}", sensorInformation.id);
    }

    // 更新登陆数据
    // 更新设备登录数据表 device_login 和设备基本信息表 device 中的last_login，设备事件表 device_event
    void SQLiteDataBase::UpdateDeviceLoginData(DeviceLoginInformation &loginInformation) {
        { // 更新设备登录数据表 device_login
            SQLiteKeyValue data;
            data["id"] = std::to_string(loginInformation.id);
            data["time"] = loginInformation.time;
            data["status"] = std::to_string(loginInformation.status);
            data["ip"] = loginInformation.ip;
            data["location"] = loginInformation.location;
            data["latitude"] = loginInformation.latitude;
            data["longitude"] = loginInformation.longitude;
            if(!dbWrapper_.InsertData("device_login", data)) {
                logger_.Error("<Update Device Login Information> Failed: id {}", loginInformation.id);
                return;
            }
        }
        { // 更新基本设备表里面的登陆时间
            SQLiteKeyValue data;
            data["last_login"] = loginInformation.time;
            data["status"] = "1";
            std::string consition = "id = " + std::to_string(loginInformation.id);
            if(!dbWrapper_.UpdateData("device", data, consition)) {
                logger_.Error("<Update Device Login Information> Failed: id {}", loginInformation.id);
                return;
            }
        }
        { // 设备事件表 device_event，添加登陆事件
            SQLiteKeyValue data;
            data["id"] = std::to_string(loginInformation.id);
            data["time"] = loginInformation.time;
            data["type"] = "1";
            data["description"] = "设备上线";
            if(!dbWrapper_.InsertData("device_event", data)) {
                logger_.Error("<Insert Device Event> Failed: id {}", loginInformation.id);
                return;
            }
        }
        logger_.Info("<Update Device Login Information> Success: id {}", loginInformation.id);
    }

    void SQLiteDataBase::UpdateDeviceTime(int id) {
        SQLiteKeyValue data;
        data["last_update"] = Time::formatTime(Time::now());
        std::string condition = "id = " + std::to_string(id);
        if(!dbWrapper_.UpdateData("device", data, condition)) {
            logger_.Error("<Update Device Time> Failed: id {}", id);
            return;
        }
        logger_.Info("<Update Device Time> Success: id {}", id);
    }

    void SQLiteDataBase::DeviceLogin(int id) {
        SQLiteKeyValue data;
        std::string condition = "id=" + std::to_string(id);
        data["last_login"] = Time::formatTime(Time::now());
        data["last_update"] = Time::formatTime(Time::now());
        data["status"] = "1";
        if(!dbWrapper_.UpdateData("device", data, condition)) {
            logger_.Error("<Device Login> Failed: id {}",  id);
            return;
        }
        logger_.Info("<Device Login> Success: id {}",  id);
    }

    void SQLiteDataBase::DeviceLogout(int id) {
        auto now_time = Time::now();
        {
            SQLiteKeyValue data;
            std::string condition = "id=" + std::to_string(id);
            data["last_update"] = Time::formatTime(now_time);
            data["status"] = "0";
            if(!dbWrapper_.UpdateData("device", data, condition)) {
                logger_.Error("<Device Logout> Failed: id {}",  id);
                return;
            }
        }
        { // 设备事件表 device_event，添加登陆事件
            SQLiteKeyValue data;
            data["id"] = std::to_string(id);
            data["time"] = Time::formatTime(now_time);
            data["type"] = "2";
            data["description"] = "设备离线";
            if(!dbWrapper_.InsertData("device_event", data)) {
                logger_.Error("<Insert Device Event> Failed: id {}", id);
                return;
            }
        }
        logger_.Info("<Device Logout> Success: id {}",  id);
    }

    void SQLiteDataBase::DeviceError(int id) {
        auto now_time = Time::now();
        {
            SQLiteKeyValue data;
            std::string condition = "id=" + std::to_string(id);
            data["last_update"] = Time::formatTime(now_time);
            data["status"] = "2";
            if(!dbWrapper_.UpdateData("device", data, condition)) {
                logger_.Error("<Device Error> Failed: id {}",  id);
                return;
            }
        }
        { // 设备事件表 device_event，添加登陆事件
            SQLiteKeyValue data;
            data["id"] = std::to_string(id);
            data["time"] = Time::formatTime(now_time);
            data["type"] = "3";
            data["description"] = "设备异常";
            if(!dbWrapper_.InsertData("device_event", data)) {
                logger_.Error("<Insert Device Event> Failed: id {}", id);
                return;
            }
        }

        logger_.Info("<Device Error> Success: id {}",  id);
    }

}
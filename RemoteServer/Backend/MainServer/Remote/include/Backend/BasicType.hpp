#pragma once
#include "Time.hpp"

namespace Backend {


    // 设备数量
    struct DeviceCount {
        unsigned int allDevices;
        unsigned int onlineDevices;
        unsigned int activeDevices;
        unsigned int alarmDevices;
    };

    // 设备活动
    struct DeviceActivity {
        std::string time;
        int id;
        std::string name;
        int type;
        std::string description;
    };
    struct CompareDeviceActivity {
        bool operator()(const DeviceActivity& a, const DeviceActivity& b) const {
            auto a_time = Time::parseTime(a.time);
            auto b_time = Time::parseTime(b.time);
            return a_time > b_time; // 降序排列
        }
    };

    // 设备传感器信息
    struct DeviceSensorInformation {
        int id;
        std::string time;
        float humidity1;
        float humidity2;
        float temperature1;
        float temperature2;
        float pressure;
        float GasRes;
        float PGas;
        float CO2;
    };
    struct CompareDeviceSensorInformationByID {
        bool operator()(const DeviceSensorInformation &a, const DeviceSensorInformation &b) const {
            return a.id < b.id;
        }
    };
    struct CompareDeviceSensorInformationByTime {
        bool operator()(const DeviceSensorInformation &a, const DeviceSensorInformation &b) const {
            system_clock::time_point a_time = Time::parseTime(a.time);
            system_clock::time_point b_time = Time::parseTime(b.time);
            return a_time > b_time; // 降序排列
        }
    };

    // 设备基本状态
    struct DeviceBasicInformation {
        int  id;
        std::string name;
        int status;
        std::string lastLoginTime;
        float temperature;
        float humidity;
    };
    struct CompareDeviceBasicInformation {
        bool operator()(const DeviceBasicInformation& a, const DeviceBasicInformation& b) const {
            return a.id < b.id;
        }
    };

    struct DeviceLoginInformation {
        int id;
        std::string time;
        int status;
        std::string latitude;
        std::string longitude;
        std::string location;
        std::string ip;
    };

}
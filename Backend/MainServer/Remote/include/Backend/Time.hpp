#pragma once

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace std::chrono;

namespace Backend {
namespace Time {


    static system_clock::time_point now() {
        return system_clock::now();
    }

    // 手动解析 YYYY-MM-DD HH:MM:SS.SSS 时间字符串
    static system_clock::time_point parseTime(const string &time_str) {
        int year = 0, month = 0, day = 0;
        int hour = 0, minute = 0, second = 0;
        int millisecond = 0;
        char delimiter1, delimiter2, delimiter3, delimiter4, delimiter5;

        // 解析格式：YYYY-MM-DD HH:MM:SS.SSS
        if (sscanf(time_str.c_str(), "%d%c%d%c%d %d%c%d%c%d%c%d",
                   &year, &delimiter1, &month, &delimiter2, &day,
                   &hour, &delimiter3, &minute, &delimiter4, &second,
                   &delimiter5, &millisecond) != 12 ||
            delimiter1 != '-' || delimiter2 != '-' ||
            delimiter3 != ':' || delimiter4 != ':' ||
            delimiter5 != '.') {
            throw std::runtime_error("Invalid time format with milliseconds");
        }

        // 构造 tm 结构体
        std::tm tm = {};
        tm.tm_year = year - 1900;  // 年份从 1900 开始
        tm.tm_mon = month - 1;     // 月份从 0 开始（0~11）
        tm.tm_mday = day;          // 日期
        tm.tm_hour = hour;         // 小时
        tm.tm_min = minute;        // 分钟
        tm.tm_sec = second;        // 秒
        tm.tm_isdst = -1;          // 不确定是否为夏令时

        // 转换为 time_t 再转为 system_clock::time_point
        std::time_t t = std::mktime(&tm);
        if (t == std::time_t(-1)) {
            throw std::runtime_error("Time conversion failed");
        }
        // 手动添加毫秒偏移
        auto tp = system_clock::from_time_t(t) + milliseconds(millisecond);
        return tp;
    }

    // 格式化函数
    static string formatTime(const system_clock::time_point &tp) {
        auto t = system_clock::to_time_t(tp);
        auto ms = duration_cast<milliseconds>(tp.time_since_epoch()).count() % 1000;
        stringstream ss;
        ss << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S")
           << "." << setw(3) << setfill('0') << ms;
        return ss.str();
    }

    static int duration(const system_clock::time_point &tp1, const system_clock::time_point &tp2) {
        return duration_cast<seconds>(tp2 - tp1).count();
    }


}
}



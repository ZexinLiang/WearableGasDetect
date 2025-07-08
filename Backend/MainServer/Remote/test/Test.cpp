#include "Utils/TCP.hpp"
#include "Utils/Logger.hpp"
#include "Utils/DataBase.hpp"
#include "Backend/AmapAPI.hpp"
#include "Backend/Time.hpp"

using namespace Backend;

void Test_AmapAPI() {
    std::string amap_key = "1d29422ef95b36ae7348d311ff9c5e06";
    std::string latitude = "39.90923", longitude = "116.397428";
    std::cout << AmapAPI::ReGeo(amap_key, latitude, longitude) << std::endl;
}

void Test_Time() {
    try {
        auto tp = Time::parseTime("2025-04-05 14:30:45.050");
        std::cout << "Parsed OK: " << Time::formatTime(tp) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}




int main() {
    Test_Time();
}
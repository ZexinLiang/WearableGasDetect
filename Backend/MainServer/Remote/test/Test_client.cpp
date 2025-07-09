#include "Utils/TCP.hpp"
#include "Utils/JSON.hpp"

using namespace Utils::TCP;
using namespace Utils::JSON;

std::string verify_message = R"({
  "type": "verify",
  "data": {
    "VerifyCode": "1037",
    "DeviceID": 1
  }
})";

std::string GPS_message = R"({
    "type": "GPS",
    "data": {
        "Latitude": "39.9042",
        "Longitude": "116.4074"
    }
})";

std::string sensor_message = R"({
    "type": "Sensor",
    "data": {
        "CO2": 1000,
        "GasRes": 1000,
        "PGas": 1000,
        "Humidity1": 1000,
        "Humidity2": 50,
        "Pressure": 99962.398437,
        "Temperature1": 33,
        "Temperature2": 33
    }
})";


int main() {
     TCPClient client("47.99.180.201", 3030);
//    TCPClient client("127.0.0.1", 3030);
    if(client.ConnectToServer()) {
        std::cout << "Connect to server successfully" << std::endl;
    }else {
        std::cout << "Connect to server failed" << std::endl;
        return 0;
    }
    client.SendData(verify_message + "$$");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::string res_message;
    client.RecData(res_message);
    std::cout << res_message << std::endl;
    client.SendData(GPS_message + "$$");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    client.RecData(res_message);
    std::cout << res_message << std::endl;
    JsonManager json = JsonManager::FromString(sensor_message);
    for(int i = 1; i <= 100; i++) {
        std::cout << "Sending sensor message " << i << std::endl;
        json["data"]["Humidity1"] = random() % 100;
        json["data"]["Humidity2"] = random() % 100;
        json["data"]["Pressure"] = random() % 1000;
        json["data"]["Temperature1"] = random() % 50;
        json["data"]["Temperature2"] = random() % 50;
        client.SendData(json.toString() + "$$");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    client.SendData(GPS_message + "$$");

}
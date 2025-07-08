#include "Utils/TCP.hpp"
#include "Utils/JSON.hpp"
#include "Backend/Time.hpp"

using namespace Utils::TCP;
using namespace Utils::JSON;
using namespace Backend;

//struct TCPMessage {
//    TimePoint time;
//    int sessionId;
//    int port;
//    std::string ip;
//    std::string data;
//};
int main() {
    TCPServer wgd_server(3030, "$$");
    TCPServer remote_server(3031, "$$");
    wgd_server.Start();
    remote_server.Start();
    std::cout << "Start Server!" << std::endl;
    while(true) {
        TCPMessage wgd_message;
        wgd_server.GetMessage(wgd_message);
        if(wgd_message.data.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            continue;
        }
        JsonManager json = JsonManager::FromString("{}");
        // 转发消息
        json["time"] = Time::formatTime(Time::now());
        json["sessionID"] = wgd_message.sessionId;
        json["port"] = wgd_message.port;
        json["ip"] = wgd_message.ip;
        json["data"] = wgd_message.data;
        std::cout << "wgd_server" << wgd_message.data << std::endl;
        // 发送给服务器
        remote_server.Broadcast(json.toString() + "$$");
        // 处理返回的消息
        TCPMessage rem_message;
        remote_server.GetMessage(rem_message);
        if(rem_message.data.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            continue;
        }
        JsonManager rem_json = JsonManager::FromString(rem_message.data);
        int toid = rem_json["sessionID"].Int();
        std::string todata = rem_json["data"].String();
        std::cout << "toid: " << toid << " todata: " << todata << std::endl;
        if(todata == "exit") {
            wgd_server.CloseSession(toid);
            continue;
        }else if(todata == "verify success") continue;
        std::cout << "remote_server" << rem_message.data << std::endl;
        wgd_server.Unicast(toid, "$" + todata + "*");
        remote_server.CleanExpiredSession();
    }

}
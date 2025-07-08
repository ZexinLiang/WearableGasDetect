#include "Backend/WGDServer.hpp"
#include "Backend/WebServer.hpp"

using namespace Backend;

std::atomic<bool> stopSignal(false);
void SignalHandler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        stopSignal = true;
    }
}
int main() {
    SQLiteDataBase database("data/data.db");
    WebServer webServer(1717, database, true);
    WGDServer wgdServer(3030, database);
    std::thread webThread([&]() {
        webServer.Run();
    });
    std::thread wgdThread([&]() {
        wgdServer.Run();
    });
    webThread.join();
    wgdThread.detach();

    std::signal(SIGINT, SignalHandler);     // Ctrl + C
    std::signal(SIGTERM, SignalHandler);   // kill 命令等

    std::cout << "Server is running... Press Ctrl+C to exit." << std::endl;

    while (!stopSignal) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Shutting down server..." << std::endl;
    wgdServer.Stop();
    webServer.Stop();
    return 0;
}
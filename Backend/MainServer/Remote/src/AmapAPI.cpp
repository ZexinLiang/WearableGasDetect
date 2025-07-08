#include "Backend/AmapAPI.hpp"

using namespace Utils::Network;
using namespace Utils::JSON;

namespace Backend :: AmapAPI{

    std::string ReGeo(std::string& amap_key, std::string& latitude, std::string& longitude){
        std::string url = "https://restapi.amap.com/v3/geocode/regeo?key=" + amap_key + "&location=" + longitude + "," + latitude + "&language=en";
        auto response = Request::Get(url, {});
        if(response.status == -1) {
            std::cerr << "Request Failed!" << std::endl;
            return "";
        }
        JsonManager result = JsonManager::FromString(response.text);
        if (result.exists("regeocode") && result["status"].String() == "1") {
            auto formatted_address = result["regeocode"]["formatted_address"].String();
            return formatted_address;
        }
        return "";
    }



}
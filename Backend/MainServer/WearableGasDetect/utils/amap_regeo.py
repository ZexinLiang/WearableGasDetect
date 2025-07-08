import requests
import json

def amap_geocode(amap_key, longitude, latitude):
    """
    使用高德地图API将经纬度转换为包含省市区三级的地址信息
    
    :param amap_key: 高德地图API的key
    :param longitude: 经度
    :param latitude: 纬度
    :return: 地址信息字典, 包含详细地址信息; 如果失败则返回None
    """
    url = 'https://restapi.amap.com/v3/geocode/regeo?key=' + amap_key + '&location=' + longitude + ',' + latitude + '&language=en'
    
    try:
        response = requests.get(url)
        
        result = json.loads(response.content.decode('utf-8'))
        
        if result["status"] == "1" and result["regeocode"]:
            address_component = result["regeocode"]["addressComponent"]
            province = address_component["province"]
            city = address_component["city"]
            district = address_component["district"]

            all_address = result["regeocode"]["formatted_address"]

            # 拼接省市区三级地址
            if city != []:
                full_address = f"{province} {city} {district}"
            else:
                full_address = f"{province} {district}"
            return all_address
        else:
            print("无法获取地址信息")
            return None
    except Exception as e:
        print("请求过程中发生异常:", str(e))
        return None

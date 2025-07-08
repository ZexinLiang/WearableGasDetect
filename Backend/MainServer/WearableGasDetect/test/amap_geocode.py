from utils import amap_geocode

# 示例用法
if __name__ == "__main__":

    amap_key = "3f97f3dce8b62b205f6f25dc2830e942"
    
    # 示例经纬度（北京天安门）
    longitude = "116.4074"
    latitude = "39.9042"
    
    address = amap_geocode(amap_key, longitude, latitude)
    if address:
        print(f"地址信息: {address}")
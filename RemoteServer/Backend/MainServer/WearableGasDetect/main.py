from utils import AsyncTCPServer, amap_geocode
import asyncio
import json
import logging
import os

server = AsyncTCPServer('0.0.0.0', 3030)

amap_key = "3f97f3dce8b62b205f6f25dc2830e942"

last_position = ""
last_GPS = [116.4074, 39.9042]
delta_GPS = 0.01

logger = logging.getLogger(__name__)  # 获取当前模块的logger
logger.setLevel(logging.DEBUG)  # 设置logger级别
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')  # 创建日志格式器
 
# 创建一个handler，用于写入日志文件
if not os.path.exists('./cache'):
    os.mkdir('./cache')
file_handler = logging.FileHandler('./cache/WearableGasDectect.log')
file_handler.setFormatter(formatter)  # 为handler设置格式器
logger.addHandler(file_handler)  # 将handler添加到logger中


async def main_loop(server):
    global last_position, last_GPS
    while True:
        message = await server.message_queue.get()  # ✅ 异步等待消息
        if message:
            print(f"Received message from client {message['client_id']}: {message['message']}")
            logger.info(f"Received message from {message['client_address']}: {message['client_port']}")
            logger.info(f"Message: {message['message']}")
            try:
                json_data = json.loads(message['message'])
            except json.JSONDecodeError as e:
                print(f"Error decoding JSON: {e}")
                continue
            print(f"Message Type: {json_data['type']}")
            if json_data['type'] == 'GPS' or json_data['type'] == 'LBS':
                lat = float(json_data['data'].get("Latitude", 0.0))
                lon = float(json_data['data'].get("Longitude", 0.0))
                now_GPS = [lat, lon]
                print("GPS:", now_GPS[0], now_GPS[1])
                if abs(now_GPS[0] - last_GPS[0]) > delta_GPS or abs(now_GPS[1] - last_GPS[1]) > delta_GPS:
                    print("GPS改变")
                    last_GPS = now_GPS
                    last_position = amap_geocode(amap_key, str(now_GPS[1]), str(now_GPS[0]))
                else:
                    print("GPS未改变")
                server.send_message(message['client_id'], "$A" + last_position + "*")
            print(f"当前位置: {last_position}")
        
        await asyncio.sleep(0.1)  # ✅ 异步让出控制权

if __name__ == "__main__":
    server = AsyncTCPServer()
    
    try:
        loop = asyncio.get_event_loop()
        loop.create_task(server.start())  # 启动TCP服务
        loop.run_until_complete(main_loop(server))  # 启动主业务循环
    except KeyboardInterrupt:
        server.stop()
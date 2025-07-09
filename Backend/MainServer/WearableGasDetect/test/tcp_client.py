from utils import TCPClient
import asyncio
import time


GPS_message = '{ "type": "GPS", "data": { "Latitude": "30.5166103", "Longitude": "114.4266997" } }'


# 示例用法
if __name__ == "__main__":
    client = TCPClient("127.0.0.1", 3030)
    client.connect()

    while True:
        data = input("Enter message: ")
        if data == "exit":
            # 获取消息（非阻塞）
            for _ in range(10):
                msg = client.get_message()
                if msg:
                    print("Received:", msg)
            client.close()
            break
        # 示例发送消息
        client.send(GPS_message)
        for _ in range(10):
            msg = client.get_message()
            if msg:
                print("Postion:", msg)
                break
            else:
                time.sleep(0.5)

        

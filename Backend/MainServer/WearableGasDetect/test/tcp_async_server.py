from utils import AsyncTCPServer
import asyncio

async def main_loop(server):
    while True:
        message = await server.message_queue.get()  # ✅ 异步等待消息
        if message:
            print(f"Received message from client {message['client_id']}: {message['message']}")
            server.send_message(message['client_id'], "Hello from server!")
        await asyncio.sleep(0.1)  # ✅ 异步让出控制权

if __name__ == "__main__":
    server = AsyncTCPServer()
    
    try:
        loop = asyncio.get_event_loop()
        loop.create_task(server.start())  # 启动TCP服务
        loop.run_until_complete(main_loop(server))  # 启动主业务循环
    except KeyboardInterrupt:
        server.stop()
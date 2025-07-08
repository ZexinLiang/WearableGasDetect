from utils import TCPServer
import time

# 示例使用
if __name__ == "__main__":
    server = TCPServer()
    server.start()

    try:
        while True:
            msg = server.get_message()
            if msg:
                print("[RECV]", msg)
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("Shutting down server...")
        server.stop()
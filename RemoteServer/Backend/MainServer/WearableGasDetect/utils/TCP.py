import asyncio
from asyncio import Queue
from time import strftime, localtime
import queue
import socket
import threading
from datetime import datetime
import uuid

class ClientSession:
    def __init__(self, conn: socket.socket, address):
        self.conn = conn
        self.address = address  # (ip, port)
        self.id = str(uuid.uuid4())[:8]  # 简短唯一标识
        self.seq = 0  # 消息序号
        self.lock = threading.Lock()

    def send(self, message: str):
        with self.lock:
            try:
                self.conn.sendall((message + '\n').encode('utf-8'))
            except Exception as e:
                print(f"[{self.address}] Send error: {e}")

    def close(self):
        with self.lock:
            try:
                self.conn.shutdown(socket.SHUT_RDWR)
            except Exception:
                pass
            self.conn.close()

class TCPServer:
    def __init__(self, host='0.0.0.0', port=3030):
        self.host = host
        self.port = port
        self.server_socket = None
        self.clients = {}  # id -> ClientSession
        self.message_queue = queue.Queue()
        self.running = threading.Event()

    def start(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(100)
        self.server_socket.setblocking(True)

        self.running.set()
        print(f"Server started on {self.host}:{self.port}")

        threading.Thread(target=self._accept_loop, daemon=True).start()

    def _accept_loop(self):
        while self.running.is_set():
            try:
                conn, addr = self.server_socket.accept()
                session = ClientSession(conn, addr)
                self.clients[session.id] = session
                print(f"[+] New connection {addr}, id={session.id}")
                threading.Thread(target=self._handle_client, args=(session,), daemon=True).start()
            except Exception as e:
                print(f"[!] Accept error: {e}")

    def _handle_client(self, session: ClientSession):
        conn = session.conn
        addr = session.address
        try:
            while self.running.is_set():
                data = conn.recv(4096)
                if not data:
                    break
                message = data.decode('utf-8')
                session.seq += 1
                package = {
                    'timestamp': datetime.now().isoformat(),
                    'client_id': session.id,
                    'client_address': addr[0],
                    'client_port': addr[1],
                    'sequence': session.seq,
                    'message': message
                }
                self.message_queue.put(package)
        except Exception as e:
            print(f"[{addr}] Error: {e}")
        finally:
            print(f"[-] Client disconnected: {addr}, id={session.id}")
            session.close()
            del self.clients[session.id]

    def send_to_client(self, client_id: str, message: str):
        client = self.clients.get(client_id)
        if client:
            client.send(message)
        else:
            print(f"[!] Client ID {client_id} not found.")

    def get_message(self):
        try:
            return self.message_queue.get_nowait()
        except queue.Empty:
            return None

    def stop(self):
        self.running.clear()
        for client in self.clients.values():
            client.close()
        if self.server_socket:
            self.server_socket.close()
        print("Server stopped.")

class AsyncTCPServer:
    def __init__(self, host='0.0.0.0', port=3030):
        self.host = host
        self.port = port
        self.server = None
        self.clients = {}  # {client_id: writer}
        self.client_count = 0
        self.message_queue = Queue()  # 消息队列用于主线程消费
        self.running = False
        self.lock = asyncio.Lock()

    async def start(self):
        """启动异步TCP服务器"""
        self.server = await asyncio.start_server(
            self._handle_client,
            self.host,
            self.port
        )
        self.running = True
        print(f"Async TCP Server started on {self.host}:{self.port}")
        await self.server.serve_forever()

    def run_forever(self):
        """主入口方法"""
        try:
            asyncio.run(self.start())
        except KeyboardInterrupt:
            print("Shutting down...")
            self.stop()

    async def _handle_client(self, reader, writer):
        async with self.lock:
            self.client_count += 1
            client_id = self.client_count
            addr = writer.get_extra_info('peername')
            print(f"[+] Client {client_id} connected from {addr}")

        self.clients[client_id] = writer

        try:
            while self.running:
                # ✅ 使用 readline() 替代 read()，确保按消息边界读取
                data = await reader.readuntil(b'$$')
                if not data:
                    break
                message = data.decode('utf-8').rstrip('$')
                timestamp = strftime("%Y-%m-%d %H:%M:%S", localtime())

                msg = {
                    'client_id': client_id,
                    'timestamp': timestamp,
                    'message': message,
                    'client_address': addr[0],
                    'client_port': addr[1]
                }
                await self.message_queue.put(msg)
                print(f"Received from {client_id}: {message}")
        except Exception as e:
            print(f"Error handling client {client_id}: {str(e)}")
        finally:
            writer.close()
            await writer.wait_closed()
            
            async with self.lock:
                self.clients.pop(client_id, None)
            print(f"[-] Client {client_id} disconnected")

    def get_message(self):
        """从队列中取出一条消息"""
        try:
            return self.message_queue.get_nowait()
        except asyncio.QueueEmpty:
            return None

    async def _send_message(self, client_id, message):
        """内部发送消息协程"""
        async with self.lock:  # 加锁保护读取
            writer = self.clients.get(client_id)

        if writer and not writer.is_closing():
            try:
                writer.write((message + '\n').encode('utf-8'))
                await writer.drain()
                print(f"Sent to client {client_id}: {message}")
                return True
            except:
                print(f"Failed to send message to client {client_id}.")
                self._remove_client(client_id)
                return False
        else:
            print(f"Client {client_id} not found or disconnected.")
            return False

    def send_message(self, client_id, message):
        """同步接口：向指定客户端发送消息"""
        asyncio.create_task(self._send_message(client_id, message))

    def _remove_client(self, client_id):
        """移除断开连接的客户端"""
        writer = self.clients.pop(client_id, None)
        if writer:
            writer.close()

    def stop(self):
        """停止服务器"""
        self.running = False
        for writer in self.clients.values():
            writer.close()
        self.clients.clear()
        if self.server:
            self.server.close()
        print("Async TCP Server stopped.")

class TCPClient:
    def __init__(self, host: str, port: int):
        self.host = host
        self.port = port
        self.sock = None
        self.recv_thread = None
        self.stop_event = threading.Event()
        self.recv_queue = queue.Queue()

    def connect(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.sock.connect((self.host, self.port))
            self.stop_event.clear()
            self.recv_thread = threading.Thread(target=self._receive_loop)
            self.recv_thread.start()
            print(f"Connected to server {self.host}:{self.port}")
        except Exception as e:
            print(f"Connection failed: {e}")
            self.sock = None

    def _receive_loop(self):
        try:
            while not self.stop_event.is_set():
                if not self.sock:
                    print("socket closed")
                    break
                data = self.sock.recv(4096)
                if data:
                    self.recv_queue.put(data.decode('utf-8'))
                else:
                    print("Server closed the connection.")
                    self.stop_event.set()
                    break
        except Exception as e:
            print(f"Receive error: {e}")
        finally:
            self.close()

    def send(self, message: str):
        if self.sock:
            try:
                self.sock.sendall((message+'$$').encode('utf-8'))
            except Exception as e:
                print(f"Send error: {e}")

    def get_message(self):
        try:
            return self.recv_queue.get_nowait()
        except queue.Empty:
            return None

    def close(self):
        self.stop_event.set()
        if self.sock:
            try:
                self.sock.shutdown(socket.SHUT_RDWR)
            except Exception:
                pass
            self.sock.close()
            self.sock = None
        print("Connection closed.")


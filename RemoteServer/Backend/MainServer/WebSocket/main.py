from flask import Flask, request, jsonify
from flask_socketio import SocketIO, emit
import random
import time

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your-secret-key'
socketio = SocketIO(app, cors_allowed_origins="*")

# 模拟数据生成函数
def generate_sensor_data():
    return {
        'cpu': round(random.uniform(10, 90), 1),
        'memory': round(random.uniform(20, 80), 1),
        'disk': round(random.uniform(10, 60), 1),
        'network': {
            'in': round(random.uniform(100, 1000), 1),
            'out': round(random.uniform(50, 800), 1)
        },
        'timestamp': int(time.time() * 1000)
    }

# 监听前端连接
@socketio.on('connect')
def handle_connect():
    print('客户端已连接')

# 监听登录事件
@socketio.on('login')
def handle_login(data):
    username = data.get('username')
    password = data.get('password')
    print(f"收到登录请求: 用户名={username}")
    
    # 示例验证逻辑（实际应查询数据库）
    if username == 'admin' and password == 'password':
        token = 'your-secret-token'  # 实际应生成JWT
        emit('loginResponse', {
            'success': True,
            'token': token,
            'message': '登录成功'
        })
        
        # 登录成功后启动数据推送
        def send_data():
            while True:
                sensor_data = generate_sensor_data()
                socketio.emit('data-update', sensor_data)
                socketio.sleep(1)  # 每秒发送一次数据
        
        # 在新线程中推送数据
        from threading import Thread
        Thread(target=send_data, daemon=True).start()
    else:
        emit('loginResponse', {
            'success': False,
            'message': '用户名或密码错误'
        })

# 监听断开连接
@socketio.on('disconnect')
def handle_disconnect():
    print('客户端已断开连接')

# HTTP接口（备用登录方式）
@app.route('/api/login', methods=['POST'])
def login():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    
    if username == 'admin' and password == 'password':
        return jsonify({
            'success': True,
            'token': 'your-secret-token'
        })
    else:
        return jsonify({
            'success': False,
            'message': '认证失败'
        }), 401

if __name__ == '__main__':
    print('服务器运行在 http://localhost:3001')
    socketio.run(app, host='0.0.0.0', port=3001)
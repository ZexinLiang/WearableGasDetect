# WGD

## 数据库表结构

时间存储格式：YYYY-MM-DD HH:MM:SS.SSS

### 用户表 user
| 字段名      | 类型      | 描述   |
|:---------|:--------|:-----|
| id       | INTEGER | 自增ID |
| username | TEXT    | 用户名  |
| password | TEXT    | 密码   |

### 设备基本信息表 device
| 字段名         | 类型             | 描述     |
|:------------|:---------------|:-------|
| id          | INTEGER        | 设备唯一ID |
| name        | TEXT           | 设备名称   |
| status      | INTEGER        | 设备状态   |
| last_update | TIMESTAMP/TEXT | 最后更新时间 |
| last_login  | TIMESTAMP/TEXT | 最后登录时间 |

设备状态包括：离线（0），在线（1），异常（2）

### 设备登录信息表 device_login
| 字段名       | 类型             | 描述     |
|:----------|:---------------|:-------|
| id        | INTEGER        | 设备唯一ID |
| time      | TIMESTAMP/TEXT | 时间     |
| status    | INTEGER        | 登录状态   |
| latitude  | TEXT           | 纬度     |
| longitude | TEXT           | 经度     |
| location  | TEXT           | 位置     |
| ip        | TEXT           | IP     |

登录状态包括：正常（0），异常（1）

### 设备传感器数据表 device_sensor
| 字段名          | 类型             | 描述     |
|:-------------|:---------------|:-------|
| id           | INTEGER        | 设备唯一ID |
| time         | TIMESTAMP/TEXT | 时间     |
| humidity1    | REAL           | 湿度     |
| humidity2    | REAL           | 湿度     |
| temperature1 | REAL           | 温度     |
| temperature2 | REAL           | 温度     |
| pressure     | REAL           | 压力     |
| GasRes       | REAL           | 气体     |
| PGas         | REAL           | 气体     |
| CO2          | REAL           | 二氧化碳   |


### 报警记录表  device_alarm
| 字段名         | 类型             | 描述     |
|:------------|:---------------|:-------|
| id          | INTEGER        | 设备唯一ID |
| time        | TIMESTAMP/TEXT | 时间     |
| type        | INTEGER        | 报警类型   |
| status      | INTEGER        | 报警状态   |
| description | TEXT           | 描述     |
| action      | TEXT           | 动作     |
报警类型包括：温度过高（1），温度过低（2），湿度过高（3），湿度过低（4）等  
报警状态包括：已解决（0），未解决（1）

### 设备事件表 device_event
| 字段名         | 类型             | 描述     |
|:------------|:---------------|:-------|
| id          | INTEGER        | 设备唯一ID |
| time        | TIMESTAMP/TEXT | 时间     |
| type        | INTEGER        | 事件类型   |
| description | TEXT           | 描述     |

事件类型包括：设备上线（1），设备离线（2），设备异常（3），配置更新（4）等


## 数据通信格式

### 终端设备和服务器
#### 位置信息

```json
{
  "type": "verify",
  "data": {
    "VerifyCode": "1037",
    "DeviceID": 1
  }
}
```
```json
{
    "type": "GPS/LBS",
    "data": {
        "Latitude": "39.9042",
        "Longitude": "116.4074"
    }
}
```

#### 传感器数据
```json
{
  "type": "Sensor",
  "data": {
    "Humidity1": 1100022.27,
    "Humidity2": 1100022.27,
    "Pressure": 1013.25,
    "Temperature1": 23.05,
    "Temperature2": 23.05,
    "GasRes": 436115.84,
    "PGas": 0.0,
    "CO2": 0.0
  }
}
```

```json
{
  "time": "2021-09-01 00:00:00.000",
  "sessionID": 1,
  "port": 1232,
  "ip": "192.168.1.1",
  "data": "asdfdsa"
}
```

```json
{
  "sessionID": 1,
  "data": "A########"
}
```

### 前端和后端
#### 用户登陆

接口路径：`/api/login` `POST`
```json
{
  "message": "login",
  "data": {
    "username": "admin",
    "password": "password"
  }
}
```
返回数据
```json
{
  "code": 1,
  "message": "success",
  "data": {
    "token": "token"
  }
}
```
`code`有2种返回值：成功（1）、失败（0）  
失败的时候`message`会根据错误返回不同的结果，比如：密码错误（password error），用户不存在（username not exist）

#### 用户注册
接口路径：`/api/register` `POST`
```json
{
  "message": "register",
  "data": {
    "username": "admin",
    "password": "password",
    "verifyCode": "1037"
  }
}
```
返回数据
```json
{
  "code": 1,
  "message": "success",
  "data": {
    "token": "token"
  }
}
```
`code`有2种返回值：成功（1），失败（0）  
失败的时候`message`会根据错误返回不同的结果，比如：用户已经存在（user has already exist）等

#### 仪表盘
接口路径：`/api/dashboard` `GET`
返回数据：按照事件顺序，最多发送10个事件活动
```json
{
  "code": 1,
  "message": "success",
  "data": {
    "onlineDevices": 10,
    "allDevices": 20,
    "activeDevices": 5,
    "alarmDevices": 3,
    "activities": [
      {
        "time": "2021-09-01 00:00:00",
        "deviceId": 1,
        "deviceName": "A",
        "eventType": 1,
        "description": "设备A上线"
      },
      {
        "time": "2021-09-01 00:00:00",
        "deviceId": 2,
        "deviceName": "B",
        "eventType": 2,
        "description": "设备B已离线"
      }
    ]
  }
}
```

#### 设备列表
接口路径：`/api/device/list` `GET`
返回数据：按照设备id排序

```json
{
  "code": 1,
  "message": "success",
  "data": {
    "deviceList": [
      {
        "deviceId": 1,
        "deviceName": "A",
        "deviceStatus": 1,
        "lastLoginTime": "2020-05-01 12:00:00",
        "temperature": 23.5,
        "humidity": 65.0
      },
      {
        "deviceId": 2,
        "deviceName": "B",
        "status": 0,
        "lastLoginTime": "2020-05-01 12:00:00",
        "temperature": 23.5,
        "humidity": 65.0
      }
    ]
  }
}
```
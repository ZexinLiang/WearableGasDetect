
import { defineStore } from 'pinia'
import axios from 'axios';

// 设置 axios 默认基础 URL
const apiClient = axios.create({
  baseURL: '/api',  // 设置基础URL
});

// 创建设备管理store
export const useDeviceStore = defineStore('device', {
  state: () => ({
    // 在线设备统计信息
    onlineDevices: 0,
    totalDevices: 0,
    deviceStatus: {
      active: 0,
      inactive: 0,
      error: 0
    },
    
    // 当前选中的设备
    selectedDevice: null,
    
    // 设备列表
    devices: [],
    
    // 地图数据
    mapData: {
      bounds: null,
      markers: [],
      heatmap: []
    },
    
    // 加载状态
    isLoading: false,
    
    // 错误信息
    error: null
  }),
  
  actions: {
    
    // 获取设备列表
    async fetchDevices() {
      this.isLoading = true
      this.error = null
      
      try {
        // 发送 GET 请求获取设备列表
        const response = await apiClient.get('/device/list')
        
        // 验证响应数据结构
        if (response.data && response.data.code === 1 && response.data.data) {
          // 将接口返回的设备列表映射为现有格式
          this.devices = response.data.data.deviceList.map(device => ({
            id: device.deviceID,
            name: device.deviceName,
            status: this.mapDeviceStatus(device.deviceStatus),
            lastOnline: device.lastLoginTime,
            temperature: parseFloat(device.temperature.toFixed(2)), // 保留两位小数
            humidity: parseFloat(device.humidity.toFixed(2)),
            location: { lat: 39.9042, lng: 116.4074 }
          }))

        //   this.devices = [
        //   { id: 1, name: '设备A', status: 'active', lastOnline: new Date().toISOString(), location: { lat: 39.9042, lng: 116.4074 }, temperature: 25.5, humidity: 60 },
        //   { id: 2, name: '设备B', status: 'inactive', lastOnline: new Date(Date.now() - 3600000).toISOString(), location: { lat: 31.2304, lng: 121.4737 }, temperature: 28.3, humidity: 55 },
        //   { id: 3, name: '设备C', status: 'error', lastOnline: new Date(Date.now() - 1800000).toISOString(), location: { lat: 23.1291, lng: 113.2644 }, temperature: 32.1, humidity: 45 }
        // ]
          
          // 更新地图数据
          this.updateMapData()
        } else {
          throw new Error('接口数据格式错误')
        }
      } catch (err) {
        this.error = '获取设备列表失败'
        console.error(err)
      } finally {
        this.isLoading = false
      }
    },
    
    // 更新地图数据
    updateMapData() {
      this.mapData.markers = this.devices.map(device => ({
        id: device.id,
        name: device.name,
        position: [device.location.lng, device.location.lat],
        status: device.status
      }))
      
      // 这里可以添加热力图数据生成逻辑
    },
    
    // 选择设备
    selectDevice(deviceId) {
      this.selectedDevice = this.devices.find(d => d.id === deviceId) || null
    },
    
    // 更新单个设备状态（模拟实时更新）
    updateDeviceStatus(deviceId, status) {
      const device = this.devices.find(d => d.id === deviceId)
      if (device) {
        device.status = status
        
        // 触发报警检查
        if (status === 'error') {
          this.triggerAlert(device)
        }
      }
    },
    
    // 触发报警
    triggerAlert(device) {
      // 这里可以集成Element Plus的Notification组件
      console.log(`设备 ${device.name} 发生异常：${device.error || '未知错误'}`)
      // 实际开发中可以发送通知或记录日志
    },
    
    // 获取仪表盘数据
    async fetchDashboardData() {
      this.isLoading = true
      this.error = null
      
      try {
        // 实际开发中这里应该是HTTP请求
        // await new Promise(resolve => setTimeout(resolve, 500))
        // 模拟返回数据

        // 发送登录请求
        const response_o = await apiClient.get('/dashboard');
        // console.log(response_o.data);
        const response = response_o.data;
        
        // 更新状态
        this.onlineDevices = response.data.onlineDevices
        this.totalDevices = response.data.allDevices
        this.deviceStatus.active = response.data.onlineDevices
        this.deviceStatus.error = response.data.alarmDevices
        this.deviceStatus.inactive = this.totalDevices - this.onlineDevices
        
        // 将活动数据转换为组件需要的格式
        const activities = response.data.activities.map(activity => ({
          id: activity.deviceId,
          deviceName: activity.deviceName,
          action: activity.description,
          time: activity.time,
          type: this.getActivityType(activity.eventType)
        }))
        
        // 返回活动数据
        return activities
      } catch (err) {
        this.error = '获取仪表盘数据失败'
        console.error(err)
        // 返回空数组作为后备值
        return []
      } finally {
        this.isLoading = false
      }
    },
    
    // 根据事件类型获取对应的活动类型
    getActivityType(eventType) {
      switch (eventType) {
        case 1:
          return 'success' // 上线
        case 2:
          return 'warning' // 离线
        case 3:
          return 'danger' // 异常
        default:
          return 'info' // 默认类型
      }
    },
    
    // 添加设备状态映射方法
    mapDeviceStatus(statusCode) {
      switch (statusCode) {
        case 1:
          return 'active' // 在线
        case 0:
          return 'inactive' // 离线
        default:
          return 'error' // 异常
      }
    }
  },
  
  getters: {
    // 获取在线率
    onlineRate: (state) => {
      return state.totalDevices > 0 
        ? Math.round((state.onlineDevices / state.totalDevices) * 100) 
        : 0
    },
    
    // 获取活跃设备
    activeDevices: (state) => {
      return state.devices.filter(d => d.status === 'active')
    },
    
    // 获取异常设备
    errorDevices: (state) => {
      return state.devices.filter(d => d.status === 'error')
    }
  }
})
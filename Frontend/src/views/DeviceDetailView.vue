<template>
  <div class="device-detail-container">
    <el-card class="device-info-card">
      <template #header>
        <div class="card-header">
          <span>设备详情</span>
          <el-button @click="goBack">返回</el-button>
        </div>
      </template>
      
      <div v-if="device" class="device-details">
        <el-row :gutter="20"> 
          <el-col :span="12"> 
            <el-card  class="device-status-card" v-if="device" >
              <template #header>
                <div class="card-header">
                  <strong><span>设备状态</span></strong>
                </div>
              </template>
              <div class="status-content">
                <h3>{{ device.name }}</h3>
                <el-tag :type="statusTagType" effect="dark">{{ statusText }}</el-tag>
              </div>
            </el-card>
          </el-col>

          <el-col :span="12"> 
            <el-card class="device-meta-card" v-if="device">
              <template #header>
                <div class="card-header">
                  <strong><span>设备信息</span></strong>
                </div>
              </template>
              <div class="meta-content">
                <p><strong>设备ID:</strong> {{ device.id }}</p>
                <p><strong>最后在线时间:</strong> {{ formatTime(device.lastOnline) }}</p>
                <p><strong>位置:</strong> {{ device.location.lat }}, {{ device.location.lng }}</p>
              </div>
            </el-card>
          </el-col>
        </el-row>
        
        
        <div class="device-metrics">
          <el-row :gutter="20">
            <el-col :span="12">
              <div class="metric-card">
                <div class="metric-title">温度</div>
                <div class="metric-value">{{ device.temperature }}℃</div>
                <div class="metric-chart">
                  <TemperatureChart :data="temperatureData" />
                </div>
              </div>
            </el-col>
            <el-col :span="12">
              <div class="metric-card">
                <div class="metric-title">湿度</div>
                <div class="metric-value">{{ device.humidity }}%</div>
                <div class="metric-chart">
                  <HumidityChart :data="humidityData" />
                </div>
              </div>
            </el-col>
          </el-row>
        </div>
      </div>
      
      <div v-else>
        设备信息加载中...
      </div>
    </el-card>
    
    <el-card class="device-history-card">
      <el-tabs v-model="activeTab">
        <el-tab-pane label="登录记录" name="loginLogs">
          <div class="logs-table">
            <el-table :data="loginLogs" style="width: 100%">
              <el-table-column prop="time" label="登录时间" />
              <el-table-column prop="ip" label="IP 地址" />
              <el-table-column prop="location" label="地理位置" />
              <el-table-column prop="status" label="状态">
                <template #default="{ row }">
                  <el-tag :type="row.status === '成功' ? 'success' : 'danger'">
                    {{ row.status }}
                  </el-tag>
                </template>
              </el-table-column>
            </el-table>
          </div>
        </el-tab-pane>

        <el-tab-pane label="历史位置" name="locationHistory">
          <div class="location-table">
            <el-table :data="locationHistory" style="width: 100%">
              <el-table-column prop="time" label="时间">
                <template #default="{ row }">
                  {{ formatTime(row.timestamp) }}
                </template>
              </el-table-column>
              <el-table-column prop="lat" label="纬度" />
              <el-table-column prop="lng" label="经度" />
              <el-table-column label="位置">
                <template #default="{ row }">
                  {{ `${row.address.province} ${row.address.city} ${row.address.district}` }}
                </template>
              </el-table-column>
            </el-table>
          </div>
        </el-tab-pane>

        <el-tab-pane label="报警记录" name="alerts">
          <DeviceAlerts :alerts="alerts" />
        </el-tab-pane>
      </el-tabs>
    </el-card>
  </div>
</template>

<script setup>
import { ref, onMounted, computed, watch } from 'vue'
import { useRoute, useRouter } from 'vue-router'
import { useDeviceStore } from '@/store/deviceStore'
import TemperatureChart from '@/components/TemperatureChart.vue'
import HumidityChart from '@/components/HumidityChart.vue'
import DeviceAlerts from '@/components/DeviceAlerts.vue'

const route = useRoute()
const router = useRouter()
const deviceStore = useDeviceStore()

// 当前设备信息
const device = ref(null)

// 设备ID
const deviceId = computed(() => {
  return parseInt(route.params.id)
})

// 活动标签页
const activeTab = ref('history')

// 温度数据（模拟）
const temperatureData = ref([
  { timestamp: new Date(Date.now() - 3600000).toISOString(), value: 24.5 },
  { timestamp: new Date(Date.now() - 3000000).toISOString(), value: 25.1 },
  { timestamp: new Date(Date.now() - 2400000).toISOString(), value: 25.8 },
  { timestamp: new Date(Date.now() - 1800000).toISOString(), value: 26.3 },
  { timestamp: new Date(Date.now() - 1200000).toISOString(), value: 27.0 },
  { timestamp: new Date().toISOString(), value: 27.5 }
])

// 湿度数据（模拟）
const humidityData = ref([
  { timestamp: new Date(Date.now() - 3600000).toISOString(), value: 58 },
  { timestamp: new Date(Date.now() - 3000000).toISOString(), value: 59 },
  { timestamp: new Date(Date.now() - 2400000).toISOString(), value: 57 },
  { timestamp: new Date(Date.now() - 1800000).toISOString(), value: 55 },
  { timestamp: new Date(Date.now() - 1200000).toISOString(), value: 56 },
  { timestamp: new Date().toISOString(), value: 54 }
])

// 格式化时间
const formatTime = (timeString) => {
  const date = new Date(timeString)
  return date.toLocaleString()
}

// 登录记录（模拟）
const loginLogs = ref([
  {
    time: formatTime(new Date(Date.now() - 86400000)), // 昨天
    ip: '192.168.1.1',
    location: '中国 湖北 武汉',
    status: '成功'
  },
  {
    time: formatTime(new Date(Date.now() - 3600000)),
    ip: '10.0.0.5',
    location: '中国 湖北 武汉',
    status: '失败'
  }
])

// 历史位置（模拟）
const locationHistory = ref([
  { 
    timestamp: new Date(Date.now() - 86400000).toISOString(), 
    lat: 30.5984, 
    lng: 114.3115,
    address: {
      province: '湖北省',
      city: '武汉市',
      district: '洪山区'
    }
  },
  { 
    timestamp: new Date(Date.now() - 43200000).toISOString(), 
    lat: 30.5992, 
    lng: 114.3122,
    address: {
      province: '湖北省',
      city: '武汉市',
      district: '洪山区'
    }
  },
  { 
    timestamp: new Date().toISOString(), 
    lat: 30.5977, 
    lng: 114.3116,
    address: {
      province: '湖北省',
      city: '武汉市',
      district: '洪山区'
    }
  }
])

// 报警记录
const alerts = ref([
  {
    id: 1,
    deviceName: '设备C',
    type: '高温警告',
    description: '温度超过阈值30℃',
    time: new Date(Date.now() - 1800000).toISOString(),
    resolved: false
  }
])

// 获取设备状态文本
const statusText = computed(() => {
  switch (device.value?.status) {
    case 'active':
      return '在线'
    case 'inactive':
      return '离线'
    case 'error':
      return '异常'
    default:
      return '未知'
  }
})

// 获取设备状态标签类型
const statusTagType = computed(() => {
  switch (device.value?.status) {
    case 'active':
      return 'success'
    case 'inactive':
      return 'info'
    case 'error':
      return 'danger'
    default:
      return 'warning'
  }
})

// 返回上一页
const goBack = () => {
  router.back()
}



// 监听路由变化
watch(
  () => route.params.id,
  async (newId) => {
    if (newId) {
      await loadDeviceDetails(parseInt(newId))
    }
  }
)

// 加载设备详情
const loadDeviceDetails = async (id) => {
  // 这里应该是实际的API请求
  console.log(`加载设备 ${id} 的详细信息...`)
  
  // 模拟从store获取设备信息
  device.value = deviceStore.devices.find(d => d.id === id) || null
  
  // 如果没有找到设备，返回错误
  if (!device.value) {
    console.error(`设备 ${id} 未找到`)
    router.push('/devices')
    return
  }
  
  // 可以在这里添加更多设备相关的数据请求
}

// 初始化加载设备信息
onMounted(async () => {
  await loadDeviceDetails(deviceId.value)
})
</script>

<style scoped>
.device-detail-container {
  padding: 2rem;
}

.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.device-status-card, .device-meta-card {
  box-shadow: 0 10px 20px rgba(0, 0, 0, 0.1);
  transition: transform 0.3s;
  height: 250px;
}

.device-status-card:hover, .device-meta-card:hover {
  transform: translateY(-5px);
}

.status-content, .meta-content {
  padding: 1rem;
}

.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.meta-content p {
  margin: 0.5rem 0;
  margin-bottom: 1rem;
}

.device-info-card {
  margin-bottom: 2rem;
}

.device-details {
  display: flex;
  flex-direction: column;
  gap: 1rem;
}

.device-status {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.device-meta {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
}

.device-metrics {
  margin-top: 1rem;
}

.metric-card {
  background-color: var(--el-bg-color-overlay);
  padding: 1rem;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
  transition: all 0.3s ease;
}

.metric-card:hover {
  transform: translateY(-5px);
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
}

.metric-title {
  font-weight: bold;
  margin-bottom: 0.5rem;
}

.metric-value {
  font-size: 1.5rem;
  color: var(--el-color-primary);
  margin-bottom: 1rem;
}

.metric-chart {
  height: 260px;
}

.history-charts {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 2rem;
}

.logs-table {
  margin-top: 1rem;
}

.location-table {
  margin-top: 1rem;
}

.el-table__row .el-table__cell:nth-child(4) {
  white-space: normal;
}
</style>
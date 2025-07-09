<template>
  <div class="dashboard-container">
    <el-row :gutter="20" class="dashboard-header">
      <el-col :span="6">
        <el-card class="stat-card">
          <div class="stat-icon online-icon">
            <el-icon><Monitor /></el-icon>
          </div>
          <div class="stat-info">
            <h3>{{ onlineDevices }}</h3>
            <p>在线设备</p>
          </div>
          <div class="stat-progress">
            <el-progress :percentage="onlineRate" :stroke-width="8" :show-text="false" />
          </div>
        </el-card>
      </el-col>
      
      <el-col :span="6">
        <el-card class="stat-card">
          <div class="stat-icon total-icon">
            <el-icon><List /></el-icon>
          </div>
          <div class="stat-info">
            <h3>{{ totalDevices }}</h3>
            <p>总设备数</p>
          </div>
          <div class="stat-progress">
            <el-progress :percentage="100" :stroke-width="8" :show-text="false" status="success" />
          </div>
        </el-card>
      </el-col>
      
      <el-col :span="6">
        <el-card class="stat-card">
          <div class="stat-icon active-icon">
            <el-icon><Lightning /></el-icon>
          </div>
          <div class="stat-info">
            <h3>{{ deviceStatus.active }}</h3>
            <p>活跃设备</p>
          </div>
          <div class="stat-progress">
            <el-progress :percentage="activeRate" :stroke-width="8" :show-text="false" />
          </div>
        </el-card>
      </el-col>
      
      <el-col :span="6">
        <el-card class="stat-card">
          <div class="stat-icon error-icon">
            <el-icon><Warning /></el-icon>
          </div>
          <div class="stat-info">
            <h3>{{ deviceStatus.error }}</h3>
            <p>异常设备</p>
          </div>
          <div class="stat-progress">
            <el-progress :percentage="errorRate" :stroke-width="8" :show-text="false" status="exception" />
          </div>
        </el-card>
      </el-col>
    </el-row>
    
     <el-row :gutter="20" class="dashboard-main">

      <el-col :span="15">   
        <el-card class="device-status-card">
          <template #header>
            <div class="card-header">
              <span>设备状态</span>
            </div>
          </template>
          
          <DeviceStatusChart :status="deviceStatus" />
        </el-card>
      </el-col>
      
      <el-col :span="9">
        <el-card class="recent-activity-card">
          <template #header>
            <div class="card-header">
              <span>最新活动</span>
            </div>
          </template>
          <div class="recent-activity-content">
            <RecentActivity :activities="recentActivities" />
          </div>  
          
          
        </el-card>
      </el-col>
    </el-row>
  </div>
</template>

<script setup>
import { ref, computed, onMounted, watch, onBeforeUnmount } from 'vue'
import { useDeviceStore } from '@/store/deviceStore'
import DeviceStatusChart from '@/components/DeviceStatusChart.vue'
import RecentActivity from '@/components/RecentActivity.vue'

const deviceStore = useDeviceStore()

// 设备统计数据
const onlineDevices = computed(() => deviceStore.onlineDevices)
const totalDevices = computed(() => deviceStore.totalDevices)
const deviceStatus = computed(() => deviceStore.deviceStatus)
const onlineRate = computed(() => Math.round((onlineDevices.value / totalDevices.value) * 100) || 0)
const activeDevices = computed(() => deviceStore.activeDevices)
const errorDevices = computed(() => deviceStore.errorDevices)

// 计算设备状态百分比
const activeRate = computed(() => totalDevices.value > 0 ? Math.round((activeDevices.value.length / totalDevices.value) * 100) : 0)
const errorRate = computed(() => totalDevices.value > 0 ? Math.round((errorDevices.value.length / totalDevices.value) * 100) : 0)

// 最近活动数据
const recentActivities = ref([])

// 加载状态和错误信息
const isLoading = computed(() => deviceStore.isLoading)
const error = computed(() => deviceStore.error)

// 处理设备选择
const handleDeviceSelected = (deviceId) => {
  console.log(`选中设备 ${deviceId}`)
  // 这里可以添加跳转到设备详情页的逻辑
}

let refreshInterval = null

// 加载仪表盘数据（带错误处理）
const loadDashboardData = async () => {
  try {
    const activities = await deviceStore.fetchDashboardData()
    recentActivities.value = activities
  } catch (err) {
    console.error('加载仪表盘数据失败:', err)
  }
}

// 启动定时刷新
const startAutoRefresh = () => {
  if (refreshInterval) return // 避免重复启动
  refreshInterval = setInterval(async () => {
    await loadDashboardData()
  }, 1000)
}

// 停止定时刷新
const stopAutoRefresh = () => {
  if (refreshInterval) {
    clearInterval(refreshInterval)
    refreshInterval = null
  }
}

// 页面加载时开始刷新
onMounted(async () => {
  await loadDashboardData() // 首次加载
  startAutoRefresh()
})

// 组件销毁前停止刷新
onBeforeUnmount(() => {
  stopAutoRefresh()
})
</script>

<style scoped>
.dashboard-container {
  padding: 2rem;
}

.dashboard-header {
  margin-bottom: 20px;
}

.dashboard-header .stat-card {
  display: flex;
  align-items: center;
  padding: 1rem;
}

.stat-icon {
  width: 60px;
  height: 60px;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  margin-right: 1rem;
}

.stat-icon .el-icon {
  font-size: 24px;
}

.online-icon {
  background-color: rgba(64, 158, 255, 0.2);
  color: #409EFF;
}

.total-icon {
  background-color: rgba(103, 194, 58, 0.2);
  color: #67C23A;
}

.active-icon {
  background-color: rgba(255, 208, 0, 0.2);
  color: #E6A23C;
}

.error-icon {
  background-color: rgba(245, 108, 108, 0.2);
  color: #F56C6C;
}

.stat-info h3 {
  margin: 0;
  font-size: 1.5rem;
}

.stat-info p {
  margin: 0;
  font-size: 0.9rem;
  color: var(--el-text-color-regular);
}

.stat-progress {
  margin-top: 0.5rem;
}

.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.map-card {
  height: 600px;
}

.device-status-card,
.recent-activity-card {
  height: 100%;
}


.recent-activity-card {
  margin-bottom: 1rem;
  /* height: 400px; */
}
.recent-activity-content {
  height: calc(100% - 60px);
  overflow-y: auto; /* 允许垂直滚动 */
}
</style>
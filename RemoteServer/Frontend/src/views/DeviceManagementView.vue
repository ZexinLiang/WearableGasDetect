<template>
  <div class="device-management-container">
    <el-card class="device-management-card">
      <template #header>
        <div class="card-header">
          <span>设备管理</span>
          <div class="header-actions">
            <el-input v-model="searchQuery" placeholder="搜索设备..." style="width: 200px;" />
            <el-button @click="refreshDevices" :loading="isLoading">刷新</el-button>
          </div>
        </div>
      </template>
      
      <el-table
        :data="filteredDevices"
        style="width: 100%"
        :row-class-name="tableRowClassName"
        @row-click="handleRowClick"
        :fit="true"
      >
        <el-table-column prop="name" label="设备名称" min-width="120"></el-table-column>
        <el-table-column prop="id" label="设备ID" min-width="80"></el-table-column>
        <el-table-column label="状态" min-width="80">
          <template #default="{ row }">
            <el-tag :type="statusTagType(row.status)">{{ statusText(row.status) }}</el-tag>
          </template>
        </el-table-column>
        <el-table-column prop="lastOnline" label="最后在线时间" min-width="160">
          <template #default="{ row }">
            {{ formatTime(row.lastOnline) }}
          </template>
        </el-table-column>
        <el-table-column prop="temperature" label="温度(℃)" min-width="100">
          <template #default="{ row }">
            {{ row.temperature }}
          </template>
        </el-table-column>
        <el-table-column prop="humidity" label="湿度(%)" min-width="100">
          <template #default="{ row }">
            {{ row.humidity }}
          </template>
        </el-table-column>
        <el-table-column label="操作" min-width="150">
          <template #default="{ row }">
            <el-button @click.stop="viewDetails(row)" link type="primary" size="small">详情</el-button>
            <el-button @click.stop="manageDevice(row)" link type="info" size="small">管理</el-button>
          </template>
        </el-table-column>
      </el-table>
    </el-card>
  </div>
</template>

<script setup>
import { ref, computed, onMounted } from 'vue'
import { useRouter } from 'vue-router'
import { useDeviceStore } from '@/store/deviceStore'

const router = useRouter()
const deviceStore = useDeviceStore()

// 设备列表
const devices = computed(() => deviceStore.devices)

// 加载状态
const isLoading = computed(() => deviceStore.isLoading)

// 搜索查询
const searchQuery = ref('')

// 过滤后的设备列表
const filteredDevices = computed(() => {
  if (!searchQuery.value) {
    return devices.value
  }
  
  const query = searchQuery.value.toLowerCase()
  return devices.value.filter(device => 
    device.name.toLowerCase().includes(query) || 
    device.id.toString().includes(query)
  )
})

// 获取设备状态文本
const statusText = (status) => {
  switch (status) {
    case 'active':
      return '在线'
    case 'inactive':
      return '离线'
    case 'error':
      return '异常'
    default:
      return '未知'
  }
}

// 获取设备状态标签类型
const statusTagType = (status) => {
  switch (status) {
    case 'active':
      return 'success'
    case 'inactive':
      return 'info'
    case 'error':
      return 'danger'
    default:
      return 'warning'
  }
}

// 格式化时间
const formatTime = (timeString) => {
  const date = new Date(timeString)
  return date.toLocaleString()
}

// 表格行类名
const tableRowClassName = ({ rowIndex }) => {
  if (rowIndex % 2 === 0) {
    return 'even-row'
  } else {
    return 'odd-row'
  }
}

// 刷新设备列表
const refreshDevices = async () => {
  await deviceStore.fetchDevices()
}

// 查看设备详情
const viewDetails = (device) => {
  router.push(`/device/${device.id}`)
}

// 管理设备
const manageDevice = (device) => {
  console.log(`管理设备 ${device.id}`)
  // 这里可以添加实际的管理逻辑或跳转到管理页面
}

// 处理行点击事件
const handleRowClick = (row) => {
  router.push(`/device/${row.id}`)
}

// 初始化加载设备数据
onMounted(async () => {
  await refreshDevices()
})
</script>

<style scoped>
.device-management-container {
  padding: 2rem;
}

.device-management-card {
  margin-bottom: 2rem;
}

.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.header-actions {
  display: flex;
  gap: 1rem;
}

.even-row {
  background-color: var(--el-bg-color-overlay);
}

.odd-row {
  background-color: var(--el-bg-color-page);
}
</style>
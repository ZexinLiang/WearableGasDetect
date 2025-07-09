<template>
  <div class="device-alerts-container">
    <el-table :data="alerts" style="width: 100%" :row-class-name="tableRowClassName">
      <el-table-column prop="deviceName" label="设备名称" width="150"></el-table-column>
      <el-table-column prop="type" label="报警类型" width="150">
        <template #default="{ row }">
          <el-tag :type="getAlertType(row.type)">{{ row.type }}</el-tag>
        </template>
      </el-table-column>
      <el-table-column prop="description" label="描述"></el-table-column>
      <el-table-column prop="time" label="时间" width="160">
        <template #default="{ row }">
          {{ formatTime(row.time) }}
        </template>
      </el-table-column>
      <el-table-column prop="resolved" label="状态" width="100">
        <template #default="{ row }">
          <el-tag :type="row.resolved ? 'success' : 'danger'">{{ row.resolved ? '已解决' : '未解决' }}</el-tag>
        </template>
      </el-table-column>
      <el-table-column label="操作" width="100">
        <template #default="{ row }">
          <el-button @click="resolveAlert(row)" link type="primary" size="small">{{ row.resolved ? '查看详情' : '标记为已解决' }}</el-button>
        </template>
      </el-table-column>
    </el-table>
  </div>
</template>

<script setup>
import { defineProps, defineEmits } from 'vue'

const props = defineProps({
  alerts: {
    type: Array,
    required: true,
    default: () => []
  }
})

const emit = defineEmits(['resolve-alert'])

// 格式化时间
const formatTime = (timeString) => {
  const date = new Date(timeString)
  return date.toLocaleString()
}

// 获取报警类型样式
const getAlertType = (type) => {
  switch (type) {
    case '高温警告':
      return 'danger'
    case '低温警告':
      return 'info'
    case '湿度异常':
      return 'warning'
    default:
      return 'primary'
  }
}

// 表格行类名
const tableRowClassName = ({ rowIndex }) => {
  if (rowIndex % 2 === 0) {
    return 'even-row'
  } else {
    return 'odd-row'
  }
}

// 解决报警
const resolveAlert = (alert) => {
  // 这里可以添加实际的API调用
  console.log(`标记报警 ${alert.id} 为已解决`)
  
  // 触发事件通知父组件
  emit('resolve-alert', alert)
}
</script>

<style scoped>
.device-alerts-container {
  width: 100%;
}

.even-row {
  background-color: var(--el-bg-color-overlay);
}

.odd-row {
  background-color: var(--el-bg-color-page);
}
</style>
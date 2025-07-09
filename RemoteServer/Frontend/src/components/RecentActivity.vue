<template>
  <div class="recent-activity-container">
    <el-timeline>
      <el-timeline-item
        v-for="(activity, index) in activities"
        :key="index"
        :timestamp="formatTime(activity.time)"
        :type="activity.type"
        placement="top"
      >
        <el-card class="activity-card">
          <div class="activity-content">
            <h4>{{ activity.deviceName }}</h4>
            <p>{{ activity.action }}</p>
          </div>
        </el-card>
      </el-timeline-item>
    </el-timeline>
  </div>
</template>

<script setup>
import { defineProps } from 'vue'

const props = defineProps({
  activities: {
    type: Array,
    required: true,
    default: () => []
  }
})

// 格式化时间
const formatTime = (timeString) => {
  const date = new Date(timeString)
  return date.toLocaleString()
}
</script>

<style scoped>
.recent-activity-container {
  width: 100%;
  height: 300px;
  overflow-y: auto;
}
/* 隐藏滚动条，但保留滚动功能 */
.recent-activity-container::-webkit-scrollbar {
  display: none;
}

/* 非 Webkit 浏览器兼容性设置 */
.recent-activity-container {
  -ms-overflow-style: none; /* IE 和 Edge */
  scrollbar-width: none; /* Firefox */
}

.el-timeline {
  padding-left: 1rem;
}

.activity-content {
  display: flex;
  align-items: center;
}

.activity-content h4 {
  margin-right: 0.5rem;
  font-size: 1rem;
  color: var(--el-text-color-regular);
  white-space: nowrap;
}

.activity-content p {
  font-size: 0.9rem;
  color: var(--el-text-color-secondary);
  white-space: nowrap;
}

.activity-content h4,
.activity-content p {
  margin: 0; /* 移除默认外边距 */
}

.activity-content h4 {
  margin-right: 1rem; /* 设置合理的底部间距 */
}

:deep(.activity-card) {
  width: 80%;
}

:deep(.activity-card .el-card__body) {
  padding: 10px; /* 设置为你想要的值 */
}
</style>
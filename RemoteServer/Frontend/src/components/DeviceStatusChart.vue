<template>
  <div class="device-status-chart-container">
    <div ref="chart" class="chart"></div>
  </div>
</template>

<script setup>
import { ref, onMounted, onBeforeUnmount, watch } from 'vue'
import * as echarts from 'echarts'
import { useThemeStore } from '@/store/themeStore'

const props = defineProps({
  status: {
    type: Object,
    required: true,
    default: () => ({
      active: 0,
      inactive: 0,
      error: 0
    })
  }
})

const themeStore = useThemeStore()
const chart = ref(null)
let chartInstance = null

// 根据主题获取对应的颜色
const getTextColor = () => {
  return themeStore.isDarkMode ? '#e6e6e6' : '#333'
}

// 初始化图表
const initChart = () => {
  if (!chart.value) return

  // 销毁旧实例
  if (chartInstance) {
    chartInstance.dispose()
  }

  // 初始化图表并传入主题
  chartInstance = echarts.init(chart.value)

  const option = {
    color: ['#67C23A', '#909399', '#F56C6C'],
    tooltip: {
      trigger: 'item',
      formatter: '{a}<br/>{b}: {c}台 ({d}%)',
      backgroundColor: themeStore.isDarkMode ? 'rgba(50,50,50,0.9)' : 'white',
      textStyle: {
        color: getTextColor()
      }
    },
    legend: {
      orient: 'vertical',
      left: 'right',
      top: '10%',
      textStyle: {
        color: getTextColor()
      }
    },
    series: [
      {
        name: '设备状态',
        type: 'pie',
        radius: ['40%', '70%'],
        avoidLabelOverlap: false,
        itemStyle: {
          borderRadius: 5,
          borderColor: '#fff',
          borderWidth: 2
        },
        data: [
          { value: props.status.active, name: '在线', itemStyle: { color: '#67C23A' } },
          { value: props.status.inactive, name: '离线', itemStyle: { color: '#909399' } },
          { value: props.status.error, name: '异常', itemStyle: { color: '#F56C6C' } }
        ],
        emphasis: {
          itemStyle: {
            shadowBlur: 10,
            shadowOffsetX: 0,
            shadowColor: 'rgba(0, 0, 0, 0.5)'
          }
        },
        label: {
          show: true,
          position: 'outside',
          formatter: '{b}: {c}台 ({d}%)',
          color: getTextColor()
        },
        labelLine: {
          lineStyle: {
            color: getTextColor()
          }
        }
      }
    ]
  }

  chartInstance.setOption(option)
}

const updateChartData = () => {
  if (!chartInstance) return

  chartInstance.setOption({
    series: [{
      data: [
        { value: props.status.active, name: '在线' },
        { value: props.status.inactive, name: '离线' },
        { value: props.status.error, name: '异常' }
      ]
    }]
  })
}

// 监听数据变化
watch(() => props.status.active, () => {
  updateChartData()
  // initChart()
}), {deep: true}



// 更新图表主题颜色（不重绘数据）
const updateChartTheme = () => {
  if (!chartInstance) return

  const textColor = getTextColor()

  chartInstance.setOption({
    tooltip: {
      backgroundColor: themeStore.isDarkMode ? 'rgba(50,50,50,0.9)' : 'white',
      textStyle: {
        color: textColor
      }
    },
    legend: {
      textStyle: {
        color: textColor
      }
    },
    series: [{
      label: {
        color: textColor
      },
      labelLine: {
        lineStyle: {
          color: textColor
        }
      }
    }]
  })
}

// 监听主题变化
watch(
  () => themeStore.isDarkMode,
  () => {
    updateChartTheme()
  }
)


// 监听窗口大小变化
const resizeHandler = () => {
  if (chartInstance) {
    chartInstance.resize()
  }
}

onMounted(() => {
  initChart()
  window.addEventListener('resize', resizeHandler)
})

onBeforeUnmount(() => {
  window.removeEventListener('resize', resizeHandler)
  if (chartInstance) {
    chartInstance.dispose()
    chartInstance = null
  }
})
</script>

<style scoped>
.device-status-chart-container {
  width: 100%;
  height: 100%;
}

.chart {
  width: 100%;
  height: 300px;
}
</style>
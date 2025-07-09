<template>
  <div class="humidity-chart-container">
    <div ref="chart" class="chart"></div>
  </div>
</template>

<script setup>
import { ref, onMounted, onBeforeUnmount, watch , computed } from 'vue'
import * as echarts from 'echarts'
import { useThemeStore } from '@/store/themeStore'

const themeStore = useThemeStore()
const textColor = computed(() => themeStore.isDarkMode ? '#e6e6e6' : '#000000')

const props = defineProps({
  data: {
    type: Array,
    required: true,
    default: () => []
  },
  title: {
    type: String,
    default: '湿度变化'
  }
})

const chart = ref(null)
let chartInstance = null

// 初始化图表
const initChart = () => {
  if (!chart.value) return
  
  chartInstance = echarts.init(chart.value)

  const minValue = Math.min(...props.data.map(item => item.value))
  const maxValue = Math.max(...props.data.map(item => item.value))
  

  const yAxisMin = Math.floor(minValue / 5) * 5;
  const yAxisMax = Math.ceil(maxValue / 5) * 5;

  const option = {
    textStyle: {
      color: textColor.value
    },
    title: {
      text: props.title,
      left: 'center',
      textStyle: {
        color: textColor.value,
        fontSize: 18
      }
    },
    tooltip: {
      trigger: 'axis',
      formatter: (params) => {
        return `${params[0].name}<br/>湿度: ${params[0].value}%`;
      }
    },
    xAxis: {
      type: 'category',
      data: props.data.map(item => formatTime(item.timestamp)),
      axisLabel: {
        rotate: 45,
        color: textColor.value
      }
    },
    yAxis: {
      type: 'value',
      name: '湿度(%)',
      min: yAxisMin,
      max: yAxisMax,
      axisLabel: {
        color: textColor.value
      }
    },
    series: [{
      data: props.data.map(item => item.value),
      type: 'line',
      smooth: true,
      itemStyle: {
        color: '#3a7bd5'
      },
      lineStyle: {
        color: '#3a7bd5'
      },
      areaStyle: {
        color: 'rgba(58, 123, 213, 0.2)'
      }
    }]
  }
  
  chartInstance.setOption(option)
}

// 格式化时间
const formatTime = (timeString) => {
  const date = new Date(timeString)
  return `${date.getHours()}:${date.getMinutes()}`
}

const updateChartData = () => {
  if (!chartInstance) return

  const minValue = Math.min(...props.data.map(item => item.value))
  const maxValue = Math.max(...props.data.map(item => item.value))

  const yAxisMin = Math.floor(minValue / 5) * 5
  const yAxisMax = Math.ceil(maxValue / 5) * 5

  chartInstance.setOption({
    xAxis: {
      data: props.data.map(item => formatTime(item.timestamp))
    },
    yAxis: {
      min: yAxisMin,
      max: yAxisMax
    },
    series: [{
      data: props.data.map(item => item.value)
    }]
  })
}

// 监听数据变化
watch(() => props.data, () => {
  updateChartData()
})

// 监听主题变化并更新图表颜色
watch(
  () => themeStore.isDarkMode,
  () => {
    if (chartInstance) {
      chartInstance.setOption({
        textStyle: { color: textColor.value },
        title: { textStyle: { color: textColor.value } },
        xAxis: { axisLabel: { color: textColor.value } },
        yAxis: { axisLabel: { color: textColor.value } }
      })
    }
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
.humidity-chart-container {
  width: 100%;
  height: 100%;
}

.chart {
  width: 100%;
  height: 300px;
}
</style>
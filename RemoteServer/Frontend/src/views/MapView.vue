<template>
  <div class="map-view">
    <div ref="mapChart" style="width: 100%; height: 600px;"></div>
  </div>
</template>

<script setup>
import * as echarts from 'echarts';
import chinaMap from '@/assets/map/china.json';
import { onMounted, ref } from 'vue';

// 注册中国地图
echarts.registerMap('china', chinaMap);

const mapChart = ref(null);

onMounted(() => {
  initMap();
});

const initMap = () => {
  // 基于准备好的dom，初始化echarts实例
  const myChart = echarts.init(mapChart.value);

  // 指定图表的配置项和数据
  const option = {
    title: {
      text: '平台数据分布',
      left: 'center',
      textStyle: {
        color: '#00ffff'
      }
    },
    tooltip: {
      trigger: 'item'
    },
    visualMap: {
      min: 0,
      max: 2500,
      left: 'right',
      bottom: 'bottom',
      text: ['高', '低'],
      calculable: true,
      inRange: {
        color: ['#d94e5d', '#eac736', '#50a3ba']
      },
      show: true
    },
    series: [
      {
        name: '已安装设备',
        type: 'map',
        map: 'china',
        roam: false,
        label: {
          show: true,
          color: '#fff'
        },
        itemStyle: {
          areaColor: '#031525',
          borderColor: '#3B5077'
        },
        emphasis: {
          label: {
            show: true,
            color: '#fff'
          },
          itemStyle: {
            areaColor: '#2B91B7'
          }
        },
        data: [
          { name: '北京', value: 2500 },
          { name: '天津', value: 2300 },
          { name: '上海', value: 2100 },
          { name: '重庆', value: 1900 },
          { name: '辽宁', value: 1800 },
          { name: '江苏', value: 1700 },
          { name: '浙江', value: 1600 },
          { name: '山东', value: 1500 },
          { name: '广东', value: 1400 },
          { name: '四川', value: 1300 },
          // 其他省份的数据...
        ]
      }
    ]
  };

  // 使用刚指定的配置项和数据显示图表。
  myChart.setOption(option);
};
</script>

<style scoped>
.map-view {
  padding: 2rem;
  background-color: #031525;
}
</style>
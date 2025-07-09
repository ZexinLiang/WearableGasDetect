import { createApp } from 'vue'
import { createPinia } from 'pinia'
import App from './App.vue'
import router from './router'
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import { useDark } from '@vueuse/core'
import * as ElIcons from '@element-plus/icons-vue'

// 创建Pinia store
const pinia = createPinia()

// 创建Vue应用实例
const app = createApp(App)

// 使用Element Plus UI组件库
app.use(ElementPlus)

// 使用路由
app.use(router)

// 使用Pinia状态管理
app.use(pinia)

// 全局注册所有图标
for (const [key, component] of Object.entries(ElIcons)) {
  app.component(key, component)
}

// 挂载应用
app.mount('#app')


<template>
  <el-container class="layout-container">
    <!-- 顶部导航栏 -->
    <el-header class="layout-header">
      <div class="logo">设备管理平台</div>
      <div class="header-right">
        <el-switch
          v-model="themeStore.isDarkMode"
          :active-icon="Moon"
          :inactive-icon="Sunny"
          @change="toggleDarkMode"
        />
        <el-dropdown @command="handleUserCommand">
          <span class="user-info">
            {{ username }}<el-icon><ArrowDown /></el-icon>
          </span>
          <template #dropdown>
            <el-dropdown-menu>
              <el-dropdown-item command="profile">个人中心</el-dropdown-item>
              <el-dropdown-item command="logout">退出登录</el-dropdown-item>
            </el-dropdown-menu>
          </template>
        </el-dropdown>
      </div>
    </el-header>

    <el-container>
      <!-- 左侧菜单栏 -->
      <el-aside class="layout-aside" :width="isCollapse ? '64px' : '200px'">
        <el-menu
          :default-active="$route.path"
          :collapse="isCollapse"
          :collapse-transition="false"
          router
        >
          <el-menu-item index="/dashboard">
            <el-icon><HomeFilled /></el-icon>
            <span>仪表盘</span>
          </el-menu-item>
          <el-menu-item index="/devices">
            <el-icon><Monitor /></el-icon>
            <span>设备管理</span>
          </el-menu-item>
          <el-menu-item index="/map">
            <el-icon><Location /></el-icon>
            <span>地图展示</span>
          </el-menu-item>
          <el-menu-item index="/reports">
            <el-icon><Document /></el-icon>
            <span>数据报表</span>
          </el-menu-item>
        </el-menu>
      </el-aside>

      <!-- 右侧内容区 -->
      <el-main class="layout-main">
        <router-view v-slot="{ Component }">
          <transition name="fade-transform" mode="out-in">
            <div>
              <component :is="Component" v-if="$route.meta.keepAlive && $route.name" />
              <component :is="Component" v-show="!$route.meta.keepAlive && $route.name" />
            </div>
          </transition>
        </router-view>
      </el-main>
    </el-container>
  </el-container>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import { useRoute, useRouter } from 'vue-router'
import { Moon, Sunny, ArrowDown, HomeFilled, Monitor, Location, Document } from '@element-plus/icons-vue'
import { useThemeStore } from '@/store/themeStore'

const route = useRoute()
const router = useRouter()

// 用户信息和暗黑模式状态
const username = ref('管理员')

const themeStore = useThemeStore()

const toggleDarkMode = () => {
  // themeStore.toggleTheme();
  if(themeStore.isDarkMode) {
    // document.body.classList.remove('dark-mode')
    console.log('dark-mode')
  } else {
    // document.body.classList.add('dark-mode')
    console.log('light-mode')
  }
};

// 菜单折叠状态
const isCollapse = ref(false)

// 用户操作命令处理
const handleUserCommand = (command) => {
  if (command === 'logout') {
    // 登出逻辑
    // 清楚本地token
    localStorage.removeItem('token')
    router.push('/login')
  }
}

// 监听窗口大小变化调整菜单宽度
onMounted(() => {
  const handleResize = () => {
    if (window.innerWidth < 768) {
      isCollapse.value = true
    } else {
      isCollapse.value = false
    }
  }

  window.addEventListener('resize', handleResize)
  handleResize()
})
</script>

<style scoped>
.layout-container {
  height: 100vh;
}

.layout-header {
  background-color: var(--el-bg-color-overlay);
  display: flex;
  justify-content: space-between;
  align-items: center;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
  z-index: 1000;
}

.logo {
  font-size: 1.5rem;
  font-weight: bold;
  color: var(--el-color-primary);
}

.header-right {
  display: flex;
  gap: 1rem;
  align-items: center;
}

.user-info {
  cursor: pointer;
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

.layout-aside {
  background-color: var(--el-bg-color-overlay);
  transition: width 0.3s ease;
  border-right: 1px solid var(--el-border-color);
}

.layout-main {
  padding: 1rem;
  background-color: var(--el-bg-color-page);
}

.fade-transform-enter-active,
.fade-transform-leave-active {
  transition: all 0.3s;
}

.fade-transform-enter-from,
.fade-transform-leave-to {
  opacity: 0;
  transform: translateX(-30px);
}
</style>
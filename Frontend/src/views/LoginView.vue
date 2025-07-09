<template>
  <div class="login-container">
    <div class="login-card">
      <h2>设备管理平台</h2>
      <p>{{ isRegistering ? '创建新账户' : '欢迎回来，请登录' }}</p>
      
      <!-- 登录表单 -->
      <el-form v-show="!isRegistering" ref="loginForm" :model="loginData" :rules="rules" label-width="0">
        <el-form-item prop="username">
          <el-input v-model="loginData.username" placeholder="用户名">
            <template #prefix>
              <el-icon><User /></el-icon>
            </template>
          </el-input>
        </el-form-item>
        
        <el-form-item prop="password">
          <el-input v-model="loginData.password" type="password" placeholder="密码" @keyup.enter="handleLogin">
            <template #prefix>
              <el-icon><Lock /></el-icon>
            </template>
          </el-input>
        </el-form-item>
        
        <el-form-item>
          <el-button type="primary" @click="handleLogin" class="login-button">
            登录
          </el-button>
        </el-form-item>

        
        <el-form-item>
          <div class="toggle-link">
            <el-button type="success" @click.prevent="toggleForm" class="toggle-button">
              <el-icon><User /></el-icon>
              创建新账户
            </el-button>
          </div>
        </el-form-item>
      </el-form>
      
      <!-- 注册表单 -->
      <el-form v-show="isRegistering" ref="registerForm" :model="registerData" :rules="registerRules" label-width="0">
        <el-form-item prop="username">
          <el-input v-model="registerData.username" placeholder="用户名">
            <template #prefix>
              <el-icon><User /></el-icon>
            </template>
          </el-input>
        </el-form-item>
        
        <el-form-item prop="password">
          <el-input v-model="registerData.password" type="password" placeholder="密码">
            <template #prefix>
              <el-icon><Lock /></el-icon>
            </template>
          </el-input>
        </el-form-item>
        
        <el-form-item prop="inviteCode">
          <el-input v-model="registerData.inviteCode" placeholder="邀请码">
            <template #prefix>
              <el-icon><User /></el-icon>
            </template>
          </el-input>
        </el-form-item>
        
        <el-form-item>
          <el-button type="primary" @click="handleRegister" class="login-button">
            注册
          </el-button>
        </el-form-item>
        
        <el-form-item>
          <div class="toggle-link">
            <el-button type="success" @click.prevent="toggleForm" class="toggle-button">
              <el-icon><Lock /></el-icon>
              返回登录
            </el-button>
          </div>
        </el-form-item>
      </el-form>
      
      <div class="login-footer">
        <el-checkbox v-model="rememberMe">记住账号</el-checkbox>
        <a href="#">忘记密码？</a>
      </div>
    </div>

    <!-- 暗黑模式切换按钮（定位在右上角） -->
    <el-button
      class="dark-mode-toggle"
      @click="toggleDarkMode"
      circle
      :icon="isDarkMode ? Moon : Sunny"
      size="small"
    />
    
    <div class="login-background">
      <div class="bg-circle"></div>
      <div class="bg-circle reverse"></div>
    </div>
  </div>
</template>

<script setup>
import { ref, reactive, computed, watch, onMounted } from 'vue'
import { useRouter, useRoute } from 'vue-router'
import { User, Lock, Sunny, Moon } from '@element-plus/icons-vue'
import { useThemeStore } from '@/store/themeStore'
import axios from 'axios';

const router = useRouter()
const route = useRoute()
const themeStore = useThemeStore()

// 设置 axios 默认基础 URL
const apiClient = axios.create({
  baseURL: '/api',  // 设置基础URL
});

// 添加请求拦截器
apiClient.interceptors.request.use(
  config => {
    // 在发送请求之前做些什么
    // 可以在这里添加 CORS 相关的 header
    // config.headers['Access-Control-Allow-Origin'] = '*';
    // config.headers['Access-Control-Allow-Methods'] = 'GET, POST, PUT, DELETE, OPTIONS';
    // config.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization, X-Requested-With';
    config.headers['Content-Type'] = 'application/json';
    // config.headers['Access-Control-Allow-Origin'] = '*';  // 注意：这个header通常由后端设置
    return config;
  }, 
  error => {
    // 对请求错误做些什么
    return Promise.reject(error);
  }
);

// 在组件挂载时检查路由参数
onMounted(() => {
  if (route.query.register === 'true') {
    isRegistering.value = true
  }
})

// 获取当前是否为暗色模式
const isDarkMode = computed(() => themeStore.isDarkMode)

// 切换暗色模式
const toggleDarkMode = () => {
  themeStore.toggleTheme();
}

// 登录表单数据
const loginData = ref({
  username: '',
  password: ''
})

// 注册表单数据
const registerData = ref({
  username: '',
  password: '',
  inviteCode: ''
})

// 是否正在注册
const isRegistering = ref(false)

// 记住账号状态
const rememberMe = ref(false)

// 表单验证规则
const rules = {
  username: [
    { required: true, message: '请输入用户名', trigger: 'blur' }
  ],
  password: [
    { required: true, message: '请输入密码', trigger: 'blur' }
  ]
}

// 注册表单验证规则
const registerRules = {
  username: [
    { required: true, message: '请输入用户名', trigger: 'blur' }
  ],
  password: [
    { required: true, message: '请输入密码', trigger: 'blur' }
  ],
  inviteCode: [
    { required: true, message: '请输入邀请码', trigger: 'blur' }
  ]
}

const mockUsers = [
  { username: 'admin', password: '123456' }
];

// 处理登录逻辑
const handleLogin = async () => {
  try {
     // 显式触发表单验证
    await loginForm.value.validate();

    console.log('登录请求参数:', loginData.value);

    // 发送登录请求
    const response = await apiClient.post('/login', {
      message: 'login',  // 添加 message 字段
      data: {  // 包裹在 data 字段中
        username: loginData.value.username,
        password: loginData.value.password
      }
    });

    if (response.data.code === 1) {
      // 登录成功，保存 token 到 localStorage
      localStorage.setItem('token', response.data.data.token);
      
      // 跳转到仪表盘
      router.push('/dashboard');
    } else {
      // 根据后端返回的错误信息显示提示
      alert(response.data.message || '登录失败');
      console.error('登录失败:', response.data.message);
    }
    
  } catch (error) {
    console.error('登录失败:', error)
    alert('登录失败，请检查您的网络连接');
  }
}

// 处理注册逻辑
const handleRegister = async () => {
  try {
    // 显式触发表单验证
    await registerForm.value.validate();

    console.log('注册请求参数:', registerData.value);
    
    // 发送注册请求
    const response = await apiClient.post('/register', {
      message: 'register',  // 添加 message 字段
      data: {  // 包裹在 data 字段中
        username: registerData.value.username,
        password: registerData.value.password,
        verifyCode: registerData.value.inviteCode
      }
    });

    if (response.data.code === 1) {
      // 注册成功，显示提示信息
      alert('注册成功！请使用新账户登录');
      
      // 自动切换到登录表单
      isRegistering.value = false;
    } else {
      // 根据后端返回的错误信息显示提示
      alert(response.data.message || '注册失败');
    }
    
  } catch (error) {
    console.error('注册失败:', error);
    
    // 网络错误或其他异常
    if (!navigator.onLine) {
      alert('网络连接不可用，请检查您的网络');
    } else {
      alert('注册失败，请稍后再试');
    }
  }
}

// 切换登录/注册表单
const toggleForm = () => {
  isRegistering.value = !isRegistering.value;
}

// 定义 loginForm 引用
const loginForm = ref()

// 定义 registerForm 引用
const registerForm = ref()

</script>

<style scoped>
.login-container {
  position: relative;
  min-height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  background-color: var(--el-bg-color-page);
  overflow: hidden;
}

.login-card {
  background-color: var(--el-bg-color-overlay);
  padding: 2rem;
  border-radius: 12px;
  box-shadow: 0 4px 30px rgba(0, 0, 0, 0.1);
  width: 400px;
  z-index: 1;
  animation: fadeInUp 0.5s ease-out;
}

@keyframes fadeInUp {
  from {
    opacity: 0;
    transform: translateY(20px);
  }
  to {
    opacity: 1;
    transform: translateY(0);
  }
}

.login-card h2 {
  margin-bottom: 0.5rem;
  color: var(--el-color-primary);
}

.login-card p {
  margin-bottom: 2rem;
  color: var(--el-text-color-regular);
}

.login-button {
  width: 100%;
  font-weight: bold;
  transition: all 0.3s ease;
}

.login-button:hover {
  transform: translateY(-2px);
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
}

.login-footer {
  display: flex;
  justify-content: space-between;
  margin-top: 1rem;
  font-size: 0.9rem;
}

.login-footer a {
  text-decoration: none;
  color: var(--el-color-primary);
}

.login-background {
  position: absolute;
  width: 100%;
  height: 100%;
  top: 0;
  left: 0;
  overflow: hidden;
}

.bg-circle {
  position: absolute;
  border-radius: 50%;
  background: radial-gradient(circle, var(--el-color-primary-light-7) 0%, var(--el-bg-color-page) 80%);
  width: 600px;
  height: 600px;
  animation: pulse 15s infinite;
}

.bg-circle.reverse {
  background: radial-gradient(circle, var(--el-bg-color-page) 0%, var(--el-color-primary-light-7) 80%);
  animation: pulse-reverse 15s infinite;
  right: 0;
  bottom: 0;
}

.dark-mode-toggle {
  position: absolute;
  top: 20px;
  right: 20px; /* 改成 right 定位 */
  z-index: 999;
  background-color: var(--el-bg-color-overlay);
  border: none;
  color: var(--el-text-color-primary);
}

.dark-mode-toggle:hover {
  background-color: var(--el-bg-color-hover);
}

@keyframes pulse {
  0% { transform: scale(1); opacity: 0.3; }
  50% { transform: scale(1.05); opacity: 0.5; }
  100% { transform: scale(1); opacity: 0.3; }
}

@keyframes pulse-reverse {
  0% { transform: scale(1.05); opacity: 0.5; }
  50% { transform: scale(1); opacity: 0.3; }
  100% { transform: scale(1.05); opacity: 0.5; }
}

.register-button {
  width: 100%;
  font-weight: bold;
  transition: all 0.3s ease;
  margin-top: 1rem;
}

.register-button:hover {
  transform: translateY(-2px);
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
  background-color: var(--el-color-success);
  color: white;
}

.register-link {
  margin-top: 15px;
  text-align: center;
}

.toggle-link {
  width: 100%;
}

.toggle-button {
  width: 100%;
  font-weight: bold;
  transition: all 0.3s ease;
  display: flex;
  justify-content: center;
  align-items: center;
}
</style>
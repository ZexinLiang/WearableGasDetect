import { createRouter, createWebHistory } from 'vue-router';
import RegisterView from '../views/RegisterView.vue'

const routes = [
  {
    path: '/login',
    name: 'Login',
    component: () => import('../views/LoginView.vue'),
    meta: { title: '登录' }
  },
  {
    path: '/register',
    name: 'Register',
    redirect: to => ({ path: '/login', query: { register: true } }),
    meta: { title: '注册' }
  },
  {
    path: '/',
    name: 'MainLayout',
    component: () => import('../layout/MainLayout.vue'),
    redirect: '/dashboard',
    children: [
      {
        path: 'dashboard',
        name: 'Dashboard',
        component: () => import('../views/DashboardView.vue'),
        meta: { title: '仪表盘', keepAlive: true }
      },
      {
        path: 'devices',
        name: 'Devices',
        component: () => import('../views/DeviceManagementView.vue'),
        meta: { title: '设备管理', keepAlive: true }
      },
      {
        path: 'map',
        name: 'Map',
        component: () => import('../views/MapView.vue'),
        meta: { title: '地图展示', keepAlive: true }
      },
      {
        path: 'reports',
        name: 'Reports',
        component: () => import('../views/ReportView.vue'),
        meta: { title: '数据报表', keepAlive: true }
      },
      {
        path: 'device/:id',
        name: 'DeviceDetail',
        component: () => import('../views/DeviceDetailView.vue'),
        meta: { title: '设备详情', keepAlive: false }
      }
    ]
  },
];

const router = createRouter({
  history: createWebHistory(),
  routes
});

// 路由守卫
router.beforeEach((to, from, next) => {
  const token = localStorage.getItem('token');

  // 如果用户已登录且尝试访问登录页，则重定向到仪表盘
  if (to.path === '/login' && token) {
    next('/dashboard');
    return;
  }

  // 如果用户未登录且尝试访问非登录页和非注册页，则重定向到登录页
  if (to.path !== '/login' && to.path !== '/register' && !token) {
    next('/login');
    return;
  }

  // 否则继续导航
  next();
});

export default router;
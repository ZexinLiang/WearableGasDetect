<template>
  <div id="app">
    <router-view />
  </div>
</template>

<script setup>
import { useThemeStore } from '@/store/themeStore';
import { watch, onMounted } from 'vue';

const themeStore = useThemeStore();

// 监听 isDarkMode 变化，并更新 body 的 theme-mode 属性
watch(
  () => themeStore.isDarkMode,
  (isDark) => {
    if (isDark) {
      document.body.setAttribute('theme-mode', 'dark');
    } else {
      document.body.removeAttribute('theme-mode');
    }
  },
  {
    immediate: true // 立即执行一次，确保初始状态正确
  }
);

// 初始化时也设置一次
onMounted(() => {
  if (themeStore.isDarkMode) {
    document.body.setAttribute('theme-mode', 'dark');
  } else {
    document.body.removeAttribute('theme-mode');
  }
});
</script>

<style>
/* 全局样式 */
body {
  margin: 0;
  padding: 0;
  font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
}

#app {
  width: 100%;
  height: 100%;
}

/* 
   暗黑模式样式指南

   这些自定义属性（CSS variables）用于覆盖 Element Plus 默认的主题样式，
   确保应用在暗色背景下有良好的可读性和用户体验。
*/
body[theme-mode="dark"] {
  /* 页面背景及基础色调 */
  --el-bg-color-page: #1a1a1a;          /* 主页面背景色 */
  --el-bg-color-overlay: #2a2a2a;       /* 覆盖层背景色（如弹窗） */

  /* 文字颜色 */
  --el-text-color-primary: #ffffff;     /* 主要文字颜色 */
  --el-text-color-regular: #e6e6e6;     /* 常规文字颜色 */
  --el-text-color-secondary: #cccccc;   /* 次要文字颜色 */

  /* 边框颜色 */
  --el-border-color: #4a4a4a;           /* 标准边框颜色 */
  --el-border-color-light: #3a3a3a;     /* 浅色边框（悬停状态等） */

  /* 背景颜色与交互反馈 */
  --el-bg-color: #2a2a2a;               /* 默认背景色 */
  --el-bg-color-hover: #3a3a3a;         /* 悬停时背景色 */
  --el-bg-color-active: #4a4a4a;        /* 激活状态背景色 */
  --el-bg-color-disabled: #2a2a2a;      /* 禁用状态背景色 */

  /* 输入组件背景 */
  --el-input-bg-color: #2a2a2a;         /* 输入框默认背景色 */
  --el-input-bg-color-hover: #3a3a3a;   /* 输入框悬停背景色 */
  --el-select-input-bg-color: #2a2a2a;  /* 下拉选择框背景色 */

  /* 表格样式 */
  --el-table-bg-color: #2a2a2a;         /* 表格整体背景色 */
  --el-table-tr-bg-color: #2a2a2a;      /* 表格行背景色 */
  --el-table-th-bg-color: #3a3a3a;      /* 表头单元格背景色 */
  --el-table-td-bg-color: #2a2a2a;      /* 数据单元格背景色 */

  /* 卡片组件 */
  --el-card-bg-color: #2a2a2a;          /* 卡片背景色 */

  /* 按钮样式 */
  --el-button-bg-color: #3a3a3a;        /* 按钮默认背景色 */
  --el-button-bg-color-hover: #4a4a4a;  /* 按钮悬停背景色 */
  --el-button-bg-color-plain-hover: #3a3a3a;  /* 简洁按钮悬停背景色 */
  --el-button-border-color-plain-hover: #4a4a4a;  /* 简洁按钮悬停边框色 */

  /* 导航菜单 */
  --el-menu-bg-color: #2a2a2a;          /* 菜单背景色 */
  --el-menu-item-hover-tint-percent: 0.05;  /* 菜单项悬停着色百分比 */
  --el-menu-item-active-color: #ffffff;    /* 激活菜单项文字颜色 */
  --el-menu-item-active-bg-color: #3a3a3a;  /* 激活菜单项背景色 */
  --el-menu-submenu-bg-color: #2a2a2a;     /* 子菜单背景色 */
  --el-menu-submenu-popup-bg-color: #2a2a2a;  /* 弹出子菜单背景色 */

    /* Input 组件样式 */
  --el-input-text-color: #ffffff;
  --el-input-border-color: #4a4a4a;
  --el-input-bg-color: #2a2a2a;
  --el-input-bg-color-hover: #3a3a3a;

  /* Button 组件样式 */
  --el-button-bg-color: #3a3a3a;
  --el-button-bg-color-hover: #4a4a4a;
  --el-button-text-color: #ffffff;
  --el-button-border-color: #4a4a4a;
}
body[theme-mode="dark"] .el-menu {
  --el-menu-item-font-color: #e6e6e6;
  --el-menu-submenu-title-color: #e6e6e6;
}

body[theme-mode="dark"] .el-menu-item span,
body[theme-mode="dark"] .el-sub-menu__title span {
  color: #e6e6e6 !important;
}
body[theme-mode="dark"] .el-card {
  background-color: #2a2a2a;
}
body[theme-mode="dark"] .el-card__header {
  background-color: #2a2a2a;
}
body[theme-mode="dark"] .el-card__body {
  background-color: #2a2a2a;
}

/* 暗黑模式下 input 样式强化 */
body[theme-mode="dark"] .el-input__inner {
  background-color: #2a2a2a !important;
  color: #ffffff !important;
  border-color: #4a4a4a !important;
}

/* 暗黑模式下按钮样式强化 */
body[theme-mode="dark"] .el-button:not(.is-disabled) {
  background-color: #3a3a3a !important;
  color: #ffffff !important;
  border-color: #4a4a4a !important;
}

body[theme-mode="dark"] .el-button:hover {
  background-color: #4a4a4a !important;
}
body[theme-mode="dark"] .el-input__wrapper {
  background-color: #2a2a2a !important;
  border-color: #4a4a4a !important;
}
/* 表格无数据时的占位块样式 */
body[theme-mode="dark"] .el-table__empty-block {
  background-color: #2a2a2a !important; /* 暗黑背景 */
  color: #e6e6e6 !important;            /* 浅色文字 */
  border-color: #4a4a4a !important;     /* 边框颜色 */
}

/* 可选：表格分页器在暗黑模式下的字体颜色 */
body[theme-mode="dark"] .el-table__footer-wrapper,
body[theme-mode="dark"] .el-table__header-wrapper {
  background-color: #2a2a2a !important;
  color: #e6e6e6 !important;
}

/* 黑暗模式下 el-tag 标签样式 */
body[theme-mode="dark"] .el-tag {
  --el-tag-bg-color: #3a3a3a !important;
  --el-tag-text-color: #e6e6e6 !important;
  --el-tag-border-color: #4a4a4a !important;

  background-color: #3a3a3a !important;
  color: #e6e6e6 !important;
  border-color: #4a4a4a !important;
}

/* 不同 type 类型的 el-tag 样式适配 */
body[theme-mode="dark"] .el-tag--success {
  background-color: #2e7d32 !important; /* 深绿 */
  color: #ffffff !important;
  border-color: #2e7d32 !important;
}

body[theme-mode="dark"] .el-tag--info {
  background-color: #1976d2 !important; /* 深蓝 */
  color: #ffffff !important;
  border-color: #1976d2 !important;
}

body[theme-mode="dark"] .el-tag--danger {
  background-color: #d32f2f !important; /* 深红 */
  color: #ffffff !important;
  border-color: #d32f2f !important;
}

body[theme-mode="dark"] .el-tag--warning {
  background-color: #ed6c02 !important; /* 橙色 */
  color: #ffffff !important;
  border-color: #ed6c02 !important;
}
</style>
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import path from 'path'

export default defineConfig({
  plugins: [vue()],
  resolve: {
    alias: {
      '@': path.resolve(__dirname, './src')
    }
  },
  server: {
    host: 'localhost',
    port: 8080,
    open: true,
    allowedHosts: ['dev3.motues.top'],
    proxy: {
      '/api': {
        target: 'http://47.99.180.201:1717/api',
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/api/, '')
      }
    }
  }
})
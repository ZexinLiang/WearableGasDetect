// stores/themeStore.js
import { defineStore } from 'pinia';

export const useThemeStore = defineStore('theme', {
  state: () => ({
    isDarkMode: false,
  }),
  actions: {
    toggleTheme() {
      this.isDarkMode = !this.isDarkMode;
    }
  }
});
import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

// https://vite.dev/config/
export default defineConfig({
  plugins: [react()],
  server: {
    port: 3173, // Porta dedicata per Lex demo
    strictPort: true,
  },
  base: '/Lex-compiler/', // Base path per GitHub Pages
  build: {
    rollupOptions: {
      output: {
        manualChunks: {
          'vendor-react': ['react', 'react-dom', 'react-router-dom'],
          'vendor-motion': ['framer-motion'],
          'vendor-markdown': ['react-markdown', 'remark-gfm'],
          'vendor-prism': ['prismjs'],
        }
      }
    }
  }
})

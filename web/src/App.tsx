import { HashRouter as Router, Routes, Route } from 'react-router-dom'
import Navbar from './components/Navbar'
import Footer from './components/Footer'
import Home from './pages/Home'
import Docs from './pages/Docs'
import './index.css'
import { LanguageProvider } from './i18n/LanguageContext'

function PlaygroundPlaceholder() {
  return (
    <div style={{ padding: '150px 0', textAlign: 'center', flex: 1 }}>
      <h2>[ INTERACTIVE_PLAYGROUND_OFFLINE ]</h2>
      <p style={{ color: 'var(--neon-purple)', marginTop: '20px' }}>Awaiting terminal uplink...</p>
    </div>
  )
}

function App() {
  return (
    <LanguageProvider>
      <Router future={{ v7_startTransition: true, v7_relativeSplatPath: true }}>
        <div className="app">
          <Navbar />
          <div className="main-content">
            <Routes>
              <Route path="/" element={<Home />} />
              <Route path="/docs/*" element={<Docs />} />
              <Route path="/playground" element={<PlaygroundPlaceholder />} />
            </Routes>
          </div>
          <Footer />
        </div>
      </Router>
    </LanguageProvider>
  )
}

export default App

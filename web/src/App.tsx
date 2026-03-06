import { useState } from 'react'
import { CodeTransformer } from './components/CodeTransformer'
import './index.css'

// Stats data
const stats = [
  { value: '6', label: 'Backends' },
  { value: '325', label: 'Assertions' },
  { value: '2', label: 'AI Hooks' },
  { value: '100%', label: 'FOSS' },
]

// Install commands
const installCommands = {
  windows: 'irm https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/install.ps1 | iex',
  unix: 'curl -fsSL https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/install.sh | bash',
  source: 'git clone https://github.com/David-Imperium/Lex-compiler.git && cmake -B build && cmake --build build',
}

// Backend targets
const backends = [
  { icon: '[ LUA ]', name: 'Lua', target: 'Any Lua native host' },
  { icon: '[ JSN ]', name: 'JSON', target: 'Universal abstract DB' },
  { icon: '[ GDS ]', name: 'GDScript', target: 'Godot 4.x Resources' },
  { icon: '[ C#_ ]', name: 'C#', target: 'Unity ScriptableObject' },
  { icon: '[ LV2 ]', name: 'LÖVE2D', target: 'LÖVE Framework' },
  { icon: '[ DFL ]', name: 'Defold', target: 'Defold Engine scripts' },
]

// Features
const features = [
  { icon: '[Declarative]', title: 'Syntax_Agnostic', description: 'Describe game content logically. Say goodbye to boilerplate code and unreadable dictionaries.' },
  { icon: '[Speed]', title: 'Native_execution', description: 'Compiled in pure C++. Zero runtime deps. It parses thousands of nodes before you can blink.' },
  { icon: '[Safe]', title: 'Strict_validation', description: 'Catches typos, broken references, and logic errors at compile time, not at play time.' },
  { icon: '[AI_Hooks]', title: 'LLM_ready', description: 'Built-in utilities to translate `.lex` files into agentic memory representations via queries.' },
  { icon: '[Custom]', title: 'Schema_freedom', description: 'Tower defense, RPG, visual novels. Use `--types` to define exactly the node types you need.' },
  { icon: '[Raw]', title: 'Single_Binary', description: 'No pip, no npm, no nightmare setups. One executable to rule your entire content pipeline.' },
]

// Integration links
const integrations = [
  { name: 'Godot', url: 'https://github.com/David-Imperium/Lex-compiler/blob/master/docs/INTEGRATION_GODOT.md' },
  { name: 'Unity', url: 'https://github.com/David-Imperium/Lex-compiler/blob/master/docs/INTEGRATION_UNITY.md' },
  { name: 'LÖVE2D', url: 'https://github.com/David-Imperium/Lex-compiler/blob/master/docs/INTEGRATION_LOVE2D.md' },
]

function App() {
  const [installTab, setInstallTab] = useState<'windows' | 'unix' | 'source'>('windows')

  return (
    <div className="app">
      {/* Header */}
      <header className="app-header">
        <h1 className="glitch-text" data-text="LEX" style={{ display: 'inline-block', position: 'relative' }}>LEX</h1>
        <p className="tagline" style={{ textShadow: '0 0 10px rgba(0,242,254,0.5)' }}>// Write content once, compile everywhere</p>
        <span className="version" style={{ boxShadow: '0 0 15px rgba(34,197,94,0.2)' }}>v1.0.0 :: STABLE.RELEASE</span>
      </header>

      <main>
        {/* Stats */}
        <section className="stats-section">
          <div className="stats-grid">
            {stats.map((stat, i) => (
              <div key={i} className="stat-card">
                <div className="stat-number">{stat.value}</div>
                <div className="stat-label">{stat.label}</div>
              </div>
            ))}
          </div>
        </section>

        {/* Install */}
        <section className="install-section">
          <h2>System_Install</h2>
          <div className="install-tabs">
            <button
              className={installTab === 'windows' ? 'active' : ''}
              onClick={() => setInstallTab('windows')}
            >
              WIN32
            </button>
            <button
              className={installTab === 'unix' ? 'active' : ''}
              onClick={() => setInstallTab('unix')}
            >
              UNIX
            </button>
            <button
              className={installTab === 'source' ? 'active' : ''}
              onClick={() => setInstallTab('source')}
            >
              SRC_BUILD
            </button>
          </div>
          <div className="install-code">
            {installCommands[installTab]}
          </div>
        </section>

        {/* Backends */}
        <section className="backends-section">
          <h2>Module_Targets</h2>
          <p className="subtitle">Compile architecture -&gt; output mapping</p>
          <div className="backends-grid">
            {backends.map((backend, i) => (
              <div key={i} className="backend-card">
                <div className="backend-icon">{backend.icon}</div>
                <div className="backend-name">{backend.name}</div>
                <div className="backend-target">{backend.target}</div>
              </div>
            ))}
          </div>
        </section>

        {/* Code Transformer Animation */}
        <section className="transformer-section">
          <CodeTransformer />
        </section>

        {/* Features */}
        <section className="features-section">
          <h2>Core_Features</h2>
          <div className="features-grid">
            {features.map((feature, i) => (
              <div key={i} className="feature-card">
                <div className="feature-icon">{feature.icon}</div>
                <h3>{feature.title}</h3>
                <p>{feature.description}</p>
              </div>
            ))}
          </div>
        </section>

        {/* CTA */}
        <section className="cta-section">
          <h2>Initialize Connection?</h2>
          <p className="subtitle">status = "awaiting command"</p>
          <div className="cta-buttons">
            <a href="https://github.com/David-Imperium/Lex-compiler" className="btn btn-primary" target="_blank" rel="noopener noreferrer">
              [ // INIT _ GITHUB ]
            </a>
            <a href="https://github.com/David-Imperium/Lex-compiler/releases" className="btn btn-secondary" target="_blank" rel="noopener noreferrer">
              [ DOWNLOAD_V1.0.0 ]
            </a>
            <a href="https://github.com/sponsors/David-Imperium" className="btn btn-sponsor" target="_blank" rel="noopener noreferrer">
              [ ❤️ SPONSOR ]
            </a>
          </div>
          <div className="links-row">
            {integrations.map((int, i) => (
              <a key={i} href={int.url} target="_blank" rel="noopener noreferrer">
                Link::{int.name}
              </a>
            ))}
            <a href="https://github.com/David-Imperium/Lex-compiler/blob/master/docs/ROADMAP.md" target="_blank" rel="noopener noreferrer">
              sys.roadmap()
            </a>
          </div>
        </section>
      </main>

      {/* Footer */}
      <footer className="app-footer">
        <p>LEX_COMPILER // VERSION 1.0.0 // LICENSED UNDER MIT</p>
        <p>MAINTAINED BY <a href="https://github.com/David-Imperium" target="_blank" rel="noopener noreferrer">DAVID [IMPERIUM]</a></p>
      </footer>
    </div>
  )
}

export default App

// Stats data
export const stats = [
    { value: '6', labelKey: 'stats.backends' },
    { value: '325', labelKey: 'stats.assertions' },
    { value: '2', labelKey: 'stats.hooks' },
    { value: '100%', labelKey: 'stats.foss' },
]

// Install commands
export const installCommands = {
    windows: 'irm https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/install.ps1 | iex',
    unix: 'curl -fsSL https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/install.sh | bash',
    source: 'git clone https://github.com/David-Imperium/Lex-compiler.git && cmake -B build && cmake --build build',
}

// Backend targets
export const backends = [
    { icon: '[ LUA ]', name: 'Lua', targetKey: 'backends.descLua' },
    { icon: '[ JSN ]', name: 'JSON', targetKey: 'backends.descJson' },
    { icon: '[ GDS ]', name: 'GDScript', targetKey: 'backends.descGdscript' },
    { icon: '[ C#_ ]', name: 'C#', targetKey: 'backends.descCsharp' },
    { icon: '[ LV2 ]', name: 'LÖVE2D', targetKey: 'backends.descLove2d' },
    { icon: '[ DFL ]', name: 'Defold', targetKey: 'backends.descDefold' },
]

// Features
export const features = [
    { icon: '[Declarative]', title: 'Syntax_Agnostic', descriptionKey: 'features.agnosticDesc' },
    { icon: '[Speed]', title: 'Native_execution', descriptionKey: 'features.speedDesc' },
    { icon: '[Safe]', title: 'Strict_validation', descriptionKey: 'features.safeDesc' },
    { icon: '[AI_Hooks]', title: 'LLM_ready', descriptionKey: 'features.aiDesc' },
    { icon: '[Custom]', title: 'Schema_freedom', descriptionKey: 'features.customDesc' },
    { icon: '[Raw]', title: 'Single_Binary', descriptionKey: 'features.rawDesc' },
]

// Integration links
export const integrations = [
    { name: 'Godot', url: 'https://github.com/David-Imperium/Lex-compiler/blob/master/docs/INTEGRATION_GODOT.md' },
    { name: 'Unity', url: 'https://github.com/David-Imperium/Lex-compiler/blob/master/docs/INTEGRATION_UNITY.md' },
    { name: 'LÖVE2D', url: 'https://github.com/David-Imperium/Lex-compiler/blob/master/docs/INTEGRATION_LOVE2D.md' },
]

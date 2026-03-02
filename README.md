# Lex Compiler

[![CI](https://github.com/David-Imperium/Lex-compiler/actions/workflows/ci.yml/badge.svg)](https://github.com/David-Imperium/Lex-compiler/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Version](https://img.shields.io/badge/version-0.3.1-blue.svg)](https://github.com/David-Imperium/Lex-compiler)

A declarative, multi-target transpiler for game content.

**Principle:** *Describe what, not how.*

## Quick Start

```bash
# Clone and build
git clone https://github.com/David-Imperium/Lex-compiler.git
cd lex
cmake -B build -S .
cmake --build build --config Release

# Try it!
.\build\Release\lexc.exe examples\imperium_minimal.lex -t lua,json
```

## Usage

```bash
# Basic usage (uses default Imperium schema)
lexc input.lex -t lua,json

# Custom schema for your game
lexc input.lex --types item,character,location -t json

# Multiple outputs
lexc input.lex -o output/ -t lua,json
```

Options:
- `-o, --output <dir>` — Output directory
- `-t, --target <fmt>` — Output format(s): lua, json
- `--types <list>` — Custom definition types (comma-separated)
- `--no-validate` — Skip semantic validation
- `-h, --help` — Show help

## Custom Schemas

Lex is **agnostic** — define your own types:

```lex
character Hero {
    name: "Arthur"
    level: 5
    class: "Warrior"
}

item Sword {
    name: "Excalibur"
    damage: 50
    rarity: "legendary"
}
```

Compile with:
```bash
lexc game.lex --types character,item -t json
```

Output:
```json
{
  "characters": {
    "Hero": {
      "id": "Hero",
      "type": "character",
      "name": "Arthur",
      "level": 5,
      "class": "Warrior"
    }
  },
  "items": {
    "Sword": {
      "id": "Sword",
      "type": "item",
      "name": "Excalibur",
      "damage": 50,
      "rarity": "legendary"
    }
  }
}
```

## Example

Default schema (Imperium-style):

```lex
structure SteamFactory {
    era: Steampunk
    name: "Steam Factory"
    
    cost: {
        Coal: 8,
        Steel: 5,
        Gold: 50
    }
    
    production: {
        Energy: 15,
        Industry: 10
    }
    
    available_if has_technology(SteamEngine) {
    }
}
```

## Features

- **Declarative syntax** — Clean, readable definitions
- **Multi-target** — Lua and JSON backends (TypeScript planned)
- **Custom schemas** — Define your own types via `--types`
- **Type-safe** — Strong typing with inference
- **Semantic validation** — Catches errors before runtime
- **Expression parser** — Full operator precedence support
- **English keywords** — Accessible to international community

## Roadmap

| Version | Status | Features |
|---------|--------|----------|
| v0.3.1 | ✅ Current | Agnostic core, `--types` flag |
| v0.4.0 | 🔜 Next | Binary releases, tutorials, VS Code extension |
| v0.5.0 | 📋 Planned | TypeScript backend |

See [ROADMAP.md](docs/ROADMAP.md) for details.

## Testing

```bash
# Unit tests
.\build\tests\Debug\lexer_tests.exe

# Lua output validation
python tests/lua_validator.py output/game.lua
```

## License

MIT

## Author

David (Imperium Game Engine)

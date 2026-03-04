# Lex Development Roadmap

**Version:** 0.4.0
**Last Updated:** 2026-03-04

---

## Current Status: v0.4.0 (Free Tier Complete)

### Completed Components
| Component | Status | Notes |
|-----------|--------|-------|
| Lexer | ✅ Done | 50+ keywords, full literal support |
| Parser | ✅ Done | Dynamic types via `--types`, conditions, error recovery |
| Expression Parser | ✅ Done | Pratt parser with operator precedence |
| AST | ✅ Done | Type-safe, visitor pattern, typed accessors |
| Type Checker | ✅ Done | Semantic type validation |
| Validator | ✅ Done | Errors/warnings separation |
| **6 Backends** | ✅ Done | **Free Tier Complete** |
| ↳ Lua Backend | ✅ Done | Full expression/condition generation |
| ↳ JSON Backend | ✅ Done | Dynamic output for any type |
| ↳ Godot Backend | ✅ Done | GDScript Resource generation |
| ↳ Unity Backend | ✅ Done | C# ScriptableObject generation |
| ↳ Love2D Backend | ✅ Done | LÖVE2D framework with hot reload |
| ↳ Defold Backend | ✅ Done | Defold engine with collection factory |
| CLI | ✅ Done | `--types`, `--mode` flags |
| Module System | ✅ Done | `use`, `module`, visibility modifiers |
| Tests | ✅ Active | 325 assertions |

### New in v0.4.0
- **Love2D Backend** — LÖVE2D framework code generation with `love.filesystem` integration
- **Defold Backend** — Defold engine code generation with collection factory support
- **Free Tier Complete** — All 6 backends available for free (MIT License)

---

## Roadmap: Core Tier (v0.5.0)

### 1. Core Language Features
| Feature | Description | Status |
|---------|-------------|--------|
| `state` | Global variables with serialization | 📋 Planned |
| `fn` | Functions (pure + side effects) | 📋 Planned |
| `on`/`event` | Event-driven system | 📋 Planned |
| `@serialize` | Auto save/load | 📋 Planned |
| `@hot_reload` | Development mode | 📋 Planned |

### 2. Core Tier Backends
| Backend | Difficulty | Status |
|---------|------------|--------|
| Pygame | 🟢 Easy | 📋 Planned |
| Python | 🟢 Easy | 📋 Planned |
| Construct 3 | 🟢 Easy | 📋 Planned |
| GameMaker | 🟡 Medium | 📋 Planned |
| Bevy | 🟡 Medium | 📋 Planned |
| Raylib | 🟡 Medium | 📋 Planned |
| C++ Header | 🟡 Medium | 📋 Planned |
| Rust | 🟡 Medium | 📋 Planned |
| Unreal | 🔴 Hard | 📋 Planned |

---

## Roadmap: Accessibility (v0.4.x)

Making Lex usable by everyone, not just C++ developers.

### 1. Binary Releases ⚡ HIGH PRIORITY

**Goal:** Download `lexc.exe` and run — no compilation needed.

| Task | Platform | Status |
|------|----------|--------|
| Windows `.exe` | Windows 10+ | 📋 Planned |
| Linux binary | Ubuntu 20.04+ | 📋 Planned |
| macOS binary | macOS 11+ | 📋 Planned |
| GitHub Releases workflow | CI/CD | 📋 Planned |

**Implementation:**
- GitHub Actions matrix build (3 OS)
- Static linking for portability
- Automatic release on version tags

### 2. Documentation

| Task | Status |
|------|--------|
| Tutorial: "Your first mod" | 📋 Planned |
| **Integration Guide: Existing Games** | 📋 Planned |
| API reference | 📋 Planned |
| Error message catalog | 📋 Planned |

### 3. Error Messages
| Task | Status |
|------|--------|
| User-friendly wording | 📋 Planned |
| Suggestions on typos | 📋 Planned |
| Error codes reference | 📋 Planned |
| `--verbose` mode | 📋 Planned |

### 4. Editor Support

| Task | Priority | Status |
|------|----------|--------|
| VS Code extension | ⚡ High | 📋 Planned |
| Syntax highlighting | ⚡ High | 📋 Planned |
| Autocomplete | 🟡 Medium | 📋 Planned |
| Error squiggles | 🟡 Medium | 📋 Planned |

### 5. Examples

| Task | Status |
|------|--------|
| Complete mini-game example | 📋 Planned |
| Multiple schema examples | 📋 Planned |
| **Integration examples (Unity, Godot, Love2D)** | 📋 Planned |

---

## Integration for Existing Games

**Lex works with your existing game — no engine changes required.**

### How It Works

```
You write:           game.lex
Lex compiles to:     game.json / game.lua / game.cs
Your game reads:     Standard file formats
```

Your game doesn't need to know Lex exists.

### Integration Steps

1. **Define your data** in `.lex` format
2. **Compile** with `lexc game.lex -t json` (or lua, cs, gd)
3. **Load the output** in your game like any other data file

### Example: Unity Integration

```csharp
// Before: Manual data
public class Items {
    public static Item[] all = new Item[] {
        new Item { name = "Sword", damage = 50 }
    };
}

// After: Generated from .lex
// 1. Write items.lex
// 2. Run: lexc items.lex -t cs
// 3. Include generated Items.cs in Unity
// No other changes needed!
```

### Supported Outputs

| Output | Game Engine | Integration |
|--------|-------------|-------------|
| `.json` | Any | Read via JSON parser |
| `.lua` | Love2D, Defold, custom | `require()` or `dofile()` |
| `.cs` | Unity | ScriptableObject |
| `.gd` | Godot 4.x | `ResourceLoader.load()` |

### For Modders

Players can create mods by:
1. Writing `.lex` files
2. Compiling with `lexc` (needs binary release)
3. Placing output in game's mod folder

**Future:** Lex Runtime (embed in game) would allow hot-reload without restart.

---

## Roadmap: Backends (v0.5.0) — Planned

### Godot Backend ✅ Complete
GDScript generation for Godot Engine integration.

### Unity Backend ✅ Complete  
C# generation for Unity integration.

### TypeScript/React Backend — Planned
Generate TypeScript interfaces from definitions.

```bash
lexc game.lex -o output/ -t lua,json,ts
# Produces: *.lua, *.json, *.ts
```

**Tasks:**
- [ ] TypeScript interface generator
- [ ] React component props generation
- [ ] Type-safe game data hooks

---

## v1.0.0 Release Criteria

- [ ] Binary releases for all platforms
- [ ] Complete tutorial documentation
- [ ] VS Code extension published
- [ ] 4 backends functional (Lua, JSON, Godot, Unity)
- [ ] 90%+ test coverage
- [ ] 3+ real projects built with Lex

---

## Changelog

### 2026-03-03: v0.3.2 — Documentation Update
- Fixed EBNF EraDefinition syntax error in LEX_SPECIFICATION.md
- Updated JSON Backend status from "Future" to "Complete"
- Added Godot and Unity backends as complete
- TypeScript/Python backends marked as "Planned"
- Keywords count aligned to 50+ (actual implementation)

### 2026-03-02: v0.3.1 — Agnostic Core
- Added `--types` CLI flag for custom schemas
- Decoupled from Imperium (now uses default schema)
- Dynamic JSON backend for any definition type

### 2026-03-02: v0.3.0 — Core Complete
**Commits:** 1466c3f, 1206cdc, ddcfbd7
**Result:** Core compiler feature-complete with 257 test assertions passing

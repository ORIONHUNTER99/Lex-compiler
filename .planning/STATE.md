# State
Updated: 2026-03-03

## Current Version: v0.3.1

## Active
- **Phase 1.5 COMPLETE** — Lex Base Agnostico + Libreria + Accessibility
- Lex è ora una **libreria C++** con CLI come frontend
- **Tutorial** completo per nuovi utenti
- **VS Code extension** pronta (syntax highlighting + snippets)
- **GitHub Actions** per binary releases su 3 piattaforme

## Sessione 2026-03-03 (notte)
- Lex refactorato come libreria (`lex.lib`)
- Creato `src/lex/` con API pubblica (`lex.hpp`)
- Spostato CLI in `src/cli/`
- Aggiunto tutorial (`docs/TUTORIAL.md`)
- Aggiunto workflow per binary releases
- Aggiunto VS Code extension (`editors/vscode/`)

## Struttura Attuale
```
Lex/
├── src/
│   ├── lex/           # Libreria
│   ├── cli/           # CLI frontend
│   ├── lexer/
│   ├── parser/
│   ├── ast/
│   ├── semantic/
│   ├── codegen/
│   └── schema/
├── docs/
│   ├── TUTORIAL.md    # NUOVO
│   ├── ROADMAP.md
│   └── ...
├── editors/
│   └── vscode/        # NUOVO
└── .github/workflows/
    ├── ci.yml
    └── release.yml    # NUOVO
```

## Next (Internal Priority)
1. **Pubblicare su GitHub** — Push tutto
2. **Creare prima release** — v0.3.1
3. **Pubblicare VS Code extension** — Marketplace
4. **Poi:** TypeScript backend

## Recent Commits
| Commit | Description |
|--------|-------------|
| db634af | docs: Add CHANGELOG.md for v0.3.0 release |
| 4c18406 | fix: Use FetchContent for Catch2, simplify CI |
| 8dea75f | fix: Add vcpkg to CI for Catch2 dependency |
| 97cbf64 | fix: Update GitHub username to David-Imperium |
| c67618e | fix: Remove default GitHub C/C++ workflow |

## Phase Progress

| Phase | Status | Notes |
|-------|--------|-------|
| Phase 0: Lex Base | ✅ DONE | Modder layer complete |
| Phase 1: Core | ✅ DONE | Compiler infrastructure |
| Phase 1.5: Agnostic | ✅ DONE | Schema configurabile via --types CLI |
| Phase 2: Lex Core | 🔜 NEXT | Engine bindings |
| Phase 3: Lex Shader | 📋 Planned | Material system |
| Phase 4: Lex Neural | 📋 Planned | Upscalers |
| Phase 5: Aether | 📋 Planned | AI context (Archivista + God AI) |

## I 5 Layer di Lex

```
┌─────────────────────────────────────────────────────┐
│                    Aether                           │
│           (solo agenti AI, invisibile)              │
│         Archivista + God AI                         │
├─────────────────────────────────────────────────────┤
│                  Lex Neural                         │
│         (GPU compute, DLSS/XeSS/FSR)                │
├─────────────────────────────────────────────────────┤
│                  Lex Shader                         │
│      (interfaccia dichiarativa al RenderGraph)      │
├─────────────────────────────────────────────────────┤
│                  Lex Core                           │
│     (sviluppatore, engine C++, editor Rust)         │
├─────────────────────────────────────────────────────┤
│                  Lex Base                           │
│          (modder, dichiarativo, sicuro)             │
└─────────────────────────────────────────────────────┘
```

## Component Status

| Component | Status | Location |
|-----------|--------|----------|
| Lexer | ✅ | src/lexer/ |
| Parser | ✅ | src/parser/ |
| AST | ✅ | src/ast/ |
| Type Checker | ✅ | src/semantic/ |
| Validator | ✅ | src/semantic/ |
| Lua Backend | ✅ | src/codegen/ |
| JSON Backend | ✅ | src/codegen/ |
| CLI | ✅ | src/main.cpp |
| Tests | ✅ | tests/ |

## Engine Problems Solved by Lex

| Problem | Solution | Layer |
|---------|----------|-------|
| Modder can break game | Lex Base sandbox | Base |
| Manual C++ bindings | Auto-generate from Lex | Core |
| Shader cross-platform | Multi-target compilation | Shader |
| Upscaler fragmentation | Single API abstraction | Neural |
| AI lacks game context | Auto context generation | Aether |

## Build Commands
```bash
cmake -B build -S .
cmake --build build --config Release
.\build\Debug\lexc.exe input.lex -t lua,json -o output/
```

## Test Commands
```bash
.\build\tests\Debug\lexer_tests.exe
python tests/lua_validator.py build/output/imperium_minimal.lua
```

## Documents
- **Public:** docs/ROADMAP.md (simplified)
- **Internal:** .planning/INTERNAL_ROADMAP.md (full vision)
- **Master Design:** docs/LEX_MASTER_DESIGN.md (complete architecture)

# State
Updated: 2026-03-02

## Current Version: v0.3.0

## Active
- **Phase 1.5: Lex Base Agnostico** — Disaccoppiare da Imperium
- Obiettivo: Pubblicabile su GitHub come tool generico per sviluppatori
- Target: Sviluppatori di giochi, non modder finali

## Next (Internal Priority)
1. **Lex Base Agnostico** — Sistema di schema configurabile
2. **Config Imperium** — Schema predefinito per Imperium
3. **Documentazione** — "Come configurare Lex per il tuo gioco"
4. **GitHub Ready** — Pulire e pubblicare
5. **Poi:** Lex Core (C++ backend, engine bindings)

## Sessione 2026-03-02 (Serata)
- Discussione su target utenti: sviluppatori vs modder
- **DECISIONE:** Lex è tool per sviluppatori (Opzione A)
- I modder usano Lex tramite il gioco che scaricano
- Inizio lavoro su schema configurabile
- File creati: `src/shared/layer.h`, `src/core/definitions_core.h`, `src/base/validator_base.h`

## Decisioni Importanti
| Decisione | Motivo |
|-----------|--------|
| Target = Sviluppatori | Modder non usano Lex da soli, serve un gioco |
| Schema configurabile | Ogni dev definisce i tipi del suo gioco |
| Imperium come esempio | Mostra il valore, ma non è hardcoded |

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

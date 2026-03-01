# Lex Language - Development Roadmap

**Versione:** 0.1.0  
**Data Inizio:** 2026-03-01  
**Ultimo Aggiornamento:** 2026-03-01

---

## 📊 Overview

**Obiettivo:** Creare un transpiler multi-target per modding di giochi.

**MVP Target:** 2 settimane (2026-03-15)  
**Full Release Target:** 3 mesi (2026-06-01)

---

## 🎯 Milestones

### Milestone 0: Documentazione Base ✅ COMPLETATO
**Data:** 2026-03-01  
**Stato:** ✅ 100%

**Deliverables:**
- [x] `LEX_VISION.md` - Visione progetto
- [x] `LEX_CHANGELOG.md` - Tracciamento cambiamenti
- [x] `LEX_AI_INTEGRATION.md` - Guida integrazione AI
- [x] `LEX_KEYWORDS_EN_IT.md` - Reference bilingue
- [x] `LEX_ECOSYSTEM_INTEGRATION.md` - Integrazione ecosistema
- [x] `TODO.md` - Task tracking
- [x] `progress.md` - Progress tracking
- [x] 3 esempi pratici

**Criteri Successo:**
- ✅ Documentazione leggibile e completa
- ✅ Architettura multi-target definita
- ✅ Target utenti chiari (AI + umani)

---

### Milestone 1: Specifiche Complete
**Data Target:** 2026-03-03 (2 giorni)  
**Stato:** 🔴 Non Iniziato  
**Priorità:** 🔴 ALTA

**Deliverables:**
- [ ] `LEX_SPECIFICATION.md`
  - [ ] BNF/EBNF grammatica formale
  - [ ] Tipi di dato completi
  - [ ] Sintassi espressioni
  - [ ] Sintassi condizioni
  - [ ] Sintassi strutture
  - [ ] Esempi formali

- [ ] `LEX_ARCHITECTURE.md`
  - [ ] Lexer design
  - [ ] Parser design
  - [ ] AST structure
  - [ ] Code generation pipeline
  - [ ] Backend architecture

- [ ] `LEX_INTEGRATION.md`
  - [ ] Integrazione Imperium workflow
  - [ ] Output format mapping
  - [ ] Hot-reload design

**Criteri Successo:**
- [ ] Specifiche sufficienti per implementazione
- [ ] Grammatica non ambigua
- [ ] Design AST chiaro

---

### Milestone 2: Setup Progetto
**Data Target:** 2026-03-04 (1 giorno)  
**Stato:** 🔴 Non Iniziato  
**Priorità:** 🔴 ALTA

**Deliverables:**
- [ ] Struttura directory progetto
  ```
  src/
  ├── lexer/
  ├── parser/
  ├── ast/
  ├── codegen/
  └── main.cpp
  tests/
  examples/
  CMakeLists.txt
  vcpkg.json
  ```

- [ ] Build system
  - [ ] CMakeLists.txt configurato
  - [ ] vcpkg.json dependencies
  - [ ] Build test (Hello World)

- [ ] Development environment
  - [ ] Compilatore C++20 configurato
  - [ ] IDE/Editor setup
  - [ ] Test framework (Catch2)

**Criteri Successo:**
- [ ] `cmake --build build` compila senza errori
- [ ] Eseguibile vuoto gira
- [ ] Test framework funzionante

**Tempo Stimato:** 2-3 ore

---

### Milestone 3: Lexer MVP
**Data Target:** 2026-03-08 (4 giorni)  
**Stato:** 🔴 Non Iniziato  
**Priorità:** 🔴 ALTA

**Deliverables:**

**Fase 3.1: Token System (1 giorno)**
- [ ] `src/lexer/token.h`
  - [ ] `TokenType` enum (80+ tipi)
  - [ ] `Token` struct (type, value, location)
  - [ ] `Location` struct (file, line, column)

- [ ] `src/lexer/keywords.h`
  - [ ] Keyword table IT/EN
  - [ ] Operator table
  - [ ] Literal patterns

**Fase 3.2: Lexer Core (2 giorni)**
- [ ] `src/lexer/lexer.h`
- [ ] `src/lexer/lexer.cpp`
  - [ ] `Lexer::tokenize()` method
  - [ ] Skip whitespace/comments
  - [ ] Recognize keywords
  - [ ] Recognize identifiers
  - [ ] Recognize literals (string, number, hex)
  - [ ] Recognize operators
  - [ ] Error handling con location

**Fase 3.3: Testing (1 giorno)**
- [ ] `tests/test_lexer.cpp`
  - [ ] Test keywords IT/EN
  - [ ] Test identifiers
  - [ ] Test literals
  - [ ] Test operators
  - [ ] Test error recovery

- [ ] Test con file `.lex` reale
  - [ ] `tests/examples/basic_structure.lex`
  - [ ] Output tokens verificato

**Criteri Successo:**
- [ ] Lexer tokenizza file `.lex` complesso
- [ ] Tutti i test passano (100%)
- [ ] Error handling funziona
- [ ] Supporta IT + EN keywords

**Tempo Stimato:** 16-20 ore

---

### Milestone 4: Parser MVP
**Data Target:** 2026-03-15 (7 giorni)  
**Stato:** 🔴 Non Iniziato  
**Priorità:** 🔴 ALTA

**Deliverables:**

**Fase 4.1: AST Structure (2 giorni)**
- [ ] `src/ast/ast.h`
  - [ ] Base AST node
  - [ ] Structure node
  - [ ] Property nodes
  - [ ] Expression nodes
  - [ ] Condition nodes
  - [ ] Visitor pattern

- [ ] `src/ast/ast.cpp`
  - [ ] AST printing/debugging
  - [ ] AST serialization

**Fase 4.2: Parser Core (4 giorni)**
- [ ] `src/parser/parser.h`
- [ ] `src/parser/parser.cpp`
  - [ ] Recursive descent parser
  - [ ] Parse structures
  - [ ] Parse properties
  - [ ] Parse expressions
  - [ ] Parse conditions
  - [ ] Error recovery

**Fase 4.3: Validation (1 giorno)**
- [ ] `src/parser/validator.h`
- [ ] `src/parser/validator.cpp`
  - [ ] Semantic validation
  - [ ] Type checking base
  - [ ] Reference validation

**Criteri Successo:**
- [ ] Parser genera AST da tokens
- [ ] AST rappresenta correttamente source
- [ ] Validazione rileva errori semantici
- [ ] Tutti i test passano

**Tempo Stimato:** 28-32 ore

---

### Milestone 5: Lua Backend MVP
**Data Target:** 2026-03-22 (7 giorni)  
**Stato:** 🔴 Non Iniziato  
**Priorità:** 🟡 MEDIA

**Deliverables:**

**Fase 5.1: Code Generator (4 giorni)**
- [ ] `src/codegen/lua_backend.h`
- [ ] `src/codegen/lua_backend.cpp`
  - [ ] AST → Lua code generation
  - [ ] Template system
  - [ ] Code formatting
  - [ ] Comment preservation

**Fase 5.2: Integration (2 giorni)**
- [ ] Test con mod Imperium
  - [ ] Convertire struttura esistente
  - [ ] Verificare output Lua
  - [ ] Testare in-game

**Fase 5.3: CLI Tool (1 giorno)**
- [ ] `src/main.cpp`
  - [ ] `lexc compile file.lex --output file.lua`
  - [ ] Error reporting
  - [ ] Verbose mode

**Criteri Successo:**
- [ ] Genera codice Lua valido
- [ ] Codice Lua gira in Imperium
- [ ] Modder può usare CLI
- [ ] Documentazione aggiornata

**Tempo Stimato:** 28-32 ore

---

### Milestone 6: Multi-Target Backends
**Data Target:** 2026-04-05 (14 giorni)  
**Stato:** 🔴 Non Iniziato  
**Priorità:** 🟡 MEDIA

**Deliverables:**

**Fase 6.1: JSON Backend (3 giorni)**
- [ ] `src/codegen/json_backend.h`
- [ ] `src/codegen/json_backend.cpp`
  - [ ] AST → JSON generation
  - [ ] Schema validation
  - [ ] Pretty printing

**Fase 6.2: Editor Backend (4 giorni)**
- [ ] `src/codegen/editor_backend.h`
- [ ] `src/codegen/editor_backend.cpp`
  - [ ] Autocomplete data
  - [ ] Dependency graph
  - [ ] Validation rules
  - [ ] Outline view

**Fase 6.3: Lore Backend (3 giorni)**
- [ ] `src/codegen/lore_backend.h`
- [ ] `src/codegen/lore_backend.cpp`
  - [ ] Tutorial context
  - [ ] Companion context
  - [ ] Narrative extraction

**Fase 6.4: React Backend (4 giorni)**
- [ ] `src/codegen/react_backend.h`
- [ ] `src/codegen/react_backend.cpp`
  - [ ] TypeScript types
  - [ ] React components
  - [ ] Props generation

**Criteri Successo:**
- [ ] Tutti i backend generano output valido
- [ ] Output utilizzabile da rispettivi sistemi
- [ ] Documentazione per ogni backend

**Tempo Stimato:** 56-64 ore

---

### Milestone 7: Tooling
**Data Target:** 2026-04-19 (14 giorni)  
**Stato:** 🔴 Non Iniziato  
**Priorità:** 🟢 BASSA

**Deliverables:**

**Fase 7.1: LSP Server (7 giorni)**
- [ ] LSP server implementation
  - [ ] Text document sync
  - [ ] Completion
  - [ ] Diagnostics
  - [ ] Go to definition
  - [ ] Hover

**Fase 7.2: VS Code Extension (4 giorni)**
- [ ] Syntax highlighting
- [ ] Language client
- [ ] Configuration

**Fase 7.3: Advanced CLI (3 giorni)**
- [ ] Watch mode
- [ ] Incremental compilation
- [ ] Project management

**Criteri Successo:**
- [ ] LSP funziona in VS Code
- [ ] Autocomplete funzionante
- [ ] Error highlighting funzionante

**Tempo Stimato:** 56-64 ore

---

### Milestone 8: Testing & Quality
**Data Target:** 2026-05-03 (14 giorni)  
**Stato:** 🔴 Non Iniziato  
**Priorità:** 🟢 BASSA

**Deliverables:**
- [ ] Comprehensive test suite
  - [ ] Unit tests (80%+ coverage)
  - [ ] Integration tests
  - [ ] Performance tests
  - [ ] Regression tests

- [ ] Documentation
  - [ ] User guide
  - [ ] API reference
  - [ ] Examples gallery
  - [ ] Tutorial

**Criteri Successo:**
- [ ] Test coverage >80%
- [ ] Documentazione completa
- [ ] Performance accettabile

**Tempo Stimato:** 40-48 ore

---

### Milestone 9: Community Release
**Data Target:** 2026-06-01 (4 settimane)  
**Stato:** 🔴 Non Iniziato  
**Priorità:** 🟢 BASSA

**Deliverables:**
- [ ] GitHub repository pubblico
- [ ] Release binaries
- [ ] Community documentation
- [ ] Example projects
- [ ] Contribution guidelines

**Criteri Successo:**
- [ ] Repository pubblico
- [ ] Community engagement
- [ ] Issues/PRs gestiti

**Tempo Stimato:** Variabile

---

## 📅 Timeline Visuale

```
2026-03-01  [M0] Documentazione Base ✅
    |
2026-03-03  [M1] Specifiche Complete
    |
2026-03-04  [M2] Setup Progetto
    |
2026-03-08  [M3] Lexer MVP
    |
2026-03-15  [M4] Parser MVP
    |
2026-03-22  [M5] Lua Backend MVP
    |
            ├─ MVP COMPLETE 🎉
            |
2026-04-05  [M6] Multi-Target Backends
    |
2026-04-19  [M7] Tooling
    |
2026-05-03  [M8] Testing & Quality
    |
2026-06-01  [M9] Community Release
    |
            └─ v1.0.0 RELEASE 🚀
```

---

## 🎯 MVP Definition

**MVP = Milestone 0 + 1 + 2 + 3 + 4 + 5**

**Data Target MVP:** 2026-03-22 (3 settimane)  
**Funzionalità MVP:**
- ✅ Documentazione completa
- ✅ Lexer funzionante
- ✅ Parser funzionante
- ✅ Lua backend funzionante
- ✅ CLI tool base
- ✅ Testato con mod Imperium reale

**Criterio Successo MVP:**
> Un modder può scrivere un file `.lex` e ottenere codice Lua funzionante che gira in Imperium.

---

## 📊 Metriche Avanzamento

### Code Metrics (Aggiornare settimanalmente)

| Settimana | Righe Codice | Test Coverage | Backend Pronti |
|-----------|--------------|---------------|----------------|
| 1 (03-01) | 0            | 0%            | 0              |
| 2 (03-08) | -            | -             | -              |
| 3 (03-15) | -            | -             | -              |
| 4 (03-22) | ~3000 (MVP)  | 60%+          | 1 (Lua)        |

### Documentation Metrics

| Settimana | File Doc | Righe Doc | Esempi |
|-----------|----------|-----------|--------|
| 1 (03-01) | 11       | ~2840     | 3      |
| 2 (03-08) | -        | -         | -      |

---

## ⚠️ Rischi e Mitigazioni

| Rischio | Probabilità | Impatto | Mitigazione | Owner |
|---------|-------------|---------|-------------|-------|
| Scope creep | Alta | Alto | MVP rigoroso, dire "no" | David |
| Performance lexer | Media | Medio | Profiling early | Dev |
| Bugs parser | Alta | Medio | Test coverage 80%+ | Dev |
| Incompatibilità Lua | Media | Alto | Test con mod reale | Dev |
| Abbandono progetto | Media | Alto | Release frequenti | David |

---

## 🔄 Processo di Aggiornamento

**Frequenza:**
- Ogni completamento milestone
- Ogni cambio priorità
- Ogni settimana (venerdì)

**Responsabile:** David (approvazione) + AI (aggiornamento)

**Formato:**
- [x] Task completato
- [~] Task in corso
- [ ] Task da fare
- [-] Task cancellato

---

## 📝 Note Importanti

### Principi di Sviluppo
1. **MVP First:** Funziona prima, perfetto dopo
2. **Test Early:** Testare da subito
3. **Document Everything:** Ogni decisione va documentata
4. **Iterate:** Non perfectionismo, iterazione

### Comunicazione
- Ogni sessione inizia con: leggere progress.md
- Ogni sessione finisce con: aggiornare progress.md + TODO.md
- Decisioni importanti: aggiungere a LEX_CHANGELOG.md

---

## 🎉 Definition of Done

**Una milestone è "Done" quando:**
- [ ] Tutti i deliverables completati
- [ ] Test passano (se applicabile)
- [ ] Documentazione aggiornata
- [ ] Codice reviewato (se team)
- [ ] Demo/funzionante verificata

---

**Ultimo aggiornamento:** 2026-03-01  
**Prossimo aggiornamento:** 2026-03-08 (dopo Lexer MVP)

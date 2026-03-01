# Lex TODO List

**Ultimo aggiornamento:** 2026-03-01

---

## 🔴 ALTA PRIORITÀ (Questa Settimana)

### Setup Progetto
- [x] **Documentazione Base** ✅ Completato
- [x] **ROADMAP.md** ✅ Completato - Milestones definite
- [ ] **Setup Ambiente Sviluppo**
  - [ ] Creare struttura directory `src/`
  - [ ] Configurare `CMakeLists.txt`
  - [ ] Configurare `vcpkg.json`
  - [ ] Test build vuoto
  - [ ] Setup Catch2 per testing

- [ ] **Implementare Lexer MVP**
  - [ ] `src/lexer/token.h` - Definizione token types
  - [ ] `src/lexer/keywords.h` - Tabella keyword IT/EN
  - [ ] `src/lexer/lexer.h` - Lexer interface
  - [ ] `src/lexer/lexer.cpp` - Implementazione
  - [ ] `tests/test_lexer.cpp` - Unit tests
  - [ ] Test con file `.lex` reale

### Documentazione (Parallelamente)
- [ ] **LEX_SPECIFICATION.md** - Specifiche linguistiche
  - [ ] Sintassi formale (BNF/EBNF)
  - [ ] Tipi di dato
  - [ ] Keyword (EN only per formale)
  - [ ] Strutture (era, struttura, unità, tecnologia, scelta, finale)
  - [ ] Espressioni e condizioni
  - [ ] Esempi concreti
  
- [ ] **LEX_ARCHITECTURE.md** - Architettura compilatore
  - [ ] Lexer design
  - [ ] Parser design
  - [ ] AST structure
  - [ ] Code generation pipeline
  - [ ] Multi-target backend system

- [ ] **LEX_INTEGRATION.md** - Integrazione Imperium
  - [ ] Come genera Lua (gameplay)
  - [ ] Come genera JSON (data)
  - [ ] Come genera React (UI)
  - [ ] Come genera Lore (AI)
  - [ ] Workflow modder

### Esempi
- [ ] `examples/conditional_logic.lex` - Esempio con condizionali complessi
- [ ] `examples/technology_tree.lex` - Esempio albero tecnologico
- [ ] `examples/unit_combat.lex` - Esempio sistema di combattimento

---

## 🟡 MEDIA PRIORITÀ (Prossime 2 Settimane)

### Implementazione - Lexer
- [ ] Tokenization
  - [ ] Keywords recognition
  - [ ] Identifiers
  - [ ] Literals (string, number, hex colors)
  - [ ] Operators
  - [ ] Comments

- [ ] Error handling
  - [ ] Syntax errors con posizione
  - [ ] Error messages user-friendly
  - [ ] Recovery mechanism

### Implementazione - Parser
- [ ] AST generation
  - [ ] Struttura nodi AST
  - [ ] Type system (base)
  - [ ] Symbol table
  
- [ ] Validation
  - [ ] Syntax validation
  - [ ] Semantic checks
  - [ ] Reference validation

### Implementazione - Lua Backend
- [ ] Code generator
  - [ ] Template system
  - [ ] Code formatting
  - [ ] Comment preservation
  
- [ ] Integration
  - [ ] Test con mod Imperium esistente
  - [ ] Hot-reload support
  - [ ] Error mapping (AST → source)

---

## 🟢 BASSA PRIORITÀ (Dopo MVP)

### Tooling
- [ ] CLI Tool (`lexc`)
  - [ ] Command-line interface
  - [ ] File watching
  - [ ] Output formatting
  - [ ] Verbose mode

- [ ] VS Code Extension
  - [ ] Syntax highlighting
  - [ ] Autocomplete (basic)
  - [ ] Error squiggles
  - [ ] Go to definition

### Testing
- [ ] Unit Tests
  - [ ] Lexer tests
  - [ ] Parser tests
  - [ ] Code generator tests

- [ ] Integration Tests
  - [ ] Mod Imperium completo
  - [ ] Multi-file compilation
  - [ ] Hot-reload scenarios

- [ ] Performance Tests
  - [ ] Large file compilation
  - [ ] Incremental compilation
  - [ ] Memory usage

### Altri Backend
- [ ] JSON Backend
- [ ] React/TypeScript Backend
- [ ] Lore Backend
- [ ] C++ Bindings Backend (opzionale)

---

## 📝 Note e Decisioni

### Design Decisions

#### 2026-03-01: Lex come Transpiler Multi-Target
**Decisione:** Lex compila a Lua/JSON/React/Lore invece di avere runtime proprio.  
**Motivazione:** Zero overhead, integrazione nativa, debugging semplice.  
**Alternativa scartata:** Lex runtime side-by-side con Lua (troppo overhead).

#### 2026-03-01: MVP Focus su Lua Backend
**Decisione:** Prima implementazione genera solo Lua.  
**Motivazione:** 1 settimana per avere qualcosa di funzionante, testabile subito.  
**Altri backend:** Vengono dopo.

### Domande Aperte

#### Sintassi
- [ ] Sintassi esatta per condizioni: `quando espressione` vs `se espressione`?
- [ ] Come gestire cross-references: `requisiti: [TechA, TechB]` vs `requisiti: {TechA, TechB}`?
- [ ] Supportare inline Lua code per logica custom?

#### Type System
- [ ] Type inference o dichiarazione esplicita?
- [ ] Generics support (es. `List<TipoRisorsa>`)?
- [ ] Union types (es. `Era | List<Era>`)?

#### Integrazione
- [ ] Come mappare errori Lua → source .lex?
- [ ] Hot-reload durante sviluppo: file watching?
- [ ] Debug mode: source maps?

---

## 🎯 Milestones

### Milestone 1: Documentazione Base ✅
- [x] LEX_VISION.md
- [x] LEX_CHANGELOG.md
- [x] progress.md
- [x] Esempi base
- [x] README.md

### Milestone 2: Specifiche Complete
- [ ] LEX_SPECIFICATION.md
- [ ] LEX_ARCHITECTURE.md
- [ ] LEX_INTEGRATION.md
- [ ] Esempi avanzati

### Milestone 3: MVP Transpiler
- [ ] Lexer funzionante
- [ ] Parser funzionante
- [ ] Lua backend funzionante
- [ ] CLI tool base
- [ ] Test con mod reale

### Milestone 4: Multi-Target
- [ ] JSON backend
- [ ] React backend
- [ ] Lore backend
- [ ] Hot-reload

### Milestone 5: Tooling
- [ ] VS Code extension
- [ ] LSP
- [ ] Debug mode

---

## 🔄 Frequenza Aggiornamento

**Aggiornare questo file:**
- ✅ Inizio di ogni sessione di lavoro
- ✅ Fine di ogni sessione di lavoro
- ✅ Quando si cambia priorità
- ✅ Quando si completano task

**Formato:**
- `- [ ]` → Task da fare
- `- [x]` → Task completato
- `- [~]` → Task in corso
- `- [-]` → Task cancellato

---

**Prossima sessione:**
1. Leggere `LEX_VISION.md` e `LEX_CHANGELOG.md`
2. Scrivere `LEX_SPECIFICATION.md`
3. Creare `examples/conditional_logic.lex`

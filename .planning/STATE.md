# State
Updated: 2026-03-01

## Active
(nessun task attivo)

## Next
- Estendere test parser (più casi edge, resource maps, conditions)
- Integrare parser con CLI main.cpp
- Test con file .lex reali

## Recent
- [x] Parser completo con test (4 test, 17 totali)
  - Definition types: era, structure, unit, technology, resource, choice, ending, event, secret
  - Property parsing con Expression, ResourceMap, ReferenceList
  - Condition parsing (when, if, available_if, etc.)
  - Error recovery
- [x] Lexer completo con test (13 test)
- [x] Lua backend aggiornato per nuovo AST
- [x] Documentazione aggiornata (keywords solo inglesi)

// Esempio base: Struttura semplice in Lex
// Questo file mostra la sintassi minimale per definire una struttura

struttura Fattoria {
    era: Antica
    
    costo: {
        Oro: 50,
        Legno: 20
    }
    
    produzione: {
        Cibo: 5
    }
    
    descrizione: "Una fattoria che produce cibo per la popolazione"
}

---

// Note per modder:
// - La sintassi è dichiarativa: descrivi COSA è, non COME funziona
// - Il compilatore genera automaticamente:
//   - Lua: scripts/lua/buildings/fattoria.lua
//   - JSON: data/buildings/fattoria.json
//   - React: ui/buildings/FattoriaPanel.tsx
//   - Lore: ai/lore/fattoria.txt

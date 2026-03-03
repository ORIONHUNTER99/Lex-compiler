# Lex RPG Demo - Godot 4.x

Un mini-demo che mostra come usare i dati generati da Lex in Godot.

## Come eseguire

1. Apri Godot 4.2+
2. Importa questa cartella come progetto
3. Premi F5 per eseguire

## Struttura

```
godot_demo/
├── project.godot      # Configurazione progetto Godot
├── main.tscn          # Scena principale (UI)
├── main.gd            # Logica UI
├── game_data.gd       # Dati generati da Lex (GameData autoload)
├── rpg_data.lex       # Sorgente dati Lex
└── icon.svg           # Icona progetto
```

## Flusso di sviluppo

1. Modifica `rpg_data.lex` con i tuoi dati
2. Genera: `lexc rpg_data.lex -t gd -o . --types item,character,location`
3. Rinomina output in `game_data.gd`
4. Riavvia Godot per ricaricare

## Features demo

- Visualizzazione items con stats e costi
- Browse locations con descrizioni
- Character sheet con stats
- Sistema acquisto items (click su item)
- Inventory tracking

## Generare nuovi dati

```bash
# Dalla root di Lex
build\Debug\lexc.exe examples\godot_demo\rpg_data.lex -t gd -o examples\godot_demo\ --types item,character,location
```

Poi rinomina `rpg_data.gd` in `game_data.gd`.

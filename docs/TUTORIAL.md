# Lex Tutorial: Your First Mod

**You're about to write game content that compiles to 6 different engines.** Let's make something cool.

## What You'll Build

A simple strategy game with:
- **Eras** — progression through ages
- **Structures** — buildings with costs and production
- **Units** — military and civilian
- **Technology** — research unlocks

**Time:** 10 minutes  
**Result:** Clean code for Godot, Unity, LÖVE2D, Defold, or generic Lua/JSON.

---

## Prerequisites

- Lex Compiler installed — `lexc --version` should show v1.0.0
- A text editor — VS Code with the Lex extension is nice
- Basic understanding of game data — if you know what JSON is, you're good

---

## Step 1: Create Your First .lex File

Create `my_game.lex`. We'll start simple:

```lex
// Define eras first (game progression)
era Ancient {
    name: "Ancient Age"
    description: "The beginning of civilization"
}

era Medieval {
    name: "Medieval Age"
    description: "Knights and castles"
}

// Define resources
resource Gold {
    name: "Gold"
    category: currency
    description: "Primary currency"
}

resource Wood {
    name: "Wood"
    category: material
    description: "Building material"
}

// Define structures
structure Farm {
    era: Ancient
    name: "Farm"
    description: "Produces food for your population"
    
    cost: { Gold: 50, Wood: 30 }
    production: { Food: 5 }
}

structure Barracks {
    era: Ancient
    name: "Barracks"
    description: "Train basic military units"
    
    cost: { Gold: 100, Wood: 50 }
    
    available_if gold > 100 {
        // Only available when you have enough gold
    }
}

// Define units
unit Warrior {
    era: Ancient
    name: "Warrior"
    description: "Basic infantry unit"
    
    attack: 10
    defense: 5
    health: 100
    
    cost: { Gold: 25 }
}

// Define technology
technology IronWorking {
    era: Ancient
    name: "Iron Working"
    description: "Unlock stronger units and buildings"
    
    research_cost: 200
}
```

## Step 2: Compile It

One command. Multiple outputs.

```bash
# For Godot
lexc my_game.lex -t gd -o output/

# For Unity
lexc my_game.lex -t cs -o output/

# For LÖVE2D
lexc my_game.lex -t love2d -o output/

# Or compile to everything at once
lexc my_game.lex -t lua,json,gd,cs,love2d,defold -o output/
```

**What you get:**
- `output/my_game.gd` — Godot 4.x Resource
- `output/my_game.cs` — Unity C# ScriptableObject
- `output/my_game.lua` — LÖVE2D module
- `output/my_game.json` — Universal data format

---

## Step 3: Use It in Your Engine

### Godot 4.x

```gdscript
# Load your data
var game_data = preload("res://my_game.gd").new()

# Access structures
for structure_id in game_data.structures:
    var structure = game_data.structures[structure_id]
    print(structure["name"], " costs ", structure["cost"])

# Check conditions
if game_data.evaluate_condition("has_technology(IronWorking)", game_state):
    print("You have Iron Working!")
```

### Unity

```csharp
// Load your data
var gameData = GameData.LoadFromFile("my_game.json");

// Access units
foreach (var unit in gameData.Units.Values) {
    Debug.Log($"{unit.Name}: ATK {unit.Attack}, DEF {unit.Defense}");
}

// Check conditions
if (gameData.EvaluateCondition("gold > 100", gameState)) {
    Debug.Log("You have enough gold!");
}
```

### LÖVE2D

```lua
-- Load your data
local GameData = require("my_game")

-- Access structures
for id, structure in pairs(GameData.structures) do
    print(structure.name, "costs", structure.cost.Gold)
end

-- Check conditions
if GameData.helpers.has_technology("IronWorking", game_state) then
    print("You have Iron Working!")
end
```

## Step 4: Multi-File Projects

Organize large projects with multiple files:

```
game/
├── main.lex          # Entry point
├── eras.lex          # Era definitions
├── resources.lex     # Resource definitions
├── structures.lex    # Building definitions
├── units.lex         # Unit definitions
└── technologies.lex  # Tech tree
```

In `main.lex`:

```lex
// Import other modules
use "eras.lex"
use "resources.lex"
use "structures.lex"
use "units.lex"
use "technologies.lex"

// This file can contain game-wide settings
// or remain empty as an orchestrator
```

Compile:

```bash
lexc game/main.lex -t json,gd,cs -o output/
```

## Step 5: AI Context Generation

Generate context for AI assistants:

```bash
lexc my_game.lex --context json -o ai_context/
```

This creates `ai_context/my_game.context.json` containing:
- Schema information
- All entities with summaries
- Relationships and dependencies
- Natural language descriptions

Use this to help AI tools understand your game data:

```
User: What does the Barracks require?
AI: The Barracks costs 100 Gold and 50 Wood. It's available in the Ancient era and trains military units like Warriors.
```

## Next Steps

- Read the [Language Reference](./public/en/spec/language.md) for all syntax options
- Check [Integration Guides](./INTEGRATION_GODOT.md) for engine-specific details
- Explore [Examples](./examples/) for more complex projects

## Common Patterns

### Prerequisites

```lex
technology Mathematics {
    era: Ancient
    research_cost: 150
}

technology Geometry {
    era: Medieval
    research_cost: 200
    
    // This requires Mathematics first
    if has_technology(Mathematics) { }
}
```

### Conditional Availability

```lex
structure University {
    era: Medieval
    
    // Only available if you have a Library
    available_if has_structure(Library) { }
    
    // Multiple conditions
    if era == Medieval and has_technology(Mathematics) { }
}
```

### Secret Content

```lex
secret AncientArtifact {
    name: "Ancient Artifact"
    description: "A mysterious relic"
    
    // Only discoverable through special events
    secret_if has_event(ArcheologicalDig) { }
}
```

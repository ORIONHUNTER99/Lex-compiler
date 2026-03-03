# Lex Tutorial: Your First Mod

This tutorial walks you through creating a simple game mod using Lex.

## Prerequisites

- Lex compiler installed (or built from source)
- A text editor
- Basic understanding of game content (items, characters, etc.)

## Step 1: Install Lex

### Option A: Download Binary (Recommended)

Download the latest release for your platform:
- Windows: `lexc-windows-x64.zip`
- Linux: `lexc-linux-x64.tar.gz`
- macOS: `lexc-macos-x64.tar.gz`

Extract and add to your PATH.

### Option B: Build from Source

```bash
git clone https://github.com/David-Imperium/Lex-compiler.git
cd Lex-compiler
cmake -B build -S .
cmake --build build --config Release
```

The executable is at `build/Release/lexc` (or `build\Release\lexc.exe` on Windows).

## Step 2: Create Your First Definition

Create a file called `mymod.lex`:

```lex
item HealthPotion {
    name: "Health Potion"
    description: "Restores 50 health points"
    rarity: "common"
    value: 25
}

item MagicSword {
    name: "Excalibur"
    description: "A legendary sword of immense power"
    rarity: "legendary"
    damage: 150
    value: 1000
}

character Goblin {
    name: "Goblin Warrior"
    level: 5
    health: 100
    damage: 15
}

character Dragon {
    name: "Ancient Dragon"
    level: 50
    health: 5000
    damage: 200
}
```

## Step 3: Compile

```bash
lexc mymod.lex --types item,character -t lua,json
```

This tells Lex:
- `--types item,character` — We're using custom types "item" and "character"
- `-t lua,json` — Generate both Lua and JSON output

## Step 4: Check the Output

### JSON Output (`mymod.json`)

```json
{
  "version": "1.0",
  "generated_by": "Lex Compiler v0.3.1",
  "items": {
    "HealthPotion": {
      "id": "HealthPotion",
      "type": "item",
      "name": "Health Potion",
      "description": "Restores 50 health points",
      "rarity": "common",
      "value": 25
    },
    "MagicSword": {
      "id": "MagicSword",
      "type": "item",
      "name": "Excalibur",
      "description": "A legendary sword of immense power",
      "rarity": "legendary",
      "damage": 150,
      "value": 1000
    }
  },
  "characters": {
    "Goblin": {
      "id": "Goblin",
      "type": "character",
      "name": "Goblin Warrior",
      "level": 5,
      "health": 100,
      "damage": 15
    },
    "Dragon": {
      "id": "Dragon",
      "type": "character",
      "name": "Ancient Dragon",
      "level": 50,
      "health": 5000,
      "damage": 200
    }
  }
}
```

## Step 5: Using Conditions

Lex supports conditional blocks:

```lex
item FrostSword {
    name: "Frost Brand"
    damage: 75
    
    available_if player_level > 10 {
        description: "A sword that freezes enemies"
    }
    
    bonus_if has_skill(IceMagic) {
        damage_bonus: 25
    }
}
```

## Step 6: Resource Maps

For costs, production, etc.:

```lex
structure Blacksmith {
    name: "Village Blacksmith"
    
    cost: {
        Gold: 500,
        Wood: 100,
        Stone: 50
    }
    
    production: {
        Gold: 10
    }
}
```

## Using with Your Game

### Lua Integration

```lua
-- Load the generated file
local items = dofile("mymod.lua")

-- Access items
print(items.HealthPotion.name)  -- "Health Potion"
print(items.MagicSword.damage)  -- 150
```

### JSON Integration (Python example)

```python
import json

with open("mymod.json") as f:
    data = json.load(f)

print(data["items"]["HealthPotion"]["name"])  # "Health Potion"
```

### C++ Integration (using the library)

```cpp
#include <lex/lex.hpp>

// Read your .lex file
std::ifstream file("mymod.lex");
std::string source((std::istreambuf_iterator<char>(file)), {});

// Compile
lex::CompileOptions options;
options.types = {"item", "character"};

lex::CompileResult result = lex::compile(source, options);

if (result.success) {
    // Get JSON output
    std::string json = result.outputs["json"];
    
    // Parse and use in your game...
}
```

## Tips

1. **Start simple** — One type, a few definitions
2. **Use `--verbose`** — See what the compiler is doing
3. **Check errors carefully** — Lex tells you line numbers
4. **Organize by type** — Keep items, characters, etc. in separate files if needed

## Next Steps

- Read the [Language Specification](LEX_SPECIFICATION.md)
- See more [Examples](../examples/)
- Check the [ROADMAP](ROADMAP.md) for upcoming features

## Getting Help

- Open an issue on GitHub
- Check existing examples in the `examples/` directory

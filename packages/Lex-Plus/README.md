# Lex-Plus

Premium package for Lex Compiler. All premium backends in one package, license key unlocks your tier.

## Installation

```bash
# 1. Extract to Lex packages directory
unzip lex-plus-v1.0.0.zip -d C:\Lex\packages\

# 2. Build Lex (auto-detects Lex-Plus)
cd C:\Lex
cmake -B build
cmake --build build --config Release

# 3. Use with license key
.\build\Release\lexc.exe game.lex -t unreal --license LEX-CORE-XXXX-XXXX-XXXX
```

## Structure

```
Lex-Plus/
├── CMakeLists.txt           # Links to lex library
├── src/
│   └── codegen/
│       ├── unreal_backend.cpp
│       ├── gamemaker_backend.cpp
│       ├── rust_backend.cpp
│       ├── cpp_backend.cpp
│       └── python_backend.cpp
├── backends/                # Additional backends
├── shader/                  # Shader DSL (Shader tier)
├── neural/                  # Neural inference (Neural tier)
└── studio/                  # Visual editor (Studio tier)
```

## Tiers

One package, license controls access:

| Tier | Backends Unlocked |
|------|-------------------|
| **Base** | lua, json, godot, unity, love2d, defold (FREE) |
| **Core** | + unreal, gamemaker, rust, cpp, python |

## License Usage

```bash
# Via CLI flag
lexc game.lex -t unreal --license LEX-CORE-XXXX-XXXX-XXXX

# Via environment variable
export LEX_LICENSE=LEX-CORE-XXXX-XXXX-XXXX
lexc game.lex -t unreal
```

## Development

```bash
# Clone this repo
git clone https://codeberg.org/David-Imperium/Lex-Plus.git

# Develop backends
cd Lex-Plus/src/codegen
# Edit unreal_backend.cpp, etc.

# Sync to build
.\sync-lex-plus.ps1

# Build & test
cd C:\Lex
cmake --build build --config Release
```

## Distribution

This package is distributed via GitHub Sponsors. Access requires purchase.

## Security

- Premium code NOT in public Lex repo
- License verification embedded in compiler
- Ed25519 signature verification (planned)

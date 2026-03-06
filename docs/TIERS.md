# Lex Tiers

Lex offers multiple tiers to match different needs — from free modding tools to professional game development.

## Quick Comparison

| Tier | Price | Backends | Best For |
|------|-------|----------|----------|
| **Base** | FREE | 6 backends | Modders, hobbyists |
| **Core** | $49 lifetime | +9 backends | Indie developers |

---

## Base (Free)

**MIT License — No purchase required**

### Backends
- Lua — Gameplay scripts
- JSON — Data files
- Godot (GDScript) — Godot Engine
- Unity (C#) — Unity game development
- LÖVE2D — Lua framework
- Defold — Defold engine

### Features
- Module system
- Visibility filtering (modder/developer modes)
- Schema-driven validation
- AI context generator
- Query system

---

## Core ($49 lifetime)

**For indie developers who need more engine support**

### Backends (+9)
- **Unreal** — C++ Headers for Unreal Engine
- **GameMaker** — GML scripts
- **Construct 3** — Event sheets
- **Bevy** — Rust ECS
- **Pygame** — Python game framework
- **Raylib** — C game library
- **C++ Header** — Raw C++ data structures
- **Rust** — Rust structs and enums
- **Python** — Python dataclasses

### Features
- Multi-file projects
- Advanced expressions
- All Base features

---

## Pricing

### Early Bird (Limited Time)

| Tier | Price |
|------|-------|
| Core | $49 lifetime |

**Early adopters keep lifetime access forever.**

### Standard Pricing (After Launch)

| Tier | Monthly | Annual | Lifetime |
|------|---------|--------|----------|
| Core | $9/mo | $79/year | Not available |

**Why the change?**
Lifetime pricing is for early supporters. Once Lex matures, we'll switch to subscriptions for sustainable development.

---

## FAQ

### Why Lex?

**Why use Lex instead of writing JSON/Lua directly?**
You write once, compile to any engine. Change your engine? Recompile. No manual translation. No copy-paste errors. Your `.lex` file is the single source of truth.

**Why not just use a spreadsheet?**
Spreadsheets are great for data, but:
- No type validation
- No references between tables
- No visibility filtering
- No code generation
- Hard to version control

Lex gives you all of that + compiles to real code.

**How is Lex different from other DSLs?**
- **No lock-in:** Output is standard code, not a proprietary format
- **Multi-target:** One file → 6+ engines
- **Schema-agnostic:** Define your own types, not hardcoded to any game
- **Offline:** No cloud, no API, runs locally

**Is Lex only for games?**
Primarily, but not exclusively. Any project that needs:
- Declarative data definitions
- Multiple output formats
- Type validation
- Cross-references

...can use Lex. Some non-game use cases: configuration files, content management, API schemas.

**What if my engine isn't supported?**
- Free backends: lua, json work everywhere
- Core backends: more engines coming
- Custom backend: implement the `Backend` interface (C++)

Or [request a backend](https://github.com/David-Imperium/Lex-compiler/issues).

**Is Lex production-ready?**
Yes. Lex Base (free) is stable with 35+ tests, used in production projects. Core backends are newer but follow the same quality standards.

---

### Pricing & Licensing

**Can I use Base commercially?**
Yes! The MIT license allows any use — personal, commercial, open source. No attribution required.

**Does every team member need a license?**
Yes, each developer needs their own license. Contact us for team pricing (5+ seats).

**Can I upgrade later?**
We only have one tier right now (Core). When new tiers launch, early adopters get upgrade discounts.

**Does lifetime license expire?**
Never. Pay once, use forever. Including all future updates to Core backends.

**What happens if I cancel my subscription?**
You lose access to premium backends when the billing period ends. Your `.lex` files still work with free backends.

**Do I need internet to use Lex?**
No. Lex works completely offline. License verification is local, no call-home.

**Can I get a refund?**
Yes, 30-day money-back guarantee. No questions asked.

**What backends are actually ready?**
- Free: lua, json, godot, unity, love2d, defold (all ready)
- Core: unreal (ready), others planned

**When will other Core backends be ready?**
GameMaker, Rust, C++, Python are on the roadmap. No fixed dates — quality over speed.

---

## How to Purchase

1. Visit [GitHub Sponsors](https://github.com/sponsors/David-Imperium)
2. Choose your tier
3. Receive Lex-Plus package + license key
4. Install and activate

---

## FAQ

**Can I use Base commercially?**
Yes! MIT license allows any use.

**Do I need separate licenses for team members?**
Yes, each developer needs their own license. Contact for team pricing.

**Lifetime license never expires?**
Correct. Pay once, use forever.

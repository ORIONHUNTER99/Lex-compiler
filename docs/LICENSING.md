# Lex Licensing

Lex offers multiple tiers to match different needs — from free modding tools to professional game development.

## Tiers Overview

```
┌─────────────────────────────────────────────────────┐
│                    Aether                           │
│              AI Layer (Archivista + God AI)          │
│                    $99-199/mo                       │
├─────────────────────────────────────────────────────┤
│                  Lex Neural                         │
│         DLSS/XeSS/FSR Configuration                 │
│                    $49/mo                           │
├─────────────────────────────────────────────────────┤
│                  Lex Shader                         │
│         Material System Configuration               │
│            $99 lifetime / $19/mo                    │
├─────────────────────────────────────────────────────┤
│                  Lex Studio                         │
│      Visual Editor, Debugger, Profiler              │
│            $79 lifetime / $15/mo                    │
├─────────────────────────────────────────────────────┤
│                  Lex Net                            │
│      Multiplayer Configuration                     │
│            $69 lifetime / $12/mo                    │
├─────────────────────────────────────────────────────┤
│                  Lex Core                           │
│   Advanced Backends, Expressions, Multi-file        │
│            $49 lifetime / $9/mo                     │
├─────────────────────────────────────────────────────┤
│                  Lex Base                           │
│         FREE — MIT License                          │
│      6 Backends: Lua, JSON, Godot, Unity,           │
│      LÖVE2D, Defold                                 │
└─────────────────────────────────────────────────────┘
```

## Pricing

### Early Bird (Limited Time)

| Tier | Price | Model |
|------|-------|-------|
| **Core** | $49 | Lifetime |
| **Studio** | $79 | Lifetime |
| **Net** | $69 | Lifetime |
| **Shader** | $99 | Lifetime |

**Early adopters keep lifetime access forever.**

### Standard Pricing (After Launch)

| Tier | Monthly | Annual | Model |
|------|---------|--------|-------|
| **Core** | $9 | $79 | Subscription |
| **Studio** | $15 | $149 | Subscription |
| **Net** | $12 | $99 | Subscription |
| **Shader** | $19 | $189 | Subscription |
| **Neural** | $49 | — | Subscription only |
| **Aether** | $99-199 | — | Subscription only |

## Feature Matrix

### Backends

| Backend | Base (Free) | Core+ |
|---------|-------------|-------|
| Lua | ✅ | ✅ |
| JSON | ✅ | ✅ |
| Godot (GDScript) | ✅ | ✅ |
| Unity (C#) | ✅ | ✅ |
| LÖVE2D | ✅ | ✅ |
| Defold | ✅ | ✅ |
| **Unreal** | ❌ | ✅ |
| **GameMaker** | ❌ | ✅ |
| **Construct 3** | ❌ | ✅ |
| **Bevy (Rust)** | ❌ | ✅ |
| **Pygame** | ❌ | ✅ |
| **Raylib** | ❌ | ✅ |
| **C++ Header** | ❌ | ✅ |
| **Rust** | ❌ | ✅ |
| **Python** | ❌ | ✅ |

### Features

| Feature | Base | Core | Studio | Net | Shader | Neural | Aether |
|---------|------|------|--------|-----|--------|--------|--------|
| Module System | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Visibility Filtering | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Advanced Expressions | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Multi-file Projects | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Visual Editor | ❌ | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Debugger | ❌ | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Profiler | ❌ | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Multiplayer Config | ❌ | ❌ | ❌ | ✅ | ✅ | ✅ | ✅ |
| Material System | ❌ | ❌ | ❌ | ❌ | ✅ | ✅ | ✅ |
| DLSS/XeSS/FSR | ❌ | ❌ | ❌ | ❌ | ❌ | ✅ | ✅ |
| AI Tools | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ | ✅ |

## How It Works

### 1. Sponsor via GitHub

Visit [GitHub Sponsors](https://github.com/sponsors/David-Imperium) and choose your tier.

### 2. Receive Your License Key

After sponsoring, you'll receive a license key via:
- Email (if provided)
- GitHub DM

License format: `LEX-CORE-XXXX-XXXX-XXXX`

### 3. Activate in Lex Compiler

```bash
lexc game.lex -t lua --license LEX-CORE-XXXX-XXXX-XXXX
```

Or set environment variable:
```bash
export LEX_LICENSE=LEX-CORE-XXXX-XXXX-XXXX
lexc game.lex -t lua
```

### 4. Enjoy Premium Features

Your license unlocks all backends and features for your tier.

## License Verification

- **Offline verification** — No internet required after activation
- **Cryptographically signed** — Cannot be forged or guessed
- **Per-machine binding** — One license = one developer

## FAQ

### Can I use the free tier commercially?
Yes! Lex Base is MIT licensed — use it for any project, commercial or not.

### What happens if I cancel my subscription?
You keep access until the billing period ends. Lifetime licenses never expire.

### Can I upgrade my tier later?
Yes! Contact us for upgrade pricing.

### Do I need a license for team members?
Each developer needs their own license. Contact us for team pricing.

## Support

- **Issues:** [GitHub Issues](https://github.com/David-Imperium/Lex-compiler/issues)
- **Discussions:** [GitHub Discussions](https://github.com/David-Imperium/Lex-compiler/discussions)
- **Email:** [See GitHub profile]

---

**Early Bird Offer:** Lock in lifetime access now before subscriptions take over.

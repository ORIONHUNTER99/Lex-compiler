#pragma once

#include <string>
#include <string_view>
#include <optional>
#include <unordered_set>
#include <chrono>
#include <cstdint>

namespace lex::license {

// ============================================================================
// Tier Definitions
// ============================================================================

enum class Tier : uint8_t {
    Base,      // Free
    Core,      // $49 lifetime / $9/mo
    Studio,    // $79 lifetime / $15/mo
    Net,       // $69 lifetime / $12/mo
    Shader,    // $149 lifetime / $29/mo
    Neural,    // $149 lifetime / $29/mo
    Engine,    // Future: $199 lifetime / $39/mo
    Unknown
};

// ============================================================================
// License Key Structure
// ============================================================================

struct License {
    Tier tier;
    std::string key;
    std::string random_part;  // XXXX-XXXX-XXXX
    bool is_lifetime;
    std::chrono::system_clock::time_point expires_at;
    bool is_valid;

    // Feature flags
    bool has_advanced_backends() const;
    bool has_studio_tools() const;
    bool has_multiplayer() const;
    bool has_shader_dsl() const;
    bool has_neural() const;

    // Backend access
    std::unordered_set<std::string> get_available_backends() const;

    // String representation
    std::string tier_name() const;
};

// ============================================================================
// License Manager
// ============================================================================

class LicenseManager {
public:
    // Parse and validate license key
    static std::optional<License> parse(std::string_view key);

    // Load license from environment variable
    static std::optional<License> from_env();

    // Verify license signature (Ed25519)
    static bool verify_signature(const License& license);

    // Check if license is expired
    static bool is_expired(const License& license);

    // Get tier from key format
    static Tier tier_from_string(std::string_view str);

private:
    // Embedded Ed25519 public key (set during build)
    static constexpr uint8_t PUBLIC_KEY[32] = {
        // TODO: Generate and embed during build
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // Validate checksum
    static bool validate_checksum(std::string_view key);
};

// ============================================================================
// Free Tier Backends (Base)
// ============================================================================

inline const std::unordered_set<std::string> FREE_BACKENDS = {
    "lua", "json", "godot", "unity", "love2d", "defold"
};

inline const std::unordered_set<std::string> CORE_BACKENDS = {
    "unreal", "gamemaker", "construct", "bevy",
    "pygame", "raylib", "cpp", "rust", "python"
};

} // namespace lex::license

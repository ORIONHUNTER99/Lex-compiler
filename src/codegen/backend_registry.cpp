#include "backend.h"
#include "lua_backend.h"
#include "json_backend.h"
#include "godot_backend.h"
#include "unity_backend.h"
#include "love2d_backend.h"
#include "defold_backend.h"

namespace lex {

BackendRegistry& BackendRegistry::instance() {
    static BackendRegistry registry;
    return registry;
}

void BackendRegistry::register_factory(const std::string& name, BackendFactory factory) {
    factories_[name] = std::move(factory);
}

std::unique_ptr<Backend> BackendRegistry::create(const std::string& name) {
    auto it = factories_.find(name);
    if (it != factories_.end()) {
        return it->second();
    }
    return nullptr;
}

std::vector<std::string> BackendRegistry::available_backends() const {
    std::vector<std::string> names;
    for (const auto& [name, _] : factories_) {
        names.push_back(name);
    }
    return names;
}

// ============================================================================
// Auto-registration helper
// ============================================================================

namespace {
    struct BackendAutoRegister {
        BackendAutoRegister() {
            auto& registry = BackendRegistry::instance();
            
            registry.register_factory("lua", []() {
                return std::make_unique<LuaBackend>();
            });
            
            registry.register_factory("json", []() {
                return std::make_unique<JsonBackend>();
            });
            
            registry.register_factory("godot", []() {
                return std::make_unique<GodotBackend>();
            });
            
            registry.register_factory("unity", []() {
                return std::make_unique<UnityBackend>();
            });
            
            registry.register_factory("love2d", []() {
                return std::make_unique<Love2DBackend>();
            });
            
            registry.register_factory("defold", []() {
                return std::make_unique<DefoldBackend>();
            });
        }
    };
    
    static BackendAutoRegister auto_register;
}

} // namespace lex

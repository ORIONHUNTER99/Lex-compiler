// Test file for Lua expression generation
// Tests conditions with various operators

structure TestBuilding {
    era: Ancient
    name: "Test Building"
    
    cost: { Gold: 100 }
    
    // Simple comparison
    available_if gold > 50 {
    }
    
    // Logical operators
    if era == Steampunk or has_technology(SteamEngine) {
    }
}

unit TestUnit {
    era: Ancient
    name: "Test Unit"
    
    attack: 10
    defense: 5
    
    cost: { Gold: 50 }
}

technology TestTech {
    era: Steampunk
    name: "Test Technology"
    
    research_cost: 200
}

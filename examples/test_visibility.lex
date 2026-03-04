// Test visibility modifiers

era Ancient {
    name: "Ancient Era"
}

// Public - visible to everyone
public structure PublicBuilding {
    era: Ancient
    cost: { Gold: 100 }
}

// Internal - hidden from modders
internal structure InternalBuilding {
    era: Ancient
    cost: { Gold: 50 }
    debug_mode: true
}

// Private - same module only
private structure PrivateBuilding {
    era: Ancient
    cost: { Gold: 25 }
}

// No modifier = public (default)
structure DefaultBuilding {
    era: Ancient
    cost: { Gold: 75 }
}

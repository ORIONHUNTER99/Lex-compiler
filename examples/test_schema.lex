// Test Custom Schema - RPG Items
// This tests that Lua backend works with any definition types

item Sword {
    name: "Iron Sword"
    rarity: "common"
    damage: 15
    cost: { Gold: 100 }
}

item Shield {
    name: "Wooden Shield"
    rarity: "common"
    defense: 10
    cost: { Gold: 50 }
}

character Warrior {
    name: "Warrior"
    health: 100
    attack: 20
    available_if level > 5 {}
}

location Dungeon {
    name: "Dark Dungeon"
    level: 10
    description: "A dangerous place full of monsters."
}

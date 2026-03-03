// Lex RPG Demo - Game Data
// Source file for Lex Compiler

// === ITEMS ===
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

item Health_Potion {
    name: "Health Potion"
    rarity: "common"
    heal: 50
    cost: { Gold: 25 }
}

// === CHARACTERS ===
character Warrior {
    name: "Warrior"
    health: 100
    attack: 20
    defense: 10
}

character Mage {
    name: "Mage"
    health: 60
    attack: 35
    defense: 5
}

// === LOCATIONS ===
location Village {
    name: "Peaceful Village"
    level: 1
    description: "A safe place to rest and trade."
}

location Forest {
    name: "Dark Forest"
    level: 5
    description: "Wolves and bandits lurk in the shadows."
}

location Dungeon {
    name: "Dark Dungeon"
    level: 10
    description: "A dangerous place full of monsters and treasure."
}

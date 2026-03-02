-- Lua Simulator for Lex-generated game data
-- Tests that generated Lua is valid and usable without the actual engine

local passed = 0
local failed = 0

local function test(name, fn)
    local ok, err = pcall(fn)
    if ok then
        print("[PASS] " .. name)
        passed = passed + 1
    else
        print("[FAIL] " .. name .. ": " .. tostring(err))
        failed = failed + 1
    end
end

local function assert_eq(expected, actual, msg)
    if expected ~= actual then
        error((msg or "") .. " expected: " .. tostring(expected) .. ", got: " .. tostring(actual))
    end
end

-- Mock game state for condition testing
local game_state = {
    player = {
        gold = 100,
        resources = {
            Gold = 100,
            Wood = 50,
            Coal = 20,
            Steel = 10,
            Energy = 5
        },
    },
    current_era = "Ancient",
    technologies = {},
    cities = {
        { name = "Roma", population = 100, happiness = 80 }
    }
}

-- Helper to check if player has technology
function has_technology(tech_name)
    return game_state.technologies[tech_name] ~= nil
end

-- Helper to check resource
function has_resource(resource_name, amount)
    return (game_state.player.resources[resource_name] or 0) >= amount
end

-- Load generated data
print("=" .. string.rep("=", 60))
print("Lex Lua Output Simulator")
print("=" .. string.rep("=", 60))
print()

-- Try to load the generated file
local ok, err = pcall(dofile, "output/imperium_minimal.lua")
if not ok then
    print("[FATAL] Cannot load generated Lua: " .. tostring(err))
    os.exit(1)
end

print("Loaded: output/imperium_minimal.lua")
print()

-- Test structure
test("Buildings table exists", function()
    assert_eq("table", type(Buildings), "Buildings should be a table")
end)

test("Units table exists", function()
    assert_eq("table", type(Units), "Units should be a table")
end)

test("Technologies table exists", function()
    assert_eq("table", type(Technologies), "Technologies should be a table")
end)

test("Eras table exists", function()
    assert_eq("table", type(Eras), "Eras should be a table")
end)

test("Resources table exists", function()
    assert_eq("table", type(Resources), "Resources should be a table")
end)

-- Test specific buildings
test("Farm building exists", function()
    assert_eq("table", type(Buildings.Farm), "Farm should be a table")
end)

test("Farm has era property", function()
    assert_eq("Ancient", Buildings.Farm.era)
end)

test("Farm has cost table", function()
    assert_eq("table", type(Buildings.Farm.cost))
    assert_eq(30, Buildings.Farm.cost.Gold)
    assert_eq(15, Buildings.Farm.cost.Wood)
end)

test("Farm has production", function()
    assert_eq(5, Buildings.Farm.production.Gold)
end)

test("Farm has maintenance", function()
    assert_eq(1, Buildings.Farm.maintenance.Gold)
end)

-- Test units
test("Warrior unit exists", function()
    assert_eq("table", type(Units.Warrior))
end)

test("Warrior has combat stats", function()
    assert_eq(5, Units.Warrior.attack)
    assert_eq(3, Units.Warrior.defense)
    assert_eq(2, Units.Warrior.movement)
end)

test("SteamTank has combat stats", function()
    assert_eq(15, Units.SteamTank.attack)
    assert_eq(12, Units.SteamTank.defense)
end)

-- Test technologies
test("SteamEngine technology exists", function()
    assert_eq("table", type(Technologies.SteamEngine))
end)

test("SteamEngine has research_cost", function()
    assert_eq(100, Technologies.SteamEngine.research_cost)
end)

test("SteamEngine unlocks buildings/units", function()
    assert_eq("table", type(Technologies.SteamEngine.unlocks))
    -- Check that unlocks contains expected values
    local unlocks = Technologies.SteamEngine.unlocks
    local has_factory = false
    local has_tank = false
    for _, v in ipairs(unlocks) do
        if v == "SteamFactory" then has_factory = true end
        if v == "SteamTank" then has_tank = true end
    end
    assert_eq(true, has_factory, "Should unlock SteamFactory")
    assert_eq(true, has_tank, "Should unlock SteamTank")
end)

test("IndustrialChemistry has prerequisites", function()
    assert_eq("table", type(Technologies.IndustrialChemistry.prerequisites))
    assert_eq("SteamEngine", Technologies.IndustrialChemistry.prerequisites[1])
end)

-- Test eras
test("Ancient era exists", function()
    assert_eq("Ancient Era", Eras.Ancient.name)
end)

test("Steampunk era exists", function()
    assert_eq("Steampunk Era", Eras.Steampunk.name)
end)

-- Test iteration (important for engine integration)
test("Can iterate all buildings", function()
    local count = 0
    for _ in pairs(Buildings) do count = count + 1 end
    assert_eq(5, count, "Should have 5 buildings")
end)

test("Can iterate all units", function()
    local count = 0
    for _ in pairs(Units) do count = count + 1 end
    assert_eq(3, count, "Should have 3 units")
end)

test("Can iterate all technologies", function()
    local count = 0
    for _ in pairs(Technologies) do count = count + 1 end
    assert_eq(2, count, "Should have 2 technologies")
end)

-- Test helper functions work
test("has_technology helper works", function()
    assert_eq(false, has_technology("SteamEngine"))
    game_state.technologies["SteamEngine"] = true
    assert_eq(true, has_technology("SteamEngine"))
    game_state.technologies["SteamEngine"] = nil
end)

test("has_resource helper works", function()
    assert_eq(true, has_resource("Gold", 50))
    assert_eq(false, has_resource("Gold", 500))
end)

-- Summary
print()
print("=" .. string.rep("=", 60))
print(string.format("Results: %d passed, %d failed", passed, failed))
print("=" .. string.rep("=", 60))

if failed > 0 then
    os.exit(1)
else
    print("\nAll tests passed! Generated Lua is valid and usable.")
    os.exit(0)
end

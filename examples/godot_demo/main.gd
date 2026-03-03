extends Control

# Lex RPG Demo - Main Scene
# Demonstrates using Lex-generated GameData in Godot

@onready var item_list = $Panel/VBox/HBox/ItemsPanel/VBox/ItemList
@onready var item_details = $Panel/VBox/HBox/ItemsPanel/VBox/ItemDetails
@onready var location_list = $Panel/VBox/HBox/LocationsPanel/VBox/LocationList
@onready var location_details = $Panel/VBox/HBox/LocationsPanel/VBox/LocationDetails
@onready var char_name = $Panel/VBox/HBox/CharacterPanel/VBox/CharName
@onready var char_stats = $Panel/VBox/HBox/CharacterPanel/VBox/Stats
@onready var inventory_list = $Panel/VBox/HBox/CharacterPanel/VBox/Inventory

var player_gold: int = 500
var player_inventory: Array[String] = []

func _ready():
	_populate_items()
	_populate_locations()
	_update_character()

func _populate_items():
	item_list.clear()
	for item_id in GameData.items.keys():
		var item = GameData.items[item_id]
		item_list.add_item("%s (%d gold)" % [item.name, item.cost.get("Gold", 0)])
	item_list.item_selected.connect(_on_item_selected)

func _populate_locations():
	location_list.clear()
	for loc_id in GameData.locations.keys():
		var loc = GameData.locations[loc_id]
		location_list.add_item("%s (Lv.%d)" % [loc.name, loc.level])
	location_list.item_selected.connect(_on_location_selected)

func _update_character():
	var char_data = GameData.characters.get("Warrior", {})
	char_name.text = char_data.get("name", "Unknown")

	var stats_text = """[b]Stats[/b]
HP: %d
ATK: %d
DEF: %d

[b]Gold:[/b] %d

[b]Inventory:[/b]""" % [
		char_data.get("health", 0),
		char_data.get("attack", 0),
		char_data.get("defense", 0),
		player_gold
	]
	char_stats.text = stats_text

	# Update inventory list
	inventory_list.clear()
	for item_id in player_inventory:
		var item = GameData.items.get(item_id, {})
		inventory_list.add_item(item.get("name", item_id))

func _on_item_selected(index: int):
	var item_ids = GameData.items.keys()
	if index < item_ids.size():
		var item_id = item_ids[index]
		var item = GameData.items[item_id]

		var details = "[b]%s[/b]\n" % item.name
		details += "Rarity: %s\n\n" % item.get("rarity", "common")

		if item.has("damage"):
			details += "Damage: %d\n" % item.damage
		if item.has("defense"):
			details += "Defense: %d\n" % item.defense
		if item.has("heal"):
			details += "Heal: %d HP\n" % item.heal

		details += "\nCost: %d Gold" % item.cost.get("Gold", 0)
		item_details.text = details

		# Double-click to buy (simple demo)
		if Input.is_mouse_button_pressed(MOUSE_BUTTON_LEFT):
			_try_buy_item(item_id, item)

func _try_buy_item(item_id: String, item: Dictionary):
	var cost = item.cost.get("Gold", 0)
	if player_gold >= cost:
		player_gold -= cost
		player_inventory.append(item_id)
		_update_character()
		item_details.text += "\n\n[color=green]Purchased![/color]"

func _on_location_selected(index: int):
	var loc_ids = GameData.locations.keys()
	if index < loc_ids.size():
		var loc_id = loc_ids[index]
		var loc = GameData.locations[loc_id]

		var details = "[b]%s[/b]\n" % loc.name
		details += "Level: %d\n\n" % loc.level
		details += loc.get("description", "No description")
		location_details.text = details

#include "../game_all.h"

void ItemsManager::Awake()
{
	if (im == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		im = this;
	}
	else if (im != P<ItemsManager>(this))
	{
		Object::Destroy(gameObject);
	}
}

void ItemsManager::reloadAfterLanguageChange()
{
	Start();
	initItems();
}

void ItemsManager::Start()
{
	items = List<P<Item>>::New();
	initItem(S("key1"), 0.0f, S("keypick01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("key2"), 0.1f, S("keypick01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("key4"), 0.1f, S("keypick01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("key3"), 0.1f, S("keypick01"), nullptr, nullptr, 0, 0, true, 0, 0, 0, 0, List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("key3_inspect")) }), 100, -110, 40, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, true, nullptr, String::Empty);
	initItem(S("pipe"), 1.0f, S("metalpipe"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("sonic"), 2.5f, S("flashlight1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("sonic_remote"), GameStrings::getString(GameStrings::actions, S("remote_sonic")), nullptr, String::Empty)
	}), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("sonic_remote"), String::Empty, [this]() { sonic_remote_use(); }, S("action_s"), 50)
	}), 1, 15, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("sonic2"), 2.5f, S("flashlight1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("sonic_remote"), GameStrings::getString(GameStrings::actions, S("remote_sonic2")), nullptr, String::Empty)
	}), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("sonic_remote"), S("remote_sonic2"), nullptr, String::Empty)
	}), 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("sonic_remote"), 1.0f, S("flashlight1"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	int var = 1;
	int var2 = 1;
	int var3 = 1;
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 1)
	{
		var = 1;
		var2 = 1;
		var3 = 1;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 2)
	{
		var = 2;
		var2 = 2;
		var3 = 1;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 3)
	{
		var = 2;
		var2 = 2;
		var3 = 2;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 4)
	{
		var = 1;
		var2 = 2;
		var3 = 2;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 5)
	{
		var = 2;
		var2 = 1;
		var3 = 1;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 6)
	{
		var = 1;
		var2 = 1;
		var3 = 2;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 7)
	{
		var = 1;
		var2 = 2;
		var3 = 1;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 8)
	{
		var = 2;
		var2 = 1;
		var3 = 2;
	}
	initItem(S("bug"), 0.0f, S("meat"), nullptr, nullptr, 0, 0, true, var, var2, 1, var3, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("pest_note"), 0.0f, S("page_turn_03"), nullptr, nullptr, 0, 0, true, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("gas_note"), 0.0f, S("page_turn_03"), nullptr, nullptr, 0, 0, true, 0, 0, 0, 0, List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("gas_note")) }), 160, -60, 50, 62.0f / 255.0f, 58.0f / 255.0f, 28.0f / 255.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, false, nullptr, String::Empty);
	initItem(S("spider_note"), 0.0f, S("page_turn_03"), nullptr, nullptr, 0, 0, true, 0, 0, 0, 0, List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("spider_note")) }), 160, -60, 50, 62.0f / 255.0f, 58.0f / 255.0f, 28.0f / 255.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, false, nullptr, String::Empty);
	initItem(S("mixer_pills_note"), 0.0f, S("page_turn_03"), nullptr, nullptr, 0, 0, true, 0, 0, 0, 0, List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("mixer_pills")) }), 122, -115, -23, 62.0f / 255.0f, 58.0f / 255.0f, 28.0f / 255.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, false, nullptr, String::Empty);
	initItem(S("mixer_catalyst_note"), 0.0f, S("page_turn_03"), nullptr, nullptr, 0, 0, true, 0, 0, 0, 0, List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("mixer_catalyst")) }), 122, -115, -23, 62.0f / 255.0f, 58.0f / 255.0f, 28.0f / 255.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, false, nullptr, String::Empty);
	initItem(S("pest1"), 2.0f, S("small_can"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("pest2"), 2.0f, S("small_can"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("paperclip"), 0.0f, S("keypick01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("invoices"), 0.5f, S("page_turn_04"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("crowbar"), 1.5f, S("pickaxe01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("hammer"), 2.0f, S("wooden"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("nails1"), GameStrings::getString(GameStrings::actions, S("hammer_nails")), nullptr, String::Empty),
		New<ItemInteraction>(S("nails2"), GameStrings::getString(GameStrings::actions, S("hammer_nails")), nullptr, String::Empty),
		New<ItemInteraction>(S("nails3"), GameStrings::getString(GameStrings::actions, S("hammer_nails")), nullptr, String::Empty),
		New<ItemInteraction>(S("nails4"), GameStrings::getString(GameStrings::actions, S("hammer_nails")), nullptr, String::Empty),
		New<ItemInteraction>(S("nails5"), GameStrings::getString(GameStrings::actions, S("hammer_nails")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("broken_hammer"), 1.8f, S("wooden"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer_handle"), String::Empty, [this]() { hammer_fix(); }, String::Empty),
		New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("broken_hammer_pipe")), nullptr, String::Empty),
		New<ItemInteraction>(S("ducttape"), GameStrings::getString(GameStrings::actions, S("broken_hammer_tape")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("hammer_handle"), 0.2f, S("wooden"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("broken_hammer"), String::Empty, [this]() { hammer_fix(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("straw"), 0.0f, S("keypick01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("window_net1"), 4.0f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("window_net2"), 4.0f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("window_net3"), 4.0f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("window_bars1"), 9.0f, S("metal_bang"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("window_bars2"), 9.0f, S("metal_bang"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("window_bars3"), 9.0f, S("metal_bang"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("window_foil1"), 4.0f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("window_foil2"), 4.0f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("window_foil3"), 4.0f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("ducttape"), 0.1f, S("ducttape"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("chemsuit_dmg_dmg"), String::Empty, [this]() { chemsuit_fix1(); }, String::Empty),
		New<ItemInteraction>(S("chemsuit_dmg_rep"), String::Empty, [this]() { chemsuit_fix2(); }, String::Empty),
		New<ItemInteraction>(S("broken_hammer"), GameStrings::getString(GameStrings::actions, S("broken_hammer_tape")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("canister_empty"), 1.0f, S("jerrycan_empty"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("canister_full"), 10.0f, S("jerrycan_full"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("lighter"), GameStrings::getString(GameStrings::actions, S("dont_blow_up")), nullptr, String::Empty),
		New<ItemInteraction>(S("gasheater_empty"), GameStrings::getString(GameStrings::actions, S("gasheater_fuel")), nullptr, String::Empty),
		New<ItemInteraction>(S("flamethrower_empty"), String::Empty, [this]() { fuel_sprayer_use(); }, String::Empty),
		New<ItemInteraction>(S("watersprayer"), String::Empty, [this]() { fuel_sprayer_use(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("canister2_empty"), 1.0f, S("jerrycan_empty"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("canister2_full"), 10.0f, S("jerrycan_full"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("lighter"), GameStrings::getString(GameStrings::actions, S("dont_blow_up")), nullptr, String::Empty),
		New<ItemInteraction>(S("gasheater_empty"), GameStrings::getString(GameStrings::actions, S("gasheater_fuel")), nullptr, String::Empty),
		New<ItemInteraction>(S("flamethrower_empty"), String::Empty, [this]() { fuel_sprayer_use2(); }, String::Empty),
		New<ItemInteraction>(S("watersprayer"), String::Empty, [this]() { fuel_sprayer_use2(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("charcoal"), 10.0f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("charcoal_empty"), 0.1f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("nails1"), 0.1f, S("nails"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("hammer_nails")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("nails2"), 0.1f, S("nails"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("hammer_nails")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("nails3"), 0.1f, S("nails"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("hammer_nails")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("nails4"), 0.1f, S("nails"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("hammer_nails")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("nails5"), 0.1f, S("nails"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("board1"), 3.5f, S("logs"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("board2"), 3.5f, S("logs"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("board3"), 3.5f, S("logs"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("tarpaulin"), 4.0f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("planks1"), 2.5f, S("logs"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("planks2"), 2.5f, S("logs"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("planks3"), 2.5f, S("logs"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("planks4"), 2.5f, S("logs"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("planks5"), 2.5f, S("logs"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("ignitioncoil"), 0.2f, S("pickaxe01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("car_battery"), 0.2f, S("pickaxe01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("wheel"), 2.5f, S("pickaxe01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chem_glass"), 0.1f, S("glass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chem_glass_1"), 0.5f, S("glass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chem_glass_2"), 0.5f, S("glass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chem_glass_3"), 0.5f, S("glass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chem_glass_12"), 1.0f, S("glass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chem_glass_13"), 1.0f, S("glass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chem_glass_23"), 1.0f, S("glass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("mask_filter"), 0.1f, S("flashlight1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("chemsuit_dmg_dmg"), String::Empty, [this]() { chemsuit_filter1(); }, String::Empty),
		New<ItemInteraction>(S("chemsuit_rep_dmg"), String::Empty, [this]() { chemsuit_filter2(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	String text = str((float)GameDataController::gd->getObjectiveDetail(S("gas_dens")) / 100.0f);
	if ((double)((float)GameDataController::gd->getObjectiveDetail(S("gas_dens")) / 100.0f) == 1.6)
	{
		text += S("0");
	}
	initItem(S("drone"), 2.0f, S("metal_bang"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("drone_smash_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("drone_smash_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("screwdriver"), GameStrings::getString(GameStrings::actions, S("drone_smash_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("drone_smash_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("drone_smash_it")), nullptr, String::Empty)
	}), nullptr, 0, 0, true, 0, 0, 0, 0, List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("drone_1")) + GameDataController::gd->getObjectiveDetail(S("gas_ph")) + GameStrings::getString(GameStrings::world_labels, S("drone_2")) + text + GameStrings::getString(GameStrings::world_labels, S("drone_3")) }), 115, -18, 15, 75.0f / 255.0f, 81.0f / 255.0f, 70.0f / 255.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, nullptr, String::Empty);
	initItem(S("towel_1"), 0.2f, S("net"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("whiskey"), GameStrings::getString(GameStrings::actions, S("no_molotov")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("towel_2"), 0.2f, S("net"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("whiskey"), GameStrings::getString(GameStrings::actions, S("no_molotov")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("lighter"), 0.0f, S("flashlight1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("canister_full"), GameStrings::getString(GameStrings::actions, S("dont_blow_up")), nullptr, String::Empty),
		New<ItemInteraction>(S("canister2_full"), GameStrings::getString(GameStrings::actions, S("dont_blow_up")), nullptr, String::Empty),
		New<ItemInteraction>(S("watersprayer"), String::Empty, [this]() { lighter_sprayer_use(); }, String::Empty),
		New<ItemInteraction>(S("fuelsprayer"), String::Empty, [this]() { lighter_sprayer_use(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("wrench"), 1.0f, S("pickaxe01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("wad_of_cash"), 0.1f, S("page_turn_04"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("pestsprayer"), 10.0f, S("small_can"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("watersprayer"), 0.5f, S("flashlight1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("canister_full"), String::Empty, [this]() { fuel_sprayer_use(); }, String::Empty),
		New<ItemInteraction>(S("canister2_full"), String::Empty, [this]() { fuel_sprayer_use2(); }, String::Empty),
		New<ItemInteraction>(S("ducttape"), GameStrings::getString(GameStrings::actions, S("ducttape_watersprayer")), nullptr, String::Empty),
		New<ItemInteraction>(S("lighter"), String::Empty, [this]() { lighter_sprayer_use(); }, String::Empty),
		New<ItemInteraction>(S("pest1"), GameStrings::getString(GameStrings::actions, S("pest2_flamethrower")), nullptr, String::Empty),
		New<ItemInteraction>(S("pest2"), GameStrings::getString(GameStrings::actions, S("watersprayer_chem")), nullptr, String::Empty),
		New<ItemInteraction>(S("spiderpest1"), GameStrings::getString(GameStrings::actions, S("pest2_flamethrower")), nullptr, String::Empty),
		New<ItemInteraction>(S("spiderpest2"), GameStrings::getString(GameStrings::actions, S("pest2_flamethrower")), nullptr, String::Empty),
		New<ItemInteraction>(S("spiderpest3"), GameStrings::getString(GameStrings::actions, S("pest2_flamethrower")), nullptr, String::Empty),
		New<ItemInteraction>(S("spiderpest4"), GameStrings::getString(GameStrings::actions, S("pest2_flamethrower")), nullptr, String::Empty),
		New<ItemInteraction>(S("chem_glass_1"), GameStrings::getString(GameStrings::actions, S("watersprayer_chem")), nullptr, String::Empty),
		New<ItemInteraction>(S("chem_glass_2"), GameStrings::getString(GameStrings::actions, S("watersprayer_chem")), nullptr, String::Empty),
		New<ItemInteraction>(S("chem_glass_3"), GameStrings::getString(GameStrings::actions, S("watersprayer_chem")), nullptr, String::Empty),
		New<ItemInteraction>(S("chem_glass_12"), GameStrings::getString(GameStrings::actions, S("watersprayer_chem")), nullptr, String::Empty),
		New<ItemInteraction>(S("chem_glass_13"), GameStrings::getString(GameStrings::actions, S("watersprayer_chem")), nullptr, String::Empty),
		New<ItemInteraction>(S("chem_glass_23"), GameStrings::getString(GameStrings::actions, S("watersprayer_chem")), nullptr, String::Empty),
		New<ItemInteraction>(S("poision"), GameStrings::getString(GameStrings::actions, S("poision_watersprayer")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("fuelsprayer"), 5.0f, S("jerrycan_full"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("ducttape"), GameStrings::getString(GameStrings::actions, S("ducttape_watersprayer")), nullptr, String::Empty),
		New<ItemInteraction>(S("lighter"), String::Empty, [this]() { lighter_sprayer_use(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("flamethrower_empty"), 0.5f, S("flashlight1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("canister_full"), String::Empty, [this]() { fuel_sprayer_use(); }, String::Empty),
		New<ItemInteraction>(S("canister2_full"), String::Empty, [this]() { fuel_sprayer_use2(); }, String::Empty),
		New<ItemInteraction>(S("pest1"), GameStrings::getString(GameStrings::actions, S("pest_flamethrower")), nullptr, String::Empty),
		New<ItemInteraction>(S("pest2"), GameStrings::getString(GameStrings::actions, S("pest_flamethrower")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("flamethrower"), 5.0f, S("jerrycan_full"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chemsuit_dmg_dmg"), 4.0f, S("net"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("ducttape"), String::Empty, [this]() { chemsuit_fix1(); }, String::Empty),
		New<ItemInteraction>(S("mask_filter"), String::Empty, [this]() { chemsuit_filter1(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chemsuit_dmg_rep"), 4.0f, S("net"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("ducttape"), String::Empty, [this]() { chemsuit_fix2(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chemsuit_rep_dmg"), 4.0f, S("net"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("mask_filter"), String::Empty, [this]() { chemsuit_filter2(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("chemsuit_rep_rep"), 4.0f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_0"), 5.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_1"), 5.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_2"), 5.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_3"), 5.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_4"), 5.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_5"), 5.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_6"), 5.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_o_0"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_o_1"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_o_2"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_o_3"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_o_4"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_o_5"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_o_6"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("silencer"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_s_0"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_s_1"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_s_2"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_s_3"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_s_4"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_s_5"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_s_6"), 5.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("scope"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_so_0"), 6.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_so_1"), 6.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_so_2"), 6.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_so_3"), 6.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_so_4"), 6.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_so_5"), 6.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_so_6"), 6.0f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_ammo"), String::Empty, [this]() { reloadRifle(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("spiderpest1"), 0.5f, S("small_can"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("spiderpest2"), 0.5f, S("small_can"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("spiderpest3"), 0.5f, S("small_can"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("spiderpest4"), 0.5f, S("small_can"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("bear_trap_1"), 5.0f, S("trap"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("bear_trap_2"), 5.0f, S("trap"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("bear_trap_1b"), 50.0f, S("trap"), nullptr, List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), String::Empty, [this]() { resetSpring1(); }, String::Empty),
		New<ItemInteraction>(S("crowbar"), String::Empty, [this]() { resetSpring1(); }, String::Empty),
		New<ItemInteraction>(S("wrench"), String::Empty, [this]() { resetSpring1(); }, String::Empty)
	}), 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("bear_trap_2b"), 50.0f, S("trap"), nullptr, List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), String::Empty, [this]() { resetSpring2(); }, String::Empty),
		New<ItemInteraction>(S("crowbar"), String::Empty, [this]() { resetSpring2(); }, String::Empty),
		New<ItemInteraction>(S("wrench"), String::Empty, [this]() { resetSpring2(); }, String::Empty)
	}), 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("bear_trap_3"), 5.0f, S("trap"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("bear_trap_4"), 5.0f, S("trap"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("revolver_0"), 2.0f, S("revolver"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("gun_ammo"), String::Empty, [this]() { reloadGun(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("revolver_1"), 2.0f, S("revolver"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("gun_ammo"), String::Empty, [this]() { reloadGun(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("revolver_2"), 2.0f, S("revolver"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("gun_ammo"), String::Empty, [this]() { reloadGun(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("revolver_3"), 2.0f, S("revolver"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("gun_ammo"), String::Empty, [this]() { reloadGun(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("revolver_4"), 2.0f, S("revolver"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("gun_ammo"), String::Empty, [this]() { reloadGun(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("revolver_5"), 2.0f, S("revolver"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("gun_ammo"), String::Empty, [this]() { reloadGun(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("revolver_6"), 2.0f, S("revolver"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("gun_ammo"), GameStrings::getString(GameStrings::actions, S("revolver_full")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("gun_ammo"), 1.0f, S("nails"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("revolver_0"), String::Empty, [this]() { reloadGun(); }, String::Empty),
		New<ItemInteraction>(S("revolver_1"), String::Empty, [this]() { reloadGun(); }, String::Empty),
		New<ItemInteraction>(S("revolver_2"), String::Empty, [this]() { reloadGun(); }, String::Empty),
		New<ItemInteraction>(S("revolver_3"), String::Empty, [this]() { reloadGun(); }, String::Empty),
		New<ItemInteraction>(S("revolver_4"), String::Empty, [this]() { reloadGun(); }, String::Empty),
		New<ItemInteraction>(S("revolver_5"), String::Empty, [this]() { reloadGun(); }, String::Empty),
		New<ItemInteraction>(S("revolver_6"), String::Empty, [this]() { reloadGun(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rifle_ammo"), 1.0f, S("nails"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_1"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_0"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_1"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_2"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_3"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_4"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_5"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_6"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_0"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_1"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_2"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_3"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_4"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_5"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_6"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_0"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_1"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_2"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_3"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_4"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_5"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_6"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_so_0"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_so_1"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_so_2"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_so_3"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_so_4"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_so_5"), String::Empty, [this]() { reloadRifle(); }, String::Empty),
		New<ItemInteraction>(S("rifle_so_6"), String::Empty, [this]() { reloadRifle(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("scope"), 0.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_0"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_1"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_2"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_3"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_4"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_5"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_6"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_0"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_1"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_2"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_3"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_4"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_5"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty),
		New<ItemInteraction>(S("rifle_s_6"), String::Empty, [this]() { rifleInstallScope(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("silencer"), 0.5f, S("rifle_1"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rifle_0"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_1"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_2"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_3"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_4"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_5"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_6"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_0"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_1"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_2"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_3"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_4"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_5"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty),
		New<ItemInteraction>(S("rifle_o_6"), String::Empty, [this]() { rifleInstallSilencer(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("whiskey"), 2.5f, S("glass"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("bandage"), GameStrings::getString(GameStrings::actions, S("no_molotov")), nullptr, String::Empty),
		New<ItemInteraction>(S("towel_1"), GameStrings::getString(GameStrings::actions, S("no_molotov")), nullptr, String::Empty),
		New<ItemInteraction>(S("towel_2"), GameStrings::getString(GameStrings::actions, S("no_molotov")), nullptr, String::Empty),
		New<ItemInteraction>(S("poision"), GameStrings::getString(GameStrings::actions, S("poision_whiskey")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rock"), 1.0f, S("rockbutton"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rock2"), 1.0f, S("rockbutton"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("shovel"), 1.0f, S("pickaxe01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("sheet"), 0.0f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("coat1"), 0.3f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("coat2"), 0.3f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("coat3"), 0.3f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("coat4"), 0.3f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("hose"), 0.1f, S("hose"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("gas_tank"), 10.0f, S("jerrycan_full"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("gasheater_empty"), String::Empty, [this]() { put_tank_heater(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("foodcan"), 0.3f, S("small_can"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("knife"), String::Empty, [this]() { can_open_knife(); }, String::Empty),
		New<ItemInteraction>(S("screwdriver"), String::Empty, [this]() { can_open_screwdriver(); }, String::Empty),
		New<ItemInteraction>(S("canopener"), String::Empty, [this]() { can_open(); }, String::Empty),
		New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("foodcan_smash")), nullptr, String::Empty),
		New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("foodcan_smash")), nullptr, String::Empty),
		New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("foodcan_crowbar")), nullptr, String::Empty),
		New<ItemInteraction>(S("shovel"), GameStrings::getString(GameStrings::actions, S("foodcan_shovel")), nullptr, String::Empty),
		New<ItemInteraction>(S("key1"), GameStrings::getString(GameStrings::actions, S("foodcan_key")), nullptr, String::Empty),
		New<ItemInteraction>(S("key2"), GameStrings::getString(GameStrings::actions, S("foodcan_key")), nullptr, String::Empty),
		New<ItemInteraction>(S("key3"), GameStrings::getString(GameStrings::actions, S("foodcan_key")), nullptr, String::Empty),
		New<ItemInteraction>(S("key4"), GameStrings::getString(GameStrings::actions, S("foodcan_key")), nullptr, String::Empty),
		New<ItemInteraction>(S("rock"), GameStrings::getString(GameStrings::actions, S("foodcan_smash")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("foodcanopen"), 0.3f, S("meat"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("knife"), 0.1f, S("knife"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("blanketb"), GameStrings::getString(GameStrings::actions, S("knife_dont_cut_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("flag"), GameStrings::getString(GameStrings::actions, S("knife_dont_cut_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("blanket"), GameStrings::getString(GameStrings::actions, S("knife_dont_cut_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("thermalb"), GameStrings::getString(GameStrings::actions, S("knife_dont_cut_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("coat1"), GameStrings::getString(GameStrings::actions, S("knife_dont_cut_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("coat2"), GameStrings::getString(GameStrings::actions, S("knife_dont_cut_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("coat3"), GameStrings::getString(GameStrings::actions, S("knife_dont_cut_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("coat4"), GameStrings::getString(GameStrings::actions, S("knife_dont_cut_it")), nullptr, String::Empty),
		New<ItemInteraction>(S("foodcan"), String::Empty, [this]() { can_open_knife(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("canopener"), 0.1f, S("pickaxe01"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("screwdriver"), 0.1f, S("pickaxe01"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("foodcan"), String::Empty, [this]() { can_open_screwdriver(); }, String::Empty),
		New<ItemInteraction>(S("fan_broken"), String::Empty, [this]() { fan_fix1(); }, String::Empty),
		New<ItemInteraction>(S("heater_broken"), String::Empty, [this]() { heater_fix1(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("rope"), 2.0f, S("hose"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hook"), String::Empty, [this]() { rope_hook_use(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("ropehook"), 2.5f, S("hose"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("hook"), 0.5f, S("pickaxe01"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("rope"), String::Empty, [this]() { rope_hook_use(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("deadbird"), 0.1f, S("meat"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("flag"), 0.5f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("blanket"), 0.5f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("blanketb"), 0.5f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("thermalb"), 0.1f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("generator"), 7.0f, S("metal_bang"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("canister_full"), String::Empty, [this]() { fuel_generator(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("generator2"), 20.0f, S("metal_bang"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("locket"), 0.0f, S("necklace"), nullptr, nullptr, 0, 0, true, 1, 1, 1, 0, List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("barry_locket_1")),
		GameStrings::getString(GameStrings::world_labels, S("barry_locket_2")),
		GameStrings::getString(GameStrings::world_labels, S("barry_locket_3"))
	}), 120, -110, 40, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, true, [this]() { locketRead(); }, String::Empty);
	initItem(S("gasheater_empty"), 10.0f, S("metal_bang"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("canister_full"), GameStrings::getString(GameStrings::actions, S("gasheater_fuel")), nullptr, String::Empty),
		New<ItemInteraction>(S("canister2_full"), GameStrings::getString(GameStrings::actions, S("gasheater_fuel")), nullptr, String::Empty),
		New<ItemInteraction>(S("gas_tank"), String::Empty, [this]() { put_tank_heater(); }, String::Empty)
	}), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("gas_tank"), String::Empty, [this]() { put_tank_heater_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("canister_full"), GameStrings::getString(GameStrings::actions, S("gasheater_fuel")), nullptr, String::Empty),
		New<ItemInteraction>(S("canister2_full"), GameStrings::getString(GameStrings::actions, S("gasheater_fuel")), nullptr, String::Empty)
	}), 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("gasheater"), 20.0f, S("metal_bang"), nullptr, nullptr, 5, 5, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, S("heater1"));
	initItem(S("ext_cord"), 0.3f, S("hose"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("cord_plug_first")), nullptr, String::Empty),
		New<ItemInteraction>(S("fan"), GameStrings::getString(GameStrings::actions, S("cord_plug_first")), nullptr, String::Empty),
		New<ItemInteraction>(S("heater"), GameStrings::getString(GameStrings::actions, S("cord_plug_first")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("ext_cord_place"), -1.0f, S("hose"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("heater"), 2.5f, S("electric_item"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("ext_cord"), GameStrings::getString(GameStrings::actions, S("cord_plug_first")), nullptr, String::Empty),
		New<ItemInteraction>(S("screwdriver"), GameStrings::getString(GameStrings::actions, S("not_broken")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("fan"), 2.5f, S("electric_item"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("ext_cord"), GameStrings::getString(GameStrings::actions, S("cord_plug_first")), nullptr, String::Empty),
		New<ItemInteraction>(S("screwdriver"), GameStrings::getString(GameStrings::actions, S("not_broken")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("heater_broken"), 2.5f, S("electric_item_broken"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("screwdriver"), String::Empty, [this]() { heater_fix1(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("fan_broken"), 2.5f, S("electric_item_broken"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("screwdriver"), String::Empty, [this]() { fan_fix1(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("ac_cord"), -1.0f, S("hose"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("ac"), 10.0f, S("metal_bang"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("ext_cord"), GameStrings::getString(GameStrings::actions, S("cord_plug_first")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("heat_absorber1"), 0.5f, S("rock"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), String::Empty, [this]() { activate_absorber_1(); }, String::Empty),
		New<ItemInteraction>(S("crowbar"), String::Empty, [this]() { activate_absorber_1(); }, String::Empty),
		New<ItemInteraction>(S("pipe"), String::Empty, [this]() { activate_absorber_1(); }, String::Empty),
		New<ItemInteraction>(S("wrench"), String::Empty, [this]() { activate_absorber_1(); }, String::Empty),
		New<ItemInteraction>(S("rock"), String::Empty, [this]() { activate_absorber_1(); }, String::Empty)
	}), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), String::Empty, [this]() { activate_absorber_1_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("rock"), String::Empty, [this]() { activate_absorber_1_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("pipe"), String::Empty, [this]() { activate_absorber_1_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("wrench"), String::Empty, [this]() { activate_absorber_1_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("crowbar"), String::Empty, [this]() { activate_absorber_1_ground(); }, S("kneel_s"))
	}), 0, 0, true, 1, 1, 1, 9, List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("heater_inspect_1")),
		GameStrings::getString(GameStrings::world_labels, S("heater_inspect_2")),
		GameStrings::getString(GameStrings::world_labels, S("heater_inspect_3"))
	}), 130, -10, 40, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, true, nullptr, String::Empty);
	initItem(S("heat_absorber2"), 0.5f, S("rock"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), String::Empty, [this]() { activate_absorber_2(); }, String::Empty),
		New<ItemInteraction>(S("crowbar"), String::Empty, [this]() { activate_absorber_2(); }, String::Empty),
		New<ItemInteraction>(S("pipe"), String::Empty, [this]() { activate_absorber_2(); }, String::Empty),
		New<ItemInteraction>(S("wrench"), String::Empty, [this]() { activate_absorber_2(); }, String::Empty),
		New<ItemInteraction>(S("rock"), String::Empty, [this]() { activate_absorber_2(); }, String::Empty)
	}), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), String::Empty, [this]() { activate_absorber_2_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("rock"), String::Empty, [this]() { activate_absorber_2_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("pipe"), String::Empty, [this]() { activate_absorber_2_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("wrench"), String::Empty, [this]() { activate_absorber_2_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("crowbar"), String::Empty, [this]() { activate_absorber_2_ground(); }, S("kneel_s"))
	}), 0, 0, true, 1, 1, 1, 9, List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("heater_inspect_1")),
		GameStrings::getString(GameStrings::world_labels, S("heater_inspect_2")),
		GameStrings::getString(GameStrings::world_labels, S("heater_inspect_3"))
	}), 130, -10, 40, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, true, nullptr, String::Empty);
	initItem(S("heat_absorber3"), 0.5f, S("rock"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), String::Empty, [this]() { activate_absorber_3(); }, String::Empty),
		New<ItemInteraction>(S("crowbar"), String::Empty, [this]() { activate_absorber_3(); }, String::Empty),
		New<ItemInteraction>(S("pipe"), String::Empty, [this]() { activate_absorber_3(); }, String::Empty),
		New<ItemInteraction>(S("wrench"), String::Empty, [this]() { activate_absorber_3(); }, String::Empty),
		New<ItemInteraction>(S("rock"), String::Empty, [this]() { activate_absorber_3(); }, String::Empty)
	}), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), String::Empty, [this]() { activate_absorber_3_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("rock"), String::Empty, [this]() { activate_absorber_3_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("pipe"), String::Empty, [this]() { activate_absorber_3_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("wrench"), String::Empty, [this]() { activate_absorber_3_ground(); }, S("kneel_s")),
		New<ItemInteraction>(S("crowbar"), String::Empty, [this]() { activate_absorber_3_ground(); }, S("kneel_s"))
	}), 0, 0, true, 1, 1, 1, 9, List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("heater_inspect_1")),
		GameStrings::getString(GameStrings::world_labels, S("heater_inspect_2")),
		GameStrings::getString(GameStrings::world_labels, S("heater_inspect_3"))
	}), 130, -10, 40, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, true, nullptr, String::Empty);
	initItem(S("heat_absorber1A"), 0.5f, S("rock"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("heat_absorber2A"), 0.5f, S("rock"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("heat_absorber3A"), 0.5f, S("rock"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("water1"), 0.5f, S("waterbottle"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("water2"), 0.5f, S("waterbottle"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("water3"), 0.5f, S("waterbottle"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("water4"), 0.5f, S("waterbottle"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("sledgehammer"), 16.0f, S("metal_bang"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("sledge_head"), 15.0f, S("metal_bang"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("sledge_handle"), String::Empty, [this]() { sledgehammer_fix2(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("sledge_handle"), 1.0f, S("wooden"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("sledge_head"), String::Empty, [this]() { sledgehammer_fix1(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("maggot"), -1.0f, S("meat"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("oil"), 2.0f, S("waterbottle"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("poison"), 1.0f, S("glass"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("food_bag"), GameStrings::getString(GameStrings::actions, S("poision_food")), nullptr, String::Empty),
		New<ItemInteraction>(S("whiskey"), GameStrings::getString(GameStrings::actions, S("poision_whiskey")), nullptr, String::Empty),
		New<ItemInteraction>(S("watersprayer"), GameStrings::getString(GameStrings::actions, S("poision_watersprayer")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("food_bag"), 0.7f, S("net"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("poison"), GameStrings::getString(GameStrings::actions, S("poision_food")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("gloves"), 0.1f, S("net"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("welder"), 1.0f, S("metal_bang"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("mixer_glass"), -1.0f, S("glass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("pill_half"), -1.0f, S("hose"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("broom"), 1.0f, S("logs"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("stormcatcher1"), 1.0f, S("flashlight1"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("stormcatcher2"), 1.0f, S("flashlight1"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("stormcatcher3"), 1.0f, S("flashlight1"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("finger"), 0.0f, S("meat"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("catalyst"), 0.5f, S("glass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("pills"), 0.0f, S("hose"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("puzzle_cable"), 0.0f, S("hose"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("fire_hose"), -1.0f, S("hose"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("sidereal_id"), 0.0f, S("plastic"), nullptr, nullptr, 0, 0, true, 1, 1, 1, 0, List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("sidereal_id_1")) }), 120, -110, 40, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, true, nullptr, String::Empty);
	initItem(S("sidereal_secrets"), 0.0f, S("page_turn_04"), nullptr, nullptr, 0, 0, true, 1, 1, 1, 0, List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_1")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_2")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_3")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_4")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_5")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_6")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_7")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_8")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_9")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_10"))
	}), 150, -60, 50, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, true, nullptr, String::Empty);
	initItem(S("sidereal_docs"), 0.0f, S("page_turn_03"), nullptr, nullptr, 0, 0, true, 1, 1, 1, 0, List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("sidereal_docs_1")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_docs_2")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_docs_3")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_docs_4")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_docs_5")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_docs_6")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_docs_7")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_docs_8")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_docs_9")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_docs_10"))
	}), 120, -30, 50, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, true, nullptr, String::Empty);
	initItem(S("sidereal_id_key"), 0.0f, S("plastic"), nullptr, nullptr, 0, 0, true, 1, 1, 1, 0, List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("sidereal_id_1")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_id_2")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_id_3"))
	}), 120, -110, 40, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, true, [this]() { siderealIdExamined(); }, String::Empty, false);
	initItem(S("sidereal_xero"), 0.0f, S("page_turn_03"), nullptr, nullptr, 0, 0, true, 1, 1, 1, 1, List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("sidereal_xero_1")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_xero_2")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_xero_3")),
		GameStrings::getString(GameStrings::world_labels, S("sidereal_xero_4")) + S(" ^ ^ ")
	}), 150, -60, 50, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, true, [this]() { scary(); }, String::Empty, false);
	initItem(S("remote"), 0.0f, S("plastic"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("hammer"), String::Empty, [this]() { break_remote(); }, String::Empty),
		New<ItemInteraction>(S("screwdriver"), String::Empty, [this]() { open_remote(); }, String::Empty)
	}), nullptr, 0, 0, true, 1, 1, 0, 0, List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("remote_1")),
		GameStrings::getString(GameStrings::world_labels, S("remote_2"))
	}), 100, -110, 40, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, true, nullptr, String::Empty);
	initItem(S("outpost_card"), 0.0f, S("plastic"), nullptr, nullptr, 0, 0, true, 0, 0, 0, 0, nullptr, 100, -110, 40, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, true, nullptr, String::Empty);
	initItem(S("moon_card"), 0.0f, S("plastic"), nullptr, nullptr, 0, 0, true, 0, 0, 0, 0, nullptr, 100, -110, 40, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, true, nullptr, String::Empty);
	initItem(S("batteries"), 0.0f, S("nails"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("gluegun"), String::Empty, [this]() { power_gluegon(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("gluegun"), 0.0f, S("plastic"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("batteries"), String::Empty, [this]() { power_gluegon(); }, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("gluegun_powered"), 0.0f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("fingerprint"), 0.0f, S("meat"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("vials1"), 0.1f, S("tripleglass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("vials2"), 0.1f, S("tripleglass"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("engine_calibrator"), 2.5f, S("metal_bang"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("lioh_filter"), 2.5f, S("metal_bang"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("metal_slab"), 2.0f, S("metal_bang"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("nav_chip"), 0.1f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("air_tanks"), 8.0f, S("metal_bang"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("transmission_belt"), 0.2f, S("hose"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("duplexer"), 0.2f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("noodles"), 0.2f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("voltmeter"), 0.2f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("gasket"), 0.2f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("nuts_and_bolts"), 0.2f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("wires"), 0.2f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("wire"), 2.2f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("bandage"), 0.2f, S("net"), List<P<ItemInteraction>>::New({
		New<ItemInteraction>(S("whiskey"), GameStrings::getString(GameStrings::actions, S("no_molotov")), nullptr, String::Empty)
	}), nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("disc1"), 0.0f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("disc2"), 0.0f, S("plastic"), nullptr, nullptr, 0, 0, false, 0, 0, 0, 0, nullptr, 120, 0, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
	initItem(S("manifest"), 0.0f, S("page_turn_04"), nullptr, nullptr, 0, 0, true, 0, 0, 0, 0, List<String>::New({ S("...") }), 160, -50, 50, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, false, nullptr, String::Empty);
	initItem(S("cate_note"), 0.0f, S("page_turn_03"), nullptr, nullptr, 0, 0, true, 0, 0, 0, 0, List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("cate_last_words_1")),
		GameStrings::getString(GameStrings::world_labels, S("cate_last_words_2")),
		GameStrings::getString(GameStrings::world_labels, S("cate_last_words_3")),
		GameStrings::getString(GameStrings::world_labels, S("cate_last_words_4")),
		GameStrings::getString(GameStrings::world_labels, S("cate_last_words_5")),
		GameStrings::getString(GameStrings::world_labels, S("cate_last_words_6")),
		GameStrings::getString(GameStrings::world_labels, S("cate_last_words_7")),
		GameStrings::getString(GameStrings::world_labels, S("cate_last_words_8")),
		GameStrings::getString(GameStrings::world_labels, S("cate_last_words_9")),
		GameStrings::getString(GameStrings::world_labels, S("cate_last_words_10"))
	}), 133, -20, 55, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, nullptr, String::Empty);
}


void ItemsManager::scary()
{
}

void ItemsManager::power_gluegon()
{
	PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("gluegun_powered")));
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->necklace);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->small_powerup);
	combineItems(S("gluegun"), S("batteries"), S("gluegun_powered"));
}

void ItemsManager::combineItems(String item1, String item2, String result)
{
	String selectedItemName = CursorController::cc->selectedItemName;
	CursorController::cc->deselectItem();
	selectedItemName = ((!(selectedItemName == item1)) ? item1 : item2);
	int locX = im->getItem(selectedItemName)->dataRef->locX;
	int locY = im->getItem(selectedItemName)->dataRef->locY;
	String droppedLocation = im->getItem(selectedItemName)->dataRef->droppedLocation;
	InventoryController::ic->removeItem(item1);
	InventoryController::ic->removeItem(item2);
	im->updateItem(result, droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(result));
	putAwayOrDropIfTheResultIsTooHeavy(result);
}

void ItemsManager::resetSpring1()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("reset_trap")), QuestionController::PopupType::QUESTION, [this]() { resetSpring1b(); }, 30, 6);
}

void ItemsManager::open_remote()
{
	PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("remote_open")));
	InventoryController::ic->removeItem(S("remote"));
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->screw);
	InventoryController::ic->pickOrDropItem(im->getItem(S("batteries")));
}

void ItemsManager::break_remote()
{
	PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("remote_break")));
	InventoryController::ic->removeItem(S("remote"));
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->generic_hit);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->wood_snap);
	InventoryController::ic->pickOrDropItem(im->getItem(S("batteries")));
}

void ItemsManager::resetSpring2()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("reset_trap")), QuestionController::PopupType::QUESTION, [this]() { resetSpring2b(); }, 30, 6);
}

void ItemsManager::resetSpring1b()
{
	getItem(S("bear_trap_1"))->dataRef->droppedLocation = getItem(S("bear_trap_1b"))->dataRef->droppedLocation;
	getItem(S("bear_trap_1"))->dataRef->locX = getItem(S("bear_trap_1b"))->dataRef->locX;
	getItem(S("bear_trap_1"))->dataRef->locY = getItem(S("bear_trap_1b"))->dataRef->locY;
	getItem(S("bear_trap_1b"))->dataRef->droppedLocation = S("nowhere");
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, nullptr, SoundsManagerController::sm->screw, false, [this]() { resetSpring1c(); });
}

void ItemsManager::resetSpring1c()
{
	removeGroundItem(S("bear_trap_1b"));
	Vector2 vector = ScreenControler::gameToScreen(Vector2((float)getItem(S("bear_trap_1b"))->dataRef->locX, (float)(getItem(S("bear_trap_1b"))->dataRef->locY + GroundItemController::yOffset)));
	Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
	vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
	P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion()).as<GameObject>();
	gameObject->GetComponent<GroundItemController>()->init(im->getItem(S("bear_trap_1")));
}

void ItemsManager::resetSpring2b()
{
	getItem(S("bear_trap_2"))->dataRef->droppedLocation = getItem(S("bear_trap_2b"))->dataRef->droppedLocation;
	getItem(S("bear_trap_2"))->dataRef->locX = getItem(S("bear_trap_2b"))->dataRef->locX;
	getItem(S("bear_trap_2"))->dataRef->locY = getItem(S("bear_trap_2b"))->dataRef->locY;
	getItem(S("bear_trap_2b"))->dataRef->droppedLocation = S("nowhere");
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, nullptr, SoundsManagerController::sm->screw, false, [this]() { resetSpring2c(); });
}

void ItemsManager::resetSpring2c()
{
	removeGroundItem(S("bear_trap_2b"));
	Vector2 vector = ScreenControler::gameToScreen(Vector2((float)getItem(S("bear_trap_2b"))->dataRef->locX, (float)(getItem(S("bear_trap_2b"))->dataRef->locY + GroundItemController::yOffset)));
	Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
	vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
	P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion()).as<GameObject>();
	gameObject->GetComponent<GroundItemController>()->init(im->getItem(S("bear_trap_2")));
}

void ItemsManager::rifleInstallScope()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("install_scope")), QuestionController::PopupType::QUESTION, [this]() { rifleInstallScope2(); }, 60);
}

void ItemsManager::rifleInstallScope2()
{
	InventoryButtonController::ibc->close();
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, nullptr, SoundsManagerController::sm->repair);
	String text = String::Empty;
	String theThing = String::Empty;
	for (int i = 0; i <= 1; i++)
	{
		if (i == 0)
		{
			text = String::Empty;
		}
		if (i == 1)
		{
			text = S("s_");
		}
		for (int j = 0; j <= 6; j++)
		{
			String item = S("rifle_") + text + j;
			if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(item))
			{
				int locX = im->getItem(item)->dataRef->locX;
				int locY = im->getItem(item)->dataRef->locY;
				String droppedLocation = im->getItem(item)->dataRef->droppedLocation;
				InventoryController::ic->removeItem(item);
				if (text == String::Empty)
				{
					text = S("o_");
				}
				else if (text == S("s_"))
				{
					text = S("so_");
				}
				im->updateItem(S("rifle_") + text + j, droppedLocation, locX, locY);
				InventoryController::ic->loadItem(im->getItem(S("rifle_") + text + j));
				theThing = S("rifle_") + text + j;
				PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->revolver);
			}
		}
	}
	InventoryController::ic->removeItem(S("scope"));
	putAwayOrDropIfTheResultIsTooHeavy(theThing);
}

void ItemsManager::putAwayOrDropIfTheResultIsTooHeavy(String theThing)
{
	if (!(InventoryController::ic->getCurrentWeight() > (float)InventoryController::ic->maxCapacity))
	{
		return;
	}
	bool flag = false;
	if (InventoryController::ic->trunk->get_activeSelf())
	{
		flag = InventoryController::ic->putItemInTrunk(theThing, true);
	}
	if (!flag && InventoryController::ic->chest->get_activeSelf())
	{
		flag = InventoryController::ic->putItemInChest(theThing, true);
	}
	if (!flag)
	{
		InventoryController::ic->dropItem(im->getItem(theThing), true);
		if (InventoryController::ic->trunk->get_activeSelf())
		{
			PlayerController::pc->sayLine(GameStrings::getString(GameStrings::gui, S("capacity_full2")));
		}
		else if (InventoryController::ic->chest->get_activeSelf())
		{
			PlayerController::pc->sayLine(GameStrings::getString(GameStrings::gui, S("capacity_full3")));
		}
		else
		{
			PlayerController::pc->sayLine(GameStrings::getString(GameStrings::gui, S("capacity_full1")));
		}
	}
}

void ItemsManager::rifleInstallSilencer()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("install_silencer")), QuestionController::PopupType::QUESTION, [this]() { rifleInstallSilencer2(); }, 60);
}

void ItemsManager::rifleInstallSilencer2()
{
	InventoryButtonController::ibc->close();
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, nullptr, SoundsManagerController::sm->repair);
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	String text = String::Empty;
	String theThing = String::Empty;
	for (int i = 0; i <= 1; i++)
	{
		if (i == 0)
		{
			text = String::Empty;
		}
		if (i == 1)
		{
			text = S("o_");
		}
		for (int j = 0; j <= 6; j++)
		{
			String item = S("rifle_") + text + j;
			if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(item))
			{
				int locX = im->getItem(item)->dataRef->locX;
				int locY = im->getItem(item)->dataRef->locY;
				String droppedLocation = im->getItem(item)->dataRef->droppedLocation;
				InventoryController::ic->removeItem(item);
				if (text == String::Empty)
				{
					text = S("s_");
				}
				else if (text == S("o_"))
				{
					text = S("so_");
				}
				im->updateItem(S("rifle_") + text + j, droppedLocation, locX, locY);
				InventoryController::ic->loadItem(im->getItem(S("rifle_") + text + j));
				theThing = S("rifle_") + text + j;
				PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->revolver);
			}
		}
	}
	InventoryController::ic->removeItem(S("silencer"));
	putAwayOrDropIfTheResultIsTooHeavy(theThing);
}

void ItemsManager::siderealIdExamined()
{
	InventoryController::ic->removeItem(S("sidereal_id_key"));
	InventoryController::ic->pickOrDropItem(im->getItem(S("key1")));
	InventoryController::ic->pickOrDropItem(im->getItem(S("sidereal_id")));
}

void ItemsManager::activate_absorber(String subject)
{
	CursorController::cc->deselectItem();
	int locX = im->getItem(subject)->dataRef->locX;
	int locY = im->getItem(subject)->dataRef->locY;
	String droppedLocation = im->getItem(subject)->dataRef->droppedLocation;
	InventoryController::ic->removeItem(subject);
	im->updateItem(subject + S("A"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(subject + S("A")));
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->heater_hiss);
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("heat_absorber_activated")));
}

void ItemsManager::activate_absorber_ground(String subject)
{
	CursorController::cc->deselectItem();
	im->updateItem(subject, S("nowhere"), 0, 0);
	removeGroundItem(subject);
	Vector2 vector = ScreenControler::gameToScreen(Vector2(PlayerController::wc->currentXY.x, PlayerController::wc->currentXY.y + (float)GroundItemController::yOffset));
	Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
	vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->heater_hiss);
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("heat_absorber_activated")));
	P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion()).as<GameObject>();
	gameObject->GetComponent<GroundItemController>()->init(im->getItem(subject + S("A")));
	im->getItem(subject + S("A"))->dataRef->locX = (int)PlayerController::wc->currentXY.x;
	im->getItem(subject + S("A"))->dataRef->locY = (int)PlayerController::wc->currentXY.y;
	im->getItem(subject + S("A"))->dataRef->droppedLocation = SceneManager::GetActiveScene().get_name();
}

void ItemsManager::activate_absorber_1()
{
	activate_absorber(S("heat_absorber1"));
}

void ItemsManager::activate_absorber_1_ground()
{
	activate_absorber_ground(S("heat_absorber1"));
}

void ItemsManager::activate_absorber_2()
{
	activate_absorber(S("heat_absorber2"));
}

void ItemsManager::activate_absorber_2_ground()
{
	activate_absorber_ground(S("heat_absorber2"));
}

void ItemsManager::activate_absorber_3()
{
	activate_absorber(S("heat_absorber3"));
}

void ItemsManager::activate_absorber_3_ground()
{
	activate_absorber_ground(S("heat_absorber3"));
}

void ItemsManager::put_tank_heater()
{
	String selectedItemName = CursorController::cc->selectedItemName;
	CursorController::cc->deselectItem();
	selectedItemName = ((!(selectedItemName == S("gasheater_empty"))) ? S("gasheater_empty") : S("gas_tank"));
	int locX = im->getItem(selectedItemName)->dataRef->locX;
	int locY = im->getItem(selectedItemName)->dataRef->locY;
	String droppedLocation = im->getItem(selectedItemName)->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("gas_tank"));
	InventoryController::ic->removeItem(S("gasheater_empty"));
	im->updateItem(S("gasheater"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("gasheater")));
	PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("gasheater")));
	putAwayOrDropIfTheResultIsTooHeavy(S("gasheater"));
}

void ItemsManager::put_tank_heater_ground()
{
	String text = S("gas_tank");
	CursorController::cc->deselectItem();
	int locX = im->getItem(text)->dataRef->locX;
	int locY = im->getItem(text)->dataRef->locY;
	InventoryController::ic->removeItem(S("gas_tank"));
	im->updateItem(S("gasheater_empty"), S("nowhere"), 0, 0);
	removeGroundItem(S("gasheater_empty"));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(PlayerController::wc->currentXY.x, PlayerController::wc->currentXY.y + (float)GroundItemController::yOffset));
	Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
	vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hose);
	P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion()).as<GameObject>();
	gameObject->GetComponent<GroundItemController>()->init(im->getItem(S("gasheater")));
	im->getItem(S("gasheater"))->dataRef->locX = (int)PlayerController::wc->currentXY.x;
	im->getItem(S("gasheater"))->dataRef->locY = (int)PlayerController::wc->currentXY.y;
	im->getItem(S("gasheater"))->dataRef->droppedLocation = SceneManager::GetActiveScene().get_name();
}

void ItemsManager::locketRead()
{
	GameDataController::gd->setObjective(S("house_b_wife_note_read"), true);
}

void ItemsManager::rope_hook_use()
{
	String selectedItemName = CursorController::cc->selectedItemName;
	CursorController::cc->deselectItem();
	selectedItemName = ((!(selectedItemName == S("rope"))) ? S("rope") : S("hook"));
	int locX = im->getItem(selectedItemName)->dataRef->locX;
	int locY = im->getItem(selectedItemName)->dataRef->locY;
	String droppedLocation = im->getItem(selectedItemName)->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("rope"));
	InventoryController::ic->removeItem(S("hook"));
	im->updateItem(S("ropehook"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("ropehook")));
	PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("ropehook")));
	putAwayOrDropIfTheResultIsTooHeavy(S("ropehook"));
}

void ItemsManager::sonic_remote_use()
{
	PlayerController::wc->fullStop(true);
	PlayerController::pc->spawnName = S("InfoExit");
	GameDataController::gd->previousLocation = SceneManager::GetActiveScene().get_name();
	GameDataController::gd->previousX = (int)PlayerController::wc->currentXY.x;
	GameDataController::gd->previousY = (int)PlayerController::wc->currentXY.y;
	CurtainController::cc->fadeOut(S("SonicRemote"), WalkController::Direction::S_);
	PlayerController::wc->fullStop();
}

void ItemsManager::sledgehammer_fix1()
{
	sledgehammer_fix3(S("sledge_handle"));
}

void ItemsManager::sledgehammer_fix2()
{
	sledgehammer_fix3(S("sledge_head"));
}

void ItemsManager::sledgehammer_fix3(String it2)
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	int locX = im->getItem(it2)->dataRef->locX;
	int locY = im->getItem(it2)->dataRef->locY;
	InventoryController::ic->removeItem(S("sledge_head"));
	InventoryController::ic->removeItem(S("sledge_handle"));
	im->updateItem(S("sledgehammer"), S("inventory"), locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("sledgehammer")));
}

void ItemsManager::fan_fix1()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("fan_fix")), QuestionController::PopupType::QUESTION, [this]() { fan_fix2(); }, 90, 10);
}

void ItemsManager::fan_fix2()
{
	int locX = im->getItem(S("fan_broken"))->dataRef->locX;
	int locY = im->getItem(S("fan_broken"))->dataRef->locY;
	String droppedLocation = im->getItem(S("fan_broken"))->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("fan_broken"));
	im->updateItem(S("fan"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("fan")));
	InventoryButtonController::ibc->close();
	PlayerController::pc->setBusy(true);
	CurtainController::cc->fadeOut();
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->repair);
	putAwayOrDropIfTheResultIsTooHeavy(S("fan"));
}

void ItemsManager::heater_fix1()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("heater_fix")), QuestionController::PopupType::QUESTION, [this]() { heater_fix2(); }, 90, 10);
}

void ItemsManager::heater_fix2()
{
	int locX = im->getItem(S("heater_broken"))->dataRef->locX;
	int locY = im->getItem(S("heater_broken"))->dataRef->locY;
	String droppedLocation = im->getItem(S("heater_broken"))->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("heater_broken"));
	im->updateItem(S("heater"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("heater")));
	InventoryButtonController::ibc->close();
	PlayerController::pc->setBusy(true);
	CurtainController::cc->fadeOut();
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->repair);
	putAwayOrDropIfTheResultIsTooHeavy(S("heater"));
}

void ItemsManager::hammer_fix()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	int locX = im->getItem(S("broken_hammer"))->dataRef->locX;
	int locY = im->getItem(S("broken_hammer"))->dataRef->locY;
	String droppedLocation = im->getItem(S("broken_hammer"))->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("broken_hammer"));
	InventoryController::ic->removeItem(S("hammer_handle"));
	im->updateItem(S("hammer"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("hammer")));
	putAwayOrDropIfTheResultIsTooHeavy(S("hammer"));
}

void ItemsManager::can_open()
{
	InventoryButtonController::ibc->close();
	int locX = im->getItem(S("foodcan"))->dataRef->locX;
	int locY = im->getItem(S("foodcan"))->dataRef->locY;
	String droppedLocation = im->getItem(S("foodcan"))->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("foodcan"));
	im->updateItem(S("foodcanopen"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("foodcanopen")));
	String txt = GameStrings::getString(GameStrings::actions, S("foodcan_open"));
	PlayerController::pc->sayLine(txt);
	putAwayOrDropIfTheResultIsTooHeavy(S("foodcanopen"));
}

void ItemsManager::reloadGun()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	for (int i = 0; i < 6; i++)
	{
		if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("revolver_") + i))
		{
			int locX = im->getItem(S("revolver_") + i)->dataRef->locX;
			int locY = im->getItem(S("revolver_") + i)->dataRef->locY;
			String droppedLocation = im->getItem(S("revolver_") + i)->dataRef->droppedLocation;
			InventoryController::ic->removeItem(S("revolver_") + i);
			im->updateItem(S("revolver_6"), droppedLocation, locX, locY);
			InventoryController::ic->loadItem(im->getItem(S("revolver_6")));
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->revolver);
		}
	}
}

void ItemsManager::reloadRifle()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	String text = String::Empty;
	for (int i = 0; i <= 3; i++)
	{
		if (i == 0)
		{
			text = String::Empty;
		}
		if (i == 1)
		{
			text = S("s_");
		}
		if (i == 2)
		{
			text = S("o_");
		}
		if (i == 3)
		{
			text = S("so_");
		}
		for (int j = 0; j < 6; j++)
		{
			String item = S("rifle_") + text + j;
			if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(item))
			{
				int locX = im->getItem(item)->dataRef->locX;
				int locY = im->getItem(item)->dataRef->locY;
				String droppedLocation = im->getItem(item)->dataRef->droppedLocation;
				InventoryController::ic->removeItem(item);
				im->updateItem(S("rifle_") + text + S("6"), droppedLocation, locX, locY);
				InventoryController::ic->loadItem(im->getItem(S("rifle_") + text + S("6")));
				PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->revolver);
			}
		}
	}
}

void ItemsManager::can_open_knife()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("can_open_knife")), QuestionController::PopupType::QUESTION, [this]() { can_open(); }, 5);
}

void ItemsManager::can_open_screwdriver()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("can_open_screwdriver")), QuestionController::PopupType::QUESTION, [this]() { can_open(); }, 10);
}

void ItemsManager::chemsuit_fix1()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	int locX = im->getItem(S("chemsuit_dmg_dmg"))->dataRef->locX;
	int locY = im->getItem(S("chemsuit_dmg_dmg"))->dataRef->locY;
	String droppedLocation = im->getItem(S("chemsuit_dmg_dmg"))->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("chemsuit_dmg_dmg"));
	im->updateItem(S("chemsuit_rep_dmg"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("chemsuit_rep_dmg")));
	String txt = GameStrings::getString(GameStrings::actions, S("chemsuit_ducttape"));
	PlayerController::pc->sayLine(txt);
	putAwayOrDropIfTheResultIsTooHeavy(S("chemsuit_rep_dmg"));
}

void ItemsManager::chemsuit_fix2()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	int locX = im->getItem(S("chemsuit_dmg_rep"))->dataRef->locX;
	int locY = im->getItem(S("chemsuit_dmg_rep"))->dataRef->locY;
	String droppedLocation = im->getItem(S("chemsuit_dmg_rep"))->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("chemsuit_dmg_rep"));
	im->updateItem(S("chemsuit_rep_rep"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("chemsuit_rep_rep")));
	String txt = GameStrings::getString(GameStrings::actions, S("chemsuit_ducttape"));
	PlayerController::pc->sayLine(txt);
	putAwayOrDropIfTheResultIsTooHeavy(S("chemsuit_rep_rep"));
}

void ItemsManager::chemsuit_filter1()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	int locX = im->getItem(S("chemsuit_dmg_dmg"))->dataRef->locX;
	int locY = im->getItem(S("chemsuit_dmg_dmg"))->dataRef->locY;
	String droppedLocation = im->getItem(S("chemsuit_dmg_dmg"))->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("chemsuit_dmg_dmg"));
	InventoryController::ic->removeItem(S("mask_filter"));
	im->updateItem(S("chemsuit_dmg_rep"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("chemsuit_dmg_rep")));
	String txt = GameStrings::getString(GameStrings::actions, S("chemsuit_filter"));
	PlayerController::pc->sayLine(txt);
	putAwayOrDropIfTheResultIsTooHeavy(S("chemsuit_dmg_rep"));
}

void ItemsManager::chemsuit_filter2()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	int locX = im->getItem(S("chemsuit_rep_dmg"))->dataRef->locX;
	int locY = im->getItem(S("chemsuit_dmg_dmg"))->dataRef->locY;
	String droppedLocation = im->getItem(S("chemsuit_rep_dmg"))->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("chemsuit_rep_dmg"));
	InventoryController::ic->removeItem(S("mask_filter"));
	im->updateItem(S("chemsuit_rep_rep"), droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("chemsuit_rep_rep")));
	String txt = GameStrings::getString(GameStrings::actions, S("chemsuit_filter"));
	PlayerController::pc->sayLine(txt);
	putAwayOrDropIfTheResultIsTooHeavy(S("chemsuit_rep_rep"));
}

void ItemsManager::fuel_generator()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	String text = S("generator");
	int locX = im->getItem(text)->dataRef->locX;
	int locY = im->getItem(text)->dataRef->locY;
	int locX2 = im->getItem(S("canister_full"))->dataRef->locX;
	int locY2 = im->getItem(S("canister_full"))->dataRef->locY;
	InventoryController::ic->removeItem(S("canister_full"));
	InventoryController::ic->removeItem(text);
	im->updateItem(S("canister_empty"), S("inventory"), locX2, locY2);
	InventoryController::ic->loadItem(im->getItem(S("canister_empty")));
	String text2 = GameStrings::getString(GameStrings::actions, S("fuel_generator"));
	im->updateItem(S("generator2"), S("inventory"), locX, locY);
	InventoryController::ic->loadItem(im->getItem(S("generator2")));
	PlayerController::pc->textField->viewText(text2, true);
}

void ItemsManager::fuel_sprayer_use()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	String text = ((!(im->getItem(S("watersprayer"))->dataRef->droppedLocation == S("inventory")) && !(im->getItem(S("watersprayer"))->dataRef->droppedLocation == S("chest")) && !(im->getItem(S("watersprayer"))->dataRef->droppedLocation == S("trunk"))) ? S("flamethrower_empty") : S("watersprayer"));
	int locX = im->getItem(text)->dataRef->locX;
	int locY = im->getItem(text)->dataRef->locY;
	String droppedLocation = im->getItem(text)->dataRef->droppedLocation;
	String droppedLocation2 = im->getItem(S("canister_full"))->dataRef->droppedLocation;
	int locX2 = im->getItem(S("canister_full"))->dataRef->locX;
	int locY2 = im->getItem(S("canister_full"))->dataRef->locY;
	InventoryController::ic->removeItem(S("canister_full"));
	InventoryController::ic->removeItem(text);
	im->updateItem(S("canister_empty"), droppedLocation2, locX2, locY2);
	InventoryController::ic->loadItem(im->getItem(S("canister_empty")));
	String text2 = GameStrings::getString(GameStrings::actions, S("fuel_watersprayer"));
	if (text == S("watersprayer"))
	{
		im->updateItem(S("fuelsprayer"), droppedLocation, locX, locY);
		InventoryController::ic->loadItem(im->getItem(S("fuelsprayer")));
		PlayerController::pc->sayLine(text2);
		putAwayOrDropIfTheResultIsTooHeavy(S("fuelsprayer"));
	}
	else
	{
		text2 += GameStrings::getString(GameStrings::actions, S("flamethrower_ready"));
		im->updateItem(S("flamethrower"), droppedLocation, locX, locY);
		InventoryController::ic->loadItem(im->getItem(S("flamethrower")));
		PlayerController::pc->sayLine(text2);
		GameDataController::Achievement(S("S_PYRO"));
		putAwayOrDropIfTheResultIsTooHeavy(S("flamethrower"));
	}
}

void ItemsManager::fuel_sprayer_use2()
{
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	String text = ((!(im->getItem(S("watersprayer"))->dataRef->droppedLocation == S("inventory")) && !(im->getItem(S("watersprayer"))->dataRef->droppedLocation == S("chest")) && !(im->getItem(S("watersprayer"))->dataRef->droppedLocation == S("trunk"))) ? S("flamethrower_empty") : S("watersprayer"));
	int locX = im->getItem(text)->dataRef->locX;
	int locY = im->getItem(text)->dataRef->locY;
	String droppedLocation = im->getItem(text)->dataRef->droppedLocation;
	int locX2 = im->getItem(S("canister2_full"))->dataRef->locX;
	int locY2 = im->getItem(S("canister2_full"))->dataRef->locY;
	String droppedLocation2 = im->getItem(S("canister2_full"))->dataRef->droppedLocation;
	InventoryController::ic->removeItem(S("canister2_full"));
	InventoryController::ic->removeItem(text);
	im->updateItem(S("canister2_empty"), droppedLocation2, locX2, locY2);
	InventoryController::ic->loadItem(im->getItem(S("canister2_empty")));
	String text2 = GameStrings::getString(GameStrings::actions, S("fuel_watersprayer"));
	if (text == S("watersprayer"))
	{
		im->updateItem(S("fuelsprayer"), droppedLocation, locX, locY);
		InventoryController::ic->loadItem(im->getItem(S("fuelsprayer")));
		PlayerController::pc->sayLine(text2);
		putAwayOrDropIfTheResultIsTooHeavy(S("fuelsprayer"));
	}
	else
	{
		text2 += GameStrings::getString(GameStrings::actions, S("flamethrower_ready"));
		im->updateItem(S("flamethrower"), droppedLocation, locX, locY);
		InventoryController::ic->loadItem(im->getItem(S("flamethrower")));
		GameDataController::Achievement(S("S_PYRO"));
		PlayerController::pc->sayLine(text2);
		putAwayOrDropIfTheResultIsTooHeavy(S("flamethrower"));
	}
}

void ItemsManager::lighter_sprayer_use()
{
	if ((im->getItem(S("ducttape"))->dataRef->droppedLocation != S("inventory") && !InventoryController::ic->trunk->get_activeSelf() && !InventoryController::ic->chest->get_activeSelf()) || (im->getItem(S("ducttape"))->dataRef->droppedLocation != S("inventory") && InventoryController::ic->trunk->get_activeSelf() && !InventoryController::ic->chest->get_activeSelf() && im->getItem(S("ducttape"))->dataRef->droppedLocation != S("trunk")) || (im->getItem(S("ducttape"))->dataRef->droppedLocation != S("inventory") && !InventoryController::ic->trunk->get_activeSelf() && InventoryController::ic->chest->get_activeSelf() && im->getItem(S("ducttape"))->dataRef->droppedLocation != S("chest")))
	{
		PlayerController::wc->fullStop(true);
		CursorController::cc->deselectItem();
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("no_ducttape_watersprayer")), true);
		return;
	}
	String text = ((!(im->getItem(S("watersprayer"))->dataRef->droppedLocation == S("inventory")) && !(im->getItem(S("watersprayer"))->dataRef->droppedLocation == S("chest")) && !(im->getItem(S("watersprayer"))->dataRef->droppedLocation == S("trunk"))) ? S("fuelsprayer") : S("watersprayer"));
	PlayerController::wc->fullStop(true);
	CursorController::cc->deselectItem();
	int locX = im->getItem(text)->dataRef->locX;
	int locY = im->getItem(text)->dataRef->locY;
	String droppedLocation = im->getItem(text)->dataRef->droppedLocation;
	InventoryController::ic->removeItem(text);
	InventoryController::ic->removeItem(S("lighter"));
	String text2 = GameStrings::getString(GameStrings::actions, S("lighter_watersprayer"));
	if (text == S("watersprayer"))
	{
		im->updateItem(S("flamethrower_empty"), droppedLocation, locX, locY);
		InventoryController::ic->loadItem(im->getItem(S("flamethrower_empty")));
		PlayerController::pc->sayLine(text2);
		putAwayOrDropIfTheResultIsTooHeavy(S("flamethrower_empty"));
	}
	else
	{
		text2 += GameStrings::getString(GameStrings::actions, S("flamethrower_ready"));
		im->updateItem(S("flamethrower"), droppedLocation, locX, locY);
		InventoryController::ic->loadItem(im->getItem(S("flamethrower")));
		GameDataController::Achievement(S("S_PYRO"));
		PlayerController::pc->sayLine(text2);
		putAwayOrDropIfTheResultIsTooHeavy(S("flamethrower"));
	}
}

void ItemsManager::revolverShot(String gunName)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rifle_shoot);
	int num = 0;
	String text = S("revolver_");
	num = int_Parse(gunName.Substring(text.Length()));
	num--;
	int locX = im->getItem(gunName)->dataRef->locX;
	int locY = im->getItem(gunName)->dataRef->locY;
	String droppedLocation = im->getItem(gunName)->dataRef->droppedLocation;
	InventoryController::ic->removeItem(gunName);
	im->updateItem(text + num, droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(text + num));
}

void ItemsManager::rifleShot(String gunName, bool boom)
{
	if (boom)
	{
		if (gunName.IndexOf(S("rifle_s")) != -1)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rifle_shoot_silenced);
		}
		else
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rifle_shoot);
		}
	}
	int num = 0;
	String text = S("rifle_");
	if (gunName.IndexOf(S("rifle_so_")) != -1)
	{
		text = S("rifle_so_");
	}
	else if (gunName.IndexOf(S("rifle_o_")) != -1)
	{
		text = S("rifle_o_");
	}
	else if (gunName.IndexOf(S("rifle_s_")) != -1)
	{
		text = S("rifle_s_");
	}
	else if (gunName.IndexOf(S("rifle_")) != -1)
	{
		text = S("rifle_");
	}
	num = int_Parse(gunName.Substring(text.Length()));
	num--;
	int locX = im->getItem(gunName)->dataRef->locX;
	int locY = im->getItem(gunName)->dataRef->locY;
	String droppedLocation = im->getItem(gunName)->dataRef->droppedLocation;
	InventoryController::ic->removeItem(gunName);
	im->updateItem(text + num, droppedLocation, locX, locY);
	InventoryController::ic->loadItem(im->getItem(text + num));
}

void ItemsManager::OnEnable()
{
}

void ItemsManager::removeGroundItem(String itemName)
{
	Array<P<GroundItemController>> array = Object::FindObjectsOfType<GroundItemController>();
	for (int i = 0; i < array.Length(); i++)
	{
		if (array[i]->GetComponent<GroundItemController>()->itemRef->id == itemName)
		{
			Object::Destroy(array[i]->gameObject);
		}
	}
}

void ItemsManager::initGroundAndInv()
{
	Array<P<GroundItemController>> array = Object::FindObjectsOfType<GroundItemController>();
	for (int i = 0; i < array.Length(); i++)
	{
		Object::Destroy(array[i]->gameObject);
	}
	for (int j = 0; j < items.Count(); j++)
	{
		if (items[j]->dataRef->droppedLocation.Equals(SceneManager::GetActiveScene().get_name()))
		{
			Vector2 vector = ScreenControler::gameToScreen(Vector2((float)items[j]->dataRef->locX, (float)(items[j]->dataRef->locY + GroundItemController::yOffset)));
			Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
			vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
			MonoBehaviour::print(S("CREATING A GROUND ITEM ") + items[j]->id + S(" i=") + j);
			P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion()).as<GameObject>();
			gameObject->GetComponent<GroundItemController>()->init(items[j]);
		}
		else if (items[j]->dataRef->droppedLocation.Equals(S("inventory")))
		{
			inv->GetComponent<InventoryController>()->loadItem(items[j]);
		}
		else if (items[j]->dataRef->droppedLocation.Equals(S("trunk")))
		{
			inv->GetComponent<InventoryController>()->loadTrunkItem(items[j]);
		}
		else if (items[j]->dataRef->droppedLocation.Equals(S("chest")))
		{
			inv->GetComponent<InventoryController>()->loadChestItem(items[j]);
		}
	}
}

void ItemsManager::fixGroundItems(Vector2 newLoc, Vector2 shift)
{
	MonoBehaviour::print(S("FIXING GROUND ITEMS "));
	for (int i = 0; i < items.Count(); i++)
	{
		if (items[i]->dataRef->droppedLocation.Equals(SceneManager::GetActiveScene().get_name()))
		{
			MonoBehaviour::print(S("FOUND A GROUND ITEM"));
			Vector2 vector = ScreenControler::gameToScreen(Vector2((float)items[i]->dataRef->locX, (float)items[i]->dataRef->locY));
			Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
			vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
			Vector2 vector3 = Vector2(vector2.x, vector2.y);
			RaycastHit2D raycastHit2D = Physics2D::Linecast(vector3, vector3, LayerMask::GetMask(S("obstacleLayer")));
			MonoBehaviour::print(raycastHit2D.get_collider());
			if (raycastHit2D.get_collider() != nullptr)
			{
				MonoBehaviour::print(S("AND WE MOVE IT"));
				items[i]->dataRef->locX = (int)newLoc.x + (int)Random::Range(0.0f - shift.x, shift.x);
				items[i]->dataRef->locY = (int)newLoc.y + (int)Random::Range(0.0f - shift.y, shift.y);
			}
		}
	}
}

void ItemsManager::updateItem(String id, String droppedLocation, int locX, int locY)
{
	P<Item> item = nullptr;
	for (int i = 0; i < items.Count(); i++)
	{
		if (items[i]->id.Equals(id))
		{
			item = items[i];
			break;
		}
	}
	if (item != nullptr)
	{
		item->dataRef->droppedLocation = droppedLocation;
		item->dataRef->locX = locX;
		item->dataRef->locY = locY;
	}
	JournalTexts::pickTexts(GameDataController::gd->getCurrentDay());
}

void ItemsManager::initItem(String name, float weight, String soundName, List<P<ItemInteraction>> usablesI, List<P<ItemInteraction>> usablesG, int animationFrames, int animationDelay, bool hasExamineScreen, int var1, int var2, int var3, int var4, List<String> texts, int wid, int xShift, int yShift, float r1, float g1, float b1, float a1, float r2, float g2, float b2, float a2, bool cycle, ExamineSprite_Delegate lookAction, String soundL, bool actionOnLook)
{
	P<Item> item = New<Item>();
	item->id = name;
	item->weight = weight;
	item->examineCycleSprites = cycle;
	item->usableItemsGround = usablesG;
	item->usableItemsInventory = usablesI;
	if (texts != nullptr)
	{
		item->textWidth = wid;
		item->examineTexts = texts;
		item->textColor1 = Color(r1, g1, b1, a1);
		item->textColor2 = Color(r2, g2, b2, a2);
		item->textShiftX = xShift;
		item->textShiftY = yShift;
	}
	if (soundL != String::Empty)
	{
		item->soundLoop = Resources::Load<AudioClip>(S("Sounds/Items/") + soundL);
	}
	item->sound = Resources::Load<AudioClip>(S("Sounds/Items/") + soundName);
	item->groundSprite = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_ground"));
	item->inventorySprite = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_inv"));
	if (hasExamineScreen)
	{
		item->examineSprite = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_examine"));
		item->lookAction = lookAction;
		item->actionOnLook = actionOnLook;
		if (var1 != 0)
		{
			item->examineSprite_1 = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_examine_1_") + var1);
		}
		if (var2 != 0)
		{
			item->examineSprite_2 = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_examine_2_") + var2);
		}
		if (var3 != 0)
		{
			item->examineSprite_3 = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_examine_3_") + var3);
		}
		if (var4 != 0)
		{
			item->examineSprite_4 = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_examine_4_") + var4);
		}
	}
	if (animationFrames > 0)
	{
		if (animationFrames >= 1)
		{
			item->groundSprite_1 = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_ground_1"));
		}
		if (animationFrames >= 2)
		{
			item->groundSprite_2 = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_ground_2"));
		}
		if (animationFrames >= 3)
		{
			item->groundSprite_3 = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_ground_3"));
		}
		if (animationFrames >= 4)
		{
			item->groundSprite_4 = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_ground_4"));
		}
		if (animationFrames >= 5)
		{
			item->groundSprite_5 = Resources::Load<Sprite>(S("Bitmaps/Items/") + name + S("_ground_5"));
		}
		item->animationDelay = animationDelay;
	}
	items.Add(item);
}

void ItemsManager::initItems()
{
	for (int i = 0; i < items.Count(); i++)
	{
		items[i]->dataRef = GameDataController::gd->getItemData(items[i]->id);
	}
	int num = 1;
	int num2 = 1;
	int num3 = 1;
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 1)
	{
		num = 1;
		num2 = 1;
		num3 = 1;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 2)
	{
		num = 2;
		num2 = 2;
		num3 = 1;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 3)
	{
		num = 2;
		num2 = 2;
		num3 = 2;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 4)
	{
		num = 1;
		num2 = 2;
		num3 = 2;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 5)
	{
		num = 2;
		num2 = 1;
		num3 = 1;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 6)
	{
		num = 1;
		num2 = 1;
		num3 = 2;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 7)
	{
		num = 1;
		num2 = 2;
		num3 = 1;
	}
	if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 8)
	{
		num = 2;
		num2 = 1;
		num3 = 2;
	}
	im->getItem(S("bug"))->examineSprite_1 = Resources::Load<Sprite>(S("Bitmaps/Items/bug_examine_1_") + num);
	im->getItem(S("bug"))->examineSprite_2 = Resources::Load<Sprite>(S("Bitmaps/Items/bug_examine_2_") + num2);
	im->getItem(S("bug"))->examineSprite_4 = Resources::Load<Sprite>(S("Bitmaps/Items/bug_examine_4_") + num3);
	String text = str((float)GameDataController::gd->getObjectiveDetail(S("gas_dens")) / 100.0f);
	if ((double)((float)GameDataController::gd->getObjectiveDetail(S("gas_dens")) / 100.0f) == 1.6)
	{
		text += S("0");
	}
	im->getItem(S("drone"))->examineTexts = List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("drone_1")) + GameDataController::gd->getObjectiveDetail(S("gas_ph")) + GameStrings::getString(GameStrings::world_labels, S("drone_2")) + text + GameStrings::getString(GameStrings::world_labels, S("drone_3")) });
	String text2 = GameStrings::getString(GameStrings::world_labels, S("manifest_start"));
	text2 = text2 + S("^ 1. ") + GameStrings::getString(GameStrings::world_labels, S("airplane_cargo_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_1")));
	text2 = text2 + S("^ 2. ") + GameStrings::getString(GameStrings::world_labels, S("airplane_cargo_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_2")));
	text2 = text2 + S("^ 3. ") + GameStrings::getString(GameStrings::world_labels, S("airplane_cargo_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_3")));
	text2 = text2 + S("^ 4. ") + GameStrings::getString(GameStrings::world_labels, S("airplane_cargo_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_4")));
	text2 = text2 + S("^ 5. ") + GameStrings::getString(GameStrings::world_labels, S("airplane_cargo_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_5")));
	text2 = text2 + S("^ 6. ") + GameStrings::getString(GameStrings::world_labels, S("airplane_cargo_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_6")));
	text2 = text2 + S("^ 7. ") + GameStrings::getString(GameStrings::world_labels, S("airplane_cargo_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_7")));
	text2 = text2 + S("^ ^") + GameStrings::getString(GameStrings::world_labels, S("manifest_end"));
	im->getItem(S("manifest"))->examineTexts = List<String>::New({ text2 });
	String text3 = S("SP-");
	text3 = ((!GameDataController::gd->getObjective(S("previous_disc_barry")) && !GameDataController::gd->getObjective(S("previous_disc_cody"))) ? (text3 + S("1")) : (text3 + S("2")));
	text3 = ((GameDataController::gd->getObjectiveDetail(S("day_2_threat")) != 1) ? (text3 + (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) + 1)) : (text3 + (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) + 5)));
	text3 = ((GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 1) ? (text3 + (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) + 2)) : (text3 + (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) + 7)));
	text3 += S("8");
	im->getItem(S("sidereal_secrets"))->examineTexts[1] = GameStrings::getString(GameStrings::world_labels, S("sidereal_secrets_2"));
	im->getItem(S("sidereal_secrets"))->examineTexts[1] = im->getItem(S("sidereal_secrets"))->examineTexts[1].Replace(S("SP-12119"), String::Empty + text3);
}

void ItemsManager::exmineItem(P<Item> itemRef)
{
	ExamineSprite::es->textField->shift.x = itemRef->textShiftX;
	ExamineSprite::es->textField->shift.y = itemRef->textShiftY;
	List<String> list = List<String>::New();
	if (itemRef->examineTexts != nullptr)
	{
		for (int i = 0; i < itemRef->examineTexts.Count(); i++)
		{
			list.Add(itemRef->examineTexts[i]);
		}
	}
	ExamineSprite::es->readyText(list, itemRef->textWidth, itemRef->textColor1.r, itemRef->textColor1.g, itemRef->textColor1.b, itemRef->textColor2.r, itemRef->textColor2.g, itemRef->textColor2.b, itemRef->textColor2.a);
	ExamineSprite::es->cycleSprites = itemRef->examineCycleSprites;
	ExamineSprite::es->show(itemRef->examineSprite, itemRef->examineSprite_1, itemRef->examineSprite_2, itemRef->examineSprite_3, itemRef->examineSprite_4, itemRef->lookAction, itemRef->actionOnLook);
}

P<Item> ItemsManager::getItem(String name)
{
	for (int i = 0; i < items.Count(); i++)
	{
		if (items[i]->dataRef->id.Equals(name))
		{
			return items[i];
		}
	}
	return nullptr;
}

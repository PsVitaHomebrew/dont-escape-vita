#include "../game_all.h"

// Vita port: true while Load copies objectives from a save (see the loop in Load); the journal is rebuilt once after.
static bool s_journalHold = false;
struct JournalHold { JournalHold() { s_journalHold = true; } ~JournalHold() { s_journalHold = false; } };

void GameDataController::Awake()
{
	if (gd == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		gd = this;
	}
	else if (gd != P<GameDataController>(this))
	{
		Object::Destroy(gameObject);
	}
}

void GameDataController::Achievement(String id)
{
	if (persistentData->achievements.Find([=](const P<Objective>& x) { return x->id == id; }) != nullptr)
	{
		persistentData->achievements.Find([=](const P<Objective>& x) { return x->id == id; })->state = true;
		gd->PersistentSave();
	}
	else
	{
		Debug::LogWarning(S("ACHIEVEMENT ID NOT FOUND IN PERSISTENT DATA"));
	}
}

void GameDataController::Start()
{
	if (GOG)
	{
		VERSION += S("-G");
	}
	if (KART)
	{
		VERSION += S("-K");
	}
	if (!PlayerPrefs::HasKey(S("stati")))
	{
		PlayerPrefs::SetInt(S("stati"), 80);
		PlayerPrefs::SetInt(S("music"), 80);
		PlayerPrefs::SetInt(S("sound"), 100);
		PlayerPrefs::SetFloat(S("textSpeed"), 0.0425f);
		PlayerPrefs::SetString(S("lang"), str(GameStrings::Language::EN));
		PlayerPrefs::Save();
	}
	persistentData = New<PersistentData>();
	initPersistantAchieves();
	persistentDataView = New<PersistentData>();
	newGame();
	if (GOG)
	{
		InvokeRepeating(S("updateAchievements"), 1.0f, 5.0f);
	}
}

void GameDataController::updateAchievements()
{
}

void GameDataController::Update()
{
	persistentDataView = persistentData;
}

int GameDataController::getRandomHash(int len)
{
	List<String> list = List<String>::New();
	for (int i = 1; i <= len; i++)
	{
		list.Add(str(i));
	}
	for (int j = 0; j < 20; j++)
	{
		int index = Random::Range(0, list.Count());
		list.Add(list[index]);
		list.RemoveAt(index);
	}
	String text = String::Empty;
	for (int k = 0; k < list.Count(); k++)
	{
		text += list[k];
	}
	return int_Parse(text);
}

void GameDataController::newGame()
{
	PersistentLoad();
	if (InventoryController::ic != nullptr && items != nullptr)
	{
		InventoryController::ic->clearInventory();
	}
	items = List<P<ItemData>>::New();
	objectives = List<P<Objective>>::New();
	journals = List<P<Objective>>::New();
	visited = List<P<Objective>>::New();
	gameTime = 420;
	timeLimit = 1200;
	journalEntries = String::Empty;
	newJournalEntries = S("1");
	traveledTime = 0;
	workedTime = 0;
	items.Add(New<ItemData>(S("key1"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("key2"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("key3"), S("nowhere"), 1, 3));
	items.Add(New<ItemData>(S("key4"), S("nowhere"), 1, 3));
	items.Add(New<ItemData>(S("pipe"), S("nowhere"), 1, 4));
	items.Add(New<ItemData>(S("sonic"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("sonic2"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("sonic_remote"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("pest_note"), S("nowhere"), 3, 1));
	items.Add(New<ItemData>(S("gas_note"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("spider_note"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("pest1"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("pest2"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("paperclip"), S("nowhere"), 2, 1));
	items.Add(New<ItemData>(S("invoices"), S("nowhere"), 2, 2));
	items.Add(New<ItemData>(S("crowbar"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("straw"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("window_foil1"), S("nowhere"), 3, 1));
	items.Add(New<ItemData>(S("window_foil2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("window_foil3"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("window_bars1"), S("nowhere"), 4, 2));
	items.Add(New<ItemData>(S("window_bars2"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("window_bars3"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("window_net1"), S("nowhere"), 3, 3));
	items.Add(New<ItemData>(S("window_net2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("window_net3"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("planks1"), S("nowhere"), 4, 1));
	items.Add(New<ItemData>(S("planks2"), S("nowhere"), 4, 2));
	items.Add(New<ItemData>(S("planks3"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("planks4"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("planks5"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("nails1"), S("nowhere"), 4, 1));
	items.Add(New<ItemData>(S("nails2"), S("nowhere"), 4, 2));
	items.Add(New<ItemData>(S("nails3"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("nails4"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("nails5"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("ducttape"), S("nowhere"), 3, 3));
	items.Add(New<ItemData>(S("canister_full"), S("nowhere"), 2, 1));
	items.Add(New<ItemData>(S("canister2_full"), S("nowhere"), 2, 1));
	items.Add(New<ItemData>(S("bug"), S("nowhere"), 4, 1));
	items.Add(New<ItemData>(S("hammer"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("hammer_handle"), S("nowhere"), 4, 2));
	items.Add(New<ItemData>(S("broken_hammer"), S("chest"), 1, 1));
	items.Add(New<ItemData>(S("canister2_empty"), S("nowhere"), 3, 4));
	items.Add(New<ItemData>(S("canister_empty"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("lighter"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("watersprayer"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("pestsprayer"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("fuelsprayer"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("flamethrower"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("flamethrower_empty"), S("nowhere"), 3, 4));
	items.Add(New<ItemData>(S("wrench"), S("nowhere"), 4, 5));
	items.Add(New<ItemData>(S("wad_of_cash"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("chem_glass"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("chem_glass_1"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("chem_glass_2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("chem_glass_3"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("chem_glass_12"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("chem_glass_13"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("chem_glass_23"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("drone"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("towel_1"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("towel_2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("chemsuit_dmg_dmg"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("chemsuit_rep_dmg"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("chemsuit_dmg_rep"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("chemsuit_rep_rep"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("mask_filter"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_0"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_1"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("rifle_2"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("rifle_3"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_4"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("rifle_5"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_6"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_s_0"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_s_1"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("rifle_s_2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_s_3"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_s_4"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("rifle_s_5"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_s_6"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_o_0"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_o_1"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("rifle_o_2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_o_3"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_o_4"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("rifle_o_5"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("rifle_o_6"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_so_0"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_so_1"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("rifle_so_2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_so_3"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_so_4"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("rifle_so_5"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("rifle_so_6"), S("nowhere"), 3, 3));
	items.Add(New<ItemData>(S("bear_trap_1b"), S("nowhere"), 1, 3));
	items.Add(New<ItemData>(S("bear_trap_2b"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("bear_trap_1"), S("nowhere"), 1, 3));
	items.Add(New<ItemData>(S("bear_trap_2"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("bear_trap_3"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("bear_trap_4"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("rock"), S("LocationGasstation2"), 175, 47));
	items.Add(New<ItemData>(S("rock2"), S("SiderealF3C"), 97, 50));
	items.Add(New<ItemData>(S("ignitioncoil"), S("nowhere"), 4, 2));
	items.Add(New<ItemData>(S("wheel"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("car_battery"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("spiderpest1"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("spiderpest2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("spiderpest3"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("spiderpest4"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("coat1"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("coat2"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("coat3"), S("nowhere"), 3, 4));
	items.Add(New<ItemData>(S("coat4"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("sheet"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("shovel"), S("nowhere"), 3, 3));
	items.Add(New<ItemData>(S("hose"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("gas_tank"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("locket"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("foodcan"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("foodcanopen"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("screwdriver"), S("nowhere"), 1, 5));
	items.Add(New<ItemData>(S("canopener"), S("nowhere"), 2, 5));
	items.Add(New<ItemData>(S("knife"), S("nowhere"), 3, 5));
	items.Add(New<ItemData>(S("hook"), S("nowhere"), 1, 5));
	items.Add(New<ItemData>(S("rope"), S("nowhere"), 3, 2));
	items.Add(New<ItemData>(S("flag"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("ropehook"), S("nowhere"), 3, 4));
	items.Add(New<ItemData>(S("deadbird"), S("nowhere"), 3, 2));
	items.Add(New<ItemData>(S("charcoal"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("charcoal_empty"), S("nowhere"), 4, 2));
	items.Add(New<ItemData>(S("generator"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("generator2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("blanket"), S("nowhere"), 3, 3));
	items.Add(New<ItemData>(S("blanketb"), S("nowhere"), 3, 1));
	items.Add(New<ItemData>(S("thermalb"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("gasheater"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("gasheater_empty"), S("LocationRestaurant4"), 56, 27));
	items.Add(New<ItemData>(S("heater"), S("nowhere"), 55, 45));
	items.Add(New<ItemData>(S("heater_broken"), S("nowhere"), 55, 45));
	items.Add(New<ItemData>(S("ac"), S("nowhere"), 3, 2));
	items.Add(New<ItemData>(S("ext_cord"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("ext_cord_place"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("ac_cord"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("fan"), S("nowhere"), 2, 2));
	items.Add(New<ItemData>(S("fan_broken"), S("nowhere"), 3, 2));
	items.Add(New<ItemData>(S("heat_absorber1"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("heat_absorber2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("heat_absorber3"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("heat_absorber1A"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("heat_absorber2A"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("heat_absorber3A"), S("nowhere"), 1, 3));
	items.Add(New<ItemData>(S("water1"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("water2"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("water3"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("water4"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("sledgehammer"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("sledge_head"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("sledge_handle"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("puzzle_cable"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("fire_hose"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("sidereal_id"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("sidereal_id_key"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("sidereal_docs"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("sidereal_xero"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("sidereal_secrets"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("revolver_0"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("revolver_1"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("revolver_2"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("revolver_3"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("revolver_4"), S("nowhere"), 1, 5));
	items.Add(New<ItemData>(S("revolver_5"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("revolver_6"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("gun_ammo"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("rifle_ammo"), S("nowhere"), 3, 4));
	items.Add(New<ItemData>(S("scope"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("silencer"), S("nowhere"), 105, 40));
	items.Add(New<ItemData>(S("whiskey"), S("nowhere"), 1, 3));
	items.Add(New<ItemData>(S("maggot"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("oil"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("poison"), S("nowhere"), 1, 2));
	items.Add(New<ItemData>(S("food_bag"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("gloves"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("welder"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("mixer_glass"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("pill_half"), S("nowhere"), 0, 0));
	items.Add(New<ItemData>(S("pills"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("catalyst"), S("nowhere"), 2, 1));
	items.Add(New<ItemData>(S("mixer_pills_note"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("mixer_catalyst_note"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("outpost_card"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("moon_card"), S("nowhere"), 4, 3));
	items.Add(New<ItemData>(S("remote"), S("nowhere"), 3, 2));
	items.Add(New<ItemData>(S("batteries"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("gluegun"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("gluegun_powered"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("fingerprint"), S("nowhere"), 3, 3));
	items.Add(New<ItemData>(S("vials1"), S("nowhere"), 3, 3));
	items.Add(New<ItemData>(S("vials2"), S("nowhere"), 3, 3));
	items.Add(New<ItemData>(S("engine_calibrator"), S("nowhere"), 4, 1));
	items.Add(New<ItemData>(S("lioh_filter"), S("nowhere"), 4, 2));
	items.Add(New<ItemData>(S("metal_slab"), S("nowhere"), 3, 4));
	items.Add(New<ItemData>(S("nav_chip"), S("nowhere"), 1, 4));
	items.Add(New<ItemData>(S("air_tanks"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("transmission_belt"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("duplexer"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("noodles"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("voltmeter"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("gasket"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("nuts_and_bolts"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("wires"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("wire"), S("nowhere"), 4, 4));
	items.Add(New<ItemData>(S("manifest"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("broom"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("stormcatcher1"), S("nowhere"), 1, 4));
	items.Add(New<ItemData>(S("stormcatcher2"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("stormcatcher3"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("disc1"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("disc2"), S("nowhere"), 2, 5));
	items.Add(New<ItemData>(S("bandage"), S("nowhere"), 2, 4));
	items.Add(New<ItemData>(S("finger"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("cate_note"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("tarpaulin"), S("nowhere"), 2, 3));
	items.Add(New<ItemData>(S("board1"), S("nowhere"), 1, 1));
	items.Add(New<ItemData>(S("board2"), S("nowhere"), 2, 1));
	items.Add(New<ItemData>(S("board3"), S("nowhere"), 3, 1));
	objectives.Add(New<Objective>(S("cody_warned"), false));
	objectives.Add(New<Objective>(S("barry_warned"), false));
	objectives.Add(New<Objective>(S("previous_disc_barry"), persistentData->disc_barry));
	objectives.Add(New<Objective>(S("previous_disc_cody"), persistentData->disc_cody));
	objectives.Add(New<Objective>(S("moonfall_progress_1"), false));
	objectives.Add(New<Objective>(S("moonfall_progress_2"), false));
	objectives.Add(New<Objective>(S("moonfall_progress_3"), false));
	objectives.Add(New<Objective>(S("moonfall_progress_4"), false));
	objectives.Add(New<Objective>(S("day_1_threat"), false, 1));
	objectives.Add(New<Objective>(S("day_2_threat"), false));
	objectives.Add(New<Objective>(S("day_3_threat"), false));
	objectives.Add(New<Objective>(S("day_4_threat"), false));
	objectives.Add(New<Objective>(S("gas_ph"), false, Random::Range(0, 8)));
	objectives.Add(New<Objective>(S("spiders_type"), false, Random::Range(0, 4)));
	objectives.Add(New<Objective>(S("journal_page"), false));
	objectives.Add(New<Objective>(S("car_travel"), false));
	int num;
	do
	{
		num = Random::Range(159, 164);
	}
	while (num == 161);
	objectives.Add(New<Objective>(S("chitchat"), false, -20));
	objectives.Add(New<Objective>(S("chitchat_cate"), false, getRandomHash()));
	String text = str(getRandomHash(7));
	text = text.Insert(2, S("8"));
	text = text.Insert(3, S("9"));
	objectives.Add(New<Objective>(S("chitchat_cate_cody"), false, int_Parse(text)));
	objectives.Add(New<Objective>(S("chitchat_cate_barry"), false, getRandomHash()));
	objectives.Add(New<Objective>(S("chitchat_cate_cody_barry"), false, getRandomHash()));
	objectives.Add(New<Objective>(S("chitchat_cate_cody_deadbarry"), false, getRandomHash()));
	objectives.Add(New<Objective>(S("chitchat_cate_barry_deadcody"), false, getRandomHash()));
	objectives.Add(New<Objective>(S("gas_dens"), false, num));
	objectives.Add(New<Objective>(S("drone_taken"), false));
	objectives.Add(New<Objective>(S("towel_1_taken"), false));
	objectives.Add(New<Objective>(S("towel_2_taken"), false));
	objectives.Add(New<Objective>(S("towel_1_at_door"), false));
	objectives.Add(New<Objective>(S("towel_2_at_door"), false));
	objectives.Add(New<Objective>(S("dream_day_1_started"), false));
	objectives.Add(New<Objective>(S("dream_day_1_window_broken"), false));
	objectives.Add(New<Objective>(S("dream_day_2_started"), false));
	objectives.Add(New<Objective>(S("dream_day_2_window_broken"), false));
	objectives.Add(New<Objective>(S("dream_day_2_awake"), false));
	objectives.Add(New<Objective>(S("dream_day_3_started"), false));
	objectives.Add(New<Objective>(S("dream_day_3b_started"), false));
	objectives.Add(New<Objective>(S("dream_day_3_window_broken"), false));
	objectives.Add(New<Objective>(S("dream_day_3_awake"), false));
	objectives.Add(New<Objective>(S("dream_day_4_started"), false));
	objectives.Add(New<Objective>(S("dream_day_4_door_open"), false));
	objectives.Add(New<Objective>(S("dream_day_4_awake"), false));
	objectives.Add(New<Objective>(S("day_2_hatch_fallen"), false));
	objectives.Add(New<Objective>(S("tent_awake"), false));
	objectives.Add(New<Objective>(S("tent_backpack_taken"), false));
	objectives.Add(New<Objective>(S("tent_distance_triggered"), false));
	objectives.Add(New<Objective>(S("tent_distance_checked"), false));
	objectives.Add(New<Objective>(S("intro_desert_walked"), false));
	objectives.Add(New<Objective>(S("tutorial_door_opened"), false));
	objectives.Add(New<Objective>(S("tutorial_hammer_taken"), false));
	objectives.Add(New<Objective>(S("tutorial_handle_taken"), false));
	objectives.Add(New<Objective>(S("tutorial_wall_smashed"), false));
	objectives.Add(New<Objective>(S("wall_encountered"), false));
	objectives.Add(New<Objective>(S("run_hint"), false));
	objectives.Add(New<Objective>(S("location01_door2_locked"), true));
	objectives.Add(New<Objective>(S("location01_door2_open"), false));
	objectives.Add(New<Objective>(S("location02_door_open"), false));
	objectives.Add(New<Objective>(S("location02_door_locked"), true));
	objectives.Add(New<Objective>(S("kitchen_oven_open"), false));
	objectives.Add(New<Objective>(S("kitchen_heater_plugged"), false));
	objectives.Add(New<Objective>(S("kitchen_fan_plugged"), false));
	objectives.Add(New<Objective>(S("kitchen_cord_plugged"), false));
	objectives.Add(New<Objective>(S("kitchen_cord_dragged"), false));
	objectives.Add(New<Objective>(S("base_upstairs_cord_dragged"), false));
	objectives.Add(New<Objective>(S("base_heater_cord_plugged"), false));
	objectives.Add(New<Objective>(S("base_fan_cord_plugged"), false));
	objectives.Add(New<Objective>(S("window1_ac_placed"), false));
	objectives.Add(New<Objective>(S("base_ac_cord_plugged"), false));
	objectives.Add(New<Objective>(S("base_window_1_net"), false));
	objectives.Add(New<Objective>(S("base_window_1_net_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_1_net_taped"), false));
	objectives.Add(New<Objective>(S("base_window_1_foil"), false));
	objectives.Add(New<Objective>(S("base_window_1_foil_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_1_foil_taped"), false));
	objectives.Add(New<Objective>(S("base_window_1_bars"), false));
	objectives.Add(New<Objective>(S("base_window_1_bars_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_1_bars_taped"), false));
	objectives.Add(New<Objective>(S("base_window_1_blanketb"), false));
	objectives.Add(New<Objective>(S("base_window_1_blanketb_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_1_blanketb_taped"), false));
	objectives.Add(New<Objective>(S("base_window_1_blanket"), false));
	objectives.Add(New<Objective>(S("base_window_1_blanket_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_1_blanket_taped"), false));
	objectives.Add(New<Objective>(S("base_window_1_flag"), false));
	objectives.Add(New<Objective>(S("base_window_1_flag_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_1_flag_taped"), false));
	objectives.Add(New<Objective>(S("base_window_1_therm"), false));
	objectives.Add(New<Objective>(S("base_window_1_therm_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_1_therm_taped"), false));
	objectives.Add(New<Objective>(S("base_window_1_board"), false));
	objectives.Add(New<Objective>(S("base_window_1_board_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_1_board_taped"), false));
	objectives.Add(New<Objective>(S("base_window1_broken"), false));
	objectives.Add(New<Objective>(S("base_window_2_net"), false));
	objectives.Add(New<Objective>(S("base_window_2_net_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_2_net_taped"), false));
	objectives.Add(New<Objective>(S("base_window_2_foil"), false));
	objectives.Add(New<Objective>(S("base_window_2_foil_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_2_foil_taped"), false));
	objectives.Add(New<Objective>(S("base_window_2_bars"), false));
	objectives.Add(New<Objective>(S("base_window_2_bars_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_2_bars_taped"), false));
	objectives.Add(New<Objective>(S("base_window2_broken"), false));
	objectives.Add(New<Objective>(S("base_window_2_blanketb"), false));
	objectives.Add(New<Objective>(S("base_window_2_blanketb_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_2_blanketb_taped"), false));
	objectives.Add(New<Objective>(S("base_window_2_blanket"), false));
	objectives.Add(New<Objective>(S("base_window_2_blanket_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_2_blanket_taped"), false));
	objectives.Add(New<Objective>(S("base_window_2_flag"), false));
	objectives.Add(New<Objective>(S("base_window_2_flag_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_2_flag_taped"), false));
	objectives.Add(New<Objective>(S("base_window_2_therm"), false));
	objectives.Add(New<Objective>(S("base_window_2_therm_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_2_therm_taped"), false));
	objectives.Add(New<Objective>(S("base_window_2_board"), false));
	objectives.Add(New<Objective>(S("base_window_2_board_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_2_board_taped"), false));
	objectives.Add(New<Objective>(S("base_window_3_net"), false));
	objectives.Add(New<Objective>(S("base_window_3_net_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_3_net_taped"), false));
	objectives.Add(New<Objective>(S("base_window_3_foil"), false));
	objectives.Add(New<Objective>(S("base_window_3_foil_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_3_foil_taped"), false));
	objectives.Add(New<Objective>(S("base_window_3_bars"), false));
	objectives.Add(New<Objective>(S("base_window_3_bars_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_3_bars_taped"), false));
	objectives.Add(New<Objective>(S("base_window3_broken"), false));
	objectives.Add(New<Objective>(S("base_window_3_blanket"), false));
	objectives.Add(New<Objective>(S("base_window_3_blanket_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_3_blanket_taped"), false));
	objectives.Add(New<Objective>(S("base_window_3_blanketb"), false));
	objectives.Add(New<Objective>(S("base_window_3_blanketb_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_3_blanketb_taped"), false));
	objectives.Add(New<Objective>(S("base_window_3_flag"), false));
	objectives.Add(New<Objective>(S("base_window_3_flag_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_3_flag_taped"), false));
	objectives.Add(New<Objective>(S("base_window_3_therm"), false));
	objectives.Add(New<Objective>(S("base_window_3_therm_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_3_therm_taped"), false));
	objectives.Add(New<Objective>(S("base_window_3_board"), false));
	objectives.Add(New<Objective>(S("base_window_3_board_nailed"), false));
	objectives.Add(New<Objective>(S("base_window_3_board_taped"), false));
	objectives.Add(New<Objective>(S("base_hatch_therm"), false));
	objectives.Add(New<Objective>(S("base_hatch_blanketb"), false));
	objectives.Add(New<Objective>(S("base_hatch_blanket"), false));
	objectives.Add(New<Objective>(S("base_hatch_flag"), false));
	objectives.Add(New<Objective>(S("base_fireplace_lit"), false));
	objectives.Add(New<Objective>(S("attic_hatch_open"), false));
	objectives.Add(New<Objective>(S("ginger_from_attic"), false));
	objectives.Add(New<Objective>(S("deadbird_taken"), false));
	objectives.Add(New<Objective>(S("chimney_cleaned"), false));
	objectives.Add(New<Objective>(S("chimney_wood"), false));
	objectives.Add(New<Objective>(S("chimney_note"), false));
	objectives.Add(New<Objective>(S("chimney_papers"), false));
	objectives.Add(New<Objective>(S("chimney_cash"), false));
	objectives.Add(New<Objective>(S("chimney_charcoal"), false));
	objectives.Add(New<Objective>(S("chimney_bag"), false));
	objectives.Add(New<Objective>(S("basket_wood"), false));
	objectives.Add(New<Objective>(S("basket_note"), false));
	objectives.Add(New<Objective>(S("basket_papers"), false));
	objectives.Add(New<Objective>(S("basket_cash"), false));
	objectives.Add(New<Objective>(S("basket_charcoal"), false));
	objectives.Add(New<Objective>(S("basket_bag"), false));
	objectives.Add(New<Objective>(S("house_oven"), false));
	objectives.Add(New<Objective>(S("house_heater"), false));
	objectives.Add(New<Objective>(S("house_gasheater"), false));
	objectives.Add(New<Objective>(S("upstairs_paperclip_taken"), false));
	objectives.Add(New<Objective>(S("upstairs_papers_taken"), false));
	objectives.Add(New<Objective>(S("screwdriver_taken"), false));
	objectives.Add(New<Objective>(S("ext_cord_taken"), false));
	objectives.Add(New<Objective>(S("outside0_window_broken"), false));
	objectives.Add(New<Objective>(S("base_discovered"), false));
	objectives.Add(New<Objective>(S("bridge_discovered"), false));
	objectives.Add(New<Objective>(S("gasstation_discovered"), false));
	objectives.Add(New<Objective>(S("pesttruck_locker1_open"), false));
	objectives.Add(New<Objective>(S("pesttruck_locker2_open"), false));
	objectives.Add(New<Objective>(S("pesttruck_locker2_unlocked"), false));
	objectives.Add(New<Objective>(S("pesttruck_locker3_open"), false));
	objectives.Add(New<Objective>(S("pesttruck_locker4_open"), false));
	objectives.Add(New<Objective>(S("pesttruck_sonic_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_note_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_pest1_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_pest2_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_unlocked"), false));
	objectives.Add(New<Objective>(S("pesttruck_ducttape_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_chem_glass_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_chemsuit_dmg_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_spiderpest1_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_spiderpest2_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_spiderpest3_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_spiderpest4_taken"), false));
	objectives.Add(New<Objective>(S("pesttruck_bear_traps_taken"), false));
	objectives.Add(New<Objective>(S("mask_filter_taken"), false));
	objectives.Add(New<Objective>(S("barn_pipe_taken"), false));
	objectives.Add(New<Objective>(S("barn_haystack_3"), false));
	objectives.Add(New<Objective>(S("barn_haystack_2"), false));
	objectives.Add(New<Objective>(S("barn_haystack_1"), false));
	objectives.Add(New<Objective>(S("barn_pipe_fixed"), false));
	objectives.Add(New<Objective>(S("car_location"), false));
	objectives.Add(New<Objective>(S("barn_car_inspected"), false));
	objectives.Add(New<Objective>(S("barn_car_wheel_repaired"), false));
	objectives.Add(New<Objective>(S("barn_car_coil_repaired"), false));
	objectives.Add(New<Objective>(S("barn_car_battery_repaired"), true));
	objectives.Add(New<Objective>(S("barn_car_refueled"), false));
	objectives.Add(New<Objective>(S("barn_pump_fueled"), false));
	objectives.Add(New<Objective>(S("barn_pump_started"), false, 1));
	objectives.Add(New<Objective>(S("barn_pump_start_try"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_enabled"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_b1"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_b2"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_b3"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_b4"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_b5"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_b6"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_b7"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_b8"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_fed1"), false));
	objectives.Add(New<Objective>(S("barn_sprinklers_fed2"), false));
	objectives.Add(New<Objective>(S("bridge_crowbar_taken"), false));
	objectives.Add(New<Objective>(S("bridge_handle_taken"), false));
	objectives.Add(New<Objective>(S("bridge_wheel_taken"), false));
	objectives.Add(New<Objective>(S("bridge_westside"), false));
	objectives.Add(New<Objective>(S("bridge_planks_used_1"), false));
	objectives.Add(New<Objective>(S("bridge_planks_used_2"), false));
	objectives.Add(New<Objective>(S("crashsite_discovered_bugs"), false));
	objectives.Add(New<Objective>(S("crashsite_truck_open"), false));
	objectives.Add(New<Objective>(S("crashsite_sonic_remote_taken"), false));
	objectives.Add(New<Objective>(S("crashsite_wrench_taken"), false));
	objectives.Add(New<Objective>(S("crashsite_bug_taken"), false));
	objectives.Add(New<Objective>(S("crashsite_gas_note_read"), false));
	objectives.Add(New<Objective>(S("crashsite_car_examined"), false));
	objectives.Add(New<Objective>(S("crashsite_car_harvested"), false));
	objectives.Add(New<Objective>(S("sonic_frequency"), false, 123));
	objectives.Add(New<Objective>(S("bug_type"), false, Random::Range(1, 9)));
	objectives.Add(New<Objective>(S("greenhouse_nails"), true, 4));
	objectives.Add(New<Objective>(S("greenhouse_sprayer_taken"), false));
	objectives.Add(New<Objective>(S("bugs_bath"), false));
	objectives.Add(New<Objective>(S("gasstation_lighter_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_canister_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_charcoal_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_foil1_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_foil2_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_foil3_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_net1_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_net2_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_net3_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_bars1_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_bars2_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_bars3_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_straw_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_plastic_cup_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_cash_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_crowbar_free"), false));
	objectives.Add(New<Objective>(S("gasstation_canister_placed_under_tank"), false));
	objectives.Add(New<Objective>(S("gasstation_canister2_placed_under_tank"), false));
	objectives.Add(New<Objective>(S("gasstation_canister_filled"), false));
	objectives.Add(New<Objective>(S("gasstation_canister2_filled"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_canister_filled"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_canister_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_intro"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_shot"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_reason"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_rank"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_army"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_razor"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_razor_army"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_ship"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_moon"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_convinced"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_convincing1"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_convincing2"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_convincing3"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_convincing4"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_convincing5"), false));
	objectives.Add(New<Objective>(S("gasstation_sarge_first_bye"), false));
	objectives.Add(New<Objective>(S("gasstation_thugs_safe"), false));
	objectives.Add(New<Objective>(S("gasstation_map_warned"), false));
	objectives.Add(New<Objective>(S("gasstation_spy_mode"), false));
	objectives.Add(New<Objective>(S("thugs_gasstation_talk"), false));
	objectives.Add(New<Objective>(S("thugs_gasstation_spotted"), false));
	objectives.Add(New<Objective>(S("gasstation_rifle_taken"), false));
	objectives.Add(New<Objective>(S("gasstation_spider_discovered"), false));
	objectives.Add(New<Objective>(S("gasstation_spider_baited"), false));
	objectives.Add(New<Objective>(S("gasstation_spider_player_fallen"), false));
	objectives.Add(New<Objective>(S("gasstation_spider_shot"), false));
	objectives.Add(New<Objective>(S("restaurant_pipe_inserted"), false));
	objectives.Add(New<Objective>(S("restaurant_pipe_switched"), false));
	objectives.Add(New<Objective>(S("restaurant_flag_lowered"), false));
	objectives.Add(New<Objective>(S("restaurant_trash_tried"), false));
	objectives.Add(New<Objective>(S("restaurant_trash_moved"), false));
	objectives.Add(New<Objective>(S("restaurant_can_taken"), false));
	objectives.Add(New<Objective>(S("restaurant_door_opened"), false));
	objectives.Add(New<Objective>(S("restaurant_door_opened2"), false));
	objectives.Add(New<Objective>(S("restaurant_knife_taken"), false));
	objectives.Add(New<Objective>(S("restaurant_cupboard1_open"), false));
	objectives.Add(New<Objective>(S("restaurant_cupboard2_open"), false));
	objectives.Add(New<Objective>(S("restaurant_cupboard3_open"), false));
	objectives.Add(New<Objective>(S("restaurant_ac_taken"), false));
	objectives.Add(New<Objective>(S("restaurant_fridge_open"), false));
	objectives.Add(New<Objective>(S("restaurant_fridge_broken"), false));
	objectives.Add(New<Objective>(S("restaurant_water_taken1"), false));
	objectives.Add(New<Objective>(S("restaurant_water_taken2"), false));
	objectives.Add(New<Objective>(S("restaurant_freezer_open"), false));
	objectives.Add(New<Objective>(S("restaurant_absorbers_taken"), false));
	objectives.Add(New<Objective>(S("restaurant_dead_cody_commented"), false));
	objectives.Add(New<Objective>(S("restaurant_poision_taken"), false));
	objectives.Add(New<Objective>(S("restaurant_chem_door_open"), false));
	objectives.Add(New<Objective>(S("restaurant_chem_walked"), false));
	objectives.Add(New<Objective>(S("restaurant_oil_taken"), false));
	objectives.Add(New<Objective>(S("restaurant_door_opened_teamed"), false));
	objectives.Add(New<Objective>(S("restaurant_soliders_encountered"), false));
	objectives.Add(New<Objective>(S("restaurant_sarge_encountered"), false));
	objectives.Add(New<Objective>(S("restaurant_sarge_awaits"), false));
	objectives.Add(New<Objective>(S("map_base_revealed"), true, TravelAgency::LOCATION_STATUS_REACHABLE));
	objectives.Add(New<Objective>(S("map_bridge_revealed"), false, TravelAgency::LOCATION_STATUS_REACHABLE));
	objectives.Add(New<Objective>(S("map_gasstation_revealed"), false, TravelAgency::LOCATION_STATUS_UNDISCOVERED));
	objectives.Add(New<Objective>(S("map_houseb_revealed"), false, TravelAgency::LOCATION_STATUS_UNDISCOVERED));
	objectives.Add(New<Objective>(S("map_restaurant_revealed"), false, TravelAgency::LOCATION_STATUS_UNDISCOVERED));
	objectives.Add(New<Objective>(S("map_cars_revealed"), false, TravelAgency::LOCATION_STATUS_REACHABLE));
	objectives.Add(New<Objective>(S("map_rv_revealed"), false, TravelAgency::LOCATION_STATUS_UNDISCOVERED));
	objectives.Add(New<Objective>(S("map_hunters_revealed"), false, TravelAgency::LOCATION_STATUS_UNDISCOVERED));
	objectives.Add(New<Objective>(S("map_sidereal_revealed"), false, TravelAgency::LOCATION_STATUS_UNDISCOVERED));
	objectives.Add(New<Objective>(S("map_construction_revealed"), false, TravelAgency::LOCATION_STATUS_UNDISCOVERED));
	objectives.Add(New<Objective>(S("map_outpost_revealed"), false, TravelAgency::LOCATION_STATUS_UNDISCOVERED));
	objectives.Add(New<Objective>(S("map_airplane_revealed"), false, TravelAgency::LOCATION_STATUS_UNDISCOVERED));
	objectives.Add(New<Objective>(S("map_bus_revealed"), false, TravelAgency::LOCATION_STATUS_UNDISCOVERED));
	objectives.Add(New<Objective>(S("house_b_sheet_taken"), false));
	objectives.Add(New<Objective>(S("house_b_blanket_taken"), false));
	objectives.Add(New<Objective>(S("house_b_coat1_taken"), false));
	objectives.Add(New<Objective>(S("house_b_coat2_taken"), false));
	objectives.Add(New<Objective>(S("house_b_wife_note_taken"), false));
	objectives.Add(New<Objective>(S("house_b_wife_note_read"), false));
	objectives.Add(New<Objective>(S("house_b_wife_covered"), false));
	objectives.Add(New<Objective>(S("house_b_wife_moved"), false));
	objectives.Add(New<Objective>(S("house_b_wife_barry_moved"), false));
	objectives.Add(New<Objective>(S("house_b_closet_open"), false));
	objectives.Add(New<Objective>(S("house_b_grave_dug"), false));
	objectives.Add(New<Objective>(S("house_b_body_in_grave"), false));
	objectives.Add(New<Objective>(S("house_b_grave_filled"), false));
	objectives.Add(New<Objective>(S("house_b_shovel_taken"), false));
	objectives.Add(New<Objective>(S("house_b_garage_open"), false));
	objectives.Add(New<Objective>(S("house_b_hose_disconnected"), false));
	objectives.Add(New<Objective>(S("house_b_hose_taken"), false));
	objectives.Add(New<Objective>(S("house_b_tank_taken"), false));
	objectives.Add(New<Objective>(S("house_b_heater_taken"), false));
	objectives.Add(New<Objective>(S("house_b_fan_taken"), false));
	objectives.Add(New<Objective>(S("house_b_dead_barry_commented"), false));
	objectives.Add(New<Objective>(S("rv_hook_taken"), false));
	objectives.Add(New<Objective>(S("rv_hook_installed"), false));
	objectives.Add(New<Objective>(S("rv_cave_therm"), false));
	objectives.Add(New<Objective>(S("rv_cave_blanketb"), false));
	objectives.Add(New<Objective>(S("rv_cave_blanket"), false));
	objectives.Add(New<Objective>(S("rv_cave_flag"), false));
	objectives.Add(New<Objective>(S("rv_cord_plugged"), false));
	objectives.Add(New<Objective>(S("rv_cord_caved"), false));
	objectives.Add(New<Objective>(S("rv_power"), true));
	objectives.Add(New<Objective>(S("cave_heater_cord_plugged"), false));
	objectives.Add(New<Objective>(S("cave_fan_cord_plugged"), false));
	objectives.Add(New<Objective>(S("cave_ac_cord_plugged"), false));
	objectives.Add(New<Objective>(S("cave_ac_placed"), false));
	objectives.Add(New<Objective>(S("rv_coat1_taken"), false));
	objectives.Add(New<Objective>(S("rv_coat2_taken"), false));
	objectives.Add(New<Objective>(S("rv_shelf1_open"), false));
	objectives.Add(New<Objective>(S("rv_shelf2_open"), false));
	objectives.Add(New<Objective>(S("rv_aid_open"), false));
	objectives.Add(New<Objective>(S("rv_silver_taken"), false));
	objectives.Add(New<Objective>(S("rv_bandage_taken"), false));
	objectives.Add(New<Objective>(S("rv_generator_taken"), false));
	objectives.Add(New<Objective>(S("rv_blanket_taken"), false));
	objectives.Add(New<Objective>(S("rv_door_open"), false));
	objectives.Add(New<Objective>(S("rv_inspected"), false));
	objectives.Add(New<Objective>(S("rv_fueled"), false));
	objectives.Add(New<Objective>(S("rv_started"), false));
	objectives.Add(New<Objective>(S("rv_water3_taken"), false));
	objectives.Add(New<Objective>(S("rv_water4_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_roof_collapsed"), false));
	objectives.Add(New<Objective>(S("sidereal_roof_wait_for_rescue"), false));
	objectives.Add(New<Objective>(S("sidereal_roof_npc_shocked"), false));
	objectives.Add(New<Objective>(S("sidereal_roof_afterfall_talk"), false));
	objectives.Add(New<Objective>(S("sidereal_npc_found"), false));
	objectives.Add(New<Objective>(S("sidereal_npc_died"), false));
	objectives.Add(New<Objective>(S("sidereal_npc_buried"), false));
	objectives.Add(New<Objective>(S("sidereal_base_located"), false));
	objectives.Add(New<Objective>(S("sidereal_lucid_dreaming_discovered"), false));
	objectives.Add(New<Objective>(S("sidereal_vent_open"), false));
	objectives.Add(New<Objective>(S("sidereal_barry_pipe_moved"), false));
	objectives.Add(New<Objective>(S("sidereal_barry_door_open"), false));
	objectives.Add(New<Objective>(S("sidereal_cody_disk_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_barry_disk_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_exit_unlocked"), false));
	objectives.Add(New<Objective>(S("sidereal_elevator_f1_hosed"), false));
	objectives.Add(New<Objective>(S("sidereal_elevator_f1_open"), false));
	objectives.Add(New<Objective>(S("sidereal_elevator_f2_open"), false));
	objectives.Add(New<Objective>(S("sidereal_elevator_f3_open"), false));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_a"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_b"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_c"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_d"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_e"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_s_a"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_s_b"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_s_c"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_s_d"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_s_e"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_a1"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_a2"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_b1"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_b2"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_b3"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_c1"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_c2"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_d1"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_d2"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_d3"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_d4"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_e1"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_e2"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_e3"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_A"), true));
	objectives.Add(New<Objective>(S("sidereal_electric_pin_B"), true));
	objectives.Add(New<Objective>(S("sidereal_email_displayed"), false));
	objectives.Add(New<Objective>(S("sidereal_email_page"), false));
	objectives.Add(New<Objective>(S("sidereal_internet_displayed"), false));
	objectives.Add(New<Objective>(S("sidereal_papers_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_xero_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_secrets_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_keys_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_pipe_tried"), false));
	objectives.Add(New<Objective>(S("sidereal_f1c_s_open"), false));
	objectives.Add(New<Objective>(S("sidereal_f1c_b_open"), false));
	objectives.Add(New<Objective>(S("sidereal_f2c_b_open"), false));
	objectives.Add(New<Objective>(S("sidereal_f2c_b_unlocked"), false));
	objectives.Add(New<Objective>(S("sidereal_read_last_mail"), false));
	objectives.Add(New<Objective>(S("sidereal_read_cate_mail"), false));
	objectives.Add(New<Objective>(S("sidereal_mixer_b1"), false));
	objectives.Add(New<Objective>(S("sidereal_mixer_b2"), false));
	objectives.Add(New<Objective>(S("sidereal_mixer_b3"), false));
	objectives.Add(New<Objective>(S("sidereal_mixer_b4"), false));
	objectives.Add(New<Objective>(S("sidereal_mixer_b5"), false));
	objectives.Add(New<Objective>(S("sidereal_mixer_b6"), false));
	objectives.Add(New<Objective>(S("sidereal_mixer_mixed"), false));
	objectives.Add(New<Objective>(S("sidereal_components_1"), false));
	objectives.Add(New<Objective>(S("sidereal_components_2"), false));
	objectives.Add(New<Objective>(S("sidereal_vials1_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_vials2_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_disc1_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_disc2_taken"), false));
	objectives.Add(New<Objective>(S("sidereal_lab_open"), false));
	objectives.Add(New<Objective>(S("sidereal_finger_cut"), false));
	objectives.Add(New<Objective>(S("sidereal_silencer"), false));
	objectives.Add(New<Objective>(S("sidereal_lab_locked"), true));
	objectives.Add(New<Objective>(S("hunters_lodge_trap_cleared"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_trap_picked"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_scratches_found"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_couch_moved"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_horn_pulled"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_chest_opened"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_hatch_gun_taken"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_hatch_ammo1_taken"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_hatch_ammo2_taken"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_trap1_taken"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_trap2_taken"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_trap4_taken"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_scope_taken"), false));
	objectives.Add(New<Objective>(S("hunters_lodge_whiskey_taken"), false));
	objectives.Add(New<Objective>(S("lodge_board_taken"), false));
	objectives.Add(New<Objective>(S("gloves_taken"), false));
	objectives.Add(New<Objective>(S("cs_park_nogo"), false));
	objectives.Add(New<Objective>(S("cs_guard_distracted"), false));
	objectives.Add(New<Objective>(S("cs_crow_away"), false));
	objectives.Add(New<Objective>(S("cs_ammo_oiled"), false));
	objectives.Add(New<Objective>(S("cs_ammo_watered"), false));
	objectives.Add(New<Objective>(S("cs_food_poisioned"), false));
	objectives.Add(New<Objective>(S("cs_food_taken"), false));
	objectives.Add(New<Objective>(S("cs_thug_shot"), false));
	objectives.Add(New<Objective>(S("cs_bars_taken"), false));
	objectives.Add(New<Objective>(S("cs_arrive_from_inside"), false));
	objectives.Add(New<Objective>(S("constructionsite_from_above"), false));
	objectives.Add(New<Objective>(S("cs_rope_used"), false));
	objectives.Add(New<Objective>(S("cs_welder_taken"), false));
	objectives.Add(New<Objective>(S("cs_rain_enter_left"), false));
	objectives.Add(New<Objective>(S("cs_pack_lifted"), false));
	objectives.Add(New<Objective>(S("cs_wire_taken"), false));
	objectives.Add(New<Objective>(S("cs_engine_fueled"), false));
	objectives.Add(New<Objective>(S("cs_engine_started"), false));
	objectives.Add(New<Objective>(S("cs_crane_left"), false));
	objectives.Add(New<Objective>(S("cs_crane_down"), true));
	objectives.Add(New<Objective>(S("cs_crane_closed"), true));
	objectives.Add(New<Objective>(S("cs_cables_open"), false));
	objectives.Add(New<Objective>(S("cs_stormcatcher_installed"), false));
	objectives.Add(New<Objective>(S("cs_tarpaulin_taken"), false));
	objectives.Add(New<Objective>(S("cs_safe"), false));
	objectives.Add(New<Objective>(S("outpost_doormat_triggered"), false));
	objectives.Add(New<Objective>(S("outpost_doormat_first_time"), false));
	objectives.Add(New<Objective>(S("outpost_door_open"), false));
	objectives.Add(New<Objective>(S("outpost_fuse_11"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_12"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_13"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_14"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_15"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_21"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_22"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_23"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_24"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_25"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_31"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_32"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_33"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_34"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_35"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_41"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_42"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_43"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_44"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_45"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_51"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_52"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_53"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_54"), true));
	objectives.Add(New<Objective>(S("outpost_fuse_55"), true));
	objectives.Add(New<Objective>(S("outpost_radar_open"), false));
	objectives.Add(New<Objective>(S("outpost_radar_repaired"), false));
	objectives.Add(New<Objective>(S("outpost_doormat_just_disabled"), false));
	objectives.Add(New<Objective>(S("outpost_doormat_they_enter"), false));
	objectives.Add(New<Objective>(S("outpost_door_powered"), true));
	objectives.Add(New<Objective>(S("outpost_fusebox_open"), false));
	objectives.Add(New<Objective>(S("outpost_elevator_powered"), false));
	objectives.Add(New<Objective>(S("outpost_elevator_open"), false));
	objectives.Add(New<Objective>(S("outpost_elevator_up"), false));
	objectives.Add(New<Objective>(S("outpost_fuse_short_circuit"), false));
	objectives.Add(New<Objective>(S("outpost_elevator_travel"), false));
	objectives.Add(New<Objective>(S("outpost_underground_light"), false));
	objectives.Add(New<Objective>(S("outpost_fingerprint_unlocked"), false));
	objectives.Add(New<Objective>(S("outpost_storage_open"), false));
	objectives.Add(New<Objective>(S("outpost_switch_pressed"), false));
	objectives.Add(New<Objective>(S("outpost_remote_taken"), false));
	objectives.Add(New<Objective>(S("outpost_card_taken"), false));
	objectives.Add(New<Objective>(S("outpost_calibrator_taken"), false));
	objectives.Add(New<Objective>(S("outpost_filter_taken"), false));
	objectives.Add(New<Objective>(S("outpost_spaceship_discovered"), false));
	objectives.Add(New<Objective>(S("outpost_hall_unlocked"), false));
	objectives.Add(New<Objective>(S("outpost_hall_open"), false));
	objectives.Add(New<Objective>(S("outpost_control_room_open"), false));
	objectives.Add(New<Objective>(S("outpost_bars_a"), false, 50));
	objectives.Add(New<Objective>(S("outpost_bars_b"), false, 50));
	objectives.Add(New<Objective>(S("outpost_bars_c"), false, 50));
	objectives.Add(New<Objective>(S("outpost_bars_d"), false, 50));
	objectives.Add(New<Objective>(S("outpost_bars_e"), false, 50));
	objectives.Add(New<Objective>(S("outpost_score_a"), false));
	objectives.Add(New<Objective>(S("outpost_score_b"), false));
	objectives.Add(New<Objective>(S("outpost_score_c"), false));
	objectives.Add(New<Objective>(S("outpost_score_d"), false));
	objectives.Add(New<Objective>(S("outpost_score_e"), false));
	objectives.Add(New<Objective>(S("ship_toolbox_open"), false));
	objectives.Add(New<Objective>(S("ship_toolbox_searched"), false));
	objectives.Add(New<Objective>(S("ship_launched"), false));
	objectives.Add(New<Objective>(S("bus_fingerprint_molded"), false));
	objectives.Add(New<Objective>(S("bus_key_taken"), false));
	objectives.Add(New<Objective>(S("plane_undig"), false));
	objectives.Add(New<Objective>(S("moon_shocked1"), false));
	objectives.Add(New<Objective>(S("moon_shocked2"), false));
	objectives.Add(New<Objective>(S("moon_shocked3"), false));
	objectives.Add(New<Objective>(S("moon_suited_up"), false));
	objectives.Add(New<Objective>(S("moon_door_open"), false));
	objectives.Add(New<Objective>(S("moon_closet_open"), false));
	objectives.Add(New<Objective>(S("moon_talk_base_enter"), false));
	objectives.Add(New<Objective>(S("moon_allow_fast_travel_now"), false));
	objectives.Add(New<Objective>(S("moon_talk_pods"), false));
	objectives.Add(New<Objective>(S("moon_cody_sleeps"), false));
	objectives.Add(New<Objective>(S("moon_barry_sleeps"), false));
	objectives.Add(New<Objective>(S("moon_cate_sleeps"), false));
	objectives.Add(New<Objective>(S("moon_disc1_used"), false));
	objectives.Add(New<Objective>(S("moon_disc2_used"), false));
	objectives.Add(New<Objective>(S("moon_card_taken"), false));
	objectives.Add(New<Objective>(S("moon_card_used"), false));
	objectives.Add(New<Objective>(S("moon_console_unlocked"), false));
	objectives.Add(New<Objective>(S("pods_cosnole_inspected"), false));
	objectives.Add(New<Objective>(S("moon_pods_unlocked"), false));
	objectives.Add(New<Objective>(S("moon_light_failed"), false));
	objectives.Add(New<Objective>(S("moon_light_restored"), false));
	objectives.Add(New<Objective>(S("moon_ship_collapsed"), false));
	objectives.Add(New<Objective>(S("moon_window_cracked"), false));
	objectives.Add(New<Objective>(S("moon_door_closed"), false));
	objectives.Add(New<Objective>(S("moon_david_sleeps"), false));
	objectives.Add(New<Objective>(S("airlock_ring_1"), false, Random::Range(1, 6)));
	objectives.Add(New<Objective>(S("airlock_ring_2"), false, Random::Range(2, 5)));
	objectives.Add(New<Objective>(S("airlock_ring_3"), false, Random::Range(2, 5)));
	objectives.Add(New<Objective>(S("airlock_ring_4"), false, Random::Range(3, 4)));
	objectives.Add(New<Objective>(S("airlock_ring_5"), false, Random::Range(3, 4)));
	List<int> list = List<int>::New();
	list.Add(1);
	list.Add(2);
	list.Add(3);
	list.Add(4);
	list.Add(5);
	list.Add(6);
	list.Add(7);
	for (int i = 0; i < 20; i++)
	{
		int index = Random::Range(0, 7);
		list.Add(list[index]);
		list.RemoveAt(index);
	}
	objectives.Add(New<Objective>(S("plane_crate_1"), false, list[0]));
	objectives.Add(New<Objective>(S("plane_crate_2"), false, list[1]));
	objectives.Add(New<Objective>(S("plane_crate_3"), false, list[2]));
	objectives.Add(New<Objective>(S("plane_crate_4"), false, list[3]));
	objectives.Add(New<Objective>(S("plane_crate_5"), false, list[4]));
	objectives.Add(New<Objective>(S("plane_crate_6"), false, list[5]));
	objectives.Add(New<Objective>(S("plane_crate_7"), false, list[6]));
	objectives.Add(New<Objective>(S("plane_crate_1_taken"), false));
	objectives.Add(New<Objective>(S("plane_crate_2_taken"), false));
	objectives.Add(New<Objective>(S("plane_crate_3_taken"), false));
	objectives.Add(New<Objective>(S("plane_crate_4_taken"), false));
	objectives.Add(New<Objective>(S("plane_crate_5_taken"), false));
	objectives.Add(New<Objective>(S("plane_crate_6_taken"), false));
	objectives.Add(New<Objective>(S("plane_crate_7_taken"), false));
	objectives.Add(New<Objective>(S("plane_transponder_disabled"), false));
	objectives.Add(New<Objective>(S("plane_pilot_searched"), false));
	objectives.Add(New<Objective>(S("outpost_computer_part_taken"), false));
	objectives.Add(New<Objective>(S("outpost_hatch_open"), false));
	objectives.Add(New<Objective>(S("outpost_belt_hatch"), true));
	objectives.Add(New<Objective>(S("outpost_belt_elevator"), false));
	objectives.Add(New<Objective>(S("outpost_navigation_chip_inserted"), false));
	objectives.Add(New<Objective>(S("outpost_lioh_filters_inserted"), false));
	objectives.Add(New<Objective>(S("outpost_air_tanks_inserted"), false));
	objectives.Add(New<Objective>(S("outpost_calibrator_inserted"), false));
	objectives.Add(New<Objective>(S("outpost_cabinet_open"), false));
	objectives.Add(New<Objective>(S("outpost_catalyst_used"), false));
	objectives.Add(New<Objective>(S("outpost_hull_repaired_outside"), false));
	objectives.Add(New<Objective>(S("outpost_hull_repaired_inside"), false));
	objectives.Add(New<Objective>(S("mixer_note_taken"), false));
	objectives.Add(New<Objective>(S("plane_undig"), false));
	objectives.Add(New<Objective>(S("barry_pills_taken"), false));
	objectives.Add(New<Objective>(S("cody_pills_taken"), false));
	objectives.Add(New<Objective>(S("cate_pills_taken"), false));
	objectives.Add(New<Objective>(S("thug_to_kill_bathroom"), false));
	objectives.Add(New<Objective>(S("thug_killed_bathroom"), false));
	objectives.Add(New<Objective>(S("day4_started"), false));
	objectives.Add(New<Objective>(S("d4_intro"), false));
	objectives.Add(New<Objective>(S("lodge_cord_plugged"), false));
	objectives.Add(New<Objective>(S("lodge_cord_dragged"), false));
	objectives.Add(New<Objective>(S("lodge_cord_climbed"), false));
	objectives.Add(New<Objective>(S("lodge_tree_stormcatcher"), false));
	objectives.Add(New<Objective>(S("lodge_roof_cleaned"), false));
	objectives.Add(New<Objective>(S("lodge_broom_taken"), false));
	visited.Add(New<Objective>(S("visited_location1"), false));
	visited.Add(New<Objective>(S("visited_location2"), false));
	visited.Add(New<Objective>(S("visited_baseBathroom"), false));
	visited.Add(New<Objective>(S("visited_baseUpstairs"), false));
	visited.Add(New<Objective>(S("visited_baseOutside0"), false));
	visited.Add(New<Objective>(S("visited_baseOutside1"), false));
	visited.Add(New<Objective>(S("visited_baseOutside2"), false));
	visited.Add(New<Objective>(S("visited_baseOutside3"), false));
	visited.Add(New<Objective>(S("visited_barn"), false));
	visited.Add(New<Objective>(S("visited_crossroad"), false));
	visited.Add(New<Objective>(S("visited_bridge"), false));
	visited.Add(New<Objective>(S("visited_gasstation1"), false));
	visited.Add(New<Objective>(S("visited_gasstation2"), false));
	visited.Add(New<Objective>(S("visited_gasstationRoom1"), false));
	visited.Add(New<Objective>(S("visited_gasstationRoom2"), false));
	visited.Add(New<Objective>(S("visited_crashsite1"), false));
	visited.Add(New<Objective>(S("visited_crashsite2"), false));
	visited.Add(New<Objective>(S("visited_pestTruck"), false));
	visited.Add(New<Objective>(S("visited_attic1"), false));
	visited.Add(New<Objective>(S("visited_attic2"), false));
	visited.Add(New<Objective>(S("visited_roof1"), false));
	visited.Add(New<Objective>(S("visited_roof2"), false));
	visited.Add(New<Objective>(S("visited_house_b"), false));
	visited.Add(New<Objective>(S("visited_house_b_inside"), false));
	visited.Add(New<Objective>(S("visited_house_b_back"), false));
	visited.Add(New<Objective>(S("visited_restaurant_back"), false));
	visited.Add(New<Objective>(S("visited_restaurant_front"), false));
	visited.Add(New<Objective>(S("visited_restaurant_inside"), false));
	visited.Add(New<Objective>(S("visited_restaurant_kitchen"), false));
	visited.Add(New<Objective>(S("visited_restaurant_wc"), false));
	visited.Add(New<Objective>(S("visited_cave"), false));
	visited.Add(New<Objective>(S("visited_rv"), false));
	visited.Add(New<Objective>(S("visited_rv_inside"), false));
	visited.Add(New<Objective>(S("visited_hunters_lodge_1"), false));
	visited.Add(New<Objective>(S("visited_hunters_lodge_2"), false));
	visited.Add(New<Objective>(S("visited_hunters_lodge_outside_1"), false));
	visited.Add(New<Objective>(S("visited_hunters_lodge_outside_2"), false));
	visited.Add(New<Objective>(S("visited_sidereal_outside_1"), false));
	visited.Add(New<Objective>(S("visited_sidereal_outside_2"), false));
	visited.Add(New<Objective>(S("visited_sidereal_outside_3"), false));
	visited.Add(New<Objective>(S("visited_sidereal_roof"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f3c"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f3s"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f2s"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f2c"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f2b"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f1b"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f1s"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f1c"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f0c"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f0c0a"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f0s"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f0c1"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f0c2"), false));
	visited.Add(New<Objective>(S("visited_sidereal_f0c3"), false));
	visited.Add(New<Objective>(S("visited_sidereal_lab"), false));
	visited.Add(New<Objective>(S("visited_cs_1"), false));
	visited.Add(New<Objective>(S("visited_cs_2"), false));
	visited.Add(New<Objective>(S("visited_cs_3"), false));
	visited.Add(New<Objective>(S("visited_cs_4"), false));
	visited.Add(New<Objective>(S("visited_airplane1"), false));
	visited.Add(New<Objective>(S("visited_airplane2"), false));
	visited.Add(New<Objective>(S("visited_airplane3"), false));
	visited.Add(New<Objective>(S("visited_bus1"), false));
	visited.Add(New<Objective>(S("visited_bus2"), false));
	visited.Add(New<Objective>(S("visited_fusebox"), false));
	visited.Add(New<Objective>(S("visited_mixer"), false));
	visited.Add(New<Objective>(S("visited_outpost1"), false));
	visited.Add(New<Objective>(S("visited_outpost2"), false));
	visited.Add(New<Objective>(S("visited_outpost3"), false));
	visited.Add(New<Objective>(S("visited_outpost4"), false));
	visited.Add(New<Objective>(S("visited_outpost5"), false));
	visited.Add(New<Objective>(S("visited_outpost6"), false));
	visited.Add(New<Objective>(S("visited_outpost7"), false));
	visited.Add(New<Objective>(S("visited_outpost8"), false));
	visited.Add(New<Objective>(S("visited_outpost9"), false));
	visited.Add(New<Objective>(S("visited_outpost10"), false));
	visited.Add(New<Objective>(S("visited_outpost11"), false));
	visited.Add(New<Objective>(S("visited_ship1"), false));
	visited.Add(New<Objective>(S("visited_ship2"), false));
	visited.Add(New<Objective>(S("visited_moonbase1"), false));
	visited.Add(New<Objective>(S("visited_moonbase2"), false));
	visited.Add(New<Objective>(S("visited_moonbase3"), false));
	objectives.Add(New<Objective>(S("house_key_taken"), false));
	objectives.Add(New<Objective>(S("day1_complete"), false));
	objectives.Add(New<Objective>(S("day2_complete"), false));
	objectives.Add(New<Objective>(S("day3_complete"), false));
	objectives.Add(New<Objective>(S("day4_complete"), false));
	journals.Add(New<Objective>(S("journal_changed"), false));
	journals.Add(New<Objective>(S("day2_ginger"), false));
	journals.Add(New<Objective>(S("day2_barry"), false));
	journals.Add(New<Objective>(S("day2_cody"), false));
	journals.Add(New<Objective>(S("windows_blankets_1_d2"), false));
	journals.Add(New<Objective>(S("windows_blankets_2_d2"), false));
	journals.Add(New<Objective>(S("windows_blankets_3_d2"), false));
	journals.Add(New<Objective>(S("windows_foil_1_d2"), false));
	journals.Add(New<Objective>(S("windows_foil_2_d2"), false));
	journals.Add(New<Objective>(S("windows_foil_3_d2"), false));
	journals.Add(New<Objective>(S("hatch_blanket_d2"), false));
	journals.Add(New<Objective>(S("heat_absorber_base_1"), false));
	journals.Add(New<Objective>(S("heat_absorber_base_2"), false));
	journals.Add(New<Objective>(S("heat_absorber_base_3"), false));
	journals.Add(New<Objective>(S("house_ac"), false));
	journals.Add(New<Objective>(S("house_fan"), false));
	journals.Add(New<Objective>(S("cave_blanket_d2"), false));
	journals.Add(New<Objective>(S("cave_ac"), false));
	journals.Add(New<Objective>(S("cave_fan"), false));
	journals.Add(New<Objective>(S("rv_started"), false));
	journals.Add(New<Objective>(S("heat_absorber_cave_1"), false));
	journals.Add(New<Objective>(S("heat_absorber_cave_2"), false));
	journals.Add(New<Objective>(S("heat_absorber_cave_3"), false));
	journals.Add(New<Objective>(S("ginger_water"), false));
	journals.Add(New<Objective>(S("barry_water"), false));
	journals.Add(New<Objective>(S("cody_water"), false));
	journals.Add(New<Objective>(S("david_water"), false));
	journals.Add(New<Objective>(S("ginger_coat"), false));
	journals.Add(New<Objective>(S("barry_coat"), false));
	journals.Add(New<Objective>(S("cody_coat"), false));
	journals.Add(New<Objective>(S("david_coat"), false));
	journals.Add(New<Objective>(S("house_gasheater"), false));
	journals.Add(New<Objective>(S("house_oven"), false));
	journals.Add(New<Objective>(S("house_heater"), false));
	journals.Add(New<Objective>(S("day1_base"), false));
	journals.Add(New<Objective>(S("day1_sonic"), false));
	journals.Add(New<Objective>(S("day1_spider_trap11"), false));
	journals.Add(New<Objective>(S("day1_spider_trap22"), false));
	journals.Add(New<Objective>(S("day1_spider_trap1"), false));
	journals.Add(New<Objective>(S("day1_spider_trap2"), false));
	journals.Add(New<Objective>(S("day1_spray_pest"), false));
	journals.Add(New<Objective>(S("day1_spray_water_bugs"), false));
	journals.Add(New<Objective>(S("day1_spray_chem_gas"), false));
	journals.Add(New<Objective>(S("day1_spray_water_gas"), false));
	journals.Add(New<Objective>(S("day1_spray_water_spiders"), false));
	journals.Add(New<Objective>(S("day1_spray_pest_spiders"), false));
	journals.Add(New<Objective>(S("windows_net_1"), false));
	journals.Add(New<Objective>(S("windows_net_2"), false));
	journals.Add(New<Objective>(S("windows_net_3"), false));
	journals.Add(New<Objective>(S("windows_bars_1"), false));
	journals.Add(New<Objective>(S("windows_bars_2"), false));
	journals.Add(New<Objective>(S("windows_bars_3"), false));
	journals.Add(New<Objective>(S("windows_foil_1"), false));
	journals.Add(New<Objective>(S("windows_foil_2"), false));
	journals.Add(New<Objective>(S("windows_foil_3"), false));
	journals.Add(New<Objective>(S("day1_flamethrower"), false));
	journals.Add(New<Objective>(S("day1_pestspray"), false));
	journals.Add(New<Objective>(S("day1_rifle"), false));
	journals.Add(New<Objective>(S("day1_hazmat"), false));
	journals.Add(New<Objective>(S("day1_gas_density"), false));
	journals.Add(New<Objective>(S("day1_doors_towels"), false));
	journals.Add(New<Objective>(S("day1_doors"), false));
	journals.Add(New<Objective>(S("day3_funeral"), false));
	journals.Add(New<Objective>(S("day3_sidereal_arrive"), false));
	journals.Add(New<Objective>(S("day3_sidereal_lodge_location"), false));
	journals.Add(New<Objective>(S("day3_sidereal_outpost_location"), false));
	journals.Add(New<Objective>(S("day3_sidereal_barry_dead"), false));
	journals.Add(New<Objective>(S("day3_sidereal_cody_dead"), false));
	journals.Add(New<Objective>(S("day3_silencer_constructed"), false));
	journals.Add(New<Objective>(S("day3_sniper_constructed"), false));
	journals.Add(New<Objective>(S("day3_thugs_heard"), false));
	journals.Add(New<Objective>(S("day3_sarge_shot"), false));
	journals.Add(New<Objective>(S("day3_sarge_convinced"), false));
	journals.Add(New<Objective>(S("day3_guard_killed"), false));
	journals.Add(New<Objective>(S("day3_whiskey_left"), false));
	journals.Add(New<Objective>(S("day3_food_poisoned"), false));
	journals.Add(New<Objective>(S("day3_ammo_spoiled"), false));
	journals.Add(New<Objective>(S("day3_window_bars"), false));
	journals.Add(New<Objective>(S("day3_window_block"), false));
	journals.Add(New<Objective>(S("day3_traps"), false));
	journals.Add(New<Objective>(S("day3_rifle_rounds"), false));
	journals.Add(New<Objective>(S("day3_revolver_barry"), false));
	journals.Add(New<Objective>(S("day3_revolver_cody"), false));
	journals.Add(New<Objective>(S("day4_outpost_hulloutside"), false));
	journals.Add(New<Objective>(S("day4_outpost_catlyst"), false));
	journals.Add(New<Objective>(S("day4_outpost_calibrator"), false));
	journals.Add(New<Objective>(S("day4_outpost_navchip"), false));
	journals.Add(New<Objective>(S("day4_outpost_fuel_mixture"), false));
	journals.Add(New<Objective>(S("day4_outpost_catepills"), false));
	journals.Add(New<Objective>(S("day4_outpost_codypills"), false));
	journals.Add(New<Objective>(S("day4_outpost_barrypills"), false));
	journals.Add(New<Objective>(S("day4_outpost_hullinside"), false));
	journals.Add(New<Objective>(S("day4_outpost_airtanks"), false));
	journals.Add(New<Objective>(S("day4_outpost_lioh"), false));
	journals.Add(New<Objective>(S("day4_outpost_air_mixture"), false));
	journals.Add(New<Objective>(S("day4_hatch_open"), false));
	journals.Add(New<Objective>(S("day4_outpost_spaceship"), false));
	journals.Add(New<Objective>(S("day4_outpost_arrive"), false));
	journals.Add(New<Objective>(S("day4_razor_spared"), false));
	journals.Add(New<Objective>(S("day4_razor_killed"), false));
	journals.Add(New<Objective>(S("windows_boards_1"), false));
	journals.Add(New<Objective>(S("windows_boards_2"), false));
	journals.Add(New<Objective>(S("windows_boards_3"), false));
	objectives.Add(New<Objective>(S("npc1_alive"), true));
	objectives.Add(New<Objective>(S("dialogue_ginger_intro"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_dreams"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_dreams2"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_outpost"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_first_exit"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_base_comment"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_weather_comment"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_moon"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_car"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_ship"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_map"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_about"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_barry_distracted"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_reunited"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_dead_mourned"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_sidereal_arrival_outpost"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_sidereal_arrival_docs"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_sidereal_arrival_connections1"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_sidereal_arrival_connections2"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_thug_kill_waste"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_thug_kill_lesson"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_thug_kill_better"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_thug_kill_end_anyway"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_thug_kill_yes"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_thug_kill_no"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_fingerprint"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_moon_radio1"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_moon_radio2"), false));
	objectives.Add(New<Objective>(S("dialogue_moonbase2_sleeper_pods"), false));
	objectives.Add(New<Objective>(S("dialogue_moonbase2_body_dies"), false));
	objectives.Add(New<Objective>(S("dialogue_moonbase2_realm_of_dreams"), false));
	objectives.Add(New<Objective>(S("dialogue_moonbase2_intro"), false));
	objectives.Add(New<Objective>(S("dialogue_pods_intro"), false));
	objectives.Add(New<Objective>(S("dialogue_pods_phase_controller"), false));
	objectives.Add(New<Objective>(S("dialogue_pods_merge_mode"), false));
	objectives.Add(New<Objective>(S("dialogue_pods_loop1"), false));
	objectives.Add(New<Objective>(S("dialogue_pods_loop2"), false));
	objectives.Add(New<Objective>(S("dialogue_pods_paradox"), false));
	objectives.Add(New<Objective>(S("dialogue_pods_where"), false));
	objectives.Add(New<Objective>(S("dialogue_pods_lockdown"), false));
	objectives.Add(New<Objective>(S("dialogue_pods_emergency_mode"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_pills"), false));
	objectives.Add(New<Objective>(S("ginger_sidereal_reveal"), false));
	objectives.Add(New<Objective>(S("ginger_sidereal_why"), false));
	objectives.Add(New<Objective>(S("ginger_sidereal_else"), false));
	objectives.Add(New<Objective>(S("ginger_sidereal_ship"), false));
	objectives.Add(New<Objective>(S("ginger_sidereal_dreams"), false));
	objectives.Add(New<Objective>(S("ginger_moon_disk"), false));
	objectives.Add(New<Objective>(S("ginger_moon_disks"), false));
	objectives.Add(New<Objective>(S("npc2_joined"), false));
	objectives.Add(New<Objective>(S("npc2_alive"), true));
	objectives.Add(New<Objective>(S("dialogue_npc2_house_blocked"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_intro"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_come"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_come2"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_moon"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_wife"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_burial"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_burial2"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_ship"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_ginger1"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_ginger2"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_ginger3"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_cody1"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_cody2"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_cody3"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_cody_dead"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_cody_dead"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_cody1"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_cody2"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_cody3"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_barry1"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_barry2"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_barry3"), false));
	objectives.Add(New<Objective>(S("dialogue_ginger_barry_dead"), false));
	objectives.Add(New<Objective>(S("dialogue_barry_wife"), false));
	objectives.Add(New<Objective>(S("dialogue_barry_car0"), false));
	objectives.Add(New<Objective>(S("dialogue_barry_car1"), false));
	objectives.Add(New<Objective>(S("dialogue_barry_car2"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs1_cody"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs2_cody"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs3_cody"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs4_cody"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_storm1_cody"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs1_barry"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs2_barry"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs3_barry"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs4_barry"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_storm1_barry"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs1_cate"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs2_cate"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs3_cate"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_thugs4_cate"), false));
	objectives.Add(New<Objective>(S("dialogue_sarge_storm1_cate"), false));
	objectives.Add(New<Objective>(S("d4_kill_razor_cody"), false));
	objectives.Add(New<Objective>(S("d4_kill_razor_barry"), false));
	objectives.Add(New<Objective>(S("d4_kill_razor_cate"), false));
	objectives.Add(New<Objective>(S("d4_spare_razor_cody"), false));
	objectives.Add(New<Objective>(S("d4_spare_razor_barry"), false));
	objectives.Add(New<Objective>(S("d4_spare_razor_cate"), false));
	objectives.Add(New<Objective>(S("npc2_wife_note_given"), false));
	objectives.Add(New<Objective>(S("npc2_wife_burried"), false));
	objectives.Add(New<Objective>(S("npc2_hole_digged"), false));
	objectives.Add(New<Objective>(S("npc2_wife_dragged"), false));
	objectives.Add(New<Objective>(S("place_base_cate"), false));
	objectives.Add(New<Objective>(S("place_base_barry"), false));
	objectives.Add(New<Objective>(S("place_base_cody"), false));
	objectives.Add(New<Objective>(S("place_road_cate"), false));
	objectives.Add(New<Objective>(S("place_road_barry"), false));
	objectives.Add(New<Objective>(S("place_road_cody"), false));
	objectives.Add(New<Objective>(S("place_gas_station_cate"), false));
	objectives.Add(New<Objective>(S("place_gas_station_barry"), false));
	objectives.Add(New<Objective>(S("place_gas_station_cody"), false));
	objectives.Add(New<Objective>(S("place_restaurant_cate"), false));
	objectives.Add(New<Objective>(S("place_restaurant_barry"), false));
	objectives.Add(New<Objective>(S("place_restaurant_cody"), false));
	objectives.Add(New<Objective>(S("place_bhome_cate"), false));
	objectives.Add(New<Objective>(S("place_bhome_barry"), false));
	objectives.Add(New<Objective>(S("place_bhome_cody"), false));
	objectives.Add(New<Objective>(S("place_bhome2_cody"), false));
	objectives.Add(New<Objective>(S("place_rv_cate"), false));
	objectives.Add(New<Objective>(S("place_rv_barry"), false));
	objectives.Add(New<Objective>(S("place_rv_cody"), false));
	objectives.Add(New<Objective>(S("place_rv2_cate"), false));
	objectives.Add(New<Objective>(S("place_rv2_barry"), false));
	objectives.Add(New<Objective>(S("place_rv2_cody"), false));
	objectives.Add(New<Objective>(S("place_cave_cate"), false));
	objectives.Add(New<Objective>(S("place_cave_barry"), false));
	objectives.Add(New<Objective>(S("place_cave_cody"), false));
	objectives.Add(New<Objective>(S("place_sp_outside_cate"), false));
	objectives.Add(New<Objective>(S("place_sp_outside_barry"), false));
	objectives.Add(New<Objective>(S("place_sp_outside_cody"), false));
	objectives.Add(New<Objective>(S("place_sp_inside_cate"), false));
	objectives.Add(New<Objective>(S("place_sp_inside_barry"), false));
	objectives.Add(New<Objective>(S("place_sp_inside_cody"), false));
	objectives.Add(New<Objective>(S("place_construction1_cate"), false));
	objectives.Add(New<Objective>(S("place_construction1_barry"), false));
	objectives.Add(New<Objective>(S("place_construction1_cody"), false));
	objectives.Add(New<Objective>(S("place_construction2_cate"), false));
	objectives.Add(New<Objective>(S("place_construction2_barry"), false));
	objectives.Add(New<Objective>(S("place_construction2_cody"), false));
	objectives.Add(New<Objective>(S("place_hunters_cate"), false));
	objectives.Add(New<Objective>(S("place_hunters_barry"), false));
	objectives.Add(New<Objective>(S("place_hunters_cody"), false));
	objectives.Add(New<Objective>(S("place_hunters2_cody"), false));
	objectives.Add(New<Objective>(S("place_airplane_cate"), false));
	objectives.Add(New<Objective>(S("place_airplane_barry"), false));
	objectives.Add(New<Objective>(S("place_airplane_cody"), false));
	objectives.Add(New<Objective>(S("place_bus_cate"), false));
	objectives.Add(New<Objective>(S("place_bus_barry"), false));
	objectives.Add(New<Objective>(S("place_bus_cody"), false));
	objectives.Add(New<Objective>(S("place_outpost1_cate"), false));
	objectives.Add(New<Objective>(S("place_outpost1_barry"), false));
	objectives.Add(New<Objective>(S("place_outpost1_cody"), false));
	objectives.Add(New<Objective>(S("place_outpost2_cate"), false));
	objectives.Add(New<Objective>(S("place_outpost2_barry"), false));
	objectives.Add(New<Objective>(S("place_outpost2_cody"), false));
	objectives.Add(New<Objective>(S("place_moon0_cate"), false));
	objectives.Add(New<Objective>(S("place_moon0_barry"), false));
	objectives.Add(New<Objective>(S("place_moon0_cody"), false));
	objectives.Add(New<Objective>(S("place_moon1_cate"), false));
	objectives.Add(New<Objective>(S("place_moon1_barry"), false));
	objectives.Add(New<Objective>(S("place_moon1_cody"), false));
	objectives.Add(New<Objective>(S("place_moon2_cate"), false));
	objectives.Add(New<Objective>(S("place_moon2_barry"), false));
	objectives.Add(New<Objective>(S("place_moon2_cody"), false));
	objectives.Add(New<Objective>(S("place_bridge0_cate"), false));
	objectives.Add(New<Objective>(S("place_bridge0_barry"), false));
	objectives.Add(New<Objective>(S("place_bridge0_cody"), false));
	objectives.Add(New<Objective>(S("place_bridge1_cate"), false));
	objectives.Add(New<Objective>(S("place_bridge1_barry"), false));
	objectives.Add(New<Objective>(S("place_bridge1_cody"), false));
	objectives.Add(New<Objective>(S("place_bridge2_cate"), false));
	objectives.Add(New<Objective>(S("place_bridge2_barry"), false));
	objectives.Add(New<Objective>(S("place_bridge2_cody"), false));
	objectives.Add(New<Objective>(S("place_bridge3_cate"), false));
	objectives.Add(New<Objective>(S("place_bridge3_barry"), false));
	objectives.Add(New<Objective>(S("place_bridge3_cody"), false));
	objectives.Add(New<Objective>(S("d2_cold_cate"), false));
	objectives.Add(New<Objective>(S("d2_cold_barry"), false));
	objectives.Add(New<Objective>(S("d2_cold_cody"), false));
	objectives.Add(New<Objective>(S("d2_hot_cate"), false));
	objectives.Add(New<Objective>(S("d2_hot_barry"), false));
	objectives.Add(New<Objective>(S("d2_hot_cody"), false));
	objectives.Add(New<Objective>(S("d3_sidereal_cate"), false));
	objectives.Add(New<Objective>(S("d3_sidereal_barry"), false));
	objectives.Add(New<Objective>(S("d3_sidereal_cody"), false));
	objectives.Add(New<Objective>(S("d3_thugs_cate"), false));
	objectives.Add(New<Objective>(S("d3_thugs_barry"), false));
	objectives.Add(New<Objective>(S("d3_thugs_cody"), false));
	objectives.Add(New<Objective>(S("d3_storm_cate"), false));
	objectives.Add(New<Objective>(S("d3_storm_barry"), false));
	objectives.Add(New<Objective>(S("d3_storm_cody"), false));
	objectives.Add(New<Objective>(S("d4_ship_cate"), false));
	objectives.Add(New<Objective>(S("d4_ship_barry"), false));
	objectives.Add(New<Objective>(S("d4_ship_cody"), false));
	objectives.Add(New<Objective>(S("barry_base_welcome"), false));
	objectives.Add(New<Objective>(S("cody_base_welcome"), false));
	objectives.Add(New<Objective>(S("barry_base_family"), false));
	objectives.Add(New<Objective>(S("barry_cody_first_meet"), false));
	objectives.Add(New<Objective>(S("tutorial_tab"), false));
	objectives.Add(New<Objective>(S("place_sidereal_auto_barry"), false));
	objectives.Add(New<Objective>(S("place_sidereal_auto2_barry"), false));
	objectives.Add(New<Objective>(S("place_sidereal_auto_cody"), false));
	objectives.Add(New<Objective>(S("place_sidereal_auto2_cody"), false));
	objectives.Add(New<Objective>(S("helicopter_cody"), false));
	objectives.Add(New<Objective>(S("helicopter_barry"), false));
	objectives.Add(New<Objective>(S("cody_killed_someone"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_killed_bandit"), false));
	objectives.Add(New<Objective>(S("npc3_joined"), false));
	objectives.Add(New<Objective>(S("npc3_alive"), true));
	objectives.Add(New<Objective>(S("dialogue_cody_intro"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_parents"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_door_closed"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_come"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_age"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_door_opened"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_food_closed_given"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_food"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_moon"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_barry1"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_barry2"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_barry3"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_barry_dead"), false));
	objectives.Add(New<Objective>(S("dialogue_npc3_ginger1"), false));
	objectives.Add(New<Objective>(S("dialogue_npc3_ginger2"), false));
	objectives.Add(New<Objective>(S("dialogue_npc3_ginger3"), false));
	objectives.Add(New<Objective>(S("dialogue_npc3_ginger_dead"), false));
	objectives.Add(New<Objective>(S("dialogue_npc2_ginger_dead"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_orwhat"), false));
	objectives.Add(New<Objective>(S("dialogue_cody_tiger"), false));
	objectives.Add(New<Objective>(S("r_sarge_plans1"), false));
	objectives.Add(New<Objective>(S("r_sarge_plans2"), false));
	objectives.Add(New<Objective>(S("r_sarge_plans3"), false));
	objectives.Add(New<Objective>(S("r_sarge_wounded1"), false));
	objectives.Add(New<Objective>(S("r_sarge_wounded_bandage"), false));
	objectives.Add(New<Objective>(S("r_sarge_wounded_alcohol"), false));
	objectives.Add(New<Objective>(S("r_sarge_wounded2"), false));
	objectives.Add(New<Objective>(S("r_sarge_wounded3"), false));
	objectives.Add(New<Objective>(S("r_sarge_first_bye"), false));
	objectives.Add(New<Objective>(S("r_sarge_survive1"), false));
	objectives.Add(New<Objective>(S("r_sarge_gun"), false));
	objectives.Add(New<Objective>(S("r_sarge_ammo"), false));
	objectives.Add(New<Objective>(S("r_sarge_catcher"), false));
	objectives.Add(New<Objective>(S("r_sarge_catchers1"), false));
	objectives.Add(New<Objective>(S("r_sarge_catchers2"), false));
	objectives.Add(New<Objective>(S("r_sarge_catchers3"), false));
	objectives.Add(New<Objective>(S("r_paul_mount1"), false));
	objectives.Add(New<Objective>(S("r_paul_mount2"), false));
	objectives.Add(New<Objective>(S("r_paul_intro1"), false));
	objectives.Add(New<Objective>(S("r_paul_catchers1"), false));
	objectives.Add(New<Objective>(S("r_paul_catchers2"), false));
	objectives.Add(New<Objective>(S("r_paul_catchers4"), false));
	objectives.Add(New<Objective>(S("r_paul_catchers7"), false));
	objectives.Add(New<Objective>(S("r_paul_catchers_given"), false));
	objectives.Add(New<Objective>(S("r_paul_come1"), false));
	objectives.Add(New<Objective>(S("r_sarge_places1"), false));
	objectives.Add(New<Objective>(S("r_steve_you1"), false));
	objectives.Add(New<Objective>(S("r_steve_you5"), false));
	objectives.Add(New<Objective>(S("r_steve_come1"), false));
	objectives.Add(New<Objective>(S("r_steve_intro1"), false));
	objectives.Add(New<Objective>(S("r_mark_sarge1"), false));
	objectives.Add(New<Objective>(S("r_josh_sarge1"), false));
	objectives.Add(New<Objective>(S("r_mark_come1"), false));
	objectives.Add(New<Objective>(S("r_josh_come1"), false));
	objectives.Add(New<Objective>(S("chest_tutorial"), false));
	objectives.Add(New<Objective>(S("dream_tiger_intro"), false));
	objectives.Add(New<Objective>(S("dream_tiger_remember"), false));
	objectives.Add(New<Objective>(S("dream_tiger_who"), false));
	objectives.Add(New<Objective>(S("dream_tiger_cody"), false));
	objectives.Add(New<Objective>(S("dream_tiger_future"), false));
	objectives.Add(New<Objective>(S("dream_maggie_intro"), false));
	objectives.Add(New<Objective>(S("dream_maggie_remember"), false));
	objectives.Add(New<Objective>(S("dream_maggie_who"), false));
	objectives.Add(New<Objective>(S("dream_maggie_barry"), false));
	objectives.Add(New<Objective>(S("dream_maggie_future"), false));
	objectives.Add(New<Objective>(S("base_outside_dug"), false));
	objectives.Add(New<Objective>(S("lighting_rod_installed"), false));
	objectives.Add(New<Objective>(S("helicopter_covered"), false));
	objectives.Add(New<Objective>(S("helicopter_covered_taped"), false));
	objectives.Add(New<Objective>(S("barry_improved_car"), false));
	objectives.Add(New<Objective>(S("crossroads_left"), false));
	objectives.Add(New<Objective>(S("car_driven"), false));
	objectives.Add(New<Objective>(S("intro_skipped"), false));
	ItemsManager::im->initItems();
}


bool GameDataController::getObjective(String id)
{
	if (id.IndexOf(S("visited_")) != -1)
	{
		for (int i = 0; i < visited.Count(); i++)
		{
			if (visited[i]->id.Equals(id))
			{
				return visited[i]->state;
			}
		}
	}
	else
	{
		for (int j = 0; j < objectives.Count(); j++)
		{
			if (objectives[j]->id.Equals(id))
			{
				return objectives[j]->state;
			}
		}
	}
	return false;
}

int GameDataController::getObjectiveDetail(String id)
{
	if (id.IndexOf(S("visited_")) != -1)
	{
		for (int i = 0; i < visited.Count(); i++)
		{
			if (visited[i]->id.Equals(id))
			{
				return visited[i]->detail;
			}
		}
	}
	else
	{
		for (int j = 0; j < objectives.Count(); j++)
		{
			if (objectives[j]->id.Equals(id))
			{
				return objectives[j]->detail;
			}
		}
	}
	return -1;
}

bool GameDataController::getJournal(String id)
{
	for (int i = 0; i < journals.Count(); i++)
	{
		if (journals[i]->id.Equals(id))
		{
			return journals[i]->state;
		}
	}
	return false;
}

int GameDataController::getJournalDetail(String id)
{
	for (int i = 0; i < journals.Count(); i++)
	{
		if (journals[i]->id.Equals(id))
		{
			return journals[i]->detail;
		}
	}
	return -100;
}

void GameDataController::setJournal(String id, bool state)
{
	for (int i = 0; i < journals.Count(); i++)
	{
		if (journals[i]->id.Equals(id))
		{
			journals[i]->state = state;
		}
	}
}

void GameDataController::setJournalDetail(String id, int detail)
{
	for (int i = 0; i < journals.Count(); i++)
	{
		if (journals[i]->id.Equals(id))
		{
			journals[i]->detail = detail;
		}
	}
}

int GameDataController::getObjectiveIndex(String id)
{
	if (id.IndexOf(S("visited_")) != -1)
	{
		for (int i = 0; i < visited.Count(); i++)
		{
			if (visited[i]->id.Equals(id))
			{
				return i;
			}
		}
	}
	else
	{
		for (int j = 0; j < objectives.Count(); j++)
		{
			if (objectives[j]->id.Equals(id))
			{
				return j;
			}
		}
	}
	return -1;
}

void GameDataController::setObjective(String id, bool state)
{
	if (id.IndexOf(S("visited_")) != -1)
	{
		for (int i = 0; i < visited.Count(); i++)
		{
			if (visited[i]->id.Equals(id))
			{
				visited[i]->state = state;
			}
		}
	}
	else
	{
		for (int j = 0; j < objectives.Count(); j++)
		{
			if (objectives[j]->id.Equals(id))
			{
				objectives[j]->state = state;
			}
		}
	}
	if (!s_journalHold) JournalTexts::pickTexts(gd->getCurrentDay());   // Vita port: skipped while Load copies a save
}

bool GameDataController::saveIfOK(String sciezka)
{
	if (sciezka == String::Empty)
	{
		sciezka = CONTINUE;
	}
	if (isOKtoSave(sciezka))
	{
		if (sciezka != CONTINUE)
		{
			ScreenShots::ss->shotAndSave(sciezka);
		}
		Save(sciezka);
		return true;
	}
	return false;
}

bool GameDataController::isOKtoSave(String sciezka)
{
	bool result = true;
	if (SceneManager::GetActiveScene().get_name() == S("PauseMenu") || SceneManager::GetActiveScene().get_name() == S("ChapterResults") || SceneManager::GetActiveScene().get_name() == S("LocationBugDeath") || SceneManager::GetActiveScene().get_name() == S("LocationCh2Death") || SceneManager::GetActiveScene().get_name() == S("PauseMenu") || SceneManager::GetActiveScene().get_name() == S("InfoLocation") || SceneManager::GetActiveScene().get_name() == S("sky_paralax") || SceneManager::GetActiveScene().get_name() == S("LocationDesertTitle") || SceneManager::GetActiveScene().get_name() == S("DEMO_START") || SceneManager::GetActiveScene().get_name() == S("MainMenu") || SceneManager::GetActiveScene().get_name() == S("LocationTent2") || SceneManager::GetActiveScene().get_name() == S("Ending1") || SceneManager::GetActiveScene().get_name() == S("Ending2") || SceneManager::GetActiveScene().get_name() == S("Ending3") || SceneManager::GetActiveScene().get_name() == S("Ending4") || SceneManager::GetActiveScene().get_name() == S("Ending5") || SceneManager::GetActiveScene().get_name() == S("Credits") || SceneManager::GetActiveScene().get_name() == S("SonicRemote") || SceneManager::GetActiveScene().get_name() == S("Dream3B") || SceneManager::GetActiveScene().get_name() == S("FontSelector") || SceneManager::GetActiveScene().get_name() == S("LocationMap"))
	{
		result = false;
	}
	if (gd->getObjective(S("moon_david_sleeps")))
	{
		result = false;
	}
	if (!DialogueController::dc->hidden && sciezka == CONTINUE)
	{
		result = false;
	}
	if (DialogueController::dc->talking && sciezka == CONTINUE)
	{
		result = false;
	}
	if (sciezka == CONTINUE && (PlayerController::pc->dialogue != PlayerController::DialogueState::NONE || (Timeline::t->actions != nullptr && Timeline::t->actions.Count() > 0)))
	{
		result = false;
	}
	if (SceneManager::GetActiveScene().get_name() == S("SaveMenu") && sciezka.IndexOf(S("autosave")) != -1)
	{
		result = false;
	}
	return result;
}

void GameDataController::setObjectiveDetail(String id, int detail)
{
	if (id.IndexOf(S("visited_")) != -1)
	{
		for (int i = 0; i < visited.Count(); i++)
		{
			if (visited[i]->id.Equals(id))
			{
				visited[i]->detail = detail;
			}
		}
	}
	else
	{
		for (int j = 0; j < objectives.Count(); j++)
		{
			if (objectives[j]->id.Equals(id))
			{
				objectives[j]->detail = detail;
			}
		}
	}
	if (id.IndexOf(S("chitchat")) == -1 && !s_journalHold)   // Vita port: skipped while Load copies a save
	{
		JournalTexts::pickTexts(gd->getCurrentDay());
	}
}

P<ItemData> GameDataController::getItemData(String id)
{
	for (int i = 0; i < items.Count(); i++)
	{
		if (items[i]->id.Equals(id))
		{
			return items[i];
		}
	}
	return nullptr;
}

void GameDataController::autoSave()
{
	saveIfOK(AUTOSAVE);
}

void GameDataController::PersistentSave()
{
	String text = S("core_save");
	BinaryFormatter binaryFormatter;
	P<FileStream> fileStream = File::Open(Application::get_persistentDataPath() + S("/") + text, FileMode::OpenOrCreate);
	P<PersistentData> persistentData = New<PersistentData>();
	persistentData->chapter1_locust = GameDataController::persistentData->chapter1_locust;
	persistentData->chapter1_gas = GameDataController::persistentData->chapter1_gas;
	persistentData->chapter1_spiders = GameDataController::persistentData->chapter1_spiders;
	persistentData->chapter2_cold = GameDataController::persistentData->chapter2_cold;
	persistentData->chapter2_hot = GameDataController::persistentData->chapter2_hot;
	persistentData->chapter3_bandits = GameDataController::persistentData->chapter3_bandits;
	persistentData->chapter3_thunderstorm = GameDataController::persistentData->chapter3_thunderstorm;
	persistentData->chapter4_air = GameDataController::persistentData->chapter4_air;
	persistentData->chapter4_fuel = GameDataController::persistentData->chapter4_fuel;
	persistentData->disc_barry = GameDataController::persistentData->disc_barry;
	persistentData->disc_cody = GameDataController::persistentData->disc_cody;
	persistentData->kong_car = GameDataController::persistentData->kong_car;
	persistentData->kong_disk = GameDataController::persistentData->kong_disk;
	persistentData->kong_game = GameDataController::persistentData->kong_game;
	persistentData->custom_unlocked = GameDataController::persistentData->custom_unlocked;
	persistentData->achievements = List<P<Objective>>::New();
	for (int i = 0; i < GameDataController::persistentData->achievements.Count(); i++)
	{
		persistentData->achievements.Add(New<Objective>(GameDataController::persistentData->achievements[i]->id, GameDataController::persistentData->achievements[i]->state));
	}
	binaryFormatter.Serialize(fileStream, persistentData);
	fileStream->Close();
}

void GameDataController::PersistentLoad()
{
	String text = S("core_save");
	if (File::Exists(Application::get_persistentDataPath() + S("/") + text))
	{
		BinaryFormatter binaryFormatter;
		P<FileStream> fileStream = File::Open(Application::get_persistentDataPath() + S("/") + text, FileMode::OpenOrCreate);
		P<PersistentData> persistentData = binaryFormatter.Deserialize<PersistentData>(fileStream);
		GameDataController::persistentData->chapter1_locust = persistentData->chapter1_locust;
		GameDataController::persistentData->chapter1_gas = persistentData->chapter1_gas;
		GameDataController::persistentData->chapter1_spiders = persistentData->chapter1_spiders;
		GameDataController::persistentData->chapter2_cold = persistentData->chapter2_cold;
		GameDataController::persistentData->chapter2_hot = persistentData->chapter2_hot;
		GameDataController::persistentData->chapter3_bandits = persistentData->chapter3_bandits;
		GameDataController::persistentData->chapter3_thunderstorm = persistentData->chapter3_thunderstorm;
		GameDataController::persistentData->chapter4_air = persistentData->chapter4_air;
		GameDataController::persistentData->chapter4_fuel = persistentData->chapter4_fuel;
		GameDataController::persistentData->disc_barry = persistentData->disc_barry;
		GameDataController::persistentData->disc_cody = persistentData->disc_cody;
		GameDataController::persistentData->kong_car = persistentData->kong_car;
		GameDataController::persistentData->kong_disk = persistentData->kong_disk;
		GameDataController::persistentData->kong_game = persistentData->kong_game;
		GameDataController::persistentData->custom_unlocked = persistentData->custom_unlocked;
		GameDataController::persistentData->achievements = List<P<Objective>>::New();
		if (persistentData->achievements == nullptr)
		{
			initPersistantAchieves();
		}
		else
		{
			for (int i = 0; i < persistentData->achievements.Count(); i++)
			{
				GameDataController::persistentData->achievements.Add(New<Objective>(persistentData->achievements[i]->id, persistentData->achievements[i]->state));
			}
		}
		fileStream->Close();
	}
	else
	{
		GameDataController::persistentData = New<PersistentData>();
		GameDataController::persistentData->chapter1_locust = false;
		GameDataController::persistentData->chapter1_gas = false;
		GameDataController::persistentData->chapter1_spiders = false;
		GameDataController::persistentData->chapter2_cold = false;
		GameDataController::persistentData->chapter2_hot = false;
		GameDataController::persistentData->chapter3_bandits = false;
		GameDataController::persistentData->chapter3_thunderstorm = false;
		GameDataController::persistentData->chapter4_air = false;
		GameDataController::persistentData->chapter4_fuel = false;
		GameDataController::persistentData->disc_barry = false;
		GameDataController::persistentData->disc_cody = false;
		GameDataController::persistentData->kong_car = false;
		GameDataController::persistentData->kong_disk = false;
		GameDataController::persistentData->kong_game = false;
		GameDataController::persistentData->custom_unlocked = false;
		initPersistantAchieves();
		PersistentSave();
	}
}

void GameDataController::initPersistantAchieves()
{
	persistentData->achievements = List<P<Objective>>::New();
	persistentData->achievements.Add(New<Objective>(S("DAY_1"), false));
	persistentData->achievements.Add(New<Objective>(S("DAY_2"), false));
	persistentData->achievements.Add(New<Objective>(S("DAY_3"), false));
	persistentData->achievements.Add(New<Objective>(S("DAY_4"), false));
	persistentData->achievements.Add(New<Objective>(S("ENDING_1"), false));
	persistentData->achievements.Add(New<Objective>(S("ENDING_2"), false));
	persistentData->achievements.Add(New<Objective>(S("ENDING_3"), false));
	persistentData->achievements.Add(New<Objective>(S("P_LOCUST"), false));
	persistentData->achievements.Add(New<Objective>(S("P_GAS"), false));
	persistentData->achievements.Add(New<Objective>(S("P_SPIDERS"), false));
	persistentData->achievements.Add(New<Objective>(S("P_COLD"), false));
	persistentData->achievements.Add(New<Objective>(S("P_HEAT"), false));
	persistentData->achievements.Add(New<Objective>(S("P_BANDITS"), false));
	persistentData->achievements.Add(New<Objective>(S("P_STORM"), false));
	persistentData->achievements.Add(New<Objective>(S("P_AIR"), false));
	persistentData->achievements.Add(New<Objective>(S("P_FUEL"), false));
	persistentData->achievements.Add(New<Objective>(S("S_GRAVE"), false));
	persistentData->achievements.Add(New<Objective>(S("S_BIRD"), false));
	persistentData->achievements.Add(New<Objective>(S("S_TREASURE"), false));
	persistentData->achievements.Add(New<Objective>(S("S_SNOWMAN"), false));
	persistentData->achievements.Add(New<Objective>(S("S_TOUR"), false));
	persistentData->achievements.Add(New<Objective>(S("S_FAMILY"), false));
	persistentData->achievements.Add(New<Objective>(S("S_WOLF"), false));
	persistentData->achievements.Add(New<Objective>(S("S_WALKING"), false));
	persistentData->achievements.Add(New<Objective>(S("S_PYRO"), false));
}

void GameDataController::Save(String path)
{
	BinaryFormatter binaryFormatter;
	P<FileStream> fileStream = File::Open(Application::get_persistentDataPath() + S("/") + path, FileMode::OpenOrCreate);
	MonoBehaviour::print(S("SAVING GAME...... ") + path + S(" ") + SceneManager::GetActiveScene().get_name());
	P<SaveData> saveData = New<SaveData>();
	saveData->objectives = gd->objectives;
	saveData->journals = gd->journals;
	saveData->visited = gd->visited;
	saveData->items = gd->items;
	saveData->gameTime = gd->gameTime;
	saveData->timeLimit = gd->timeLimit;
	saveData->gameDay = gd->getCurrentDay();
	saveData->dateTime = DateTime::Now();
	saveData->traveledTime = gd->traveledTime;
	saveData->workedTime = gd->workedTime;
	saveData->journalEntries = journalEntries;
	gd->location = SceneManager::GetActiveScene().get_name();
	if (gd->location != S("SaveMenu"))
	{
		saveData->location = gd->location;
		saveData->usedSpawner = gd->usedSpawner;
		gd->currentX = (int)PlayerController::wc->currentXY.x;
		gd->currentY = (int)PlayerController::wc->currentXY.y;
	}
	else
	{
		saveData->location = gd->previousLocation;
		saveData->usedSpawner = gd->usedSpawner;
		gd->currentX = gd->previousX;
		gd->currentY = gd->previousY;
	}
	saveData->currentX = gd->currentX;
	saveData->currentY = gd->currentY;
	saveData->previousX = gd->previousX;
	saveData->previousY = gd->previousY;
	saveData->previousLocation = gd->previousLocation;
	saveData->finishingLocation = gd->finishingLocation;
	binaryFormatter.Serialize(fileStream, saveData);
	fileStream->Close();
	MonoBehaviour::print(S("FILE SAVED"));
}

void GameDataController::politeLoad(String path)
{
	CurtainController::cc->fadeOut(S("LOAD"), WalkController::Direction::NULL_, path);
}

void GameDataController::tryLoad(String path, bool autosaveInstead)
{
	gd->newGame();
	if (!gd->Load(path))
	{
		if (autosaveInstead)
		{
			gd->Load(S("autosave0"));
			return;
		}
		gd->Load(path);
		PlayerController::pc->spawnName = S("InfoExit");
		CurtainController::cc->fadeOut(S("LocationDreamBugs"), WalkController::Direction::N);
	}
}

bool GameDataController::checkSave(String path)
{
	if (File::Exists(Application::get_persistentDataPath() + S("/") + path))
	{
		return true;
	}
	return false;
}

P<SaveData> GameDataController::getSavePreview(String path)
{
	if (File::Exists(Application::get_persistentDataPath() + S("/") + path))
	{
		BinaryFormatter binaryFormatter;
		P<FileStream> fileStream = File::Open(Application::get_persistentDataPath() + S("/") + path, FileMode::Open);
		P<SaveData> result = binaryFormatter.Deserialize<SaveData>(fileStream);
		fileStream->Close();
		return result;
	}
	return nullptr;
}

bool GameDataController::Load(String path)
{
	MonoBehaviour::print(S("Loading file ") + Application::get_persistentDataPath() + S("/") + path);
	if (File::Exists(Application::get_persistentDataPath() + S("/") + path))
	{
		if (InventoryController::ic != nullptr && items != nullptr)
		{
			InventoryController::ic->clearInventory();
		}
		BinaryFormatter binaryFormatter;
		P<FileStream> fileStream = File::Open(Application::get_persistentDataPath() + S("/") + path, FileMode::Open);
		P<SaveData> saveData = binaryFormatter.Deserialize<SaveData>(fileStream);
		gd->currentX = saveData->currentX;
		gd->currentY = saveData->currentY;
		gd->previousX = saveData->currentX;
		gd->previousY = saveData->currentY;
		gd->location = saveData->location;
		gd->usedSpawner = saveData->usedSpawner;
		gd->journalEntries = saveData->journalEntries;
		PlayerController::pc->spawnName = S("previous");
		{ JournalHold hold;   // Vita port
		for (int i = 0; i < saveData->visited.Count(); i++)
		{
			gd->setObjective(saveData->visited[i]->id, saveData->visited[i]->state);
			gd->setObjectiveDetail(saveData->visited[i]->id, saveData->visited[i]->detail);
		}
		for (int j = 0; j < saveData->objectives.Count(); j++)
		{
			gd->setObjective(saveData->objectives[j]->id, saveData->objectives[j]->state);
			gd->setObjectiveDetail(saveData->objectives[j]->id, saveData->objectives[j]->detail);
		}
		}
		for (int k = 0; k < saveData->journals.Count(); k++)
		{
			gd->setJournal(saveData->journals[k]->id, saveData->journals[k]->state);
			gd->setJournalDetail(saveData->journals[k]->id, saveData->journals[k]->detail);
		}
		for (int l = 0; l < saveData->items.Count(); l++)
		{
			gd->getItemData(saveData->items[l]->id)->droppedLocation = saveData->items[l]->droppedLocation;
			gd->getItemData(saveData->items[l]->id)->locX = saveData->items[l]->locX;
			gd->getItemData(saveData->items[l]->id)->locY = saveData->items[l]->locY;
		}
		gd->gameTime = saveData->gameTime;
		gd->timeLimit = saveData->timeLimit;
		gd->traveledTime = saveData->traveledTime;
		gd->workedTime = saveData->workedTime;
		gd->finishingLocation = saveData->finishingLocation;
		ItemsManager::im->initItems();
		if (gd->currentX != 0 && gd->currentY != 0)
		{
			PlayerController::wc->currentXY.x = (float)gd->currentX;
			PlayerController::wc->currentXY.y = (float)gd->currentY;
		}
		MonoBehaviour::print(S("SAVED SCENE : ") + gd->location);
		fileStream->Close();
		gd->previousLocation = String::Empty;
		MonoBehaviour::print(S("FILE LOADED"));
		ItemsManager::im->initItems();
		InventoryController::ic->maxCapacity = 30;
		if (gd->getObjectiveDetail(S("day1_complete")) == 1)
		{
			InventoryController::ic->maxCapacity += 5;
		}
		if (gd->getObjectiveDetail(S("day2_complete")) == 1)
		{
			InventoryController::ic->maxCapacity += 5;
		}
		if (gd->getObjectiveDetail(S("day3_complete")) == 1)
		{
			InventoryController::ic->maxCapacity += 5;
		}
		JournalTexts::pickTexts(gd->getCurrentDay());
		if (gd->location != nullptr && gd->location.Length() > 0 && !SceneManager::GetActiveScene().get_name().Equals(gd->location))
		{
			MonoBehaviour::print(S("LOADING SCENE : ") + gd->location);
			CurtainController::cc->loadScene(gd->location);
			return true;
		}
		return false;
	}
	MonoBehaviour::print(S("FILE NOT FOUND - NO FILE LOADED"));
	return false;
}

int GameDataController::getCurrentDay()
{
	if (!gd->getObjective(S("day1_complete")))
	{
		return 1;
	}
	if (!gd->getObjective(S("day2_complete")))
	{
		return 2;
	}
	if (!gd->getObjective(S("day3_complete")))
	{
		return 3;
	}
	if (!gd->getObjective(S("day4_complete")))
	{
		return 4;
	}
	return 5;
}

#include "../game_all.h"

void JournalTexts::Start()
{
}

void JournalTexts::Update()
{
}

bool JournalTexts::anotherText(String condition, String text)
{
	return anotherText(GameDataController::gd->getObjective(condition), text, String::Empty);
}

int JournalTexts::findOldestJournalEntry()
{
	if (GameDataController::gd->journals.Count() == 0)
	{
		return 0;
	}
	Array<int> array = Array<int>::New(GameDataController::gd->journals.Count());
	for (int i = 0; i < GameDataController::gd->journals.Count(); i++)
	{
		array[i] = GameDataController::gd->journals[i]->detail - GameDataController::gd->getCurrentDay() * 10000000 - GameDataController::gd->gameTime * 1000;
		if (array[i] < 0)
		{
			array[i] = 0;
		}
	}
	return *std::max_element(array.vec().begin(), array.vec().end());
}

bool JournalTexts::anotherText(bool condition, String text, String text2)
{
	if (GameDataController::gd->getJournalDetail(text) == -100)
	{
		MonoBehaviour::print(S("MISSING JOURNAL DATA FOR ") + text);
		GameDataController::gd->journals.Add(New<Objective>(text, false));
	}
	if (condition)
	{
		if (GameDataController::gd->getJournalDetail(String::Empty + text) > 0 && GameDataController::gd->getJournalDetail(String::Empty + text) < 10000000)
		{
			GameDataController::gd->setJournalDetail(text, GameDataController::gd->getJournalDetail(String::Empty + text) * 1000);
		}
		if (GameDataController::gd->getJournalDetail(String::Empty + text) == 0)
		{
			int num = findOldestJournalEntry() + 1;
			if (num > 999)
			{
				num = 999;
			}
			GameDataController::gd->setJournalDetail(String::Empty + text, GameDataController::gd->gameTime * 1000 + GameDataController::gd->getCurrentDay() * 10000000 + num);
			GameDataController::gd->setJournalDetail(S("journal_changed"), 1);
		}
		else if (GameDataController::gd->getJournalDetail(String::Empty + text) < GameDataController::gd->getCurrentDay() * 10000000)
		{
			GameDataController::gd->setJournalDetail(String::Empty + text, -1);
		}
		MonoBehaviour::print(S("CREATING NEW JOURNAL TIME ITEM: ") + text + S(" | ") + GameDataController::gd->getJournalDetail(String::Empty + text));
		if (text2 == String::Empty)
		{
			text2 = text;
		}
		journalTimeItems.Add(New<Objective>(text2, false, GameDataController::gd->getJournalDetail(String::Empty + text) - GameDataController::gd->getCurrentDay() * 10000000));
		return true;
	}
	if (GameDataController::gd->getJournalDetail(String::Empty + text) != 0)
	{
		GameDataController::gd->setJournalDetail(String::Empty + text, 0);
	}
	return false;
}

String JournalTexts::pickTexts(int chapter, bool updateNumber)
{
	textToType = String::Empty;
	textToType2 = String::Empty;
	journalTimeItems = List<P<Objective>>::New();
	if (chapter == 1)
	{
		textToType = chapter1Texts();
	}
	if (chapter == 2)
	{
		textToType = chapter2Texts();
	}
	if (chapter == 3)
	{
		textToType = chapter3Texts();
	}
	if (chapter == 4)
	{
		textToType = chapter4Texts();
	}
	journalTimeItems.Sort([](const P<Objective>& x, const P<Objective>& y) -> int
	{
		if (x->detail > y->detail)
		{
			return 1;
		}
		return (x->detail < y->detail) ? (-1) : 0;
	});
	int num = -10;
	bool flag = false;
	for (int num2 = 0; num2 < journalTimeItems.Count(); num2++)
	{
		if (journalTimeItems[num2]->detail < 0)
		{
			flag = true;
		}
	}
	if (flag)
	{
		textToType = textToType + S(" ^ ") + GameStrings::getString(GameStrings::journal, S("yesterday"));
	}
	for (int num3 = 0; num3 < journalTimeItems.Count(); num3++)
	{
		if (journalTimeItems[num3]->detail < 0)
		{
			textToType = textToType + S(" ^ ") + GameStrings::getString(GameStrings::gui, S("journal_bullet")) + GameStrings::getString(GameStrings::journal, journalTimeItems[num3]->id);
		}
	}
	for (int num4 = 0; num4 < journalTimeItems.Count(); num4++)
	{
		if (journalTimeItems[num4]->detail > 0)
		{
			textToType += S(" ^ ^");
			if (num != journalTimeItems[num4]->detail / 1000)
			{
				textToType = textToType + ClockController::getClockTime(journalTimeItems[num4]->detail / 1000) + S(" ^");
				num = journalTimeItems[num4]->detail / 1000;
			}
			textToType = textToType + GameStrings::getString(GameStrings::gui, S("journal_bullet")) + GameStrings::getString(GameStrings::journal, journalTimeItems[num4]->id);
		}
	}
	textToType = textToType + S(" ^ ^ ") + textToType2;
	if (!updateNumber)
	{
		if (jbc == nullptr)
		{
			P<GameObject> gameObject = GameObject::Find(S("journal"));
			if (gameObject != nullptr)
			{
				jbc = gameObject->GetComponent<JournalButtonController>();
			}
		}
		if (jbc != nullptr)
		{
			if (GameDataController::gd->getJournalDetail(S("journal_changed")) == 1)
			{
				MonoBehaviour::print(S("JOURNAL WARNING VISIBLE"));
				jbc->setWarning(true);
			}
			else
			{
				jbc->setWarning(false);
			}
		}
	}
	return textToType;
}

String JournalTexts::chapter4Texts()
{
	textToType = GameStrings::getString(GameStrings::journal, S("entry_intro_day4_intro"));
	bool flag = false;
	if (!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2 && GameDataController::gd->getObjective(S("npc3_joined")))
	{
		textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("entry_intro_day4_cody_dead"));
		flag = true;
	}
	if (!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2 && GameDataController::gd->getObjective(S("npc2_joined")))
	{
		flag = true;
		textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("entry_intro_day4_barry_dead"));
	}
	if (flag)
	{
		if (!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2 && GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2 && GameDataController::gd->getObjective(S("npc3_joined")))
		{
			textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("day4_funeral_a"));
		}
		else
		{
			textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("day4_funeral_b"));
		}
	}
	textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("entry_intro_day4_both"));
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		anotherText(!GameDataController::gd->getObjective(S("thug_to_kill_bathroom")) && GameDataController::gd->getObjective(S("thug_killed_bathroom")), S("day4_razor_killed"), String::Empty);
		anotherText(!GameDataController::gd->getObjective(S("thug_to_kill_bathroom")) && !GameDataController::gd->getObjective(S("thug_killed_bathroom")), S("day4_razor_spared"), String::Empty);
	}
	anotherText(S("visited_outpost1"), S("day4_outpost_arrive"));
	anotherText(S("visited_outpost5"), S("day4_outpost_spaceship"));
	anotherText(S("outpost_hatch_open"), S("day4_hatch_open"));
	int num = 0;
	num += GameDataController::gd->getObjectiveDetail(S("outpost_score_a"));
	num += GameDataController::gd->getObjectiveDetail(S("outpost_score_b"));
	num += GameDataController::gd->getObjectiveDetail(S("outpost_score_c"));
	num += GameDataController::gd->getObjectiveDetail(S("outpost_score_d"));
	num += GameDataController::gd->getObjectiveDetail(S("outpost_score_e"));
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
	{
		anotherText(num > 0, S("day4_outpost_air_mixture"), String::Empty);
		anotherText(S("outpost_lioh_filters_inserted"), S("day4_outpost_lioh"));
		anotherText(S("outpost_air_tanks_inserted"), S("day4_outpost_airtanks"));
		anotherText(S("outpost_hull_repaired_inside"), S("day4_outpost_hullinside"));
		anotherText(S("barry_pills_taken"), S("day4_outpost_barrypills"));
		anotherText(S("cody_pills_taken"), S("day4_outpost_codypills"));
		anotherText(S("cate_pills_taken"), S("day4_outpost_catepills"));
	}
	else
	{
		anotherText(num > 0, S("day4_outpost_fuel_mixture"), String::Empty);
		anotherText(S("outpost_navigation_chip_inserted"), S("day4_outpost_navchip"));
		anotherText(S("outpost_calibrator_inserted"), S("day4_outpost_calibrator"));
		anotherText(S("outpost_catalyst_used"), S("day4_outpost_catlyst"));
		anotherText(S("outpost_hull_repaired_outside"), S("day4_outpost_hulloutside"));
	}
	int count = journalTimeItems.Count();
	if (!GameDataController::gd->getObjective(S("visited_outpost1")))
	{
		textToType2 += GameStrings::getString(GameStrings::journal, S("entry_objs_no4a"));
	}
	if (GameDataController::gd->getObjective(S("visited_outpost5")))
	{
		textToType2 += GameStrings::getString(GameStrings::journal, S("entry_objs_no4b"));
	}
	return textToType;
}

String JournalTexts::chapter3Texts()
{
	textToType = GameStrings::getString(GameStrings::journal, S("entry_intro_day3_intro"));
	bool flag = false;
	if (!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 0 && GameDataController::gd->getObjective(S("npc3_joined")))
	{
		textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("entry_intro_day3_cody_dead"));
		flag = true;
	}
	if (!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 0 && GameDataController::gd->getObjective(S("npc2_joined")))
	{
		flag = true;
		textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("entry_intro_day3_barry_dead"));
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("entry_intro_day3_thugs"));
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("entry_intro_day3_storm"));
	}
	if (flag)
	{
		textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("day3_funeral"));
	}
	if (!GameDataController::gd->getObjective(S("visited_sidereal_outside_1")))
	{
		textToType = textToType + S("^ ") + GameStrings::getString(GameStrings::journal, S("entry_objs_no3a"));
	}
	anotherText(S("visited_sidereal_outside_1"), S("day3_sidereal_arrive"));
	anotherText(GameDataController::gd->getObjectiveDetail(S("map_hunters_revealed")) != TravelAgency::LOCATION_STATUS_UNDISCOVERED, S("day3_sidereal_lodge_location"), String::Empty);
	anotherText(S("sidereal_base_located"), S("day3_sidereal_outpost_location"));
	anotherText(!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1 && GameDataController::gd->getObjective(S("npc3_joined")), S("day3_sidereal_cody_dead"), String::Empty);
	anotherText(!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1 && GameDataController::gd->getObjective(S("npc2_joined")), S("day3_sidereal_barry_dead"), String::Empty);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		anotherText(InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_6")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_5")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_4")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_3")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_2")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_1")), S("day1_rifle"), S("day3_rifle"));
		anotherText(InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_s_0")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_s_1")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_s_2")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_s_3")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_s_4")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_s_5")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_s_6")), S("day3_silencer_constructed"), String::Empty);
		anotherText(InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_o_0")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_o_1")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_o_2")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_o_3")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_o_4")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_o_5")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_o_6")), S("day3_sniper_constructed"), String::Empty);
		anotherText(InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_so_0")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_so_1")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_so_2")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_so_3")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_so_4")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_so_5")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_so_6")), S("day3_silencer_sniper_constructed"), String::Empty);
		anotherText(S("thugs_gasstation_talk"), S("day3_thugs_heard"));
		anotherText(S("day3_sarge_shot"), S("day3_sarge_shot"));
		anotherText(S("day3_sarge_convinced"), S("day3_sarge_convinced"));
		anotherText(S("day3_guard_killed"), S("day3_guard_killed"));
		anotherText(S("day3_whiskey_left"), S("day3_whiskey_left"));
		anotherText(S("day3_food_poisoned"), S("day3_food_poisoned"));
		anotherText(S("day3_ammo_spoiled"), S("day3_ammo_spoiled"));
		int num = 0;
		for (int i = 1; i <= 4; i++)
		{
			if (ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1)
			{
				if (ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("locationbaseoutside")) != -1)
				{
					num++;
				}
				else if (ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) != -1 || ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) != -1 || ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) != -1 || ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) != -1)
				{
					num++;
				}
			}
		}
		anotherText(num > 0, S("day3_traps"), String::Empty);
		int num2 = 0;
		int num3 = 0;
		int num4 = 0;
		int num5 = 0;
		if ((GameDataController::gd->getObjective(S("base_window_1_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_1_bars_taped"))) && !GameDataController::gd->getObjective(S("base_window1_broken")))
		{
			num2++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_2_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_2_bars_taped"))) && !GameDataController::gd->getObjective(S("base_window2_broken")))
		{
			num2++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_3_bars_taped"))) && !GameDataController::gd->getObjective(S("base_window3_broken")))
		{
			num2++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_1_net_nailed")) || GameDataController::gd->getObjective(S("base_window_1_net_taped"))) && !GameDataController::gd->getObjective(S("base_window1_broken")))
		{
			num3++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_2_net_nailed")) || GameDataController::gd->getObjective(S("base_window_2_net_taped"))) && !GameDataController::gd->getObjective(S("base_window2_broken")))
		{
			num3++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_3_net_nailed")) || GameDataController::gd->getObjective(S("base_window_3_net_taped"))) && !GameDataController::gd->getObjective(S("base_window3_broken")))
		{
			num3++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_1_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_1_blanketb_taped"))) && !GameDataController::gd->getObjective(S("base_window1_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_2_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_2_blanketb_taped"))) && !GameDataController::gd->getObjective(S("base_window2_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanketb_taped"))) && !GameDataController::gd->getObjective(S("base_window3_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_1_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_1_blanket_taped"))) && !GameDataController::gd->getObjective(S("base_window1_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_2_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_2_blanket_taped"))) && !GameDataController::gd->getObjective(S("base_window2_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanket_taped"))) && !GameDataController::gd->getObjective(S("base_window3_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_1_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_1_flag_taped"))) && !GameDataController::gd->getObjective(S("base_window1_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_2_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_2_flag_taped"))) && !GameDataController::gd->getObjective(S("base_window2_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_3_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_3_flag_taped"))) && !GameDataController::gd->getObjective(S("base_window3_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_1_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_1_therm_taped"))) && !GameDataController::gd->getObjective(S("base_window1_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_2_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_2_therm_taped"))) && !GameDataController::gd->getObjective(S("base_window2_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_3_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_3_therm_taped"))) && !GameDataController::gd->getObjective(S("base_window3_broken")))
		{
			num4++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_1_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_1_foil_taped"))) && !GameDataController::gd->getObjective(S("base_window1_broken")))
		{
			num5++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_2_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_2_foil_taped"))) && !GameDataController::gd->getObjective(S("base_window2_broken")))
		{
			num5++;
		}
		if ((GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_taped"))) && !GameDataController::gd->getObjective(S("base_window3_broken")))
		{
			num5++;
		}
		anotherText(!anotherText(!anotherText(num2 == 1, S("windows_bars_1"), String::Empty) && num2 == 2, S("windows_bars_2"), String::Empty) && num2 == 3, S("windows_bars_3"), String::Empty);
		anotherText(!anotherText(!anotherText(num3 == 1, S("windows_net_1"), String::Empty) && num3 == 2, S("windows_net_2"), String::Empty) && num3 == 3, S("windows_net_3"), String::Empty);
		anotherText(!anotherText(!anotherText(num5 == 1, S("windows_foil_1"), String::Empty) && num5 == 2, S("windows_foil_2"), String::Empty) && num5 == 3, S("windows_foil_3"), String::Empty);
		anotherText(!anotherText(!anotherText(num4 == 1, S("windows_blankets_1_d2"), String::Empty) && num4 == 2, S("windows_blankets_2_d2"), String::Empty) && num4 == 3, S("windows_blankets_3_d2"), String::Empty);
		if (ItemsManager::im->getItem(S("revolver_6"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("revolver_5"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("revolver_4"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("revolver_3"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("revolver_2"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("revolver_1"))->dataRef->droppedLocation == S("npc3"))
		{
			anotherText(true, S("day3_revolver_cody"), String::Empty);
		}
		if (ItemsManager::im->getItem(S("revolver_6"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("revolver_5"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("revolver_4"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("revolver_3"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("revolver_2"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("revolver_1"))->dataRef->droppedLocation == S("npc2"))
		{
			anotherText(true, S("day3_revolver_barry"), String::Empty);
		}
		int num6 = journalTimeItems.Count();
		if (num6 > 7)
		{
			num6 = 7;
		}
		if (num6 < 6 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
		{
			textToType2 = textToType2 + S(" ^ ") + GameStrings::getString(GameStrings::journal, S("entry_obj0_no3a"));
		}
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		anotherText(S("restaurant_sarge_encountered"), S("restaurant_sarge_encountered"));
		anotherText(S("r_sarge_catcher"), S("d3_1_catcher_restaurant"));
		anotherText(GameDataController::gd->getObjective(S("cs_engine_fueled")) && GameDataController::gd->getObjective(S("cs_engine_started")) && GameDataController::gd->getObjective(S("cs_stormcatcher_installed")), S("d3_1_catcher_construction"), String::Empty);
		anotherText(GameDataController::gd->getObjective(S("lodge_tree_stormcatcher")) && GameDataController::gd->getObjective(S("lodge_roof_cleaned")), S("d3_1_catcher_forest"), String::Empty);
		anotherText(S("base_outside_dug"), S("base_outside_dug"));
		anotherText(!GameDataController::gd->getObjective(S("attic_hatch_open")), S("attic_hatch_open"), String::Empty);
		anotherText(S("helicopter_covered"), S("helicopter_covered"));
		anotherText(S("helicopter_covered_taped"), S("helicopter_covered_taped"));
		anotherText(S("lighting_rod_installed"), S("lighting_rod_installed"));
		int num7 = 0;
		int num8 = 0;
		int num9 = 0;
		int num10 = 0;
		int num11 = 0;
		for (int j = 1; j <= 3; j++)
		{
			if (GameDataController::gd->getObjective(S("base_window_") + j + S("_board_nailed")) || GameDataController::gd->getObjective(S("base_window_") + j + S("_board_taped")))
			{
				num11++;
			}
			if (GameDataController::gd->getObjective(S("base_window_") + j + S("_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_") + j + S("_blanketb_taped")))
			{
				num9++;
			}
			if (GameDataController::gd->getObjective(S("base_window_") + j + S("_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_") + j + S("_blanket_taped")))
			{
				num9++;
			}
			if (GameDataController::gd->getObjective(S("base_window_") + j + S("_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_") + j + S("_flag_taped")))
			{
				num9++;
			}
			if (GameDataController::gd->getObjective(S("base_window_") + j + S("_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_") + j + S("_therm_taped")))
			{
				num9++;
			}
			if (GameDataController::gd->getObjective(S("base_window_") + j + S("_net_nailed")) || GameDataController::gd->getObjective(S("base_window_") + j + S("_net_taped")))
			{
				num8++;
			}
			if (GameDataController::gd->getObjective(S("base_window_") + j + S("_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_") + j + S("_bars_taped")))
			{
				num7++;
			}
			if (GameDataController::gd->getObjective(S("base_window_") + j + S("_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_") + j + S("_foil_taped")))
			{
				num10++;
			}
		}
		anotherText(!anotherText(!anotherText(num11 == 1, S("windows_boards_1"), String::Empty) && num11 == 2, S("windows_boards_2"), String::Empty) && num11 == 3, S("windows_boards_3"), String::Empty);
		anotherText(!anotherText(!anotherText(num7 == 1, S("windows_bars_1"), String::Empty) && num7 == 2, S("windows_bars_2"), String::Empty) && num7 == 3, S("windows_bars_3"), String::Empty);
		anotherText(!anotherText(!anotherText(num8 == 1, S("windows_net_1"), String::Empty) && num8 == 2, S("windows_net_2"), String::Empty) && num8 == 3, S("windows_net_3"), String::Empty);
		anotherText(!anotherText(!anotherText(num10 == 1, S("windows_foil_1"), String::Empty) && num10 == 2, S("windows_foil_2"), String::Empty) && num10 == 3, S("windows_foil_3"), String::Empty);
		anotherText(!anotherText(!anotherText(num9 == 1, S("windows_blankets_1_d2"), String::Empty) && num9 == 2, S("windows_blankets_2_d2"), String::Empty) && num9 == 3, S("windows_blankets_3_d2"), String::Empty);
		int num12 = journalTimeItems.Count();
		if (num12 > 7)
		{
			num12 = 7;
		}
		if (num12 < 6)
		{
			textToType2 = textToType2 + S(" ^ ") + GameStrings::getString(GameStrings::journal, S("entry_obj0_no3b"));
		}
	}
	return textToType;
}

String JournalTexts::chapter2Texts()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		textToType += GameStrings::getString(GameStrings::journal, S("entry_intro_day2_hot"));
	}
	else
	{
		textToType += GameStrings::getString(GameStrings::journal, S("entry_intro_day2_cold"));
	}
	textToType = textToType + S(" ") + GameStrings::getString(GameStrings::journal, S("entry_intro_day2_heli"));
	anotherText(S("dialogue_ginger_intro"), S("day2_ginger"));
	anotherText(S("npc2_joined"), S("day2_barry"));
	anotherText(S("npc3_joined"), S("day2_cody"));
	int num = 0;
	int num2 = 0;
	if (GameDataController::gd->getObjective(S("base_window_1_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_1_blanketb_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_2_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_2_blanketb_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanketb_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_1_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_1_blanket_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_2_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_2_blanket_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanket_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_1_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_1_flag_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_2_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_2_flag_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_3_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_3_flag_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_1_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_1_therm_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_2_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_2_therm_taped")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("base_window_3_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_3_therm_taped")))
	{
		num++;
	}
	if ((GameDataController::gd->getObjective(S("base_window_1_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_1_foil_taped"))) && !GameDataController::gd->getObjective(S("base_window1_broken")))
	{
		num2++;
	}
	if ((GameDataController::gd->getObjective(S("base_window_2_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_2_foil_taped"))) && !GameDataController::gd->getObjective(S("base_window2_broken")))
	{
		num2++;
	}
	if ((GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_taped"))) && !GameDataController::gd->getObjective(S("base_window3_broken")))
	{
		num2++;
	}
	anotherText(!anotherText(!anotherText(num == 1, S("windows_blankets_1_d2"), String::Empty) && num == 2, S("windows_blankets_2_d2"), String::Empty) && num == 3, S("windows_blankets_3_d2"), String::Empty);
	anotherText(!anotherText(!anotherText(num2 == 1, S("windows_foil_1"), S("windows_foil_1_d2")) && num2 == 2, S("windows_foil_2"), S("windows_foil_2_d2")) && num2 == 3, S("windows_foil_3"), S("windows_foil_3_d2"));
	anotherText(GameDataController::gd->getObjective(S("base_hatch_therm")) || GameDataController::gd->getObjective(S("base_hatch_blanket")) || GameDataController::gd->getObjective(S("base_hatch_blanketb")) || GameDataController::gd->getObjective(S("base_hatch_flag")), S("hatch_blanket_d2"), String::Empty);
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		int num3 = 0;
		if (ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("Location1") || ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("Location2") || ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("LocationBaseUpstairs") || ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("LocationBaseBathroom"))
		{
			num3++;
		}
		if (ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("Location1") || ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("Location2") || ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("LocationBaseUpstairs") || ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("LocationBaseBathroom"))
		{
			num3++;
		}
		if (ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("Location1") || ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("Location2") || ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("LocationBaseUpstairs") || ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("LocationBaseBathroom"))
		{
			num3++;
		}
		if (num3 > 0)
		{
			anotherText(num3 == 1, S("heat_absorber_base_1"), String::Empty);
			anotherText(num3 == 2, S("heat_absorber_base_2"), String::Empty);
			anotherText(num3 == 3, S("heat_absorber_base_3"), String::Empty);
		}
	}
	anotherText(GameDataController::gd->getObjective(S("base_ac_cord_plugged")) && GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1, S("house_ac"), String::Empty);
	anotherText((GameDataController::gd->getObjective(S("kitchen_fan_plugged")) || GameDataController::gd->getObjective(S("base_fan_cord_plugged"))) && GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1, S("house_fan"), String::Empty);
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
	{
		anotherText(GameDataController::gd->getObjective(S("kitchen_oven_open")) && GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1, S("house_oven"), String::Empty);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
	{
		anotherText((GameDataController::gd->getObjective(S("kitchen_heater_plugged")) || GameDataController::gd->getObjective(S("base_heater_cord_plugged"))) && GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1, S("house_heater"), String::Empty);
	}
	if (ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) != -1 || ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) != -1 || ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) != -1 || ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) != -1)
	{
		anotherText(true, S("house_gasheater"), String::Empty);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		int num4 = 0;
		anotherText(GameDataController::gd->getObjective(S("rv_cave_therm")) || GameDataController::gd->getObjective(S("rv_cave_flag")) || GameDataController::gd->getObjective(S("rv_cave_blanket")) || GameDataController::gd->getObjective(S("rv_cave_blanketb")), S("cave_blanket_d2"), String::Empty);
		anotherText(S("cave_ac_cord_plugged"), S("cave_ac"));
		anotherText(S("cave_fan_cord_plugged"), S("cave_fan"));
		if (GameDataController::gd->getObjective(S("cave_fan_cord_plugged")) || GameDataController::gd->getObjective(S("cave_ac_cord_plugged")))
		{
			anotherText(S("rv_started"), S("rv_started"));
		}
		num4 = 0;
		if (ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("LocationCave"))
		{
			num4++;
		}
		if (ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("LocationCave"))
		{
			num4++;
		}
		if (ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("LocationCave"))
		{
			num4++;
		}
		if (num4 > 0)
		{
			anotherText(num4 == 1, S("heat_absorber_cave_1"), String::Empty);
			anotherText(num4 == 2, S("heat_absorber_cave_2"), String::Empty);
			anotherText(num4 == 3, S("heat_absorber_cave_3"), String::Empty);
		}
	}
	if (ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation == S("ginger"))
	{
		anotherText(true, S("ginger_water"), String::Empty);
	}
	if (ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation == S("npc2"))
	{
		anotherText(true, S("barry_water"), String::Empty);
	}
	if (ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation == S("npc3"))
	{
		anotherText(true, S("cody_water"), String::Empty);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0 && (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("water1")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("water2")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("water3")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("water4"))))
	{
		anotherText(true, S("david_water"), String::Empty);
	}
	if (ItemsManager::im->getItem(S("coat1"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("coat2"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("coat3"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("coat4"))->dataRef->droppedLocation == S("ginger"))
	{
		anotherText(true, S("ginger_coat"), String::Empty);
	}
	if (ItemsManager::im->getItem(S("coat1"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("coat2"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("coat3"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("coat4"))->dataRef->droppedLocation == S("npc2"))
	{
		anotherText(true, S("barry_coat"), String::Empty);
	}
	if (ItemsManager::im->getItem(S("coat1"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("coat2"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("coat3"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("coat4"))->dataRef->droppedLocation == S("npc3"))
	{
		anotherText(true, S("cody_coat"), String::Empty);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1 && (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("coat1")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("coat2")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("coat3")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("coat4"))))
	{
		anotherText(true, S("david_coat"), String::Empty);
	}
	int count = journalTimeItems.Count();
	if (!anotherText(GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) != 0 && GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) != 0, S("day1_doors_towels"), String::Empty))
	{
	}
	if (count < 5)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			textToType2 = textToType2 + S("^") + GameStrings::getString(GameStrings::journal, S("entry_obj0_no2a"));
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			textToType2 = textToType2 + S("^") + GameStrings::getString(GameStrings::journal, S("entry_obj0_no2b"));
		}
	}
	return textToType;
}

String JournalTexts::chapter1Texts()
{
	String text = GameStrings::getString(GameStrings::journal, S("entry_intro_day1"));
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		text += GameStrings::getString(GameStrings::journal, S("entry_intro_day1_bugs"));
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		text += GameStrings::getString(GameStrings::journal, S("entry_intro_day1_gas"));
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		text += GameStrings::getString(GameStrings::journal, S("entry_intro_day1_spiders"));
	}
	text = text + S("^") + GameStrings::getString(GameStrings::journal, S("entry_obj0_no1"));
	if (!anotherText(GameDataController::gd->getObjective(S("base_discovered")), S("day1_base"), String::Empty))
	{
	}
	anotherText(GameDataController::gd->getItemData(S("sonic"))->droppedLocation.ToLower().IndexOf(S("outside")) != -1, S("day1_sonic"), String::Empty);
	int num = 0;
	int num2 = 0;
	if (ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1)
	{
		num = ((ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1) ? 1 : ((ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) == -1) ? 3 : 2));
	}
	if (ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1)
	{
		num2 = ((ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1) ? 1 : ((ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) == -1) ? 3 : 2));
	}
	if (!anotherText(num == 1 && num2 == 1, S("day1_spider_trap11"), String::Empty) && !anotherText(num == 2 && num2 == 2, S("day1_spider_trap22"), String::Empty))
	{
		anotherText(num == 1 || num2 == 1, S("day1_spider_trap1"), String::Empty);
		anotherText(num == 2 || num2 == 2, S("day1_spider_trap2"), String::Empty);
	}
	if (GameDataController::gd->getObjective(S("barn_sprinklers_enabled")))
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			if (!anotherText(GameDataController::gd->getObjective(S("barn_sprinklers_fed1")), S("day1_spray_pest"), String::Empty))
			{
				anotherText(true, S("day1_spray_water_bugs"), String::Empty);
			}
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			if (!anotherText(ItemsManager::im->getItem(S("chem_glass_12"))->dataRef->droppedLocation == S("sprinklers") || ItemsManager::im->getItem(S("chem_glass_13"))->dataRef->droppedLocation == S("sprinklers") || ItemsManager::im->getItem(S("chem_glass_23"))->dataRef->droppedLocation == S("sprinklers"), S("day1_spray_chem_gas"), String::Empty))
			{
				anotherText(true, S("day1_spray_water_gas"), String::Empty);
			}
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !anotherText(GameDataController::gd->getObjective(S("barn_sprinklers_fed1")), S("day1_spray_pest_spiders"), String::Empty))
		{
			anotherText(true, S("day1_spray_water_spiders"), String::Empty);
		}
	}
	int num3 = 0;
	int num4 = 0;
	int num5 = 0;
	if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")) || GameDataController::gd->getObjective(S("base_window_1_net_taped")))
	{
		num3++;
	}
	if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")) || GameDataController::gd->getObjective(S("base_window_2_net_taped")))
	{
		num3++;
	}
	if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")) || GameDataController::gd->getObjective(S("base_window_3_net_taped")))
	{
		num3++;
	}
	if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
	{
		num4++;
	}
	if (GameDataController::gd->getObjective(S("base_window_2_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
	{
		num4++;
	}
	if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
	{
		num4++;
	}
	if (GameDataController::gd->getObjective(S("base_window_1_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
	{
		num5++;
	}
	if (GameDataController::gd->getObjective(S("base_window_2_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_2_foil_taped")))
	{
		num5++;
	}
	if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
	{
		num5++;
	}
	if (!anotherText(num3 == 1, S("windows_net_1"), String::Empty) && !anotherText(num3 == 2, S("windows_net_2"), String::Empty))
	{
		anotherText(num3 == 3, S("windows_net_3"), String::Empty);
	}
	if (!anotherText(num4 == 1, S("windows_bars_1"), String::Empty) && !anotherText(num4 == 2, S("windows_bars_2"), String::Empty))
	{
		anotherText(num4 == 3, S("windows_bars_3"), String::Empty);
	}
	if (!anotherText(num5 == 1, S("windows_foil_1"), String::Empty) && !anotherText(num5 == 2, S("windows_foil_2"), String::Empty))
	{
		anotherText(num5 == 3, S("windows_foil_3"), String::Empty);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 1)
	{
		if (!anotherText(InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("flamethrower")), S("day1_flamethrower"), String::Empty) && !anotherText(InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("pestsprayer")), S("day1_pestspray"), String::Empty))
		{
			anotherText(InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_6")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_5")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_4")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_3")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_2")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("rifle_1")), S("day1_rifle"), String::Empty);
		}
	}
	else
	{
		anotherText(InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("chemsuit_dmg_dmg")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("chemsuit_rep_dmg")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("chemsuit_dmg_rep")) || InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("chemsuit_rep_rep")), S("day1_hazmat"), String::Empty);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		anotherText(GameDataController::gd->getObjective(S("crashsite_gas_note_read")), S("day1_gas_density"), String::Empty);
	}
	int num6 = journalTimeItems.Count();
	if (!anotherText(GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) != 0 && GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) != 0, S("day1_doors_towels"), String::Empty))
	{
	}
	if (num6 > 7)
	{
		num6 = 7;
	}
	if (num6 > 0)
	{
		textToType2 += GameStrings::getString(GameStrings::journal, S("entry_obj") + num6 + S("_no1"));
	}
	return text;
}

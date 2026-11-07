#include "../game_all.h"

int ResultsChapterStorm::checkTrap(String trapname)
{
	int result = 0;
	if (ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1)
	{
		result = ((ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("baseoutside")) != -1) ? 1 : ((ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) == -1 && ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) == -1 && ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) == -1 && ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) == -1) ? 3 : 2));
	}
	return result;
}

int ResultsChapterStorm::checkWindows(P<TimelineAction> tla, String name1, String name2, int value1)
{
	int num = value1 / 3;
	int num2 = value1 / 2;
	int num3 = value1 / 6;
	int num4 = value1 / 2;
	int num5 = value1 / 6;
	int num6 = value1 / 2;
	int num7 = value1 / 6;
	int num8 = value1 / 2;
	int num9 = value1 / 6;
	int num10 = 1;
	int num11 = 0;
	if (GameDataController::gd->getObjective(S("base_") + name1 + S("_broken")))
	{
		num11 = 0;
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_empty");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_open")) + S(" ") + GameStrings::getString(GameStrings::results, S("window_broken_barricade"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_board_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_board_taped")))
	{
		num11 = value1;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_board_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_board")) + S(" ") + GameStrings::getString(GameStrings::results, S("board_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_board_taped")))
	{
		num11 = value1 - num10;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_board_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_board")) + S(" ") + GameStrings::getString(GameStrings::results, S("board_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_board_nailed")))
	{
		num11 = value1 - num10;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_board_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_board")) + S(" ") + GameStrings::getString(GameStrings::results, S("board_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_board")))
	{
		num11 = num;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_board_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_board")) + S(" ") + GameStrings::getString(GameStrings::results, S("board_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanketb_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_blanketb_taped")))
	{
		num11 = num2;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanketb_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanketb_taped")))
	{
		num11 = num2 - num10;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanketb_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanketb_nailed")))
	{
		num11 = num2 - num10;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanketb_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanketb")))
	{
		num11 = num3;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanketb_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanket_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_blanket_taped")))
	{
		num11 = num4;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanket_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanket_taped")))
	{
		num11 = num4 - num10;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanket_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanket_nailed")))
	{
		num11 = num4 - num10;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanket_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanket")))
	{
		num11 = num5;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanket_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_flag_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_flag_taped")))
	{
		num11 = num6;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_flag_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_flag_taped")))
	{
		num11 = num6 - num10;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_flag_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_flag_nailed")))
	{
		num11 = num6 - num10;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_flag_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_flag")) + GameStrings::getString(GameStrings::results, S("flag_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_flag")))
	{
		num11 = num7;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_flag_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_therm_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_therm_taped")))
	{
		num11 = num8;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_therm_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_therm_taped")))
	{
		num11 = num8 - num10;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_value1_therm_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_therm_nailed")))
	{
		num11 = num8 - num10;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_therm_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_therm")))
	{
		num11 = num9;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_therm_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_net_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_net_taped")))
	{
		num11 = 0;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_net_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_net_taped")))
	{
		num11 = 0;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_net_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_net_nailed")))
	{
		num11 = 0;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_net_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_net")))
	{
		num11 = 0;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_net_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_foil_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_foil_taped")))
	{
		num11 = num4;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_foil_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_foil_taped")))
	{
		num11 = num4;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_foil_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_foil_nailed")))
	{
		num11 = num4;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_foil_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_foil")))
	{
		num11 = num5;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_foil_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_bars_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_bars_taped")))
	{
		num11 = 0;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_bars_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_bars_taped")))
	{
		num11 = 0;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_bars_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_bars_nailed")))
	{
		num11 = 0;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_bars_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_bars")))
	{
		num11 = 0;
		if (num11 > value1)
		{
			num11 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_bars_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
	}
	else
	{
		num11 = 0;
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_empty");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_open"));
	}
	if (num11 < 0)
	{
		num11 = 0;
	}
	return num11;
}

void ResultsChapterStorm::chapterResult()
{
	surviavbleDanger = 20;
	danger = 0;
	removeDanger = 0;
	winQuality = 3;
	pbc->total = 100;
	changeDanger(str(pbc->total));
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_1_1a1"));
	Timeline::t->addAction(timelineAction);
	if (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2") || GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom") || GameDataController::gd->previousLocation == S("LocationAttic1") || GameDataController::gd->previousLocation == S("LocationAttic2"))
	{
		analytics_stayed = S("base");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_1_1a2"));
		Timeline::t->addAction(timelineAction);
		check(0, S("r_d3_1_1a3"), String::Empty);
		int num = 0;
		if (GameDataController::gd->getObjective(S("cs_engine_fueled")) && GameDataController::gd->getObjective(S("cs_engine_started")) && GameDataController::gd->getObjective(S("cs_stormcatcher_installed")))
		{
			num++;
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_catcher_construction_1"), S("c_storm_catcher_construction")); }
			{ int prev = removeDanger; removeDanger = prev + check(5, S("r_d3_1_catcher_construction_2"), String::Empty); }
		}
		if (GameDataController::gd->getObjective(S("lodge_tree_stormcatcher")) && GameDataController::gd->getObjective(S("lodge_roof_cleaned")))
		{
			num++;
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_catcher_lodge_1"), S("c_storm_catcher_forest")); }
			{ int prev = removeDanger; removeDanger = prev + check(5, S("r_d3_1_catcher_lodge_2"), String::Empty); }
		}
		if (GameDataController::gd->getObjective(S("r_sarge_catcher")))
		{
			num++;
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_catcher_restaurant_1"), S("c_storm_catcher_restaurant")); }
			{ int prev = removeDanger; removeDanger = prev + check(5, S("r_d3_1_catcher_restaurant_2"), String::Empty); }
		}
		if (num > 0 && num < 3)
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_catchers_0a"), S("hide")); }
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_catchers_0b"), String::Empty); }
		}
		if (num == 3)
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_catchers_3a"), S("c_map_catchers")); }
			{ int prev = removeDanger; removeDanger = prev + check(20, S("r_d3_1_catchers_3b"), String::Empty); }
		}
		if (GameDataController::gd->getObjective(S("base_outside_dug")))
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_ditch_1a"), S("c_dig")); }
			{ int prev = removeDanger; removeDanger = prev + check(15, S("r_d3_1_ditch_1b"), String::Empty); }
		}
		else
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_ditch_2a"), S("hide")); }
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_ditch_2b"), String::Empty); }
		}
		if (GameDataController::gd->getObjective(S("helicopter_covered")) && GameDataController::gd->getObjective(S("helicopter_covered_taped")))
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_heli_1a"), S("c_helicopter")); }
			{ int prev = removeDanger; removeDanger = prev + check(20, S("r_d3_1_heli_1b"), String::Empty); }
		}
		else if (GameDataController::gd->getObjective(S("helicopter_covered")))
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_heli_2a"), S("c_helicopter")); }
			{ int prev = removeDanger; removeDanger = prev + check(10, S("r_d3_1_heli_2b"), String::Empty); }
		}
		else
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_heli_3a"), S("hide")); }
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_heli_3b"), String::Empty); }
		}
		int num2 = pbc->total - removeDanger;
		if (num2 > 10)
		{
			num2 = 10;
		}
		if (!GameDataController::gd->getObjective(S("attic_hatch_open")))
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_hatch_1a"), S("roof_hatch_closed")); }
			{ int prev = removeDanger; removeDanger = prev + check(10, GameStrings::getString(GameStrings::results, S("r_d3_hatch_1b")) + S(" ") + num2 + GameStrings::getString(GameStrings::results, S("r_d3_hatch_1c")), String::Empty, false); }
		}
		else
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_hatch_2a"), S("roof_hatch_open")); }
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_hatch_2b"), String::Empty); }
		}
		if (GameDataController::gd->getObjective(S("lighting_rod_installed")))
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_rod_1a"), S("c_thunder_rod")); }
			{ int prev = removeDanger; removeDanger = prev + check(20, S("r_d3_1_rod_1b"), String::Empty); }
		}
		else
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_rod_2a"), S("hide")); }
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_rod_2b"), String::Empty); }
		}
		if (removeDanger >= pbc->total)
		{
			winQuality = 3;
		}
		else
		{
			winQuality = 2;
		}
		int num3 = pbc->total - removeDanger;
		float num4 = 4.0f;
		float num5 = 4.0f;
		float num6 = 8.0f;
		float num7 = 8.0f;
		float num8 = 8.0f;
		float num9 = 8.0f;
		num3 = danger - removeDanger - (int)num4 - (int)num5 - (int)num6 - (int)num7 - (int)num8 - (int)num9;
		int num10 = 0;
		int num11 = (int)num4 - 1;
		int num12 = (int)num4;
		int num13 = 0;
		if (!GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
			{
				{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_door1_1a"), S("c_door1_closed_towel")); }
				{ int prev = removeDanger; removeDanger = prev + check(num12, S("r_d3_1_door1_1b"), String::Empty); }
			}
			else
			{
				{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_door1_2a"), S("c_door1_closed")); }
				{ int prev = removeDanger; removeDanger = prev + check(num11, S("r_d3_1_door1_2b"), String::Empty); }
			}
		}
		else
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_door1_3a"), S("c_door1_open")); }
			{ int prev = removeDanger; removeDanger = prev + check(num11, S("r_d3_1_door1_3b"), String::Empty); }
		}
		if (!GameDataController::gd->getObjective(S("location02_door_open")))
		{
			if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
			{
				{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_door2_1a"), S("c_door2_closed_towel")); }
				{ int prev = removeDanger; removeDanger = prev + check(num12, S("r_d3_1_door2_1b"), String::Empty); }
			}
			else
			{
				{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_door2_2a"), S("c_door2_closed")); }
				{ int prev = removeDanger; removeDanger = prev + check(num11, S("r_d3_1_door2_2b"), String::Empty); }
			}
		}
		else
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_door2_3a"), S("c_door2_open")); }
			{ int prev = removeDanger; removeDanger = prev + check(num11, S("r_d3_1_door2_3b"), String::Empty); }
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->actionWithText = true;
		int num14 = 0;
		num14 = checkWindows(timelineAction, S("window1"), S("window_1"), (int)num6);
		Timeline::t->addAction(timelineAction);
		removeDanger += num14;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->param = S("-") + num14;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_1_window_result1")) + S(" ") + num14 + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_1_window_result2"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->actionWithText = true;
		num14 = 0;
		num14 = checkWindows(timelineAction, S("window2"), S("window_2"), (int)num7);
		Timeline::t->addAction(timelineAction);
		removeDanger += num14;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->param = S("-") + num14;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_1_window_result1")) + S(" ") + num14 + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_1_window_result2"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->actionWithText = true;
		num14 = 0;
		num14 = checkWindows(timelineAction, S("window3"), S("window_3"), (int)num8);
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->param = S("-") + num14;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_1_window_result1")) + S(" ") + num14 + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_1_window_result2"));
		removeDanger += num14;
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->actionWithText = true;
		num14 = 0;
		if (GameDataController::gd->getObjective(S("base_hatch_therm")))
		{
			num14 = (int)num9;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_therm");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_therm"));
		}
		else if (GameDataController::gd->getObjective(S("base_hatch_flag")))
		{
			num14 = (int)num9;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_flag");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_flag"));
		}
		else if (GameDataController::gd->getObjective(S("base_hatch_blanketb")))
		{
			num14 = (int)num9;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_blanketb");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_blanketb"));
		}
		else if (GameDataController::gd->getObjective(S("base_hatch_blanket")))
		{
			num14 = (int)num9;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_blanket");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_blanket"));
		}
		else
		{
			num14 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_empty"));
		}
		Timeline::t->addAction(timelineAction);
		{ int prev = removeDanger; removeDanger = prev + check(num14, GameStrings::getString(GameStrings::results, S("r_d3_1_hatch_result1")) + S(" ") + num14 + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_1_hatch_result2")), String::Empty, false); }
		if (danger - removeDanger > 10)
		{
			{ int prev = removeDanger; removeDanger = prev + check(0, GameStrings::getString(GameStrings::results, S("r_d3_1_bad_1a")) + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_1_bad_1b")), S("hide"), false); }
			if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
			{
				{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_cody_1a"), S("c_cody_drowned")); }
				{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_cody_1b"), String::Empty); }
				winQuality = 1;
				GameDataController::gd->setObjective(S("npc3_alive"), false);
				GameDataController::gd->setObjectiveDetail(S("npc3_alive"), 2);
			}
			if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
			{
				{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_barry_1a"), S("c_barry_drowned")); }
				{ int prev = removeDanger; removeDanger = prev + check(0, S("r_d3_1_barry_1b"), String::Empty); }
				winQuality = 1;
				GameDataController::gd->setObjective(S("npc2_alive"), false);
				GameDataController::gd->setObjectiveDetail(S("npc2_alive"), 2);
			}
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::liveOrDie(v); };
		timelineAction->actionWithText = true;
		timelineAction->param = S("0");
		timelineAction->text = String::Empty;
		Timeline::t->addAction(timelineAction);
	}
	else
	{
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_1_1b1"));
		timelineAction->function = [this](String v) { ResultsController::liveOrDie(v); };
		Timeline::t->addAction(timelineAction);
		analytics_stayed = S("outside");
	}
}

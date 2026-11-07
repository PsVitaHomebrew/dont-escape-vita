#include "../game_all.h"

int ResultsChapterBandits::checkTrap(String trapname)
{
	int result = 0;
	if (ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1)
	{
		result = ((ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("baseoutside")) != -1) ? 1 : ((ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) == -1 && ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) == -1 && ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) == -1 && ItemsManager::im->getItem(trapname)->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) == -1) ? 3 : 2));
	}
	return result;
}

int ResultsChapterBandits::checkWindows(P<TimelineAction> tla, String name1, String name2, int value1)
{
	int num = value1 - 3;
	int num2 = value1 - 3;
	int num3 = value1 - 3;
	int num4 = value1 - 3;
	int num5 = 1;
	int num6 = 0;
	if (GameDataController::gd->getObjective(S("base_") + name1 + S("_broken")))
	{
		num6 = 0;
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_empty");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_open")) + S(" ") + GameStrings::getString(GameStrings::results, S("window_broken_barricade"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanketb_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_blanketb_taped")))
	{
		num6 = value1;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanketb_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanketb_taped")))
	{
		num6 = value1 - num5;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanketb_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanketb_nailed")))
	{
		num6 = value1 - num5;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanketb_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanketb")))
	{
		num6 = num;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanketb_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanket_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_blanket_taped")))
	{
		num6 = value1;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanket_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanket_taped")))
	{
		num6 = value1 - num5;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanket_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanket_nailed")))
	{
		num6 = value1 - num5;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanket_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_blanket")))
	{
		num6 = num2;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_blanket_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_flag_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_flag_taped")))
	{
		num6 = value1;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_flag_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_flag_taped")))
	{
		num6 = value1 - num5;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_flag_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_flag_nailed")))
	{
		num6 = value1 - num5;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_flag_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_flag")))
	{
		num6 = num3;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_flag_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_therm_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_therm_taped")))
	{
		num6 = value1;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_therm_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_therm_taped")))
	{
		num6 = value1 - num5;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_value1_therm_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_therm_nailed")))
	{
		num6 = value1 - num5;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_therm_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_therm")))
	{
		num6 = num4;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_therm_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_net_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_net_taped")))
	{
		num6 = 0;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_net_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_net_taped")))
	{
		num6 = 0;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_net_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_net_nailed")))
	{
		num6 = 0;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_net_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_net")))
	{
		num6 = 0;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_net_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_foil_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_foil_taped")))
	{
		num6 = value1 / 2;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_foil_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_foil_taped")))
	{
		num6 = value1 / 2;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_foil_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_foil_nailed")))
	{
		num6 = value1 / 2;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_foil_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_foil")))
	{
		num6 = num2 / 2;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_foil_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_foil")) + GameStrings::getString(GameStrings::results, S("foil_none"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_bars_nailed")) && GameDataController::gd->getObjective(S("base_") + name2 + S("_bars_taped")))
	{
		num6 = 0;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_bars_3");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_bars_taped")))
	{
		num6 = 0;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_bars_2");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_bars_nailed")))
	{
		num6 = 0;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_bars_1");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
	}
	else if (GameDataController::gd->getObjective(S("base_") + name2 + S("_bars")))
	{
		num6 = 0;
		if (num6 > value1)
		{
			num6 = value1;
		}
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_bars_0");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
	}
	else
	{
		num6 = 0;
		tla->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_") + name1 + S("_empty");
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_open"));
	}
	return num6;
}

void ResultsChapterBandits::chapterResult()
{
	surviavbleDanger = 1;
	danger = 0;
	removeDanger = 0;
	winQuality = 3;
	pbc->total = 20;
	changeDanger(str(pbc->total));
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_1a1"));
	Timeline::t->addAction(timelineAction);
	if (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2") || GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom") || GameDataController::gd->previousLocation == S("LocationRoof1") || GameDataController::gd->previousLocation == S("LocationRoof2") || GameDataController::gd->previousLocation == S("LocationAttic1") || GameDataController::gd->previousLocation == S("LocationAttic2"))
	{
		analytics_stayed = S("base");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_1a2"));
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")) || GameDataController::gd->getObjective(S("gasstation_sarge_convinced")) || GameDataController::gd->getObjective(S("cs_food_poisioned")) || GameDataController::gd->getObjective(S("cs_thug_shot")) || ItemsManager::im->getItem(S("whiskey"))->dataRef->droppedLocation == S("CS3"))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_2"));
			Timeline::t->addAction(timelineAction);
			if (ItemsManager::im->getItem(S("whiskey"))->dataRef->droppedLocation == S("CS3"))
			{
				analytics_whiskey_dumped = S("true");
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_alcohol");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_3a1"));
				Timeline::t->addAction(timelineAction);
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = false;
				timelineAction->param = S("-") + 2;
				removeDanger += 2;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_3a2"));
				Timeline::t->addAction(timelineAction);
			}
			if (GameDataController::gd->getObjective(S("cs_food_poisioned")))
			{
				analytics_food_poisoned = S("true");
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_poision");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_4a1"));
				Timeline::t->addAction(timelineAction);
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = false;
				timelineAction->param = S("-") + 3;
				removeDanger += 3;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_4a2"));
				Timeline::t->addAction(timelineAction);
			}
			if (GameDataController::gd->getObjective(S("cs_thug_shot")))
			{
				if (GameDataController::gd->getObjectiveDetail(S("cs_thug_shot")) == 0)
				{
					analytics_guard_killed = S("true");
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_thugshot");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_5a1"));
					Timeline::t->addAction(timelineAction);
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = false;
					timelineAction->param = S("-") + 1;
					removeDanger++;
					timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_5a2"));
					Timeline::t->addAction(timelineAction);
				}
				else
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_thugshot");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_5b1"));
					Timeline::t->addAction(timelineAction);
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = false;
					timelineAction->param = S("-") + 1;
					removeDanger++;
					timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_5b2"));
					Timeline::t->addAction(timelineAction);
				}
			}
			if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
			{
				analytics_sarge_status = S("killed");
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_sarge_dead");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_6a1"));
				Timeline::t->addAction(timelineAction);
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = false;
				timelineAction->param = S("-") + 1;
				removeDanger++;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_6a2"));
				Timeline::t->addAction(timelineAction);
			}
			if (GameDataController::gd->getObjective(S("gasstation_sarge_convinced")))
			{
				analytics_sarge_status = S("convinced");
				if (GameDataController::gd->getObjective(S("cs_food_poisioned")))
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_sarge_poision");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_6b1"));
					Timeline::t->addAction(timelineAction);
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = false;
					timelineAction->param = S("-") + 0;
					timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_6b2"));
					Timeline::t->addAction(timelineAction);
				}
				else
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_sarge_leave");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_6c1"));
					Timeline::t->addAction(timelineAction);
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = false;
					timelineAction->param = S("-") + 5;
					removeDanger += 5;
					timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_6c2"));
					Timeline::t->addAction(timelineAction);
				}
			}
		}
		{ int _old = removeDanger; removeDanger = _old + check(0, danger - removeDanger + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_7")), String::Empty, false); }
		{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_9a1"), S("c_thugsfire")); }
		{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_9a2"), String::Empty); }
		if (GameDataController::gd->getObjective(S("cs_ammo_oiled")) || GameDataController::gd->getObjective(S("cs_ammo_watered")))
		{
			analytics_ammo_sabotaged = S("true");
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_10a1"), S("c_ammo")); }
			{ int _old = removeDanger; removeDanger = _old + check(3, S("r_d3_0_10a2"), String::Empty); }
		}
		if (InventoryController::ic->isItemEquipped(S("rifle_so_6")) || InventoryController::ic->isItemEquipped(S("rifle_so_5")) || InventoryController::ic->isItemEquipped(S("rifle_so_4")) || InventoryController::ic->isItemEquipped(S("rifle_so_3")) || InventoryController::ic->isItemEquipped(S("rifle_so_2")) || InventoryController::ic->isItemEquipped(S("rifle_so_1")) || InventoryController::ic->isItemEquipped(S("rifle_s_6")) || InventoryController::ic->isItemEquipped(S("rifle_s_5")) || InventoryController::ic->isItemEquipped(S("rifle_s_4")) || InventoryController::ic->isItemEquipped(S("rifle_s_3")) || InventoryController::ic->isItemEquipped(S("rifle_s_2")) || InventoryController::ic->isItemEquipped(S("rifle_s_1")) || InventoryController::ic->isItemEquipped(S("rifle_o_6")) || InventoryController::ic->isItemEquipped(S("rifle_o_5")) || InventoryController::ic->isItemEquipped(S("rifle_o_4")) || InventoryController::ic->isItemEquipped(S("rifle_o_3")) || InventoryController::ic->isItemEquipped(S("rifle_o_2")) || InventoryController::ic->isItemEquipped(S("rifle_o_1")) || InventoryController::ic->isItemEquipped(S("rifle_6")) || InventoryController::ic->isItemEquipped(S("rifle_5")) || InventoryController::ic->isItemEquipped(S("rifle_4")) || InventoryController::ic->isItemEquipped(S("rifle_3")) || InventoryController::ic->isItemEquipped(S("rifle_2")) || InventoryController::ic->isItemEquipped(S("rifle_1")))
		{
			if (InventoryController::ic->isItemEquipped(S("rifle_so_6")) || InventoryController::ic->isItemEquipped(S("rifle_so_5")) || InventoryController::ic->isItemEquipped(S("rifle_so_4")) || InventoryController::ic->isItemEquipped(S("rifle_so_3")) || InventoryController::ic->isItemEquipped(S("rifle_so_2")) || InventoryController::ic->isItemEquipped(S("rifle_so_1")) || InventoryController::ic->isItemEquipped(S("rifle_o_6")) || InventoryController::ic->isItemEquipped(S("rifle_o_5")) || InventoryController::ic->isItemEquipped(S("rifle_o_4")) || InventoryController::ic->isItemEquipped(S("rifle_o_3")) || InventoryController::ic->isItemEquipped(S("rifle_o_2")) || InventoryController::ic->isItemEquipped(S("rifle_o_1")))
			{
				int num = 6;
				if (GameDataController::gd->equipped.IndexOf(S("_6")) != -1)
				{
					num = 5;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_5")) != -1)
				{
					num = 4;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_4")) != -1)
				{
					num = 3;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_3")) != -1)
				{
					num = 2;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_2")) != -1)
				{
					num = 2;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_1")) != -1)
				{
					num = 1;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_0")) != -1)
				{
					num = 0;
				}
				String text = S("_a");
				if (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2"))
				{
					text = S("_b");
					if (num >= 2)
					{
						num--;
					}
				}
				else if (GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom"))
				{
					text = S("_a");
				}
				else if (GameDataController::gd->previousLocation == S("LocationRoof1") || GameDataController::gd->previousLocation == S("LocationRoof2"))
				{
					text = S("_d");
					if (num >= 4)
					{
						num++;
					}
				}
				else if (GameDataController::gd->previousLocation == S("LocationAttic1") || GameDataController::gd->previousLocation == S("LocationAttic2"))
				{
					text = S("_c");
				}
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_11c1") + text, S("c_rifle_bandits") + text); }
				{ int _old = removeDanger; removeDanger = _old + check(num, S("r_d3_0_11c2-") + num, String::Empty); }
				analytics_weapon = S("sniper_rifle_") + num;
			}
			else
			{
				int num2 = 3;
				int num3 = 0;
				if (GameDataController::gd->equipped.IndexOf(S("_6")) != -1)
				{
					num2 = 3;
					num3 = 6;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_5")) != -1)
				{
					num2 = 3;
					num3 = 5;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_4")) != -1)
				{
					num2 = 2;
					num3 = 4;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_3")) != -1)
				{
					num2 = 2;
					num3 = 3;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_2")) != -1)
				{
					num2 = 1;
					num3 = 2;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_1")) != -1)
				{
					num2 = 1;
					num3 = 1;
				}
				if (GameDataController::gd->equipped.IndexOf(S("_0")) != -1)
				{
					num2 = 0;
					num3 = 0;
				}
				analytics_weapon = S("rifle_") + num3;
				String text2 = S("_a");
				if (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2"))
				{
					text2 = S("_b");
					if (num2 >= 2)
					{
						num2--;
					}
				}
				else if (GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom"))
				{
					text2 = S("_a");
				}
				else if (GameDataController::gd->previousLocation == S("LocationRoof1") || GameDataController::gd->previousLocation == S("LocationRoof2"))
				{
					text2 = S("_d");
					if (num2 == 3)
					{
						num2++;
					}
				}
				else if (GameDataController::gd->previousLocation == S("LocationAttic1") || GameDataController::gd->previousLocation == S("LocationAttic2"))
				{
					text2 = S("_c");
				}
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_11b1") + text2, S("c_rifle_bandits") + text2); }
				{ int _old = removeDanger; removeDanger = _old + check(num2, S("r_d3_0_11b2-") + num2, String::Empty); }
			}
			if (InventoryController::ic->isItemInInventory(S("rifle_ammo")))
			{
				analytics_weapon += S("+clip");
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_12a0"), S("c_rifle_ammo")); }
				if (danger - removeDanger > 1)
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_12a1"), String::Empty); }
				}
				else
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_12a_last"), String::Empty); }
				}
			}
		}
		int num4 = 0;
		int num5 = 0;
		int num6 = 0;
		int num7 = 0;
		num4 = checkTrap(S("bear_trap_1"));
		num5 = checkTrap(S("bear_trap_2"));
		num6 = checkTrap(S("bear_trap_3"));
		num7 = checkTrap(S("bear_trap_4"));
		int num8 = 0;
		if (num4 == 1)
		{
			num8++;
		}
		if (num5 == 1)
		{
			num8++;
		}
		if (num6 == 1)
		{
			num8++;
		}
		if (num7 == 1)
		{
			num8++;
		}
		analytics_traps = String::Empty + num8 + S("/4");
		if (num8 == 1)
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_13a1"), S("c_beartrap_0")); }
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_13a2"), String::Empty); }
		}
		if (num8 > 1)
		{
			int num9 = num8 - 1;
			if (num9 >= danger - removeDanger)
			{
				num9 = danger - removeDanger - 1;
			}
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_13b1"), S("c_beartrap_0")); }
			if (num9 > 1)
			{
				{ int _old = removeDanger; removeDanger = _old + check(num9, GameStrings::getString(GameStrings::results, S("r_d3_0_13b2")) + S(" ") + num8 + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_13b3")) + S(" ") + num9 + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_13b4a1")), S("c_beartrap_bandits"), false); }
			}
			else if (num9 == 1)
			{
				{ int _old = removeDanger; removeDanger = _old + check(num9, GameStrings::getString(GameStrings::results, S("r_d3_0_13b2")) + S(" ") + num8 + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_13b3")) + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_13b4b1")), S("c_beartrap_bandits"), false); }
			}
			else if (danger - removeDanger == 1)
			{
				{ int _old = removeDanger; removeDanger = _old + check(num9, GameStrings::getString(GameStrings::results, S("r_d3_0_13b4c1")), S("c_trap_razor"), false); }
			}
		}
		int num10 = 2;
		if (GameDataController::gd->getObjective(S("location01_door2_locked")) && !GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_14a1"), S("c_door1_closed")); }
		}
		else if (!GameDataController::gd->getObjective(S("location01_door2_locked")) && !GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_14b1"), S("c_door1_closed")); }
			num10 = 1;
		}
		else if (GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_14c1"), S("c_door1_open")); }
			num10 = 0;
		}
		if (GameDataController::gd->getObjective(S("location02_door_locked")) && !GameDataController::gd->getObjective(S("location02_door_open")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_15a1"), S("c_door2_closed")); }
		}
		else if (!GameDataController::gd->getObjective(S("location02_door_locked")) && !GameDataController::gd->getObjective(S("location02_door_open")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_15b1"), S("c_door2_closed")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("location02_door_open")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_15c1"), S("c_door2_open")); }
			num10 = 0;
		}
		if (GameDataController::gd->getObjective(S("base_window1_broken")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16c1"), S("c_window1_empty")); }
			num10 = 0;
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16a1"), S("c_window1_bars_3")); }
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16a1"), S("c_window1_bars_1")); }
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16a1"), S("c_window1_bars_2")); }
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net")) && GameDataController::gd->getObjective(S("base_window_1_net_nailed")) && GameDataController::gd->getObjective(S("base_window_1_net_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_net_3")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net")) && GameDataController::gd->getObjective(S("base_window_1_net_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_net_2")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net")) && GameDataController::gd->getObjective(S("base_window_1_net_nailed")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_net_1")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_net_0")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil")) && GameDataController::gd->getObjective(S("base_window_1_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_foil_3")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil")) && GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_foil_2")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil")) && GameDataController::gd->getObjective(S("base_window_1_foil_nailed")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_foil_1")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_foil_0")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_bars_0")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanketb")) && GameDataController::gd->getObjective(S("base_window_1_blanketb_nailed")) && GameDataController::gd->getObjective(S("base_window_1_blanketb_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_blanketb_3")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanketb")) && GameDataController::gd->getObjective(S("base_window_1_blanketb_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_blanketb_2")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanketb")) && GameDataController::gd->getObjective(S("base_window_1_blanketb_nailed")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_blanketb_1")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanketb")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_blanketb_0")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanket")) && GameDataController::gd->getObjective(S("base_window_1_blanket_nailed")) && GameDataController::gd->getObjective(S("base_window_1_blanket_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_blanket_3")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanket")) && GameDataController::gd->getObjective(S("base_window_1_blanket_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_blanket_2")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanket")) && GameDataController::gd->getObjective(S("base_window_1_blanket_nailed")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_blanket_1")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanket")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_blanket_0")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_flag")) && GameDataController::gd->getObjective(S("base_window_1_flag_nailed")) && GameDataController::gd->getObjective(S("base_window_1_flag_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_flag_3")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_flag")) && GameDataController::gd->getObjective(S("base_window_1_flag_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_flag_2")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_flag")) && GameDataController::gd->getObjective(S("base_window_1_flag_nailed")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_flag_1")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_flag")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_flag_0")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_therm")) && GameDataController::gd->getObjective(S("base_window_1_therm_nailed")) && GameDataController::gd->getObjective(S("base_window_1_therm_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_therm_3")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_therm")) && GameDataController::gd->getObjective(S("base_window_1_therm_taped")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_therm_2")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_therm")) && GameDataController::gd->getObjective(S("base_window_1_therm_nailed")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_therm_1")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_therm")))
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16b1"), S("c_window1_therm_0")); }
			if (num10 >= 1)
			{
				num10 = 1;
			}
		}
		else
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_16c1"), S("c_window1_empty")); }
			num10 = 0;
		}
		analytics_doors_and_windows = num10 + String::Empty;
		if (removeDanger + 1 >= pbc->total)
		{
			winQuality = 3;
		}
		else
		{
			winQuality = 2;
		}
		if (num10 < 2)
		{
			if (removeDanger < pbc->total)
			{
				winQuality = 2;
			}
			if (danger - removeDanger > 1)
			{
				String pic = S("c_bandits_enter");
				if (danger - removeDanger == 2)
				{
					pic = S("c_bandits_enter_2");
				}
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_17a1a1")) + S(" ") + (danger - removeDanger) + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_17a1a2")), pic, false); }
				if (num10 == 1)
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_17a1a3"), String::Empty); }
				}
				else
				{
					{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_17a1a4"), String::Empty); }
				}
			}
			else
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_17a1b1"), S("c_bandits_enter_razor")); }
				if (num10 == 1)
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_17a1b2"), String::Empty); }
				}
			}
		}
		else
		{
			int num11 = 2;
			if (danger - removeDanger > 1)
			{
				if (danger - removeDanger == 2)
				{
					num11 = 1;
				}
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_17b1a1")) + S(" ") + num11 + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_17b1a2")), S("c_cate_bandits"), false); }
				{ int _old = removeDanger; removeDanger = _old + check(num11, S("r_d3_0_17b1a3"), String::Empty); }
			}
			else
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_17b1b1"), S("c_razor")); }
				{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_17b1b2"), String::Empty); }
			}
		}
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			if (ItemsManager::im->getItem(S("revolver_6"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("revolver_5"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("revolver_4"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("revolver_3"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("revolver_2"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("revolver_1"))->dataRef->droppedLocation == S("npc3"))
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_18a1"), S("c_cody_bandits")); }
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_18a2"), String::Empty); }
				if (danger - removeDanger > 1)
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_18a3a1"), String::Empty); }
					GameDataController::gd->setObjective(S("cody_killed_someone"), true);
				}
				else
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_18a3b1"), String::Empty); }
				}
			}
			else
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_18b1"), S("c_cody2_bandits")); }
			}
		}
		if (GameDataController::gd->getObjective(S("npc2_alive")))
		{
			if (ItemsManager::im->getItem(S("revolver_6"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("revolver_5"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("revolver_4"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("revolver_3"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("revolver_2"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("revolver_1"))->dataRef->droppedLocation == S("npc2"))
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_19a1"), S("c_barry_bandits")); }
				if (danger - removeDanger > 2)
				{
					{ int _old = removeDanger; removeDanger = _old + check(2, S("r_d3_0_19a2a1"), String::Empty); }
				}
				else if (danger - removeDanger > 1)
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_19a2b1"), String::Empty); }
				}
				else
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_19a2c1"), String::Empty); }
				}
			}
			else
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_19b1a1"), S("c_barry2_bandits")); }
				if (danger - removeDanger > 1)
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_19b1a2"), String::Empty); }
				}
				else
				{
					{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_19b1b1"), String::Empty); }
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_19b1b2"), String::Empty); }
				}
			}
		}
		if (GameDataController::gd->equipped.IndexOf(S("rifle")) == -1)
		{
			analytics_weapon = GameDataController::gd->equipped;
		}
		if (GameDataController::gd->equipped.IndexOf(S("rifle")) == -1 && GameDataController::gd->equipped != S("flamethrower") && GameDataController::gd->equipped.IndexOf(S("revolver")) == -1 && GameDataController::gd->equipped != String::Empty)
		{
			String text3 = S("c_banditfight_") + GameDataController::gd->equipped;
			if (danger - removeDanger > 1)
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_20a1a1")) + S(" ") + (danger - removeDanger) + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_20a1a2")), String::Empty, false); }
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_20a1a3")) + S(" ") + GameStrings::getPrefixedShort(GameStrings::items, GameDataController::gd->equipped) + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_20a1a4")), String::Empty, false); }
				{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_20a1a5"), String::Empty); }
			}
			else
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_20a1b1")), String::Empty, false); }
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_20a1a3")) + S(" ") + GameStrings::getPrefixedShort(GameStrings::items, GameDataController::gd->equipped) + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_20a1a4")), S("c_razor"), false); }
				{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_20a1b2"), String::Empty); }
			}
		}
		else if (GameDataController::gd->equipped == S("flamethrower"))
		{
			if (danger - removeDanger > 1)
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_20b1a1")) + S(" ") + (danger - removeDanger) + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_20b1a2")), S("c_flamethrower_bandits"), false); }
				{ int _old = removeDanger; removeDanger = _old + check(1, GameStrings::getString(GameStrings::results, S("r_d3_0_20b1a3")), String::Empty, false); }
			}
			else
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_20b1b1")), S("c_razor"), false); }
				{ int _old = removeDanger; removeDanger = _old + check(1, GameStrings::getString(GameStrings::results, S("r_d3_0_20b1b2")), String::Empty, false); }
			}
		}
		else if (GameDataController::gd->equipped.IndexOf(S("rifle")) == -1 && GameDataController::gd->equipped != String::Empty)
		{
			if (danger - removeDanger > 1)
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_20c1a1")) + S(" ") + (danger - removeDanger) + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_20c1a2")), S("c_banditfight_gun"), false); }
				int num12 = 2;
				if (danger - removeDanger == 2)
				{
					num12 = 1;
				}
				{ int _old = removeDanger; removeDanger = _old + check(num12, GameStrings::getString(GameStrings::results, S("r_d3_0_20c1a3")) + S(" ") + num12 + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_20c1a4")), String::Empty, false); }
			}
			else
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_20c1b1")), S("c_razor"), false); }
				{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_20c1b2")), String::Empty, false); }
				{ int _old = removeDanger; removeDanger = _old + check(1, GameStrings::getString(GameStrings::results, S("r_d3_0_20c1b3")), String::Empty, false); }
			}
			if (InventoryController::ic->isItemInInventory(S("gun_ammo")))
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_21a1"), S("c_gun_ammo")); }
				if (danger - removeDanger > 1)
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_21a2a1"), String::Empty); }
				}
				else
				{
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_21a2b1"), String::Empty); }
				}
			}
		}
		if (danger - removeDanger > 1)
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, GameStrings::getString(GameStrings::results, S("r_d3_0_22a1")) + S(" ") + (danger - removeDanger) + S(" ") + GameStrings::getString(GameStrings::results, S("r_d3_0_22a2")), String::Empty, false); }
			if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3a1"), S("c_barry_dead_bandits")); }
				winQuality = 1;
				GameDataController::gd->setObjective(S("npc2_alive"), false);
				GameDataController::gd->setObjectiveDetail(S("npc2_alive"), 2);
			}
			if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3a2"), S("c_cody_dead_bandits")); }
				winQuality = 1;
				GameDataController::gd->setObjective(S("npc3_alive"), false);
				GameDataController::gd->setObjectiveDetail(S("npc3_alive"), 2);
			}
			if ((GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2) || (GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2))
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3a3"), String::Empty); }
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3a4"), String::Empty); }
				if (danger - removeDanger <= 3)
				{
					{ int _old = removeDanger; removeDanger = _old + check(danger - removeDanger - 1, S("r_d3_0_22a3a5"), String::Empty); }
					{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_22a3a6"), String::Empty); }
				}
				else
				{
					{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3b1"), String::Empty); }
					{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3b2"), String::Empty); }
				}
			}
			else
			{
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3b1"), String::Empty); }
				{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3b2"), String::Empty); }
			}
		}
		else
		{
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3c1"), S("c_razor")); }
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3c2"), String::Empty); }
			{ int _old = removeDanger; removeDanger = _old + check(0, S("r_d3_0_22a3c3"), String::Empty); }
			{ int _old = removeDanger; removeDanger = _old + check(1, S("r_d3_0_22a3c4"), String::Empty); }
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::liveOrDie(val); };
		timelineAction->actionWithText = true;
		timelineAction->param = S("0");
		timelineAction->text = String::Empty;
		Timeline::t->addAction(timelineAction);
	}
	else
	{
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d3_0_1b1"));
		timelineAction->function = [this](String val) { ResultsController::liveOrDie(val); };
		Timeline::t->addAction(timelineAction);
		analytics_stayed = S("outside");
	}
}

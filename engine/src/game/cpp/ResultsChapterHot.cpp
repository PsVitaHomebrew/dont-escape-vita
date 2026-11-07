#include "../game_all.h"

int ResultsChapterHot::checkWindows(P<TimelineAction> tla, String name1, String name2, int value1)
{
	int num = value1 - 3;
	int num2 = value1 - 3;
	int num3 = value1 - 3;
	int num4 = value1 - 3;
	int num5 = 2;
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
		num6 = value1;
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
		num6 = value1;
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
		num6 = value1;
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
		num6 = value1;
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
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_net")) + GameStrings::getString(GameStrings::results, S("net_nailed"));
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
		tla->text = GameStrings::getString(GameStrings::results, String::Empty + name1 + S("_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
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

void ResultsChapterHot::chapterResult()
{
	surviavbleDanger = 20;
	danger = 0;
	removeDanger = 0;
	winQuality = 3;
	pbc->total = 100;
	changeDanger(str(pbc->total));
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_intro1"));
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_intro2"));
	Timeline::t->addAction(timelineAction);
	if (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2") || GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom"))
	{
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_house"));
		Timeline::t->addAction(timelineAction);
		analytics_stayed = S("base");
		int num = pbc->total - removeDanger;
		float num2 = 4.0f;
		float num3 = 4.0f;
		float num4 = 8.0f;
		float num5 = 8.0f;
		float num6 = 8.0f;
		float num7 = 8.0f;
		num = danger - removeDanger - (int)num2 - (int)num3 - (int)num4 - (int)num5 - (int)num6 - (int)num7;
		int num8 = 0;
		int num9 = (int)num2 - 1;
		int num10 = (int)num2;
		int num11 = 0;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		if (GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_door1_open");
		}
		else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
		{
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_door1_closed_towel");
		}
		else
		{
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_door1_closed");
		}
		timelineAction->text = String::Empty;
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = false;
		if (GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			timelineAction->param = S("0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_door1_open"));
		}
		else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
		{
			num11 = num10;
			if ((float)num11 > num2)
			{
				num11 = (int)num2;
			}
			removeDanger += num11;
			timelineAction->param = S("-") + num11;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_door1_closed1T")) + S(" ") + num11 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_door1_closed2T"));
		}
		else
		{
			num11 = num9;
			if ((float)num11 > num2)
			{
				num11 = (int)num2;
			}
			removeDanger += num11;
			timelineAction->param = S("-") + num11;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_door1_closed1")) + S(" ") + num11 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_door1_closed2"));
		}
		Timeline::t->addAction(timelineAction);
		analytics_doors = num11 + S("/");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num11 = 0;
		if (GameDataController::gd->getObjective(S("location02_door_open")))
		{
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_door2_open");
		}
		else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
		{
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_door2_closed_towel");
		}
		else
		{
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_door2_closed");
		}
		timelineAction->text = String::Empty;
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = false;
		if (GameDataController::gd->getObjective(S("location02_door_open")))
		{
			timelineAction->param = S("0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_door2_open"));
		}
		else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
		{
			num11 = num10;
			if ((float)num11 > num3)
			{
				num11 = (int)num3;
			}
			removeDanger += num11;
			timelineAction->param = S("-") + num11;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_door2_closed1T")) + S(" ") + num11 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_door2_closed2T"));
		}
		else
		{
			num11 = num9;
			if ((float)num11 > num3)
			{
				num11 = (int)num3;
			}
			removeDanger += num11;
			timelineAction->param = S("-") + num11;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_door2_closed1")) + S(" ") + num11 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_door2_closed2"));
		}
		Timeline::t->addAction(timelineAction);
		analytics_doors = analytics_doors + num11 + S("/");
		int num12 = (int)num7;
		int num13 = (int)num7;
		int num14 = (int)num7;
		int num15 = (int)num7;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		int num16 = 0;
		num16 = checkWindows(timelineAction, S("window1"), S("window_1"), (int)num4);
		Timeline::t->addAction(timelineAction);
		removeDanger += num16;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num16;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_window_result1")) + S(" ") + num16 + String::Empty + GameStrings::getString(GameStrings::results, S("hot_window_result2"));
		Timeline::t->addAction(timelineAction);
		analytics_doors = analytics_doors + num16 + S("/");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num16 = 0;
		num16 = checkWindows(timelineAction, S("window2"), S("window_2"), (int)num5);
		Timeline::t->addAction(timelineAction);
		removeDanger += num16;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num16;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_window_result1")) + S(" ") + num16 + String::Empty + GameStrings::getString(GameStrings::results, S("hot_window_result2"));
		Timeline::t->addAction(timelineAction);
		analytics_doors = analytics_doors + num16 + S("/");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num16 = 0;
		num16 = checkWindows(timelineAction, S("window3"), S("window_3"), (int)num6);
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num16;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_window_result1")) + S(" ") + num16 + String::Empty + GameStrings::getString(GameStrings::results, S("hot_window_result2"));
		removeDanger += num16;
		Timeline::t->addAction(timelineAction);
		analytics_doors = analytics_doors + num16 + S("/");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num16 = 0;
		if (GameDataController::gd->getObjective(S("base_hatch_therm")))
		{
			num16 = num15;
			if ((float)num16 > num6)
			{
				num16 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_therm");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_therm"));
		}
		else if (GameDataController::gd->getObjective(S("base_hatch_flag")))
		{
			num16 = num14;
			if ((float)num16 > num6)
			{
				num16 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_flag");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_flag"));
		}
		else if (GameDataController::gd->getObjective(S("base_hatch_blanketb")))
		{
			num16 = num12;
			if ((float)num16 > num6)
			{
				num16 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_blanketb");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_blanketb"));
		}
		else if (GameDataController::gd->getObjective(S("base_hatch_blanket")))
		{
			num16 = num13;
			if ((float)num16 > num6)
			{
				num16 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_blanket");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_blanket"));
		}
		else
		{
			num16 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_empty"));
		}
		Timeline::t->addAction(timelineAction);
		analytics_doors = analytics_doors + num16 + S("/");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num16;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_hatch_result1")) + S(" ") + num16 + String::Empty + GameStrings::getString(GameStrings::results, S("hot_hatch_result2"));
		removeDanger += num16;
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
		{
			analytics_oven = S("disabled");
			if (GameDataController::gd->getObjective(S("kitchen_oven_open")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_oven");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_kitchen_oven"));
				Timeline::t->addAction(timelineAction);
				int num17 = 4;
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = String::Empty + num17;
				removeDanger += -num17;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_oven_result_1")) + S(" ") + num17 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_oven_result_2"));
				Timeline::t->addAction(timelineAction);
				analytics_oven = S("enabled");
			}
			analytics_fan = S("disabled");
			if (GameDataController::gd->getObjective(S("kitchen_fan_plugged")) || GameDataController::gd->getObjective(S("base_fan_cord_plugged")))
			{
				if (GameDataController::gd->getObjective(S("kitchen_fan_plugged")))
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_fan");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_kitchen_fan"));
					Timeline::t->addAction(timelineAction);
				}
				else if (GameDataController::gd->getObjective(S("base_fan_cord_plugged")))
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_fan");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_base_fan"));
					Timeline::t->addAction(timelineAction);
				}
				int num18 = 24;
				analytics_fan = S("enabled");
				if ((GameDataController::gd->getObjective(S("kitchen_fan_plugged")) && GameDataController::gd->previousLocation != S("Location2")) || (GameDataController::gd->getObjective(S("base_fan_cord_plugged")) && GameDataController::gd->previousLocation != S("Location1")))
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-0");
					num18 /= 2;
					timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_fan_wrong_room"));
					Timeline::t->addAction(timelineAction);
					analytics_fan = S("wrong_room");
				}
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = S("-") + num18;
				removeDanger += num18;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_fan_result_1")) + S(" ") + num18 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_fan_result_2"));
				Timeline::t->addAction(timelineAction);
			}
			analytics_ac = S("disabled");
			if (GameDataController::gd->getObjective(S("base_ac_cord_plugged")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_ac");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_base_ac"));
				Timeline::t->addAction(timelineAction);
				int num19 = 26;
				analytics_ac = S("enabled");
				if (GameDataController::gd->previousLocation != S("Location1"))
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-0");
					num19 /= 2;
					timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_ac_base_wrong"));
					Timeline::t->addAction(timelineAction);
					analytics_ac = S("wrong_room");
				}
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = S("-") + num19;
				removeDanger += num19;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_ac_result_1")) + S(" ") + num19 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_ac_result_2"));
				Timeline::t->addAction(timelineAction);
			}
		}
		else
		{
			if (GameDataController::gd->getObjective(S("base_ac_cord_plugged")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_ac");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_ac_off"));
				Timeline::t->addAction(timelineAction);
				analytics_ac = S("no_power");
			}
			if (GameDataController::gd->getObjective(S("kitchen_fan_plugged")) || GameDataController::gd->getObjective(S("base_fan_cord_plugged")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_fan");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_fan_off"));
				Timeline::t->addAction(timelineAction);
				analytics_fan = S("no_power");
			}
		}
		int num20 = 0;
		if (ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("Location1") || ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("Location2") || ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("LocationBaseUpstairs") || ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("LocationBaseBathroom"))
		{
			num20++;
		}
		if (ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("Location1") || ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("Location2") || ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("LocationBaseUpstairs") || ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("LocationBaseBathroom"))
		{
			num20++;
		}
		if (ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("Location1") || ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("Location2") || ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("LocationBaseUpstairs") || ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("LocationBaseBathroom"))
		{
			num20++;
		}
		if (num20 > 0)
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_absorbertile");
			if (num20 == 1)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_absorber_base_1"));
			}
			if (num20 == 2)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_absorber_base_2"));
			}
			if (num20 == 3)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_absorber_base_3"));
			}
			Timeline::t->addAction(timelineAction);
			int num21 = 0;
			if (ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation != GameDataController::gd->previousLocation)
			{
				num21++;
			}
			if (ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation != GameDataController::gd->previousLocation)
			{
				num21++;
			}
			if (ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation != GameDataController::gd->previousLocation)
			{
				num21++;
			}
			if (num21 > 0)
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-0");
				if (num21 == 1)
				{
					timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_wrong_absorber_1"));
				}
				if (num21 == 2)
				{
					timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_wrong_absorber_2"));
				}
				if (num21 == 3)
				{
					timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_wrong_absorber_3"));
				}
				Timeline::t->addAction(timelineAction);
			}
			analytics_cooler = num20 + S("/") + num21;
			int num22 = 7;
			int num23 = (int)((float)(num22 * num20) - (float)(num20 * num21) / 2.0f);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->param = S("-") + num23;
			removeDanger += num23;
			if (num20 == 1)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_absorber_result_1a")) + S(" ") + num23 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_absorber_result_2"));
			}
			else
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_absorber_result_1b")) + S(" ") + num23 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_absorber_result_2"));
			}
			Timeline::t->addAction(timelineAction);
		}
	}
	else if (GameDataController::gd->previousLocation == S("LocationCave"))
	{
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_cave"));
		Timeline::t->addAction(timelineAction);
		int num24 = 15;
		int num25 = 20;
		analytics_stayed = S("cave");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		int num26 = 0;
		if (GameDataController::gd->getObjective(S("rv_cave_therm")))
		{
			num26 = num25;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_cave_therm");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cave_therm"));
		}
		else if (GameDataController::gd->getObjective(S("rv_cave_flag")))
		{
			num26 = num25;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_cave_flag");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cave_flag"));
		}
		else if (GameDataController::gd->getObjective(S("rv_cave_blanketb")))
		{
			num26 = num25;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_cave_blanketb");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cave_blanketb"));
		}
		else if (GameDataController::gd->getObjective(S("rv_cave_blanket")))
		{
			num26 = num25;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_cave_blanket");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cave_blanket"));
		}
		else
		{
			num26 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_cave_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cave_empty"));
		}
		Timeline::t->addAction(timelineAction);
		num26 += num24;
		analytics_doors = num26 + String::Empty;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num26;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_cave_result1")) + S(" ") + num26 + String::Empty + GameStrings::getString(GameStrings::results, S("hot_cave_result2"));
		removeDanger += num26;
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getObjective(S("cave_ac_cord_plugged")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_ac");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_cave_ac"));
			Timeline::t->addAction(timelineAction);
			analytics_ac = S("enabled");
			int num27 = 26;
			if (!GameDataController::gd->getObjective(S("rv_started")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-0");
				num27 /= 2;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_ac_cave_no_fuel"));
				Timeline::t->addAction(timelineAction);
				analytics_ac = S("low_power");
			}
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->param = S("-") + num27;
			removeDanger += num27;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_ac_result_1")) + S(" ") + num27 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_ac_result_2"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjective(S("cave_fan_cord_plugged")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_fan");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_cave_fan"));
			Timeline::t->addAction(timelineAction);
			analytics_fan = S("enabled");
			int num28 = 24;
			if (!GameDataController::gd->getObjective(S("rv_started")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-0");
				num28 /= 2;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_fan_cave_no_fuel"));
				Timeline::t->addAction(timelineAction);
				analytics_fan = S("low_power");
			}
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->param = S("-") + num28;
			removeDanger += num28;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_fan_result_1")) + S(" ") + num28 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_fan_result_2"));
			Timeline::t->addAction(timelineAction);
		}
		int num29 = 0;
		if (ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("LocationCave"))
		{
			num29++;
		}
		if (ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("LocationCave"))
		{
			num29++;
		}
		if (ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("LocationCave"))
		{
			num29++;
		}
		analytics_cooler = num29 + String::Empty;
		if (num29 > 0)
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_absorbertile");
			if (num29 == 1)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_absorber_cave_1"));
			}
			if (num29 == 2)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_absorber_cave_2"));
			}
			if (num29 == 3)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_absorber_cave_3"));
			}
			Timeline::t->addAction(timelineAction);
			int num30 = 0;
			int num31 = 7;
			int num32 = (int)((float)(num31 * num29) - (float)(num29 * num30) / 2.0f);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->param = S("-") + num32;
			removeDanger += num32;
			if (num29 == 1)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_absorber_result_1a")) + S(" ") + num32 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_absorber_result_2"));
			}
			else
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_absorber_result_1b")) + S(" ") + num32 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_absorber_result_2"));
			}
			Timeline::t->addAction(timelineAction);
		}
	}
	else
	{
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_no_house"));
		timelineAction->function = [this](String val) { ResultsController::liveOrDie(val); };
		Timeline::t->addAction(timelineAction);
		analytics_stayed = S("outside");
	}
	if (!(GameDataController::gd->previousLocation == S("Location1")) && !(GameDataController::gd->previousLocation == S("Location2")) && !(GameDataController::gd->previousLocation == S("LocationBaseUpstairs")) && !(GameDataController::gd->previousLocation == S("LocationBaseBathroom")) && !(GameDataController::gd->previousLocation == S("LocationCave")))
	{
		return;
	}
	analytics_gear = GameDataController::gd->equipped;
	if (ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation == S("ginger"))
	{
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_water");
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_ginger_water"));
		Timeline::t->addAction(timelineAction);
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")) && (ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation == S("npc3")))
	{
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_water");
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_cody_water"));
		Timeline::t->addAction(timelineAction);
	}
	if (removeDanger >= pbc->total)
	{
		winQuality = 3;
	}
	else
	{
		winQuality = 2;
	}
	if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		if (ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation == S("npc2"))
		{
			if (removeDanger >= 80)
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_water");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_barry_water"));
				Timeline::t->addAction(timelineAction);
			}
			else
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_barry_dead_hot");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_barry_dead_water"));
				Timeline::t->addAction(timelineAction);
				GameDataController::gd->setObjective(S("npc2_alive"), false);
				GameDataController::gd->setObjectiveDetail(S("npc2_alive"), 0);
				winQuality = 1;
			}
		}
		else if (removeDanger < 100)
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_barry_dead_hot");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_barry_dead_hot"));
			Timeline::t->addAction(timelineAction);
			GameDataController::gd->setObjective(S("npc2_alive"), false);
			GameDataController::gd->setObjectiveDetail(S("npc2_alive"), 0);
			winQuality = 1;
		}
	}
	if (InventoryController::ic->isItemEquipped(S("water1")) || InventoryController::ic->isItemEquipped(S("water2")) || InventoryController::ic->isItemEquipped(S("water3")) || InventoryController::ic->isItemEquipped(S("water4")))
	{
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_water");
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_water"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + 10;
		removeDanger += 10;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("hot_water_result_1")) + S(" ") + 10 + S(" ") + GameStrings::getString(GameStrings::results, S("hot_water_result_2"));
		Timeline::t->addAction(timelineAction);
	}
	if (winQuality != 1)
	{
		if (removeDanger >= pbc->total)
		{
			winQuality = 3;
		}
		else
		{
			winQuality = 2;
		}
	}
	timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->function = [this](String val) { ResultsController::liveOrDie(val); };
	timelineAction->actionWithText = true;
	timelineAction->param = S("0");
	timelineAction->text = String::Empty;
	Timeline::t->addAction(timelineAction);
}

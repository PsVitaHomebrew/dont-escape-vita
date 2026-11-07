#include "../game_all.h"

int ResultsChapterCold::checkWindows(P<TimelineAction> tla, String name1, String name2, int value1)
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

void ResultsChapterCold::chapterResult()
{
	surviavbleDanger = 20;
	danger = 0;
	removeDanger = 0;
	winQuality = 3;
	pbc->total = 100;
	int num = 30;
	int num2 = 3;
	int num3 = 3;
	changeDanger(str(pbc->total));
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_intro1"));
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_intro2"));
	Timeline::t->addAction(timelineAction);
	if (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2") || GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom"))
	{
		analytics_stayed = S("base");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_house"));
		Timeline::t->addAction(timelineAction);
		int num4 = pbc->total - removeDanger;
		float num5 = 3.0f;
		float num6 = 3.0f;
		float num7 = 6.0f;
		float num8 = 6.0f;
		float num9 = 6.0f;
		float num10 = 6.0f;
		num4 = danger - removeDanger - (int)num5 - (int)num6 - (int)num7 - (int)num8 - (int)num9 - (int)num10;
		int num11 = 0;
		int num12 = (int)num5 - 1;
		int num13 = (int)num5;
		int num14 = 0;
		analytics_doors = String::Empty;
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
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_door1_open"));
		}
		else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
		{
			num14 = num13;
			if ((float)num14 > num5)
			{
				num14 = (int)num5;
			}
			removeDanger += num14;
			timelineAction->param = S("-") + num14;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_door1_closed1T")) + S(" ") + num14 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_door1_closed2T"));
		}
		else
		{
			num14 = num12;
			if ((float)num14 > num5)
			{
				num14 = (int)num5;
			}
			removeDanger += num14;
			timelineAction->param = S("-") + num14;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_door1_closed1")) + S(" ") + num14 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_door1_closed2"));
		}
		Timeline::t->addAction(timelineAction);
		analytics_doors = num14 + S("/");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num14 = 0;
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
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_door2_open"));
		}
		else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
		{
			num14 = num13;
			if ((float)num14 > num6)
			{
				num14 = (int)num6;
			}
			removeDanger += num14;
			timelineAction->param = S("-") + num14;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_door2_closed1T")) + S(" ") + num14 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_door2_closed2T"));
		}
		else
		{
			num14 = num12;
			if ((float)num14 > num6)
			{
				num14 = (int)num6;
			}
			removeDanger += num14;
			timelineAction->param = S("-") + num14;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_door2_closed1")) + S(" ") + num14 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_door2_closed2"));
		}
		Timeline::t->addAction(timelineAction);
		analytics_doors = analytics_doors + num14 + S("/");
		int num15 = (int)num7;
		int num16 = (int)num7 - 3;
		int num17 = (int)num7;
		int num18 = (int)num7 - 3;
		int num19 = (int)num7;
		int num20 = (int)num7 - 3;
		int num21 = (int)num7;
		int num22 = (int)num7 - 3;
		int num23 = 2;
		int num24 = (int)num10;
		int num25 = (int)num10;
		int num26 = (int)num10;
		int num27 = (int)num10;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		int num28 = 0;
		if (GameDataController::gd->getObjective(S("base_window1_broken")))
		{
			num28 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_open")) + S(" ") + GameStrings::getString(GameStrings::results, S("window_broken_barricade"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanketb_nailed")) && GameDataController::gd->getObjective(S("base_window_1_blanketb_taped")))
		{
			num28 = num15;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_blanketb_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanketb_taped")))
		{
			num28 = num15;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_blanketb_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanketb_nailed")))
		{
			num28 = num15 - num23;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_blanketb_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanketb")))
		{
			num28 = num16;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_blanketb_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanket_nailed")) && GameDataController::gd->getObjective(S("base_window_1_blanket_taped")))
		{
			num28 = num17;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_blanket_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanket_taped")))
		{
			num28 = num17;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_blanket_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanket_nailed")))
		{
			num28 = num17 - num23;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_blanket_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanket")))
		{
			num28 = num18;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_blanket_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_flag_nailed")) && GameDataController::gd->getObjective(S("base_window_1_flag_taped")))
		{
			num28 = num19;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_flag_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_flag_taped")))
		{
			num28 = num19;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_flag_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_flag_nailed")))
		{
			num28 = num19 - num23;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_flag_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_flag")))
		{
			num28 = num20;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_flag_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_therm_nailed")) && GameDataController::gd->getObjective(S("base_window_1_therm_taped")))
		{
			num28 = num21;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_therm_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_therm_taped")))
		{
			num28 = num21;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_therm_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_therm_nailed")))
		{
			num28 = num21 - num23;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_therm_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_therm")))
		{
			num28 = num22;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_therm_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")) && GameDataController::gd->getObjective(S("base_window_1_net_taped")))
		{
			num28 = 0;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net_taped")))
		{
			num28 = 0;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")))
		{
			num28 = 0;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net")))
		{
			num28 = 0;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
		{
			num28 = num17 / 2;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
		{
			num28 = num17 / 2;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil_nailed")))
		{
			num28 = num17 / 2;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil")))
		{
			num28 = num18 / 2;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
		{
			num28 = 0;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
		{
			num28 = 0;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")))
		{
			num28 = 0;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars")))
		{
			num28 = 0;
			if ((float)num28 > num7)
			{
				num28 = (int)num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
		}
		else
		{
			num28 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_open"));
		}
		Timeline::t->addAction(timelineAction);
		analytics_doors = analytics_doors + num28 + S("/");
		removeDanger += num28;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num28;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_window_result1")) + S(" ") + num28 + String::Empty + GameStrings::getString(GameStrings::results, S("cold_window_result2"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num28 = 0;
		if (GameDataController::gd->getObjective(S("base_window2_broken")))
		{
			num28 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_open")) + S(" ") + GameStrings::getString(GameStrings::results, S("window_broken_barricade"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_blanketb_nailed")) && GameDataController::gd->getObjective(S("base_window_2_blanketb_taped")))
		{
			num28 = num15;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_blanketb_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_blanketb_taped")))
		{
			num28 = num15;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_blanketb_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_blanketb_nailed")))
		{
			num28 = num15 - num23;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_blanketb_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_blanketb")))
		{
			num28 = num16;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_blanketb_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_blanket_nailed")) && GameDataController::gd->getObjective(S("base_window_2_blanket_taped")))
		{
			num28 = num17;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_blanket_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_blanket_taped")))
		{
			num28 = num17;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_blanket_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_blanket_nailed")))
		{
			num28 = num17 - num23;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_blanket_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_blanket")))
		{
			num28 = num18;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_blanket_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_flag_nailed")) && GameDataController::gd->getObjective(S("base_window_2_flag_taped")))
		{
			num28 = num19;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_flag_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_flag_taped")))
		{
			num28 = num19;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_flag_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_flag_nailed")))
		{
			num28 = num19 - num23;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_flag_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_flag")))
		{
			num28 = num20;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_flag_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_therm_nailed")) && GameDataController::gd->getObjective(S("base_window_2_therm_taped")))
		{
			num28 = num21;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_therm_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_therm_taped")))
		{
			num28 = num21;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_therm_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_therm_nailed")))
		{
			num28 = num21 - num23;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_therm_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_therm")))
		{
			num28 = num22;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_therm_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")) && GameDataController::gd->getObjective(S("base_window_2_net_taped")))
		{
			num28 = 0;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_net_taped")))
		{
			num28 = 0;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")))
		{
			num28 = 0;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_net")))
		{
			num28 = 0;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_2_foil_taped")))
		{
			num28 = num17 / 2;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil_taped")))
		{
			num28 = num17 / 2;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil_nailed")))
		{
			num28 = num17 / 2;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil")))
		{
			num28 = num18 / 2;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
		{
			num28 = 0;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
		{
			num28 = 0;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars_nailed")))
		{
			num28 = 0;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars")))
		{
			num28 = 0;
			if ((float)num28 > num8)
			{
				num28 = (int)num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
		}
		else
		{
			num28 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_open"));
		}
		Timeline::t->addAction(timelineAction);
		analytics_doors = analytics_doors + num28 + S("/");
		removeDanger += num28;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num28;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_window_result1")) + S(" ") + num28 + String::Empty + GameStrings::getString(GameStrings::results, S("cold_window_result2"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num28 = 0;
		if (GameDataController::gd->getObjective(S("base_window3_broken")))
		{
			num28 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_open")) + S(" ") + GameStrings::getString(GameStrings::results, S("window_broken_barricade"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")) && GameDataController::gd->getObjective(S("base_window_3_blanketb_taped")))
		{
			num28 = num15;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_blanketb_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanketb_taped")))
		{
			num28 = num15;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_blanketb_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")))
		{
			num28 = num15 - num23;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_blanketb_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanketb")))
		{
			num28 = num16;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_blanketb_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_blanketb")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanketb_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")) && GameDataController::gd->getObjective(S("base_window_3_blanket_taped")))
		{
			num28 = num17;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_blanket_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanket_taped")))
		{
			num28 = num17;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_blanket_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")))
		{
			num28 = num17 - num23;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_blanket_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanket")))
		{
			num28 = num18;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_blanket_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_blanket")) + S(" ") + GameStrings::getString(GameStrings::results, S("blanket_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_flag_nailed")) && GameDataController::gd->getObjective(S("base_window_3_flag_taped")))
		{
			num28 = num19;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_flag_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_flag_taped")))
		{
			num28 = num19;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_flag_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_flag_nailed")))
		{
			num28 = num19 - num23;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_flag_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_flag")))
		{
			num28 = num20;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_flag_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_flag")) + S(" ") + GameStrings::getString(GameStrings::results, S("flag_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_therm_nailed")) && GameDataController::gd->getObjective(S("base_window_3_therm_taped")))
		{
			num28 = num21;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_therm_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_therm_taped")))
		{
			num28 = num21;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_therm_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_therm_nailed")))
		{
			num28 = num21 - num23;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_therm_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_therm")))
		{
			num28 = num22;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_therm_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_therm")) + S(" ") + GameStrings::getString(GameStrings::results, S("therm_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")) && GameDataController::gd->getObjective(S("base_window_3_net_taped")))
		{
			num28 = 0;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net_taped")))
		{
			num28 = 0;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")))
		{
			num28 = 0;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net")))
		{
			num28 = 0;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
		{
			num28 = num17 / 2;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
		{
			num28 = num17 / 2;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")))
		{
			num28 = num17 / 2;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil")))
		{
			num28 = num18 / 2;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
		{
			num28 = 0;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
		{
			num28 = 0;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")))
		{
			num28 = 0;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars")))
		{
			num28 = 0;
			if ((float)num28 > num9)
			{
				num28 = (int)num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
		}
		else
		{
			num28 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_open"));
		}
		Timeline::t->addAction(timelineAction);
		analytics_doors = analytics_doors + num28 + S("/");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num28;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_window_result1")) + S(" ") + num28 + String::Empty + GameStrings::getString(GameStrings::results, S("cold_window_result2"));
		removeDanger += num28;
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num28 = 0;
		if (GameDataController::gd->getObjective(S("base_hatch_therm")))
		{
			num28 = num27;
			if ((float)num28 > num9)
			{
				num28 = (int)num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_therm");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_therm"));
		}
		else if (GameDataController::gd->getObjective(S("base_hatch_flag")))
		{
			num28 = num26;
			if ((float)num28 > num9)
			{
				num28 = (int)num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_flag");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_flag"));
		}
		else if (GameDataController::gd->getObjective(S("base_hatch_blanketb")))
		{
			num28 = num24;
			if ((float)num28 > num9)
			{
				num28 = (int)num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_blanketb");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_blanketb"));
		}
		else if (GameDataController::gd->getObjective(S("base_hatch_blanket")))
		{
			num28 = num25;
			if ((float)num28 > num9)
			{
				num28 = (int)num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_blanket");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_blanket"));
		}
		else
		{
			num28 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_hatch_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("hatch_empty"));
		}
		Timeline::t->addAction(timelineAction);
		analytics_doors = analytics_doors + num28 + String::Empty;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num28;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_hatch_result1")) + S(" ") + num28 + String::Empty + GameStrings::getString(GameStrings::results, S("cold_hatch_result2"));
		removeDanger += num28;
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num28 = 0;
		if (GameDataController::gd->getObjective(S("base_fireplace_lit")))
		{
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_fire_lit");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_lit"));
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->param = S("-") + num;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_lit_result_1")) + S(" ") + num + S(" ") + GameStrings::getString(GameStrings::results, S("cold_fire_lit_result_2"));
			removeDanger += num;
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->param = S("-") + 0;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_cold_wind"));
			Timeline::t->addAction(timelineAction);
			int num29 = 0;
			if (GameDataController::gd->getObjective(S("basket_note")))
			{
				num29++;
			}
			if (GameDataController::gd->getObjective(S("basket_papers")))
			{
				num29++;
			}
			if (GameDataController::gd->getObjective(S("basket_cash")))
			{
				num29++;
			}
			if (GameDataController::gd->getObjective(S("basket_bag")))
			{
				num29++;
			}
			analytics_basket = num29 + String::Empty;
			if (num29 >= 2)
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = S("-") + 0;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_extra_kindling2"));
				Timeline::t->addAction(timelineAction);
			}
			else if (num29 > 0)
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = S("-") + 0;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_extra_kindling1"));
				Timeline::t->addAction(timelineAction);
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = String::Empty + num3;
				removeDanger -= num3;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_extra_kindling_result1")) + S(" ") + num3 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_fire_extra_kindling_result2"));
				Timeline::t->addAction(timelineAction);
			}
			else
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = S("-") + 0;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_no_extra_kindling"));
				Timeline::t->addAction(timelineAction);
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = String::Empty + num3 * 2;
				removeDanger -= num3 * 2;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_extra_kindling_result1")) + S(" ") + num3 * 2 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_fire_extra_kindling_result2"));
				Timeline::t->addAction(timelineAction);
			}
			int num30 = 0;
			num30 += GameDataController::gd->getObjectiveDetail(S("basket_wood"));
			if (GameDataController::gd->getObjective(S("basket_charcoal")))
			{
				num30++;
			}
			analytics_fireplace = num30 + String::Empty;
			if (num30 == 4)
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_supplies_full"));
				Timeline::t->addAction(timelineAction);
			}
			else
			{
				if (num30 > 0)
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_fire_no_lit");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_supplies_some"));
					Timeline::t->addAction(timelineAction);
				}
				else
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_fire_no_lit");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_supplies_none"));
					Timeline::t->addAction(timelineAction);
				}
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = String::Empty + (4 - num30) * num2;
				removeDanger -= (4 - num30) * num2;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_supplies_result_1")) + S(" ") + (4 - num30) * num2 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_fire_supplies_result_2"));
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_fire_supplies_result_1")) + S(" ") + (4 - num30) + S(" ") + GameStrings::getString(GameStrings::results, S("cold_fire_supplies_result_2")) + S(" ") + (4 - num30) * num2 + GameStrings::getString(GameStrings::results, S("cold_fire_supplies_result_3"));
				Timeline::t->addAction(timelineAction);
			}
		}
		else
		{
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_fire_no_lit");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("fire_no_lit"));
			Timeline::t->addAction(timelineAction);
			analytics_fireplace = S("0");
			if (GameDataController::gd->getObjective(S("chimney_cleaned")))
			{
				int num31 = 0;
				num31 = ((removeDanger <= 10) ? removeDanger : 10);
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = S("+") + num31;
				removeDanger -= num31;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("fire_not_lit_unclogged_1")) + S(" ") + num31 + GameStrings::getString(GameStrings::results, S("fire_not_lit_unclogged_2"));
				Timeline::t->addAction(timelineAction);
				analytics_fireplace = S("-1");
			}
		}
		if (GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
		{
			if (GameDataController::gd->getObjective(S("kitchen_oven_open")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_oven");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_kitchen_oven"));
				Timeline::t->addAction(timelineAction);
				analytics_oven = S("enabled");
				int num32 = 14;
				if (GameDataController::gd->previousLocation != S("Location2"))
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-0");
					num32 /= 2;
					timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_oven_wrong_room"));
					Timeline::t->addAction(timelineAction);
					analytics_oven = S("wrong_room");
				}
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = S("-") + num32;
				removeDanger += num32;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_oven_result_1")) + S(" ") + num32 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_oven_result_2"));
				Timeline::t->addAction(timelineAction);
			}
			if (GameDataController::gd->getObjective(S("kitchen_heater_plugged")) || GameDataController::gd->getObjective(S("base_heater_cord_plugged")))
			{
				if (GameDataController::gd->getObjective(S("kitchen_heater_plugged")))
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_heater");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_kitchen_heater"));
					Timeline::t->addAction(timelineAction);
				}
				else if (GameDataController::gd->getObjective(S("base_heater_cord_plugged")))
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_heater");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_base_heater"));
					Timeline::t->addAction(timelineAction);
				}
				analytics_electric = S("enabled");
				int num33 = 22;
				if ((GameDataController::gd->getObjective(S("kitchen_heater_plugged")) && GameDataController::gd->previousLocation != S("Location2")) || (GameDataController::gd->getObjective(S("base_heater_cord_plugged")) && GameDataController::gd->previousLocation != S("Location1")))
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-0");
					num33 /= 2;
					timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_heater_wrong_room"));
					Timeline::t->addAction(timelineAction);
					analytics_electric = S("wrong_room");
				}
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = S("-") + num33;
				removeDanger += num33;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_heater_result_1")) + S(" ") + num33 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_heater_result_2"));
				Timeline::t->addAction(timelineAction);
			}
			if (ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation == S("Location1") || ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation == S("Location2") || ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation == S("LocationBaseUpstairs") || ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation == S("LocationBaseBathroom"))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_gasheater");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_gasheater"));
				Timeline::t->addAction(timelineAction);
				int num34 = 24;
				analytics_gas = S("enabled");
				if (ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation != GameDataController::gd->previousLocation)
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-0");
					num34 /= 2;
					timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_gasheater_wrong_room"));
					Timeline::t->addAction(timelineAction);
					analytics_gas = S("wrong_room");
				}
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->param = S("-") + num34;
				removeDanger += num34;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_gasheater_result_1")) + S(" ") + num34 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_gasheater_result_2"));
				Timeline::t->addAction(timelineAction);
			}
		}
		else
		{
			if (GameDataController::gd->getObjective(S("kitchen_oven_open")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_oven_off");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_kitchen_oven_off"));
				Timeline::t->addAction(timelineAction);
				analytics_oven = S("no_power");
			}
			if (GameDataController::gd->getObjective(S("kitchen_heater_plugged")) || GameDataController::gd->getObjective(S("base_heater_cord_plugged")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_heater_off");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_heater_off"));
				Timeline::t->addAction(timelineAction);
				analytics_electric = S("no_power");
			}
		}
		int num35 = 0;
		if (ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("Location1") || ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("Location2") || ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("LocationBaseUpstairs") || ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation == S("LocationBaseBathroom"))
		{
			num35++;
		}
		if (ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("Location1") || ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("Location2") || ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("LocationBaseUpstairs") || ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation == S("LocationBaseBathroom"))
		{
			num35++;
		}
		if (ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("Location1") || ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("Location2") || ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("LocationBaseUpstairs") || ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation == S("LocationBaseBathroom"))
		{
			num35++;
		}
		if (num35 > 0)
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_absorber");
			if (num35 == 1)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_absorber_1"));
			}
			if (num35 == 2)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_absorber_2"));
			}
			if (num35 == 3)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_absorber_3"));
			}
			Timeline::t->addAction(timelineAction);
			int num36 = 3;
			int num37 = num36 * num35;
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->param = String::Empty + num37;
			removeDanger += -num37;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_absorber_result_1")) + S(" ") + num37 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_absorber_result_2"));
			Timeline::t->addAction(timelineAction);
		}
		analytics_cooler = num35 + String::Empty;
		if (removeDanger >= pbc->total)
		{
			winQuality = 3;
		}
		else
		{
			winQuality = 2;
		}
		analytics_gear = GameDataController::gd->equipped;
		if (ItemsManager::im->getItem(S("coat1"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("coat2"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("coat3"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("coat4"))->dataRef->droppedLocation == S("ginger"))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_ginger_coat");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_ginger_coat"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjective(S("npc2_joined")) && (ItemsManager::im->getItem(S("coat1"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("coat2"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("coat3"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("coat4"))->dataRef->droppedLocation == S("npc2")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_barry_coat");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_barry_coat"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")))
		{
			if (ItemsManager::im->getItem(S("coat1"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("coat2"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("coat3"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("coat4"))->dataRef->droppedLocation == S("npc3"))
			{
				if (removeDanger >= 80)
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_cody_coated");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_cody_coat"));
					Timeline::t->addAction(timelineAction);
				}
				else
				{
					timelineAction = New<TimelineAction>(Timeline::t->textField);
					timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
					timelineAction->actionWithText = true;
					timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_cody_dead_coat");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_cody_dead_coat"));
					winQuality = 1;
					Timeline::t->addAction(timelineAction);
					GameDataController::gd->setObjective(S("npc3_alive"), false);
					GameDataController::gd->setObjectiveDetail(S("npc3_alive"), 0);
				}
			}
			else if (removeDanger < 100)
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_cody_dead_cold");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_cody_dead_cold"));
				Timeline::t->addAction(timelineAction);
				winQuality = 1;
				GameDataController::gd->setObjective(S("npc3_alive"), false);
				GameDataController::gd->setObjectiveDetail(S("npc3_alive"), 0);
			}
		}
		if (InventoryController::ic->isItemEquipped(S("coat1")) || InventoryController::ic->isItemEquipped(S("coat2")) || InventoryController::ic->isItemEquipped(S("coat3")) || InventoryController::ic->isItemEquipped(S("coat4")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_coat");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_coat"));
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->param = S("-") + 10;
			removeDanger += 10;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_coat_result_1")) + S(" ") + 10 + S(" ") + GameStrings::getString(GameStrings::results, S("cold_coat_result_2"));
			Timeline::t->addAction(timelineAction);
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
		timelineAction->text = GameStrings::getString(GameStrings::results, S("cold_no_house"));
		timelineAction->function = [this](String val) { ResultsController::liveOrDie(val); };
		Timeline::t->addAction(timelineAction);
		analytics_stayed = S("outside");
	}
}

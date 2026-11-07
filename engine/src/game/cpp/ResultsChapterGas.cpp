#include "../game_all.h"

void ResultsChapterGas::chapterResult()
{
	surviavbleDanger = 15;
	danger = 0;
	removeDanger = 0;
	pbc->total = 100;
	winQuality = 3;
	changeDanger(str(pbc->total));
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_intro"));
	Timeline::t->addAction(timelineAction);
	if (GameDataController::gd->getObjective(S("base_discovered")) && (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2") || GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom")))
	{
		analytics_stayed = S("base");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_house"));
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getObjective(S("barn_sprinklers_enabled")) && GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 2)
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			if (GameDataController::gd->getItemData(S("chem_glass_12"))->droppedLocation == S("sprinklers") || GameDataController::gd->getItemData(S("chem_glass_13"))->droppedLocation == S("sprinklers") || GameDataController::gd->getItemData(S("chem_glass_23"))->droppedLocation == S("sprinklers"))
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_sprinklers_1c");
			}
			else
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_sprinklers_0b");
			}
			timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_sprinklers_on"));
			Timeline::t->addAction(timelineAction);
			int num = 0;
			if (GameDataController::gd->getObjective(S("barn_sprinklers_b1")))
			{
				num++;
			}
			if (GameDataController::gd->getObjective(S("barn_sprinklers_b2")))
			{
				num++;
			}
			if (GameDataController::gd->getObjective(S("barn_sprinklers_b3")))
			{
				num++;
			}
			if (GameDataController::gd->getObjective(S("barn_sprinklers_b4")))
			{
				num++;
			}
			if (GameDataController::gd->getObjective(S("barn_sprinklers_b5")))
			{
				num++;
			}
			if (GameDataController::gd->getObjective(S("barn_sprinklers_b6")))
			{
				num++;
			}
			if (GameDataController::gd->getObjective(S("barn_sprinklers_b7")))
			{
				num++;
			}
			if (GameDataController::gd->getObjective(S("barn_sprinklers_b8")))
			{
				num++;
			}
			analytics_sprinklers = num + S("/");
			if (!GameDataController::gd->getObjective(S("barn_pipe_fixed")))
			{
				analytics_sprinklers = S("leaking");
				num /= 2;
			}
			else
			{
				analytics_sprinklers += S("fixed");
			}
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			if (num == 0)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("sprinklers_0%"));
			}
			else if (num <= 2)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("sprinklers_25%"));
			}
			else if (num <= 4)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("sprinklers_50%"));
			}
			else if (num <= 7)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("sprinklers_75%"));
			}
			else if (num == 8)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("sprinklers_100%"));
			}
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			int num2 = num * 2;
			removeDanger += num2;
			P<TimelineAction> timelineAction2 = timelineAction;
			String text = timelineAction2->text;
			timelineAction2->text = text + S(" ^") + GameStrings::getString(GameStrings::results, S("gas_sprinklers_result1")) + S(" ") + num2 + S(" ") + GameStrings::getString(GameStrings::results, S("gas_sprinklers_result2"));
			timelineAction->param = str(-num2);
			Timeline::t->addAction(timelineAction);
			if (GameDataController::gd->getItemData(S("chem_glass_12"))->droppedLocation == S("sprinklers") || GameDataController::gd->getItemData(S("chem_glass_13"))->droppedLocation == S("sprinklers") || GameDataController::gd->getItemData(S("chem_glass_23"))->droppedLocation == S("sprinklers"))
			{
				int num3 = 0;
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				if ((GameDataController::gd->getObjectiveDetail(S("gas_ph")) == 0 || GameDataController::gd->getObjectiveDetail(S("gas_ph")) == 1 || GameDataController::gd->getObjectiveDetail(S("gas_ph")) == 2) && GameDataController::gd->getItemData(S("chem_glass_12"))->droppedLocation == S("sprinklers"))
				{
					analytics_chemichal = S("correct");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_sprinklers_chem_good"));
					num3 = 3;
				}
				else if ((GameDataController::gd->getObjectiveDetail(S("gas_ph")) == 3 || GameDataController::gd->getObjectiveDetail(S("gas_ph")) == 4 || GameDataController::gd->getObjectiveDetail(S("gas_ph")) == 5) && GameDataController::gd->getItemData(S("chem_glass_13"))->droppedLocation == S("sprinklers"))
				{
					analytics_chemichal = S("correct");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_sprinklers_chem_good"));
					num3 = 3;
				}
				else if ((GameDataController::gd->getObjectiveDetail(S("gas_ph")) == 6 || GameDataController::gd->getObjectiveDetail(S("gas_ph")) == 7) && GameDataController::gd->getItemData(S("chem_glass_23"))->droppedLocation == S("sprinklers"))
				{
					analytics_chemichal = S("correct");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_sprinklers_chem_good"));
					num3 = 3;
				}
				else
				{
					analytics_chemichal = S("wrong");
					timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_sprinklers_chem_bad"));
					num3 = 0;
				}
				num3 *= num;
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				removeDanger += num3;
				timelineAction->param = str(-num3);
				P<TimelineAction> timelineAction3 = timelineAction;
				text = timelineAction3->text;
				timelineAction3->text = text + S(" ^") + GameStrings::getString(GameStrings::results, S("gas_sprinklers_result1b")) + S(" ") + num3 + S(" ") + GameStrings::getString(GameStrings::results, S("gas_sprinklers_result2b"));
				Timeline::t->addAction(timelineAction);
			}
		}
		int num4 = pbc->total - removeDanger;
		int num5 = num4 / 5;
		int num6 = num4 / 5;
		int num7 = num4 / 5;
		int num8 = num4 / 5;
		int num9 = num4 / 5;
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		MonoBehaviour::print(str(num4));
		num4 = danger - removeDanger - num5 - num6 - num7 - num8 - num9;
		while (num4 > 0)
		{
			if (num4 > 0)
			{
				num4--;
				num5++;
			}
			if (num4 > 0)
			{
				num4--;
				num6++;
			}
			if (num4 > 0)
			{
				num4--;
				num7++;
			}
			if (num4 > 0)
			{
				num4--;
				num8++;
			}
			if (num4 > 0)
			{
				num4--;
				num9++;
			}
		}
		MonoBehaviour::print(str(num5));
		MonoBehaviour::print(str(num6));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num8));
		MonoBehaviour::print(str(num9));
		int num10 = 4;
		int num11 = 8;
		int num12 = 0;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		if (GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			analytics_doors = S("open");
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_door1_open");
		}
		else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
		{
			analytics_doors = S("closed+towel");
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_door1_closed_towel");
		}
		else
		{
			analytics_doors = S("closed");
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
			timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_door1_open"));
		}
		else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
		{
			num12 = num11;
			if (num12 > num5)
			{
				num12 = num5;
			}
			removeDanger += num12;
			timelineAction->param = S("-") + num12;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_door1_closed1T")) + S(" ") + num12 + S(" ") + GameStrings::getString(GameStrings::results, S("gas_door1_closed2T"));
		}
		else
		{
			num12 = num10;
			if (num12 > num5)
			{
				num12 = num5;
			}
			removeDanger += num12;
			timelineAction->param = S("-") + num12;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_door1_closed1")) + S(" ") + num12 + S(" ") + GameStrings::getString(GameStrings::results, S("gas_door1_closed2"));
		}
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
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
			analytics_doors += S("/open");
			timelineAction->param = S("0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_door2_open"));
		}
		else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
		{
			analytics_doors += S("/closed+towel");
			num12 = num11;
			if (num12 > num6)
			{
				num12 = num6;
			}
			removeDanger += num12;
			timelineAction->param = S("-") + num12;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_door2_closed1T")) + S(" ") + num12 + S(" ") + GameStrings::getString(GameStrings::results, S("gas_door2_closed2T"));
		}
		else
		{
			analytics_doors += S("/closed");
			num12 = num10;
			if (num12 > num6)
			{
				num12 = num6;
			}
			removeDanger += num12;
			timelineAction->param = S("-") + num12;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_door2_closed1")) + S(" ") + num12 + S(" ") + GameStrings::getString(GameStrings::results, S("gas_door2_closed2"));
		}
		Timeline::t->addAction(timelineAction);
		int num13 = 0;
		int num14 = 0;
		int num15 = 8;
		int num16 = 2;
		int num17 = 0;
		int num18 = 0;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		int num19 = 0;
		if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")) && GameDataController::gd->getObjective(S("base_window_1_net_taped")))
		{
			analytics_window_1 = S("net/attached");
			num19 = num13;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net_taped")))
		{
			analytics_window_1 = S("net/attached");
			num19 = num13;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")))
		{
			analytics_window_1 = S("net/attached");
			num19 = num13;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net")))
		{
			analytics_window_1 = S("net/loose");
			num19 = num14;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
		{
			analytics_window_1 = S("foil/attached");
			num19 = num15;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
		{
			analytics_window_1 = S("foil/attached");
			num19 = num15;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil_nailed")))
		{
			analytics_window_1 = S("foil/attached");
			num19 = num15;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil")))
		{
			analytics_window_1 = S("foil/loose");
			num19 = num16;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
		{
			analytics_window_1 = S("bars/attached");
			num19 = num17;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
		{
			analytics_window_1 = S("bars/attached");
			num19 = num17;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")))
		{
			analytics_window_1 = S("bars/attached");
			num19 = num17;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars")))
		{
			analytics_window_1 = S("bars/loose");
			num19 = num18;
			if (num19 > num7)
			{
				num19 = num7;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
		}
		else
		{
			analytics_window_1 = S("empty");
			num19 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_open"));
		}
		Timeline::t->addAction(timelineAction);
		removeDanger += num19;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num19;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_window_result1")) + S(" ") + num19 + String::Empty + GameStrings::getString(GameStrings::results, S("gas_window_result2"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num19 = 0;
		if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")) && GameDataController::gd->getObjective(S("base_window_2_net_taped")))
		{
			analytics_window_2 = S("net/attached");
			num19 = num13;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_net_taped")))
		{
			analytics_window_2 = S("net/attached");
			num19 = num13;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")))
		{
			analytics_window_2 = S("net/attached");
			num19 = num13;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_net")))
		{
			analytics_window_2 = S("net/loose");
			num19 = num14;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_2_foil_taped")))
		{
			analytics_window_2 = S("foil/attached");
			num19 = num15;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil_taped")))
		{
			analytics_window_2 = S("foil/attached");
			num19 = num15;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil_nailed")))
		{
			analytics_window_2 = S("foil/attached");
			num19 = num15;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil")))
		{
			analytics_window_2 = S("foil/loose");
			num19 = num16;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
		{
			analytics_window_2 = S("bars/attached");
			num19 = num17;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
		{
			analytics_window_2 = S("bars/attached");
			num19 = num17;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars_nailed")))
		{
			analytics_window_2 = S("bars/attached");
			num19 = num17;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars")))
		{
			analytics_window_2 = S("bars/loose");
			num19 = num18;
			if (num19 > num8)
			{
				num19 = num8;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
		}
		else
		{
			analytics_window_2 = S("empty");
			num19 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_open"));
		}
		Timeline::t->addAction(timelineAction);
		removeDanger += num19;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num19;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_window_result1")) + S(" ") + num19 + String::Empty + GameStrings::getString(GameStrings::results, S("gas_window_result2"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num19 = 0;
		if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")) && GameDataController::gd->getObjective(S("base_window_3_net_taped")))
		{
			analytics_window_3 = S("net/attached");
			num19 = num13;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net_taped")))
		{
			analytics_window_3 = S("net/attached");
			num19 = num13;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")))
		{
			analytics_window_3 = S("net/attached");
			num19 = num13;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net")))
		{
			num19 = num14;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
		{
			analytics_window_3 = S("net/loose");
			num19 = num15;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
		{
			analytics_window_3 = S("foil/attached");
			num19 = num15;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")))
		{
			analytics_window_3 = S("foil/attached");
			num19 = num15;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil")))
		{
			analytics_window_3 = S("foil/loose");
			num19 = num16;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
		{
			analytics_window_3 = S("bars/attached");
			num19 = num17;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
		{
			analytics_window_3 = S("bars/attached");
			num19 = num17;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")))
		{
			analytics_window_3 = S("bars/attached");
			num19 = num17;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars")))
		{
			analytics_window_3 = S("bars/loose");
			num19 = num18;
			if (num19 > num9)
			{
				num19 = num9;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
		}
		else
		{
			analytics_window_3 = S("empty");
			num19 = 0;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_empty");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_open"));
		}
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("-") + num19;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_window_result1")) + S(" ") + num19 + String::Empty + GameStrings::getString(GameStrings::results, S("gas_window_result2"));
		removeDanger += num19;
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("0");
		timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_enter1")) + S(" ") + (danger - removeDanger) + GameStrings::getString(GameStrings::results, S("gas_enter2"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		timelineAction->text = String::Empty;
		if (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2"))
		{
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_groundfloor");
		}
		else if (GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom"))
		{
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_firstfloor");
		}
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		timelineAction->text = String::Empty;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		int num20 = 0;
		if (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2"))
		{
			if (GameDataController::gd->getObjectiveDetail(S("gas_dens")) < 161)
			{
				num20 = 20;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_groundfloor_good1")) + S(" ") + num20 + GameStrings::getString(GameStrings::results, S("gas_groundfloor_good2"));
				removeDanger += num20;
				analytics_floor = S("correct");
			}
			else
			{
				analytics_floor = S("wrong");
				num20 = 0;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_groundfloor_wrong"));
			}
			timelineAction->param = S("-") + num20;
		}
		else if (GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom"))
		{
			if (GameDataController::gd->getObjectiveDetail(S("gas_dens")) < 161)
			{
				num20 = 0;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_firstfloor_wrong"));
			}
			else
			{
				num20 = 20;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_firstfloor_good1")) + S(" ") + num20 + GameStrings::getString(GameStrings::results, S("gas_firstfloor_good2"));
				removeDanger += num20;
			}
			timelineAction->param = S("-") + num20;
		}
		Timeline::t->addAction(timelineAction);
		if (removeDanger >= pbc->total)
		{
			winQuality = 3;
		}
		else
		{
			winQuality = 2;
		}
		analytics_gear = GameDataController::gd->equipped;
		if (InventoryController::ic->isItemEquipped(S("chemsuit_dmg_dmg")) || InventoryController::ic->isItemEquipped(S("chemsuit_rep_dmg")) || InventoryController::ic->isItemEquipped(S("chemsuit_dmg_rep")) || InventoryController::ic->isItemEquipped(S("chemsuit_rep_rep")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_hazmat");
			timelineAction->text = String::Empty;
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			int num21 = 40;
			if (ItemsManager::im->getItem(S("chemsuit_dmg_dmg"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
			{
				num21 = 10;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_hazmat_dd_1")) + S(" ") + num21 + GameStrings::getString(GameStrings::results, S("gas_hazmat_dd_2"));
			}
			if (ItemsManager::im->getItem(S("chemsuit_rep_dmg"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
			{
				num21 = 25;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_hazmat_rd_1")) + S(" ") + num21 + GameStrings::getString(GameStrings::results, S("gas_hazmat_rd_2"));
			}
			if (ItemsManager::im->getItem(S("chemsuit_dmg_rep"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
			{
				num21 = 25;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_hazmat_dr_1")) + S(" ") + num21 + GameStrings::getString(GameStrings::results, S("gas_hazmat_dr_2"));
			}
			if (ItemsManager::im->getItem(S("chemsuit_rep_rep"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
			{
				num21 = 40;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_hazmat_rr_1")) + S(" ") + num21 + GameStrings::getString(GameStrings::results, S("gas_hazmat_dd_2"));
			}
			removeDanger += num21;
			timelineAction->param = S("-") + num21;
			Timeline::t->addAction(timelineAction);
		}
		else
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_hazmat_no");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_hazmat_no"));
			Timeline::t->addAction(timelineAction);
		}
		if (removeDanger < pbc->total)
		{
			winQuality = 1;
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
		timelineAction->text = GameStrings::getString(GameStrings::results, S("gas_no_house"));
		timelineAction->function = [this](String val) { ResultsController::liveOrDie(val); };
		Timeline::t->addAction(timelineAction);
		analytics_stayed = S("outside");
	}
}

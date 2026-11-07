#include "../game_all.h"

void ResultsChapterBugs::chapterResult()
{
	surviavbleDanger = 10;
	danger = 0;
	removeDanger = 0;
	winQuality = 3;
	pbc->total = 200;
	changeDanger(str(pbc->total));
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_intro"));
	Timeline::t->addAction(timelineAction);
	if (GameDataController::gd->getObjective(S("base_discovered")) && (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2") || GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom")))
	{
		analytics_stayed = S("base");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_house"));
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getObjective(S("barn_sprinklers_enabled")) && GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 2)
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			if (GameDataController::gd->getObjective(S("barn_sprinklers_fed2")))
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_sprinklers_2");
			}
			else if (GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_sprinklers_1");
			}
			else
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_sprinklers_0");
			}
			timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_sprinklers_on"));
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
				num /= 2;
				analytics_sprinklers += S("leaking");
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
			int num2 = num * 4;
			removeDanger += num2;
			P<TimelineAction> timelineAction2 = timelineAction;
			String text = timelineAction2->text;
			timelineAction2->text = text + S(" ^") + GameStrings::getString(GameStrings::results, S("bugs_sprinklers_result1")) + S(" ") + num2 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_sprinklers_result2"));
			timelineAction->param = str(-num2);
			Timeline::t->addAction(timelineAction);
			if (GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
			{
				int num3 = 0;
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				if (GameDataController::gd->getObjective(S("barn_sprinklers_fed2")))
				{
					timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_sprinklers_pest2"));
					num3 = 6;
				}
				else if (GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
				{
					timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_sprinklers_pest1"));
					num3 = 3;
				}
				analytics_pest = num3 + S("/20");
				num3 *= num;
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				removeDanger += num3;
				timelineAction->param = str(-num3);
				P<TimelineAction> timelineAction3 = timelineAction;
				text = timelineAction3->text;
				timelineAction3->text = text + S(" ^") + GameStrings::getString(GameStrings::results, S("bugs_sprinklers_result1b")) + S(" ") + num3 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_sprinklers_result2b"));
				Timeline::t->addAction(timelineAction);
			}
		}
		float num4 = 0.0f;
		if (ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1)
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_sonic_on"));
			timelineAction->actionWithText = true;
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			if (ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1)
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_sonic_outside");
			}
			else if (ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) != -1 || ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) != -1 || ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) != -1)
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_sonic_house");
			}
			else
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_sonic_outside");
			}
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			if (ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_sonic_location_OK"));
				num4 = 1.0f;
				analytics_sonic = S("outside");
			}
			else if (ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) != -1 || ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) != -1 || ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) != -1)
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_sonic_location_inside"));
				num4 = 0.5f;
				analytics_sonic = S("inside");
			}
			else
			{
				timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_sonic_location_wrong"));
				analytics_sonic = S("elsewhere");
				num4 = 0.0f;
			}
			Timeline::t->addAction(timelineAction);
			if (ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1 || ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) != -1 || ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) != -1 || ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) != -1)
			{
				bool flag = false;
				if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 1 && GameDataController::gd->getObjectiveDetail(S("sonic_frequency")) == 110)
				{
					flag = true;
				}
				if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 2 && GameDataController::gd->getObjectiveDetail(S("sonic_frequency")) == 135)
				{
					flag = true;
				}
				if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 3 && GameDataController::gd->getObjectiveDetail(S("sonic_frequency")) == 200)
				{
					flag = true;
				}
				if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 4 && GameDataController::gd->getObjectiveDetail(S("sonic_frequency")) == 385)
				{
					flag = true;
				}
				if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 5 && GameDataController::gd->getObjectiveDetail(S("sonic_frequency")) == 420)
				{
					flag = true;
				}
				if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 6 && GameDataController::gd->getObjectiveDetail(S("sonic_frequency")) == 430)
				{
					flag = true;
				}
				if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 7 && GameDataController::gd->getObjectiveDetail(S("sonic_frequency")) == 720)
				{
					flag = true;
				}
				if (GameDataController::gd->getObjectiveDetail(S("bug_type")) == 8 && GameDataController::gd->getObjectiveDetail(S("sonic_frequency")) == 800)
				{
					flag = true;
				}
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
				if (flag)
				{
					analytics_sonic += S("_good");
					int num5 = (int)(num4 * 50.0f);
					removeDanger += num5;
					timelineAction->param = str(-num5);
					timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_sonic_result1")) + S(" ") + num5 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_sonic_result2"));
				}
				else
				{
					analytics_sonic += S("_wrong");
					int num6 = (int)(num4 * 10.0f);
					timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_sonic_frequency_wrong1")) + S(" ") + num6 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_sonic_frequency_wrong2"));
					timelineAction->param = str(-num6);
					removeDanger += num6;
				}
				Timeline::t->addAction(timelineAction);
			}
		}
		int num7 = pbc->total - removeDanger;
		int num8 = num7 / 5;
		int num9 = num7 / 5;
		int num10 = num7 / 5;
		int num11 = num7 / 5;
		int num12 = num7 / 5;
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		MonoBehaviour::print(str(num7));
		num7 = danger - removeDanger - num8 - num9 - num10 - num11 - num12;
		while (num7 > 0)
		{
			if (num7 > 0)
			{
				num7--;
				num8++;
			}
			if (num7 > 0)
			{
				num7--;
				num9++;
			}
			if (num7 > 0)
			{
				num7--;
				num10++;
			}
			if (num7 > 0)
			{
				num7--;
				num11++;
			}
			if (num7 > 0)
			{
				num7--;
				num12++;
			}
		}
		MonoBehaviour::print(str(num8));
		MonoBehaviour::print(str(num9));
		MonoBehaviour::print(str(num10));
		MonoBehaviour::print(str(num11));
		MonoBehaviour::print(str(num12));
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		if (GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_door1_open");
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
			analytics_doors = S("open");
			timelineAction->param = S("0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_door1_open"));
		}
		else
		{
			analytics_doors = S("closed");
			removeDanger += num8;
			timelineAction->param = S("-") + num8;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_door1_closed1")) + S(" ") + num8 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_door1_closed2"));
		}
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		if (GameDataController::gd->getObjective(S("location02_door_open")))
		{
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_door2_open");
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
			timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_door2_open"));
		}
		else
		{
			analytics_doors += S("/closed");
			removeDanger += num9;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_door2_closed1")) + S(" ") + num9 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_door2_closed2"));
			timelineAction->param = -num9 + S("|Bitmaps/Locations/LocationResults/c_door2_closed");
		}
		Timeline::t->addAction(timelineAction);
		int num13 = 22;
		int num14 = 10;
		int num15 = 17;
		int num16 = 9;
		int num17 = 10;
		int num18 = 5;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		int num19 = 0;
		if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")) && GameDataController::gd->getObjective(S("base_window_1_net_taped")))
		{
			analytics_window_1 = S("net/attached");
			num19 = num13;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net_taped")))
		{
			analytics_window_1 = S("net/attached");
			num19 = num13 - 2;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")))
		{
			analytics_window_1 = S("net/attached");
			num19 = num13 - 1;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net")))
		{
			analytics_window_1 = S("net/loose");
			num19 = num14;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
		{
			analytics_window_1 = S("foil/attached");
			num19 = num15;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
		{
			analytics_window_1 = S("foil/attached");
			num19 = num15 - 3;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil_nailed")))
		{
			analytics_window_1 = S("foil/attached");
			num19 = num15 - 1;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_foil")))
		{
			analytics_window_1 = S("foil/loose");
			num19 = num16;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
		{
			analytics_window_1 = S("bars/attached");
			num19 = num17;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
		{
			analytics_window_1 = S("bars/attached");
			num19 = num17 - 3;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")))
		{
			analytics_window_1 = S("bars/attached");
			num19 = num17 - 1;
			if (num19 > num10)
			{
				num19 = num10;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars")))
		{
			analytics_window_1 = S("bars/loose");
			num19 = num18;
			if (num19 > num10)
			{
				num19 = num10;
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
		timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_window_result1")) + S(" ") + num10 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_window_result2")) + S(" ") + num19 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_window_result3"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num19 = 0;
		if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")) && GameDataController::gd->getObjective(S("base_window_2_net_taped")))
		{
			analytics_window_2 = S("net/attached");
			num19 = num13;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_net_taped")))
		{
			analytics_window_2 = S("net/attached");
			num19 = num13;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")))
		{
			analytics_window_2 = S("net/attached");
			num19 = num13;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_net")))
		{
			analytics_window_2 = S("net/loose");
			num19 = num14;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_2_foil_taped")))
		{
			analytics_window_2 = S("foil/attached");
			num19 = num15;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil_taped")))
		{
			analytics_window_2 = S("foil/attached");
			num19 = num15;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil_nailed")))
		{
			analytics_window_2 = S("foil/attached");
			num19 = num15;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_foil")))
		{
			analytics_window_2 = S("foil/loose");
			num19 = num16;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
		{
			analytics_window_2 = S("bars/attached");
			num19 = num17;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
		{
			analytics_window_2 = S("bars/attached");
			num19 = num17;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars_nailed")))
		{
			analytics_window_2 = S("bars/attached");
			num19 = num17;
			if (num19 > num11)
			{
				num19 = num11;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_2_bars")))
		{
			analytics_window_2 = S("bars/loose");
			num19 = num18;
			if (num19 > num11)
			{
				num19 = num11;
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
		timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_window_result1")) + S(" ") + num11 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_window_result2")) + S(" ") + num19 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_window_result3"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->actionWithText = true;
		num19 = 0;
		if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")) && GameDataController::gd->getObjective(S("base_window_3_net_taped")))
		{
			analytics_window_3 = S("net/attached");
			num19 = num13;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net_taped")))
		{
			analytics_window_3 = S("net/attached");
			num19 = num13;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")))
		{
			analytics_window_3 = S("net/attached");
			num19 = num13;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net")))
		{
			analytics_window_3 = S("net/loose");
			num19 = num14;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
		{
			analytics_window_3 = S("foil/attached");
			num19 = num15;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
		{
			analytics_window_3 = S("foil/attached");
			num19 = num15;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")))
		{
			analytics_window_3 = S("foil/attached");
			num19 = num15;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil")))
		{
			analytics_window_3 = S("foil/loose");
			num19 = num16;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
		{
			analytics_window_3 = S("bars/attached");
			num19 = num17;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_3");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
		{
			analytics_window_3 = S("bars/attached");
			num19 = num17;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_2");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")))
		{
			analytics_window_3 = S("bars/attached");
			num19 = num17;
			if (num19 > num12)
			{
				num19 = num12;
			}
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_1");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars")))
		{
			analytics_window_3 = S("bars/loose");
			num19 = num18;
			if (num19 > num12)
			{
				num19 = num12;
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
		timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_window_result1")) + S(" ") + num12 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_window_result2")) + S(" ") + num19 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_window_result3"));
		removeDanger += num19;
		Timeline::t->addAction(timelineAction);
		if (removeDanger >= pbc->total)
		{
			winQuality = 3;
		}
		else
		{
			winQuality = 2;
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
		timelineAction->param = S("0");
		timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_enter1")) + S(" ") + (danger - removeDanger) + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_enter2"));
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getObjective(S("bugs_bath")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_bath");
			timelineAction->text = String::Empty;
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			int num20 = 25;
			if (num20 > danger - removeDanger)
			{
				num20 = danger - removeDanger;
			}
			removeDanger += num20;
			timelineAction->param = S("-") + num20;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_bath1")) + S(" ") + num20 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_bath2"));
			Timeline::t->addAction(timelineAction);
		}
		analytics_weapon = GameDataController::gd->equipped;
		if (GameDataController::gd->equipped == S("flamethrower"))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_flamethrower_bugs");
			timelineAction->text = String::Empty;
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			int num21 = 40;
			if (num21 > danger - removeDanger)
			{
				num21 = danger - removeDanger;
			}
			removeDanger += num21;
			timelineAction->param = S("-") + num21;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_flamethrower1")) + S(" ") + num21 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_flamethrower2"));
			Timeline::t->addAction(timelineAction);
		}
		else if (GameDataController::gd->equipped == S("pestsprayer"))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_spray_bugs");
			timelineAction->text = String::Empty;
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			int num22 = 30;
			if (num22 > danger - removeDanger)
			{
				num22 = danger - removeDanger;
			}
			removeDanger += num22;
			timelineAction->param = S("-") + num22;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_spray1")) + S(" ") + num22 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_spray2"));
			Timeline::t->addAction(timelineAction);
		}
		else
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			timelineAction->actionWithText = true;
			String text2 = S("fists");
			int num23 = 5;
			if (GameDataController::gd->equipped == S("wrench"))
			{
				text2 = S("wrench");
				num23 = 20;
			}
			else if (GameDataController::gd->equipped == S("crowbar"))
			{
				text2 = S("crowbar");
				num23 = 20;
			}
			else if (GameDataController::gd->equipped == S("pipe"))
			{
				text2 = S("pipe");
				num23 = 20;
			}
			else if (GameDataController::gd->equipped.IndexOf(S("rifle")) != -1)
			{
				text2 = S("rifle");
				num23 = 25;
			}
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_bugfight_") + text2;
			timelineAction->text = String::Empty;
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String val) { ResultsController::changeDanger(val); };
			if (num23 > danger - removeDanger)
			{
				num23 = danger - removeDanger;
			}
			removeDanger += num23;
			timelineAction->param = S("-") + num23;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_fight_") + text2 + S("1")) + S(" ") + num23 + S(" ") + GameStrings::getString(GameStrings::results, S("bugs_fight_") + text2 + S("2"));
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
		analytics_stayed = S("outside");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_no_house"));
		timelineAction->function = [this](String val) { ResultsController::liveOrDie(val); };
		Timeline::t->addAction(timelineAction);
	}
}

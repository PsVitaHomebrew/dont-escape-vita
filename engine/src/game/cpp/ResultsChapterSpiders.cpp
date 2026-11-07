#include "../game_all.h"

void ResultsChapterSpiders::chapterResult()
{
	surviavbleDanger = 1;
	danger = 0;
	removeDanger = 0;
	winQuality = 3;
	pbc->total = 20;
	changeDanger(str(pbc->total));
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_intro"));
	Timeline::t->addAction(timelineAction);
	if (GameDataController::gd->getObjective(S("base_discovered")) && (GameDataController::gd->previousLocation == S("Location1") || GameDataController::gd->previousLocation == S("Location2") || GameDataController::gd->previousLocation == S("LocationBaseUpstairs") || GameDataController::gd->previousLocation == S("LocationBaseBathroom")))
	{
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_house"));
		Timeline::t->addAction(timelineAction);
		analytics_stayed = S("base");
		if (GameDataController::gd->getObjective(S("barn_sprinklers_enabled")) && GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 2)
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			if (GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_sprinklers_1b");
			}
			else
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_sprinklers_0b");
			}
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_sprinklers_on"));
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
				analytics_sprinklers += S("leaking");
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
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			int num2 = num * 0;
			removeDanger += num2;
			P<TimelineAction> timelineAction2 = timelineAction;
			timelineAction2->text = timelineAction2->text + S(" ^") + GameStrings::getString(GameStrings::results, S("spiders_sprinklers_result"));
			timelineAction->param = str(-num2);
			Timeline::t->addAction(timelineAction);
			if (GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
			{
				float num3 = 0.0f;
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				if (GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
				{
					timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_sprinklers_pest1"));
					num3 = 0.0f;
				}
				if (ItemsManager::im->getItem(S("spiderpest1"))->dataRef->droppedLocation == S("sprinklers") && GameDataController::gd->getObjectiveDetail(S("spiders_type")) == 1)
				{
					num3 = 0.75f;
					analytics_repel = S("correct");
				}
				else if (ItemsManager::im->getItem(S("spiderpest2"))->dataRef->droppedLocation == S("sprinklers") && GameDataController::gd->getObjectiveDetail(S("spiders_type")) == 0)
				{
					num3 = 0.75f;
					analytics_repel = S("correct");
				}
				else if (ItemsManager::im->getItem(S("spiderpest3"))->dataRef->droppedLocation == S("sprinklers") && GameDataController::gd->getObjectiveDetail(S("spiders_type")) == 2)
				{
					num3 = 0.75f;
					analytics_repel = S("correct");
				}
				else if (ItemsManager::im->getItem(S("spiderpest4"))->dataRef->droppedLocation == S("sprinklers") && GameDataController::gd->getObjectiveDetail(S("spiders_type")) == 3)
				{
					num3 = 0.75f;
					analytics_repel = S("correct");
				}
				else
				{
					num3 = 0.0f;
					analytics_repel = S("wrong");
				}
				num3 *= (float)num;
				if (num3 > 0.0f && num3 < 1.0f)
				{
					num3 = 1.0f;
				}
				num3 = (int)Mathf::Floor(num3);
				timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
				removeDanger += (int)num3;
				timelineAction->param = str(-(int)num3);
				if (num3 != 0.0f)
				{
					P<TimelineAction> timelineAction3 = timelineAction;
					String text = timelineAction3->text;
					timelineAction3->text = text + S(" ^") + GameStrings::getString(GameStrings::results, S("spiders_sprinklers_result1b")) + S(" ") + num3 + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_sprinklers_result2b"));
				}
				else
				{
					timelineAction->param = str(-1);
					removeDanger++;
					P<TimelineAction> timelineAction4 = timelineAction;
					timelineAction4->text = timelineAction4->text + S(" ^") + GameStrings::getString(GameStrings::results, S("spiders_sprinklers_result1fail"));
				}
				Timeline::t->addAction(timelineAction);
			}
		}
		analytics_traps = String::Empty;
		if ((ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1) || (ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_trap"));
			timelineAction->actionWithText = true;
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			int num4 = 0;
			int num5 = 0;
			if (ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1)
			{
				num4 = ((ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1) ? 1 : ((ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("location\t2")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) == -1) ? 3 : 2));
			}
			if (ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1)
			{
				num5 = ((ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1) ? 1 : ((ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("location01")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("location02")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) == -1) ? 3 : 2));
			}
			if (num4 == 1 && num5 == 1)
			{
				analytics_traps = S("2 traps outside");
			}
			else if (num4 == 1 || num5 == 1)
			{
				analytics_traps = S("1 trap outside");
			}
			else
			{
				analytics_traps = S("0 traps outside");
			}
			if (num4 == 1 || num5 == 1)
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_beartrap_0");
				Timeline::t->addAction(timelineAction);
			}
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_beartrap_1");
			timelineAction->actionWithText = true;
			timelineAction->instant = true;
			Timeline::t->addAction(timelineAction);
			if (num4 == 1 && num5 == 1)
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
				int num6 = 2;
				P<TimelineAction> timelineAction5 = timelineAction;
				timelineAction5->text = timelineAction5->text + String::Empty + GameStrings::getString(GameStrings::results, S("spiders_trap2a"));
				timelineAction->param = S("-") + num6 + S("|Bitmaps/Locations/LocationResults/c_beartrap_1");
				timelineAction->actionWithText = false;
				removeDanger += num6;
				Timeline::t->addAction(timelineAction);
			}
			else if (num4 == 1 || num5 == 1)
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
				int num7 = 1;
				P<TimelineAction> timelineAction6 = timelineAction;
				timelineAction6->text = timelineAction6->text + String::Empty + GameStrings::getString(GameStrings::results, S("spiders_trap1a"));
				timelineAction->param = S("-") + num7 + S("|Bitmaps/Locations/LocationResults/c_beartrap_1");
				timelineAction->actionWithText = false;
				removeDanger += num7;
				Timeline::t->addAction(timelineAction);
			}
		}
		bool flag = false;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
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
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->actionWithText = false;
		if (GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			analytics_doors = S("open");
			flag = true;
			timelineAction->param = S("0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_door1_open"));
		}
		else
		{
			analytics_doors = S("closed");
			removeDanger = removeDanger;
			timelineAction->param = S("0");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_door1_closed1")) + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_door1_closed2"));
		}
		Timeline::t->addAction(timelineAction);
		if (!flag)
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
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
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = false;
			if (GameDataController::gd->getObjective(S("location02_door_open")))
			{
				analytics_doors += S("/open");
				flag = true;
				timelineAction->param = S("0");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_door2_open"));
			}
			else
			{
				analytics_doors += S("/open");
				removeDanger = removeDanger;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_door2_closed1")) + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_door2_closed2"));
				timelineAction->param = 0 + S("|Bitmaps/Locations/LocationResults/c_door2_closed");
			}
			Timeline::t->addAction(timelineAction);
		}
		if (!flag)
		{
			int num8 = pbc->total - removeDanger;
			int num9 = num8 / 3;
			int num10 = num8 / 3;
			int num11 = num8 / 3;
			MonoBehaviour::print(str(num8));
			MonoBehaviour::print(str(num8));
			MonoBehaviour::print(str(num8));
			MonoBehaviour::print(str(num8));
			MonoBehaviour::print(str(num8));
			MonoBehaviour::print(str(num8));
			MonoBehaviour::print(str(num8));
			num8 = danger - removeDanger - num9 - num10 - num11;
			while (num8 > 0)
			{
				if (num8 > 0)
				{
					num8--;
					num9++;
				}
				if (num8 > 0)
				{
					num8--;
					num10++;
				}
				if (num8 > 0)
				{
					num8--;
					num11++;
				}
			}
			MonoBehaviour::print(str(num9));
			MonoBehaviour::print(str(num10));
			MonoBehaviour::print(str(num11));
			int num12 = 2;
			int num13 = 0;
			int num14 = 2;
			int num15 = 0;
			int num16 = 4;
			int num17 = 2;
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			int num18 = 0;
			if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")) && GameDataController::gd->getObjective(S("base_window_1_net_taped")))
			{
				analytics_window_1 = S("net/attached");
				num18 = num12 + 1;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_3");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_net_taped")))
			{
				analytics_window_1 = S("net/attached");
				num18 = num12 - 1;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_2");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")))
			{
				analytics_window_1 = S("net/attached");
				num18 = num12;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_1");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_net")))
			{
				analytics_window_1 = S("net/loose");
				num18 = num13;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_net_0");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
			{
				analytics_window_1 = S("foil/attached");
				num18 = num14 + 1;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_3");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_foil_taped")))
			{
				analytics_window_1 = S("foil/attached");
				num18 = num14 - 1;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_2");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_foil_nailed")))
			{
				analytics_window_1 = S("foil/attached");
				num18 = num14;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_1");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_foil")))
			{
				analytics_window_1 = S("foil/loose");
				num18 = num15;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_foil_0");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
			{
				analytics_window_1 = S("bars/attached");
				num18 = num16 + 1;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_3");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
			{
				analytics_window_1 = S("bars/attached");
				num18 = num16 - 1;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_2");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_bars_nailed")))
			{
				analytics_window_1 = S("bars/attached");
				num18 = num16;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_1");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_1_bars")))
			{
				analytics_window_1 = S("bars/loose");
				num18 = num17;
				if (num18 > num9)
				{
					num18 = num9;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_bars_0");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
			}
			else
			{
				analytics_window_1 = S("empty");
				num18 = 0;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window1_empty");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window1_open"));
			}
			Timeline::t->addAction(timelineAction);
			removeDanger += num18;
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->param = S("-") + num18;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_window_result1")) + S(" ") + num9 + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_window_result2")) + S(" ") + num18 + S(" ");
			if (num18 == 1)
			{
				timelineAction->text += GameStrings::getString(GameStrings::results, S("spiders_window_result_singular"));
			}
			else
			{
				timelineAction->text += GameStrings::getString(GameStrings::results, S("spiders_window_result3"));
			}
			if (num9 - num18 > 0)
			{
				P<TimelineAction> timelineAction7 = timelineAction;
				timelineAction7->text = timelineAction7->text + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_window_break"));
			}
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			num18 = 0;
			if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")) && GameDataController::gd->getObjective(S("base_window_2_net_taped")))
			{
				analytics_window_2 = S("net/attached");
				num18 = num12 + 1;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_3");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_net_taped")))
			{
				analytics_window_2 = S("net/attached");
				num18 = num12 - 1;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_2");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")))
			{
				analytics_window_2 = S("net/attached");
				num18 = num12;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_1");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_net")))
			{
				analytics_window_2 = S("net/loose");
				num18 = num13;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_net_0");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_2_foil_taped")))
			{
				analytics_window_2 = S("foil/attached");
				num18 = num14 + 1;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_3");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_foil_taped")))
			{
				analytics_window_2 = S("foil/attached");
				num18 = num14 - 1;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_2");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_foil_nailed")))
			{
				analytics_window_2 = S("foil/attached");
				num18 = num14;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_1");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_foil")))
			{
				analytics_window_2 = S("foil/loose");
				num18 = num15;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_foil_0");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
			{
				analytics_window_2 = S("bars/attached");
				num18 = num16 + 1;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_3");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
			{
				analytics_window_2 = S("bars/attached");
				num18 = num16 - 1;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_2");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_bars_nailed")))
			{
				analytics_window_2 = S("bars/attached");
				num18 = num16;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_1");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_2_bars")))
			{
				analytics_window_2 = S("bars/loose");
				num18 = num17;
				if (num18 > num10)
				{
					num18 = num10;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_bars_0");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
			}
			else
			{
				analytics_window_2 = S("empty");
				num18 = 0;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window2_empty");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window2_open"));
			}
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->param = S("-") + num18;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_window_result1")) + S(" ") + num10 + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_window_result2")) + S(" ") + num18 + S(" ");
			if (num18 == 1)
			{
				timelineAction->text += GameStrings::getString(GameStrings::results, S("spiders_window_result_singular"));
			}
			else
			{
				timelineAction->text += GameStrings::getString(GameStrings::results, S("spiders_window_result3"));
			}
			if (num10 - num18 > 0)
			{
				P<TimelineAction> timelineAction8 = timelineAction;
				timelineAction8->text = timelineAction8->text + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_window_break"));
			}
			removeDanger += num18;
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			num18 = 0;
			if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")) && GameDataController::gd->getObjective(S("base_window_3_net_taped")))
			{
				analytics_window_3 = S("net/attached");
				num18 = num12 + 1;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_3");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_net_taped")))
			{
				analytics_window_3 = S("net/attached");
				num18 = num12 - 1;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_2");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_taped"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")))
			{
				analytics_window_3 = S("net/attached");
				num18 = num12;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_1");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_net")))
			{
				analytics_window_3 = S("net/loose");
				num18 = num13;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_net_0");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_net")) + S(" ") + GameStrings::getString(GameStrings::results, S("net_none"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
			{
				analytics_window_3 = S("foil/attached");
				num18 = num14 + 1;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_3");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
			{
				analytics_window_3 = S("foil/attached");
				num18 = num14 - 1;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_2");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_taped"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")))
			{
				analytics_window_3 = S("foil/attached");
				num18 = num14;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_1");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_foil")))
			{
				analytics_window_3 = S("foil/loose");
				num18 = num15;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_foil_0");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_foil")) + S(" ") + GameStrings::getString(GameStrings::results, S("foil_none"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
			{
				analytics_window_3 = S("bars/attached");
				num18 = num16 + 1;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_3");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
			{
				analytics_window_3 = S("bars/attached");
				num18 = num16 - 1;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_2");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_taped"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")))
			{
				analytics_window_3 = S("bars/attached");
				num18 = num16;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_1");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_nailed"));
			}
			else if (GameDataController::gd->getObjective(S("base_window_3_bars")))
			{
				analytics_window_3 = S("bars/loose");
				num18 = num17;
				if (num18 > num11)
				{
					num18 = num11;
				}
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_bars_0");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_bars")) + S(" ") + GameStrings::getString(GameStrings::results, S("bars_none"));
			}
			else
			{
				analytics_window_3 = S("empty");
				num18 = 0;
				timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_window3_empty");
				timelineAction->text = GameStrings::getString(GameStrings::results, S("window3_open"));
			}
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->param = S("-") + num18;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_window_result1")) + S(" ") + num11 + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_window_result2")) + S(" ") + num18 + S(" ");
			if (num18 == 1)
			{
				timelineAction->text += GameStrings::getString(GameStrings::results, S("spiders_window_result_singular"));
			}
			else
			{
				timelineAction->text += GameStrings::getString(GameStrings::results, S("spiders_window_result3"));
			}
			if (num11 - num18 > 0)
			{
				P<TimelineAction> timelineAction9 = timelineAction;
				timelineAction9->text = timelineAction9->text + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_window_break"));
			}
			removeDanger += num18;
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
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->param = S("0");
		timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_enter1")) + S(" ") + (danger - removeDanger) + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_enter2"));
		Timeline::t->addAction(timelineAction);
		if ((ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1) || (ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_trap_b"));
			timelineAction->actionWithText = true;
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			int num19 = 0;
			int num20 = 0;
			if (ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1)
			{
				num19 = ((ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1) ? 1 : ((ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) == -1 && ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) == -1) ? 3 : 2));
			}
			if (ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1)
			{
				num20 = ((ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1) ? 1 : ((ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) == -1 && ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) == -1) ? 3 : 2));
			}
			if (num19 == 2 && num20 == 2)
			{
				analytics_traps += S("/2 traps inside");
			}
			else if (num19 == 2 || num20 == 2)
			{
				analytics_traps += S("/1 trap inside");
			}
			else
			{
				analytics_traps += S("/0 traps inside");
			}
			if (num19 == 2 || num20 == 2)
			{
				timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_beartrap_0");
				Timeline::t->addAction(timelineAction);
			}
			MonoBehaviour::print(S("TRAP STATUS: ") + num19 + S(" ") + num20 + S(" BECAUSE DROP LOCATIONS ARE ") + ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation + S(" ") + ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_beartrap_1");
			timelineAction->actionWithText = true;
			timelineAction->instant = true;
			Timeline::t->addAction(timelineAction);
			if (num19 == 2 && num20 == 2)
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
				timelineAction->actionWithText = false;
				int num21 = 2;
				P<TimelineAction> timelineAction10 = timelineAction;
				timelineAction10->text = timelineAction10->text + String::Empty + GameStrings::getString(GameStrings::results, S("spiders_trap2b"));
				timelineAction->param = S("-") + num21 + S("|Bitmaps/Locations/LocationResults/c_beartrap_1");
				removeDanger += num21;
				Timeline::t->addAction(timelineAction);
			}
			else if (num19 == 2 || num20 == 2)
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
				timelineAction->actionWithText = false;
				int num22 = 1;
				P<TimelineAction> timelineAction11 = timelineAction;
				timelineAction11->text = timelineAction11->text + String::Empty + GameStrings::getString(GameStrings::results, S("spiders_trap1b"));
				timelineAction->param = S("-") + num22 + S("|Bitmaps/Locations/LocationResults/c_beartrap_1");
				removeDanger += num22;
				Timeline::t->addAction(timelineAction);
			}
		}
		analytics_weapon = GameDataController::gd->equipped;
		if (InventoryController::ic->isItemEquipped(S("rifle_1")) || InventoryController::ic->isItemEquipped(S("rifle_2")) || InventoryController::ic->isItemEquipped(S("rifle_5")) || InventoryController::ic->isItemEquipped(S("rifle_3")) || InventoryController::ic->isItemEquipped(S("rifle_4")) || InventoryController::ic->isItemEquipped(S("rifle_6")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_rifle_spiders");
			timelineAction->text = String::Empty;
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			int num23 = 5;
			if (num23 > danger - removeDanger)
			{
				num23 = danger - removeDanger;
			}
			removeDanger += num23;
			timelineAction->param = S("-") + num23;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_rifle1")) + S(" ") + num23 + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_rifle2"));
			Timeline::t->addAction(timelineAction);
		}
		else if (InventoryController::ic->isItemEquipped(S("flamethrower")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_flamethrower_spiders");
			timelineAction->text = String::Empty;
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			int num24 = 7;
			if (num24 > danger - removeDanger)
			{
				num24 = danger - removeDanger;
			}
			removeDanger += num24;
			timelineAction->param = S("-") + num24;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_flamethrower1")) + S(" ") + num24 + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_flamethrower2"));
			Timeline::t->addAction(timelineAction);
		}
		else
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			String text2 = S("fists");
			int num25 = 1;
			if (InventoryController::ic->isItemEquipped(S("wrench")))
			{
				text2 = S("wrench");
				num25 = 2;
			}
			else if (InventoryController::ic->isItemEquipped(S("crowbar")))
			{
				text2 = S("crowbar");
				num25 = 2;
			}
			else if (InventoryController::ic->isItemEquipped(S("pipe")))
			{
				text2 = S("pipe");
				num25 = 2;
			}
			timelineAction->param = S("0|Bitmaps/Locations/LocationResults/c_spiderfight_") + text2;
			timelineAction->text = String::Empty;
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			if (num25 > danger - removeDanger)
			{
				num25 = danger - removeDanger;
			}
			removeDanger += num25;
			timelineAction->param = S("-") + num25;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("spiders_fight_") + text2 + S("1")) + S(" ") + num25 + S(" ") + GameStrings::getString(GameStrings::results, S("spiders_fight_") + text2 + S("2"));
			Timeline::t->addAction(timelineAction);
		}
		if (removeDanger < pbc->total)
		{
			winQuality = 1;
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
		winQuality = 0;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("bugs_no_house"));
		timelineAction->function = [this](String v) { ResultsController::liveOrDie(v); };
		Timeline::t->addAction(timelineAction);
	}
}

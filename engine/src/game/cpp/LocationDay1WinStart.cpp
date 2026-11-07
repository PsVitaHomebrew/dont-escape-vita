#include "../game_all.h"

void LocationDay1WinStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -5.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("none"));
	MonoBehaviour::print(S("............................. LOCATION INFO  .................................."));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->param = S("0");
	Timeline::t->textField->directionY = 1.0f;
	timelineAction->textWidth = 190;
	Timeline::t->textField->shift.x = -80.0f;
	GameDataController::Achievement(S("DAY_1"));
	GameDataController::gd->gameTime = 480;
	if (GameDataController::gd->getObjectiveDetail(S("day1_complete")) == 1)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			GameDataController::Achievement(S("P_SPIDERS"));
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_spiders_perfect"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			GameDataController::Achievement(S("P_GAS"));
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_gas_perfect"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			GameDataController::Achievement(S("P_LOCUST"));
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_bugs_perfect"));
			Timeline::t->addAction(timelineAction);
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { continueGame(param); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("0");
		Timeline::t->textField->directionY = 1.0f;
		timelineAction->textWidth = 190;
		Timeline::t->textField->shift.x = -80.0f;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_bonus"));
		Timeline::t->addAction(timelineAction);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day1_complete")) == 0)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_spiders_good"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_gas_good"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_bugs_good"));
			Timeline::t->addAction(timelineAction);
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { continueGame(param); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("0");
		Timeline::t->textField->directionY = 1.0f;
		timelineAction->textWidth = 190;
		Timeline::t->textField->shift.x = -80.0f;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_normal"));
		Timeline::t->addAction(timelineAction);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day1_complete")) < 0)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_spiders_poor1")) + S(" ") + -GameDataController::gd->getObjectiveDetail(S("day1_complete")) + S(" ") + GameStrings::getString(GameStrings::results, S("day1_spiders_poor2"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_gas_poor1")) + S(" ") + -GameDataController::gd->getObjectiveDetail(S("day1_complete")) + S(" ") + GameStrings::getString(GameStrings::results, S("day1_gas_poor2"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_bugs_poor1")) + S(" ") + -GameDataController::gd->getObjectiveDetail(S("day1_complete")) + S(" ") + GameStrings::getString(GameStrings::results, S("day1_bugs_poor2"));
			Timeline::t->addAction(timelineAction);
		}
		GameDataController::gd->gameTime = 540;
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { continueGame(param); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("0");
		Timeline::t->textField->directionY = 1.0f;
		timelineAction->textWidth = 190;
		Timeline::t->textField->shift.x = -80.0f;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_penalty"));
		Timeline::t->addAction(timelineAction);
	}
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_success);
	JukeboxAmbient::jb->changeAmbient(nullptr, 0.0f);
	if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")) || GameDataController::gd->getObjective(S("base_window_1_net_taped")) || GameDataController::gd->getObjective(S("base_window_1_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_1_foil_taped")) || GameDataController::gd->getObjective(S("base_window_1_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_1_bars_taped")))
	{
		GameDataController::gd->setObjective(S("base_window1_broken"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")) || GameDataController::gd->getObjective(S("base_window_2_net_taped")) || GameDataController::gd->getObjective(S("base_window_2_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_2_foil_taped")) || GameDataController::gd->getObjective(S("base_window_2_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
	{
		GameDataController::gd->setObjective(S("base_window2_broken"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")) || GameDataController::gd->getObjective(S("base_window_3_net_taped")) || GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_taped")) || GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
	{
		GameDataController::gd->setObjective(S("base_window3_broken"), true);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		if (GameDataController::gd->getObjective(S("base_window_1_bars")) && !GameDataController::gd->getObjective(S("base_window_1_bars_taped")) && !GameDataController::gd->getObjective(S("base_window_1_bars_nailed")))
		{
			GameDataController::gd->setObjective(S("base_window_1_bars"), false);
			Array<P<Item>> array = Array<P<Item>>::Of({
				ItemsManager::im->getItem(S("window_bars1")),
				ItemsManager::im->getItem(S("window_bars2")),
				ItemsManager::im->getItem(S("window_bars3"))
			});
			for (int i = 0; i < array.Length(); i++)
			{
				if (array[i]->dataRef->droppedLocation == S("window1"))
				{
					array[i]->dataRef->locX = 15;
					array[i]->dataRef->locY = 25;
					array[i]->dataRef->droppedLocation = S("Location1");
				}
			}
		}
		if (GameDataController::gd->getObjective(S("base_window_2_bars")) && !GameDataController::gd->getObjective(S("base_window_2_bars_taped")) && !GameDataController::gd->getObjective(S("base_window_2_bars_nailed")))
		{
			GameDataController::gd->setObjective(S("base_window_2_bars"), false);
			Array<P<Item>> array2 = Array<P<Item>>::Of({
				ItemsManager::im->getItem(S("window_bars1")),
				ItemsManager::im->getItem(S("window_bars2")),
				ItemsManager::im->getItem(S("window_bars3"))
			});
			for (int j = 0; j < array2.Length(); j++)
			{
				if (array2[j]->dataRef->droppedLocation == S("window2"))
				{
					array2[j]->dataRef->locX = 150;
					array2[j]->dataRef->locY = 35;
					array2[j]->dataRef->droppedLocation = S("LocationBaseUpstairs");
				}
			}
		}
		if (GameDataController::gd->getObjective(S("base_window_3_bars")) && !GameDataController::gd->getObjective(S("base_window_3_bars_taped")) && !GameDataController::gd->getObjective(S("base_window_3_bars_nailed")))
		{
			GameDataController::gd->setObjective(S("base_window_3_bars"), false);
			Array<P<Item>> array3 = Array<P<Item>>::Of({
				ItemsManager::im->getItem(S("window_bars1")),
				ItemsManager::im->getItem(S("window_bars2")),
				ItemsManager::im->getItem(S("window_bars3"))
			});
			for (int k = 0; k < array3.Length(); k++)
			{
				if (array3[k]->dataRef->droppedLocation == S("window3"))
				{
					array3[k]->dataRef->locX = 65;
					array3[k]->dataRef->locY = 25;
					array3[k]->dataRef->droppedLocation = S("LocationBaseBathroom");
				}
			}
		}
		if (GameDataController::gd->getObjective(S("base_window_1_net")) && !GameDataController::gd->getObjective(S("base_window_1_net_taped")) && !GameDataController::gd->getObjective(S("base_window_1_net_nailed")))
		{
			GameDataController::gd->setObjective(S("base_window_1_net"), false);
			Array<P<Item>> array4 = Array<P<Item>>::Of({
				ItemsManager::im->getItem(S("window_net1")),
				ItemsManager::im->getItem(S("window_net2")),
				ItemsManager::im->getItem(S("window_net3"))
			});
			for (int l = 0; l < array4.Length(); l++)
			{
				if (array4[l]->dataRef->droppedLocation == S("window1"))
				{
					array4[l]->dataRef->locX = 15;
					array4[l]->dataRef->locY = 25;
					array4[l]->dataRef->droppedLocation = S("Location1");
				}
			}
		}
		if (GameDataController::gd->getObjective(S("base_window_2_net")) && !GameDataController::gd->getObjective(S("base_window_2_net_taped")) && !GameDataController::gd->getObjective(S("base_window_2_net_nailed")))
		{
			GameDataController::gd->setObjective(S("base_window_2_net"), false);
			Array<P<Item>> array5 = Array<P<Item>>::Of({
				ItemsManager::im->getItem(S("window_net1")),
				ItemsManager::im->getItem(S("window_net2")),
				ItemsManager::im->getItem(S("window_net3"))
			});
			for (int m = 0; m < array5.Length(); m++)
			{
				if (array5[m]->dataRef->droppedLocation == S("window2"))
				{
					array5[m]->dataRef->locX = 150;
					array5[m]->dataRef->locY = 35;
					array5[m]->dataRef->droppedLocation = S("LocationBaseUpstairs");
				}
			}
		}
		if (GameDataController::gd->getObjective(S("base_window_3_net")) && !GameDataController::gd->getObjective(S("base_window_3_net_taped")) && !GameDataController::gd->getObjective(S("base_window_3_net_nailed")))
		{
			GameDataController::gd->setObjective(S("base_window_3_net"), false);
			Array<P<Item>> array6 = Array<P<Item>>::Of({
				ItemsManager::im->getItem(S("window_net1")),
				ItemsManager::im->getItem(S("window_net2")),
				ItemsManager::im->getItem(S("window_net3"))
			});
			for (int n = 0; n < array6.Length(); n++)
			{
				if (array6[n]->dataRef->droppedLocation == S("window3"))
				{
					array6[n]->dataRef->locX = 65;
					array6[n]->dataRef->locY = 25;
					array6[n]->dataRef->droppedLocation = S("LocationBaseBathroom");
				}
			}
		}
		if (GameDataController::gd->getObjective(S("base_window_1_foil")) && !GameDataController::gd->getObjective(S("base_window_1_foil_taped")) && !GameDataController::gd->getObjective(S("base_window_1_foil_nailed")))
		{
			GameDataController::gd->setObjective(S("base_window_1_foil"), false);
			Array<P<Item>> array7 = Array<P<Item>>::Of({
				ItemsManager::im->getItem(S("window_foil1")),
				ItemsManager::im->getItem(S("window_foil2")),
				ItemsManager::im->getItem(S("window_foil3"))
			});
			for (int num = 0; num < array7.Length(); num++)
			{
				if (array7[num]->dataRef->droppedLocation == S("window1"))
				{
					array7[num]->dataRef->locX = 15;
					array7[num]->dataRef->locY = 25;
					array7[num]->dataRef->droppedLocation = S("Location1");
				}
			}
		}
		if (GameDataController::gd->getObjective(S("base_window_2_foil")) && !GameDataController::gd->getObjective(S("base_window_2_foil_taped")) && !GameDataController::gd->getObjective(S("base_window_2_foil_nailed")))
		{
			GameDataController::gd->setObjective(S("base_window_2_foil"), false);
			Array<P<Item>> array8 = Array<P<Item>>::Of({
				ItemsManager::im->getItem(S("window_foil1")),
				ItemsManager::im->getItem(S("window_foil2")),
				ItemsManager::im->getItem(S("window_foil3"))
			});
			for (int num2 = 0; num2 < array8.Length(); num2++)
			{
				if (array8[num2]->dataRef->droppedLocation == S("window2"))
				{
					array8[num2]->dataRef->locX = 150;
					array8[num2]->dataRef->locY = 35;
					array8[num2]->dataRef->droppedLocation = S("LocationBaseUpstairs");
				}
			}
		}
		if (GameDataController::gd->getObjective(S("base_window_3_foil")) && !GameDataController::gd->getObjective(S("base_window_3_foil_taped")) && !GameDataController::gd->getObjective(S("base_window_3_foil_nailed")))
		{
			GameDataController::gd->setObjective(S("base_window_3_foil"), false);
			Array<P<Item>> array9 = Array<P<Item>>::Of({
				ItemsManager::im->getItem(S("window_foil1")),
				ItemsManager::im->getItem(S("window_foil2")),
				ItemsManager::im->getItem(S("window_foil3"))
			});
			for (int num3 = 0; num3 < array9.Length(); num3++)
			{
				if (array9[num3]->dataRef->droppedLocation == S("window3"))
				{
					array9[num3]->dataRef->locX = 65;
					array9[num3]->dataRef->locY = 25;
					array9[num3]->dataRef->droppedLocation = S("LocationBaseBathroom");
				}
			}
		}
	}
	if (ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1 || ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) != -1 || ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) != -1 || ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) != -1 || ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) != -1)
	{
		ItemsManager::im->getItem(S("bear_trap_1b"))->dataRef->droppedLocation = ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation;
		ItemsManager::im->getItem(S("bear_trap_1b"))->dataRef->locX = ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->locX;
		ItemsManager::im->getItem(S("bear_trap_1b"))->dataRef->locY = ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->locY;
		ItemsManager::im->getItem(S("bear_trap_1"))->dataRef->droppedLocation = S("nowhere");
	}
	if (ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1 || ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) != -1 || ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) != -1 || ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) != -1 || ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) != -1)
	{
		ItemsManager::im->getItem(S("bear_trap_2b"))->dataRef->droppedLocation = ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation;
		ItemsManager::im->getItem(S("bear_trap_2b"))->dataRef->locX = ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->locX;
		ItemsManager::im->getItem(S("bear_trap_2b"))->dataRef->locY = ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->locY;
		ItemsManager::im->getItem(S("bear_trap_2"))->dataRef->droppedLocation = S("nowhere");
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && GameDataController::gd->getObjectiveDetail(S("day1_complete")) != 1)
	{
		if (InventoryController::ic->isItemEquipped(S("rifle_5")))
		{
			ItemsManager::im->getItem(S("rifle_5"))->dataRef->droppedLocation = S("nowhere");
			ItemsManager::im->getItem(S("rifle_0"))->dataRef->droppedLocation = S("inventory");
			ItemsManager::im->getItem(S("rifle_0"))->dataRef->locX = ItemsManager::im->getItem(S("rifle_5"))->dataRef->locX;
			ItemsManager::im->getItem(S("rifle_0"))->dataRef->locY = ItemsManager::im->getItem(S("rifle_5"))->dataRef->locY;
		}
		if (InventoryController::ic->isItemEquipped(S("flamethrower")))
		{
			ItemsManager::im->getItem(S("flamethrower"))->dataRef->droppedLocation = S("nowhere");
			ItemsManager::im->getItem(S("flamethrower_empty"))->dataRef->droppedLocation = S("inventory");
			ItemsManager::im->getItem(S("flamethrower_empty"))->dataRef->locX = ItemsManager::im->getItem(S("flamethrower"))->dataRef->locX;
			ItemsManager::im->getItem(S("flamethrower_empty"))->dataRef->locY = ItemsManager::im->getItem(S("flamethrower"))->dataRef->locY;
		}
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0 && GameDataController::gd->getObjectiveDetail(S("day1_complete")) != 1)
	{
		if (InventoryController::ic->isItemEquipped(S("rifle_6")))
		{
			ItemsManager::im->getItem(S("rifle_6"))->dataRef->droppedLocation = S("nowhere");
			ItemsManager::im->getItem(S("rifle_0"))->dataRef->droppedLocation = S("inventory");
			ItemsManager::im->getItem(S("rifle_0"))->dataRef->locX = ItemsManager::im->getItem(S("rifle_6"))->dataRef->locX;
			ItemsManager::im->getItem(S("rifle_0"))->dataRef->locY = ItemsManager::im->getItem(S("rifle_6"))->dataRef->locY;
		}
		if (InventoryController::ic->isItemEquipped(S("flamethrower")))
		{
			ItemsManager::im->getItem(S("flamethrower"))->dataRef->droppedLocation = S("nowhere");
			ItemsManager::im->getItem(S("flamethrower_empty"))->dataRef->droppedLocation = S("inventory");
			ItemsManager::im->getItem(S("flamethrower_empty"))->dataRef->locX = ItemsManager::im->getItem(S("flamethrower"))->dataRef->locX;
			ItemsManager::im->getItem(S("flamethrower_empty"))->dataRef->locY = ItemsManager::im->getItem(S("flamethrower"))->dataRef->locY;
		}
	}
	ItemsManager::im->getItem(S("sonic2"))->dataRef->droppedLocation = ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation;
	ItemsManager::im->getItem(S("sonic2"))->dataRef->locX = ItemsManager::im->getItem(S("sonic"))->dataRef->locX;
	ItemsManager::im->getItem(S("sonic2"))->dataRef->locY = ItemsManager::im->getItem(S("sonic"))->dataRef->locY;
	ItemsManager::im->getItem(S("sonic"))->dataRef->droppedLocation = S("nowhere");
	if (GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		GameDataController::gd->setObjective(S("barn_pump_fueled"), false);
		GameDataController::gd->setObjective(S("barn_pump_started"), false);
	}
}

void LocationDay1WinStart::continueGame(String param)
{
	house->startAnim();
	JukeboxMusic::jb->changeMusic(nullptr);
}

void LocationDay1WinStart::Update()
{
}

#include "../game_all.h"

void LocationDay3WinStart::Start()
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
	GameDataController::Achievement(S("DAY_3"));
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_success);
	GameDataController::gd->gameTime = 480;
	noroof->set_enabled(false);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
	{
		noroof->set_enabled(true);
	}
	if (GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		GameDataController::gd->setObjective(S("barn_pump_fueled"), false);
		GameDataController::gd->setObjective(S("barn_pump_started"), false);
	}
	if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("heat_absorber1A")))
	{
		InventoryController::ic->removeItem(S("heat_absorber1A"));
	}
	if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("heat_absorber2A")))
	{
		InventoryController::ic->removeItem(S("heat_absorber2A"));
	}
	if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("heat_absorber3A")))
	{
		InventoryController::ic->removeItem(S("heat_absorber3A"));
	}
	ItemsManager::im->getItem(S("heat_absorber1A"))->dataRef->droppedLocation = S("nowhere");
	ItemsManager::im->getItem(S("heat_absorber2A"))->dataRef->droppedLocation = S("nowhere");
	ItemsManager::im->getItem(S("heat_absorber3A"))->dataRef->droppedLocation = S("nowhere");
	if (GameDataController::gd->getObjective(S("base_fireplace_lit")))
	{
		GameDataController::gd->setObjective(S("base_fireplace_lit"), false);
		GameDataController::gd->setObjective(S("chimney_wood"), false);
		GameDataController::gd->setObjectiveDetail(S("chimney_wood"), 0);
		GameDataController::gd->setObjective(S("chimney_note"), false);
		GameDataController::gd->setObjective(S("chimney_papers"), false);
		GameDataController::gd->setObjective(S("chimney_cash"), false);
		GameDataController::gd->setObjective(S("chimney_charcoal"), false);
		GameDataController::gd->setObjective(S("chimney_bag"), false);
		GameDataController::gd->setObjective(S("basket_wood"), false);
		GameDataController::gd->setObjectiveDetail(S("basket_wood"), 0);
		GameDataController::gd->setObjective(S("basket_note"), false);
		GameDataController::gd->setObjective(S("basket_papers"), false);
		GameDataController::gd->setObjective(S("basket_cash"), false);
		GameDataController::gd->setObjective(S("basket_charcoal"), false);
		GameDataController::gd->setObjective(S("basket_bag"), false);
	}
	if (ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1 && ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1)
	{
		ItemsManager::im->getItem(S("gasheater_empty"))->dataRef->droppedLocation = ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation;
		ItemsManager::im->getItem(S("gasheater_empty"))->dataRef->locX = ItemsManager::im->getItem(S("gasheater"))->dataRef->locX;
		ItemsManager::im->getItem(S("gasheater_empty"))->dataRef->locY = ItemsManager::im->getItem(S("gasheater"))->dataRef->locY;
		ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation = S("nowhere");
	}
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	if (GameDataController::gd->getObjectiveDetail(S("day3_complete")) == 1)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
		{
			GameDataController::Achievement(S("P_BANDITS"));
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_thugs_perfect"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
		{
			GameDataController::Achievement(S("P_STORM"));
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_storm_perfect"));
			Timeline::t->addAction(timelineAction);
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { continueGame(param); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("0");
		Timeline::t->textField->directionY = 1.0f;
		timelineAction->textWidth = 190;
		Timeline::t->textField->shift.x = -80.0f;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_bonus"));
		Timeline::t->addAction(timelineAction);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day3_complete")) == 0)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_thugs_good"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_storm_good"));
			Timeline::t->addAction(timelineAction);
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { continueGame(param); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("0");
		Timeline::t->textField->directionY = 1.0f;
		timelineAction->textWidth = 190;
		Timeline::t->textField->shift.x = -80.0f;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_normal"));
		Timeline::t->addAction(timelineAction);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 0)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_thugs_poor"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_storm_poor"));
			Timeline::t->addAction(timelineAction);
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { continueGame(param); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("0");
		Timeline::t->textField->directionY = 1.0f;
		timelineAction->textWidth = 190;
		Timeline::t->textField->shift.x = -80.0f;
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2 && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_penalty2"));
			GameDataController::gd->gameTime = 600;
		}
		else
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_penalty1"));
			GameDataController::gd->gameTime = 540;
		}
		Timeline::t->addAction(timelineAction);
	}
	for (int i = 1; i <= 4; i++)
	{
		if (ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("outside")) != -1 || ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("location1")) != -1 || ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("location2")) != -1 || ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("upstairs")) != -1 || ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation.ToLower().IndexOf(S("locationbase")) != -1)
		{
			ItemsManager::im->getItem(S("bear_trap_") + i)->dataRef->droppedLocation = S("nowhere");
		}
	}
	if (ItemsManager::im->getItem(S("whiskey"))->dataRef->droppedLocation == S("CS3"))
	{
		ItemsManager::im->getItem(S("whiskey"))->dataRef->droppedLocation = S("nowhere");
	}
	GameDataController::gd->setObjectiveDetail(S("map_outpost_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	GameDataController::gd->setObjective(S("map_outpost_revealed"), false);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		ItemsManager::im->getItem(S("gloves"))->dataRef->droppedLocation = S("LocationRestaurant3");
		ItemsManager::im->getItem(S("gloves"))->dataRef->locX = 110;
		ItemsManager::im->getItem(S("gloves"))->dataRef->locY = 50;
	}
	if (GameDataController::gd->getObjective(S("cs_engine_started")))
	{
		GameDataController::gd->setObjective(S("cs_engine_fueled"), false);
		GameDataController::gd->setObjective(S("cs_engine_started"), false);
	}
	String empty = String::Empty;
	empty = ((!GameDataController::gd->getObjective(S("npc3_joined"))) ? S("not joined/") : S("joined/"));
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		empty += S("alive");
	}
	else
	{
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 0)
		{
			empty += S("died on day 2");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
		{
			empty += S("died in Sidereal");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2)
		{
			empty += S("died on day 3");
		}
	}
	String empty2 = String::Empty;
	empty2 = ((!GameDataController::gd->getObjective(S("npc2_joined"))) ? S("not joined/") : S("joined/"));
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		empty2 += S("alive");
	}
	else
	{
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 0)
		{
			empty2 += S("died on day 2");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
		{
			empty2 += S("died in Sidereal");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2)
		{
			empty2 += S("died on day 3");
		}
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		if (GameDataController::gd->getObjective(S("base_window_1_net_nailed")) || GameDataController::gd->getObjective(S("base_window_1_net_taped")) || GameDataController::gd->getObjective(S("base_window_1_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_1_foil_taped")) || GameDataController::gd->getObjective(S("base_window_1_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_1_bars_taped")) || GameDataController::gd->getObjective(S("base_window_1_board_taped")) || GameDataController::gd->getObjective(S("base_window_1_board_nailed")))
		{
			GameDataController::gd->setObjective(S("base_window1_broken"), true);
		}
		if (GameDataController::gd->getObjective(S("base_window_2_net_nailed")) || GameDataController::gd->getObjective(S("base_window_2_net_taped")) || GameDataController::gd->getObjective(S("base_window_2_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_2_foil_taped")) || GameDataController::gd->getObjective(S("base_window_2_board_nailed")) || GameDataController::gd->getObjective(S("base_window_2_board_taped")) || GameDataController::gd->getObjective(S("base_window_2_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_2_bars_taped")))
		{
			GameDataController::gd->setObjective(S("base_window2_broken"), true);
		}
		if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")) || GameDataController::gd->getObjective(S("base_window_3_net_taped")) || GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_taped")) || GameDataController::gd->getObjective(S("base_window_3_board_nailed")) || GameDataController::gd->getObjective(S("base_window_3_board_taped")) || GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
		{
			GameDataController::gd->setObjective(S("base_window3_broken"), true);
		}
	}
}

void LocationDay3WinStart::continueGame(String param)
{
	JukeboxMusic::jb->changeMusic(nullptr);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationDream4"), WalkController::Direction::E);
}

void LocationDay3WinStart::Update()
{
}

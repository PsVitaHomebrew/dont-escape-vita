#include "../game_all.h"

void LocationDay2WinStart::Start()
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
	GameDataController::Achievement(S("DAY_2"));
	String empty = String::Empty;
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		empty = S("npc2");
		GameObject::Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		empty = S("npc3");
		GameObject::Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	if (GameDataController::gd->getObjective(S("rv_started")))
	{
		GameDataController::gd->setObjective(S("rv_started"), false);
		GameDataController::gd->setObjective(S("rv_fueled"), false);
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
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0 && GameDataController::gd->equipped.IndexOf(S("water")) != -1)
	{
		ItemsManager::im->getItem(GameDataController::gd->equipped)->dataRef->droppedLocation = S("nowhere");
		InventoryController::ic->removeItem(GameDataController::gd->equipped);
	}
	if (ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation.ToLower().IndexOf(S("nowhere")) == -1 && ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1)
	{
		ItemsManager::im->getItem(S("gasheater_empty"))->dataRef->droppedLocation = ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation;
		ItemsManager::im->getItem(S("gasheater_empty"))->dataRef->locX = ItemsManager::im->getItem(S("gasheater"))->dataRef->locX;
		ItemsManager::im->getItem(S("gasheater_empty"))->dataRef->locY = ItemsManager::im->getItem(S("gasheater"))->dataRef->locY;
		ItemsManager::im->getItem(S("gasheater"))->dataRef->droppedLocation = S("nowhere");
	}
	GameDataController::gd->gameTime = 480;
	bool flag = false;
	if (empty == S("npc2") && GameDataController::gd->getObjective(S("npc2_joined")))
	{
		flag = true;
	}
	if (empty == S("npc3") && GameDataController::gd->getObjective(S("npc3_joined")))
	{
		flag = true;
	}
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	if (GameDataController::gd->getObjectiveDetail(S("day2_complete")) == 1)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			GameDataController::Achievement(S("P_HEAT"));
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_heat_perfect"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			GameDataController::Achievement(S("P_COLD"));
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_cold_perfect"));
			Timeline::t->addAction(timelineAction);
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { continueGame(param); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("0");
		Timeline::t->textField->directionY = 1.0f;
		timelineAction->textWidth = 190;
		Timeline::t->textField->shift.x = -80.0f;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_bonus"));
		Timeline::t->addAction(timelineAction);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day2_complete")) == 0)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_heat_good"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_cold_good"));
			Timeline::t->addAction(timelineAction);
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { continueGame(param); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("0");
		Timeline::t->textField->directionY = 1.0f;
		timelineAction->textWidth = 190;
		Timeline::t->textField->shift.x = -80.0f;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_normal"));
		Timeline::t->addAction(timelineAction);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day2_complete")) < 0)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_heat_poor"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_cold_poor"));
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
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_penalty"));
		Timeline::t->addAction(timelineAction);
	}
	if (!GameDataController::gd->getObjective(S("npc2_joined")))
	{
		GameDataController::gd->setObjective(S("npc2_alive"), false);
		GameDataController::gd->setObjectiveDetail(S("npc2_alive"), 0);
	}
	if (!GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("house_b_garage_open")))
	{
		GameDataController::gd->setObjective(S("npc2_alive"), false);
		GameDataController::gd->setObjectiveDetail(S("npc2_alive"), 0);
		ItemsManager::im->getItem(S("key4"))->dataRef->droppedLocation = S("LocationHouseB");
		ItemsManager::im->getItem(S("key4"))->dataRef->locX = 215;
		ItemsManager::im->getItem(S("key4"))->dataRef->locY = 10;
	}
	if (!GameDataController::gd->getObjective(S("npc3_joined")))
	{
		GameDataController::gd->setObjective(S("npc3_alive"), false);
		GameDataController::gd->setObjectiveDetail(S("npc3_alive"), 0);
	}
	String empty2 = String::Empty;
	empty2 = ((!GameDataController::gd->getObjective(S("npc3_joined"))) ? S("not joined/") : S("joined/"));
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		empty2 += S("alive");
	}
	else
	{
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 0)
		{
			empty2 += S("died on day 2");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
		{
			empty2 += S("died in Sidereal");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2)
		{
			empty2 += S("died on day 3");
		}
	}
	String empty3 = String::Empty;
	empty3 = ((!GameDataController::gd->getObjective(S("npc2_joined"))) ? S("not joined/") : S("joined/"));
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		empty3 += S("alive");
	}
	else
	{
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 0)
		{
			empty3 += S("died on day 2");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
		{
			empty3 += S("died in Sidereal");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2)
		{
			empty3 += S("died on day 3");
		}
	}
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_success);
}

void LocationDay2WinStart::continueGame(String param)
{
	JukeboxMusic::jb->changeMusic(nullptr);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("Dream3"), WalkController::Direction::E);
}

void LocationDay2WinStart::Update()
{
}

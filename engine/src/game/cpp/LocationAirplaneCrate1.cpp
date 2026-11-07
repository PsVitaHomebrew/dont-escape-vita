#include "../game_all.h"

void LocationAirplaneCrate1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airplane_crate_1");
	range = 2.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
}

void LocationAirplaneCrate1::clickAction()
{
	if (!GameDataController::gd->getObjective(S("plane_crate_") + number))
	{
		if (usedItem != String::Empty)
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("airplane_crate_1")) + S(" ") + number + S(" ") + GameStrings::getString(GameStrings::warnings, S("airplane_crate_2")), QuestionController_PopupType::QUESTION, [this]() { openIt(); }, 12, 2);
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("crate_locked")));
		}
	}
	else if (usedItem != String::Empty)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("generic_opened")));
	}
	else if (!GameDataController::gd->getObjective(S("plane_crate_") + number + S("_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(item)))
		{
			GameDataController::gd->setObjective(S("plane_crate_") + number + S("_taken"), true);
			updateState();
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("crate_enough_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number)));
	}
}

void LocationAirplaneCrate1::openIt()
{
	GameDataController::gd->setObjective(S("plane_crate_") + number, true);
	P<AudioClip> sound = nullptr;
	float num = (float)Random::Range(0, 3);
	if (num == 0.0f)
	{
		sound = SoundsManagerController::sm->wood_crack_1;
	}
	if (num == 1.0f)
	{
		sound = SoundsManagerController::sm->wood_crack_2;
	}
	if (num == 2.0f)
	{
		sound = SoundsManagerController::sm->wood_crack_3;
	}
	CurtainController::cc->fadeOut(S("none"), WalkController_Direction::NULL_, nullptr, sound, false, [this]() { sayOpen(); });
}

void LocationAirplaneCrate1::sayOpen()
{
	int num = 0;
	for (int i = 1; i < 8; i++)
	{
		if (GameDataController::gd->getObjective(S("plane_crate_") + i))
		{
			num++;
		}
	}
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("crate_opened_") + num));
}

void LocationAirplaneCrate1::updateState()
{
	colliderManager->setCollider(0);
	if (number == 1)
	{
		objectName = S("airplane_crate_1");
	}
	if (number == 2)
	{
		objectName = S("airplane_crate_2");
	}
	if (number == 3)
	{
		objectName = S("airplane_crate_3");
	}
	if (number == 4)
	{
		objectName = S("airplane_crate_4");
	}
	if (number == 5)
	{
		objectName = S("airplane_crate_5");
	}
	if (number == 6)
	{
		objectName = S("airplane_crate_6");
	}
	if (number == 7)
	{
		objectName = S("airplane_crate_7");
	}
	if (GameDataController::gd->getObjective(S("plane_crate_") + number) && !GameDataController::gd->getObjective(S("plane_crate_") + number + S("_taken")))
	{
		objectName = S("airplane_crate_revealed_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number);
		characterAnimationName = S("action_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else if (GameDataController::gd->getObjective(S("plane_crate_") + number))
	{
		objectName = S("airplane_crate_revealed_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number);
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number) == 1)
	{
		item = S("nav_chip");
	}
	if (GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number) == 2)
	{
		item = S("air_tanks");
	}
	if (GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number) == 3)
	{
		item = S("voltmeter");
	}
	if (GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number) == 4)
	{
		item = S("noodles");
	}
	if (GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number) == 5)
	{
		item = S("gasket");
	}
	if (GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number) == 6)
	{
		item = S("nuts_and_bolts");
	}
	if (GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number) == 7)
	{
		item = S("wires");
	}
	if (GameDataController::gd->getObjective(S("plane_crate_") + number))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void LocationAirplaneCrate1::clickAction2()
{
}

void LocationAirplaneCrate1::clickAction0()
{
	if (GameDataController::gd->getObjective(S("plane_crate_") + number) && !GameDataController::gd->getObjective(S("plane_crate_") + number + S("_taken")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("crate_take_") + GameDataController::gd->getObjectiveDetail(S("plane_crate_") + number)));
	}
}

void LocationAirplaneCrate1::whatOnClick0()
{
}

void LocationAirplaneCrate1::whatOnClick()
{
}

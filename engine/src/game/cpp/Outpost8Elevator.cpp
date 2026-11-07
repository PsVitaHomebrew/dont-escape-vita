#include "../game_all.h"

void Outpost8Elevator::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = true;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship_elevator_broken");
	range = 2.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("screwdriver"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("transmission_belt"), String::Empty, nullptr, String::Empty));
}

void Outpost8Elevator::yesTake()
{
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("transmission_belt")));
	GameDataController::gd->setObjective(S("outpost_belt_elevator"), false);
	CurtainController::cc->fadeOut();
}

void Outpost8Elevator::yesGive()
{
	InventoryController::ic->removeItem(S("transmission_belt"));
	GameDataController::gd->setObjective(S("outpost_belt_elevator"), true);
	CurtainController::cc->fadeOut();
}

void Outpost8Elevator::clickAction()
{
	if (usedItem == S("transmission_belt"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("belt_give_elevator")), QuestionController_PopupType::QUESTION, [this]() { yesGive(); }, 10);
	}
	else if (GameDataController::gd->getObjective(S("outpost_belt_elevator")))
	{
		if (usedItem == String::Empty)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("belt_with_tool")));
		}
		else
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("belt_take_elevator")), QuestionController_PopupType::QUESTION, [this]() { yesTake(); }, 10);
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("elevator_no_belt")));
	}
}

void Outpost8Elevator::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_belt_elevator")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("outpost_ship_elevator_fixed");
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		objectName = S("outpost_ship_elevator_broken");
	}
}

void Outpost8Elevator::clickAction2()
{
}

void Outpost8Elevator::clickAction0()
{
}

void Outpost8Elevator::whatOnClick0()
{
}

void Outpost8Elevator::whatOnClick()
{
}

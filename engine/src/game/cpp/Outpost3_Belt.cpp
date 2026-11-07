#include "../game_all.h"

void Outpost3_Belt::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = true;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_engine_belted");
	range = 2.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("screwdriver"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("transmission_belt"), String::Empty, nullptr, String::Empty));
}

void Outpost3_Belt::yesTake()
{
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("transmission_belt")));
	GameDataController::gd->setObjective(S("outpost_belt_hatch"), false);
	CurtainController::cc->fadeOut();
}

void Outpost3_Belt::yesGive()
{
	InventoryController::ic->removeItem(S("transmission_belt"));
	GameDataController::gd->setObjective(S("outpost_belt_hatch"), true);
	CurtainController::cc->fadeOut();
}

void Outpost3_Belt::clickAction()
{
	if (usedItem == S("transmission_belt"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("belt_give_engine")), QuestionController_PopupType::QUESTION, [this]() { yesGive(); }, 10);
	}
	else if (GameDataController::gd->getObjective(S("outpost_belt_hatch")))
	{
		if (usedItem == String::Empty)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("belt_engine_with_tool")));
		}
		else
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("belt_take_engine")), QuestionController_PopupType::QUESTION, [this]() { yesTake(); }, 10);
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("elevator_no_belt")));
	}
}

void Outpost3_Belt::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_belt_hatch")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("outpost_engine_belted");
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		objectName = S("outpost_engine_unbelted");
	}
}

void Outpost3_Belt::clickAction2()
{
}

void Outpost3_Belt::clickAction0()
{
}

void Outpost3_Belt::whatOnClick0()
{
}

void Outpost3_Belt::whatOnClick()
{
}

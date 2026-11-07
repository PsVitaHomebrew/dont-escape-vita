#include "../game_all.h"

void cs4_welder::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_welder");
	actionType = Type::NormalAction;
	doubleClickCondition = String::Empty;
}

void cs4_welder::clickAction()
{
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		if (!GameDataController::gd->getObjective(S("cs_welder_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("welder"))))
		{
			GameDataController::gd->setObjective(S("cs_welder_taken"), true);
			updateAll();
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
	}
}

void cs4_welder::updateState()
{
	if (!GameDataController::gd->getObjective(S("cs_welder_taken")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		range = 1.0f;
		characterAnimationName = S("kneel_");
		interactions = List<P<ItemInteraction>>::New();
		return;
	}
	range = 100.0f;
	characterAnimationName = S("action_stnd_");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("broom"), GameStrings::getString(GameStrings::actions, S("welder_poke")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("welder_poke")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("welder_poke")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("shovel"), GameStrings::getString(GameStrings::actions, S("welder_poke")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ropehook"), GameStrings::getString(GameStrings::actions, S("welder_pull")), nullptr, String::Empty));
}

void cs4_welder::clickAction2()
{
}

void cs4_welder::clickAction0()
{
}

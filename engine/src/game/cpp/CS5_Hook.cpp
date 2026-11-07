#include "../game_all.h"

void CS5_Hook::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_buckle");
	actionType = Type::NormalAction;
	doubleClickCondition = String::Empty;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ropehook"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("hook"), GameStrings::getString(GameStrings::actions, S("cs_buckle_hook")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rope"), GameStrings::getString(GameStrings::actions, S("cs_buckle_rope")), nullptr, String::Empty));
}

void CS5_Hook::whatOnClick0()
{
	if (usedItem == S("ropehook") || GameDataController::gd->getObjective(S("cs_rope_used")))
	{
		characterAnimationName = S("action1_e");
		animationFlip = true;
		useCurrentDirection = false;
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void CS5_Hook::clickAction()
{
	if (GameDataController::gd->getObjective(S("cs_rope_used")))
	{
		GameDataController::gd->setObjective(S("cs_rope_used"), false);
		InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("ropehook")));
	}
	if (usedItem == S("ropehook"))
	{
		GameDataController::gd->setObjective(S("cs_rope_used"), true);
		InventoryController::ic->removeItem(S("ropehook"));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_buckle")));
	}
	updateAll();
}

void CS5_Hook::updateState()
{
	if (GameDataController::gd->getObjective(S("cs_rope_used")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void CS5_Hook::clickAction2()
{
}

void CS5_Hook::clickAction0()
{
}

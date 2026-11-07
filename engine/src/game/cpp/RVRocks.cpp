#include "../game_all.h"

void RVRocks::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action1_e_lock");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_rocks");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("rope"), GameStrings::getString(GameStrings::actions, S("rope_rocks_fail")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ropehook"), String::Empty, nullptr, String::Empty));
}

void RVRocks::clickAction()
{
	if (!GameDataController::gd->getObjective(S("rv_hook_installed")))
	{
		if (usedItem == S("ropehook"))
		{
			InventoryController::ic->removeItem(S("ropehook"));
			GameDataController::gd->setObjective(S("rv_hook_installed"), true);
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_rock_rope_in")));
			updateAll();
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_rocks")));
		}
	}
	else if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("ropehook"))))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_rock_rope_out")));
		GameDataController::gd->setObjective(S("rv_hook_installed"), false);
		updateAll();
	}
}

void RVRocks::updateState()
{
	if (GameDataController::gd->getObjective(S("rv_hook_installed")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(1);
		objectName = S("rv_rocks_rope");
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(0);
		objectName = S("rv_rocks");
	}
}

void RVRocks::clickAction2()
{
}

void RVRocks::clickAction0()
{
}

void RVRocks::whatOnClick0()
{
	if ((!GameDataController::gd->getObjective(S("rv_hook_installed")) && usedItem == S("ropehook")) || GameDataController::gd->getObjective(S("rv_hook_installed")))
	{
		characterAnimationName = S("action1_e_lock");
		range = 1.0f;
	}
	else
	{
		range = 60.0f;
		characterAnimationName = S("action_stnd_e");
	}
}

void RVRocks::whatOnClick()
{
}

#include "../game_all.h"

void ShipToolbox::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ship_toolbox");
	range = 1.0f;
}

void ShipToolbox::clickAction()
{
	if (!GameDataController::gd->getObjective(S("ship_toolbox_open")))
	{
		GameDataController::gd->setObjective(S("ship_toolbox_open"), true);
		updateAll();
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->toolbox1);
	}
	else if (!GameDataController::gd->getObjective(S("ship_toolbox_searched")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->toolbox2);
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("gluegun"))))
		{
			GameDataController::gd->setObjective(S("ship_toolbox_searched"), true);
		}
	}
	updateAll();
}

void ShipToolbox::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("ship_toolbox_open")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("ship_toolbox_searched")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		characterAnimationName = S("kneel_se");
		animationFlip = true;
		useCurrentDirection = false;
	}
}

void ShipToolbox::clickAction2()
{
}

void ShipToolbox::clickAction0()
{
	if (GameDataController::gd->getObjective(S("ship_toolbox_open")) && GameDataController::gd->getObjective(S("ship_toolbox_searched")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ship_toolbox_searched2")));
	}
	if (GameDataController::gd->getObjective(S("ship_toolbox_open")) && !GameDataController::gd->getObjective(S("ship_toolbox_searched")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ship_toolbox_searched1")));
	}
}

void ShipToolbox::whatOnClick0()
{
}

void ShipToolbox::whatOnClick()
{
}

#include "../game_all.h"

void LocationRVAid::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_aid");
	range = 1.0f;
}

void LocationRVAid::clickAction()
{
	if (!GameDataController::gd->getObjective(S("rv_aid_open")))
	{
		GameDataController::gd->setObjective(S("rv_aid_open"), true);
		updateAll();
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->cabinet_open);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_aid_1")));
	}
	else if (!GameDataController::gd->getObjective(S("rv_bandage_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("bandage"))))
		{
			GameDataController::gd->setObjective(S("rv_bandage_taken"), true);
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_aid_2")));
		}
	}
	else if (!GameDataController::gd->getObjective(S("rv_silver_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("thermalb"))))
		{
			GameDataController::gd->setObjective(S("rv_silver_taken"), true);
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_aid_3")));
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_aid_4")));
	}
}

void LocationRVAid::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_aid_open")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(open);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(closed);
	}
}

void LocationRVAid::clickAction2()
{
}

void LocationRVAid::clickAction0()
{
}

void LocationRVAid::whatOnClick0()
{
}

void LocationRVAid::whatOnClick()
{
}

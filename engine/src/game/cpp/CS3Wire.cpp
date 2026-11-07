#include "../game_all.h"

void CS3Wire::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_wire");
	range = 1.0f;
	updateState();
}

void CS3Wire::Update()
{
}

void CS3Wire::clickAction()
{
	if (GameDataController::gd->getObjective(S("cs_rain_enter_left")) && !GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
	}
	else if (!GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("reel_blocked")));
	}
	else if (!GameDataController::gd->getObjective(S("cs_wire_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("wire"))))
	{
		GameDataController::gd->setObjective(S("cs_wire_taken"), true);
		updateAll();
	}
}

void CS3Wire::updateState()
{
	if (GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(reel1);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(reel2);
	}
	if (GameDataController::gd->getObjective(S("cs_wire_taken")))
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else if (GameDataController::gd->getObjective(S("cs_rain_enter_left")) && !GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		characterAnimationName = S("action_stnd_");
		animationFlip = true;
		useCurrentDirection = true;
		actionMarker = marker2;
		range = 100.0f;
	}
	else
	{
		actionMarker = marker1;
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjective(S("cs_pack_lifted")))
		{
			characterAnimationName = S("kneel_e");
			animationFlip = false;
			useCurrentDirection = false;
			range = 1.0f;
		}
		else
		{
			characterAnimationName = S("kneel_e");
			animationFlip = true;
			useCurrentDirection = false;
			range = 1.0f;
		}
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 1)
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void CS3Wire::clickAction2()
{
}

void CS3Wire::clickAction0()
{
}

void CS3Wire::whatOnClick0()
{
}

void CS3Wire::whatOnClick()
{
}

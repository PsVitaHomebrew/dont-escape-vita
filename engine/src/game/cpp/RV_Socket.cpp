#include "../game_all.h"

void RV_Socket::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_socket");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("heater_broken"), GameStrings::getString(GameStrings::actions, S("heater_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan_broken"), GameStrings::getString(GameStrings::actions, S("fan_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("heater"), GameStrings::getString(GameStrings::actions, S("socket_wrong")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("socket_wrong")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan"), GameStrings::getString(GameStrings::actions, S("socket_wrong")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ext_cord"), String::Empty, nullptr, String::Empty));
	updateState();
}

void RV_Socket::clickAction()
{
	if (usedItem == S("ext_cord"))
	{
		InventoryController::ic->removeItem(S("ext_cord"));
		GameDataController::gd->setObjective(S("rv_cord_plugged"), true);
		updateAll();
	}
	else if (GameDataController::gd->getObjective(S("rv_cord_plugged")) && GameDataController::gd->getObjective(S("rv_cord_caved")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cord_dragged")));
	}
	else if (GameDataController::gd->getObjective(S("rv_cord_plugged")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("ext_cord"))))
		{
			GameDataController::gd->setObjective(S("rv_cord_plugged"), false);
			updateAll();
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("socket_empty")));
	}
}

void RV_Socket::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_cord_plugged")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (!GameDataController::gd->getObjective(S("rv_cord_caved")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(cord);
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_sprite(cord2);
		}
		setCollider(1);
		objectName = S("plugged_cord");
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(0);
		objectName = S("rv_socket");
	}
}

void RV_Socket::clickAction2()
{
}

void RV_Socket::clickAction0()
{
}

void RV_Socket::whatOnClick0()
{
	if (usedItem != String::Empty && GameDataController::gd->getObjective(S("rv_cord_plugged")))
	{
		range = 100.0f;
		characterAnimationName = S("action_stnd_");
		useCurrentDirection = true;
	}
	else if (usedItem == String::Empty && GameDataController::gd->getObjective(S("rv_cord_plugged")) && !GameDataController::gd->getObjective(S("rv_cord_caved")))
	{
		range = 1.0f;
		characterAnimationName = S("action_n");
		useCurrentDirection = false;
	}
	else if (usedItem == String::Empty || GameDataController::gd->getObjective(S("rv_cord_caved")))
	{
		range = 100.0f;
		characterAnimationName = S("action_stnd_");
		useCurrentDirection = true;
	}
	else
	{
		range = 1.0f;
		characterAnimationName = S("action_n");
		useCurrentDirection = false;
	}
}

void RV_Socket::whatOnClick()
{
}

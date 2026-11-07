#include "../game_all.h"

void Outpost8Socket::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship_socket");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("fan"), GameStrings::getString(GameStrings::actions, S("ship_socket_power")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("heater"), GameStrings::getString(GameStrings::actions, S("ship_socket_power")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("ship_socket_power")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher1"), GameStrings::getString(GameStrings::actions, S("ship_socket_power")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher2"), GameStrings::getString(GameStrings::actions, S("ship_socket_power")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher3"), GameStrings::getString(GameStrings::actions, S("ship_socket_power")), nullptr, String::Empty));
}

void Outpost8Socket::clickAction()
{
	if (GameDataController::gd->getItemData(S("welder"))->droppedLocation == S("socket_ship_outside"))
	{
		InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("welder")));
		updateAll();
	}
	else if (usedItem != String::Empty)
	{
		InventoryController::ic->removeItem(S("welder"));
		GameDataController::gd->getItemData(S("welder"))->droppedLocation = S("socket_ship_outside");
		updateAll();
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("welder_plugged")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("welder_plug_empty")));
	}
}

void Outpost8Socket::updateState()
{
	if (GameDataController::gd->getItemData(S("welder"))->droppedLocation == S("socket_ship_outside"))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(1);
		objectName = S("outpost_ship_welder");
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("metal_slab"), GameStrings::getString(GameStrings::actions, S("welder_metal")), nullptr, String::Empty));
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(0);
		objectName = S("outpost_ship_socket");
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("welder"), String::Empty, nullptr, String::Empty));
	}
}

void Outpost8Socket::clickAction2()
{
}

void Outpost8Socket::clickAction0()
{
}

void Outpost8Socket::whatOnClick0()
{
	if (GameDataController::gd->getItemData(S("welder"))->droppedLocation == S("socket_ship_outside"))
	{
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else if (usedItem != String::Empty)
	{
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void Outpost8Socket::whatOnClick()
{
}

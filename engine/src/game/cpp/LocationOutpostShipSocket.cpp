#include "../game_all.h"

void LocationOutpostShipSocket::Start()
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

void LocationOutpostShipSocket::clickAction()
{
	if (GameDataController::gd->getItemData(S("welder"))->droppedLocation == S("socket_ship_inside"))
	{
		InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("welder")));
		updateAll();
	}
	else if (usedItem != String::Empty)
	{
		InventoryController::ic->removeItem(S("welder"));
		GameDataController::gd->getItemData(S("welder"))->droppedLocation = S("socket_ship_inside");
		updateAll();
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("welder_plugged")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("welder_plug_empty")));
	}
}

void LocationOutpostShipSocket::updateState()
{
	if (GameDataController::gd->getItemData(S("welder"))->droppedLocation == S("socket_ship_inside"))
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

void LocationOutpostShipSocket::clickAction2()
{
}

void LocationOutpostShipSocket::clickAction0()
{
}

void LocationOutpostShipSocket::whatOnClick0()
{
	if (GameDataController::gd->getItemData(S("welder"))->droppedLocation == S("socket_ship_inside"))
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

void LocationOutpostShipSocket::whatOnClick()
{
}

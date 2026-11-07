#include "../game_all.h"

void HuntersLodgeInsideOutlet::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_socket");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("heater_broken"), GameStrings::getString(GameStrings::actions, S("heater_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan_broken"), GameStrings::getString(GameStrings::actions, S("fan_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("heater"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ext_cord"), String::Empty, nullptr, String::Empty));
	updateState();
}

void HuntersLodgeInsideOutlet::Update()
{
}

void HuntersLodgeInsideOutlet::clickAction()
{
	if (usedItem == S("ext_cord"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 1)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("plug_not_needed")));
			return;
		}
		InventoryController::ic->removeItem(S("ext_cord"));
		GameDataController::gd->setObjective(S("lodge_cord_plugged"), true);
		updateAll();
	}
	else if (GameDataController::gd->getObjective(S("lodge_cord_plugged")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("plug_dont_unplug")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("socket_empty")));
	}
}

void HuntersLodgeInsideOutlet::updateState()
{
}

void HuntersLodgeInsideOutlet::clickAction2()
{
}

void HuntersLodgeInsideOutlet::clickAction0()
{
}

void HuntersLodgeInsideOutlet::whatOnClick0()
{
	if (usedItem != S("ext_cord"))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 30.0f;
	}
	else
	{
		range = 1.0f;
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void HuntersLodgeInsideOutlet::whatOnClick()
{
}

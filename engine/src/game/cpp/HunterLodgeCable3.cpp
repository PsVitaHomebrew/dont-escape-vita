#include "../game_all.h"

void HunterLodgeCable3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_cord");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("heater_broken"), GameStrings::getString(GameStrings::actions, S("heater_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan_broken"), GameStrings::getString(GameStrings::actions, S("fan_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("heater"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher3"), String::Empty, nullptr, String::Empty));
	updateState();
}

void HunterLodgeCable3::Update()
{
}

void HunterLodgeCable3::clickAction()
{
	if (usedItem == String::Empty)
	{
		if (GameDataController::gd->getObjective(S("lodge_tree_stormcatcher")))
		{
			if (GameDataController::gd->getObjective(S("lodge_roof_cleaned")))
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("lodge_tree_stormcatcher_placed")));
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("lodge_tree_stormcatcher_no_power")));
			}
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("socket_empty")));
		}
		return;
	}
	if (GameDataController::gd->getObjective(S("lodge_tree_stormcatcher")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("stormcatcher_already")));
		return;
	}
	InventoryController::ic->removeItem(usedItem);
	GameDataController::gd->setObjective(S("lodge_tree_stormcatcher"), true);
	updateState();
	if (GameDataController::gd->getObjective(S("lodge_roof_cleaned")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("lodge_tree_stormcatcher_placed")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("lodge_tree_stormcatcher_no_power")));
	}
}

void HunterLodgeCable3::updateState()
{
	if (GameDataController::gd->getObjective(S("lodge_tree_stormcatcher")))
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjective(S("lodge_roof_cleaned")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(stormcatcher_on);
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_sprite(stormcatcher_off);
		}
	}
	else if (GameDataController::gd->getObjective(S("lodge_cord_climbed")))
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(cord);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(-1);
	}
}

void HunterLodgeCable3::clickAction2()
{
}

void HunterLodgeCable3::clickAction0()
{
}

void HunterLodgeCable3::whatOnClick0()
{
	if (usedItem == String::Empty)
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 20.0f;
	}
	else
	{
		characterAnimationName = S("kneel_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 1.0f;
	}
}

void HunterLodgeCable3::whatOnClick()
{
}

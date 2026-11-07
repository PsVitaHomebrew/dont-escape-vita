#include "../game_all.h"

void LocationSiderealF2C_Waypoint_B::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_exit4");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void LocationSiderealF2C_Waypoint_B::clickAction()
{
	if (!GameDataController::gd->getObjective(S("sidereal_f2c_b_unlocked")))
	{
		doubleClickCondition = String::Empty;
		if (usedItem != String::Empty)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("generic_unlocked")));
			GameDataController::gd->setObjective(S("sidereal_f2c_b_unlocked"), true);
			updateAll();
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_lock_unlock);
			InventoryController::ic->removeItem(usedItem);
		}
		else
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_locked_3);
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("generic_locked")));
		}
	}
	else if (GameDataController::gd->getObjective(S("sidereal_f2c_b_open")))
	{
		PlayerController::pc->spawnName = S("LocationSiderealF2B_Waypoint_C");
		CurtainController::cc->fadeOut(S("SiderealF2B"), WalkController::Direction::N);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_door_open);
		GameDataController::gd->setObjective(S("sidereal_f2c_b_open"), true);
		updateAll();
	}
}

void LocationSiderealF2C_Waypoint_B::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_f2c_b_open")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("sidereal_exit4");
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
		doubleClickCondition = S("visited_sidereal_f2b");
		interactions = List<P<ItemInteraction>>::New();
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		objectName = S("sidereal_f2c_door");
		characterAnimationName = S("locked_n");
		animationFlip = false;
		useCurrentDirection = false;
		actionType = Type::NormalAction;
		trans_dir = WalkController::Direction::N;
		doubleClickCondition = String::Empty;
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("key1"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("sidereal_door_crowbar")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("paperclip"), GameStrings::getString(GameStrings::actions, S("sidereal_door_clip")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("screwdriver"), GameStrings::getString(GameStrings::actions, S("sidereal_door_screwdriver")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("sidereal_id_key"), GameStrings::getString(GameStrings::actions, S("sidereal_door_id")), nullptr, String::Empty));
	}
}

void LocationSiderealF2C_Waypoint_B::whatOnClick0()
{
	if (!GameDataController::gd->getObjective(S("sidereal_f2c_b_unlocked")))
	{
		if (usedItem != String::Empty)
		{
			characterAnimationName = S("action_n");
			animationFlip = false;
			useCurrentDirection = false;
		}
	}
	else if (!GameDataController::gd->getObjective(S("sidereal_f2c_b_open")))
	{
		characterAnimationName = S("open_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void LocationSiderealF2C_Waypoint_B::clickAction2()
{
}

void LocationSiderealF2C_Waypoint_B::clickAction0()
{
}

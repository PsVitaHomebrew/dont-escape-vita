#include "../game_all.h"

void LocationSiderealF0Ca_Waypoint_Lab::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_doorway");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = S("visited_sidereal_lab");
}

void LocationSiderealF0Ca_Waypoint_Lab::clickAction()
{
	if (usedItem == S("key3"))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_lock_unlock);
		GameDataController::gd->setObjective(S("sidereal_lab_locked"), false);
		InventoryController::ic->removeItem(S("key3"));
	}
	else if (GameDataController::gd->getObjective(S("sidereal_lab_open")))
	{
		PlayerController::pc->spawnName = S("LocationSiderealLab_Waypoint_C");
		CurtainController::cc->fadeOut(S("SiderealLab13"), WalkController::Direction::N);
	}
	else if (GameDataController::gd->getObjective(S("sidereal_lab_locked")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_locked);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_lab_locked")));
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_moan2);
		GameDataController::gd->setObjective(S("sidereal_lab_open"), true);
		updateAll();
	}
}

void LocationSiderealF0Ca_Waypoint_Lab::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_lab_open")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		actionType = Type::Transition;
		objectName = S("sidereal_doorway_lab");
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		characterAnimationName = S("action_n");
		animationFlip = false;
		useCurrentDirection = false;
		actionType = Type::NormalAction;
		objectName = S("sidereal_doorway");
	}
	if (GameDataController::gd->getObjective(S("sidereal_lab_locked")))
	{
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("sidereal_no_crowbar")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("paperclip"), GameStrings::getString(GameStrings::actions, S("sidereal_door_clip")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("sidereal_id"), GameStrings::getString(GameStrings::actions, S("sidereal_no_id_card")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("key3"), String::Empty, nullptr, String::Empty));
	}
	else
	{
		interactions = List<P<ItemInteraction>>::New();
	}
}

void LocationSiderealF0Ca_Waypoint_Lab::clickAction2()
{
}

void LocationSiderealF0Ca_Waypoint_Lab::clickAction0()
{
}

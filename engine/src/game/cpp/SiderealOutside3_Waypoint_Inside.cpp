#include "../game_all.h"

void SiderealOutside3_Waypoint_Inside::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("pull2_w");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_outside_door2");
	range = 1.0f;
	teleport = false;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
	trans_dir = WalkController::Direction::N;
}

void SiderealOutside3_Waypoint_Inside::Update()
{
}

void SiderealOutside3_Waypoint_Inside::whatOnClick()
{
}

void SiderealOutside3_Waypoint_Inside::whatOnClick0()
{
	if (usedItem == S("crowbar"))
	{
		characterAnimationName = S("crowbar_e");
		animationFlip = false;
		return;
	}
	if (GameDataController::gd->getObjective(S("sidereal_exit_unlocked")))
	{
		characterAnimationName = S("action_stnd_n");
	}
	else
	{
		characterAnimationName = S("pull2_w");
	}
	animationFlip = true;
}

void SiderealOutside3_Waypoint_Inside::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_exit_unlocked")))
	{
		PlayerController::pc->spawnName = S("LocationSiderealF0C2_Waypoint_Outside");
		CurtainController::cc->fadeOut(S("SiderealF0C2"), WalkController::Direction::S_);
	}
	else if (usedItem == S("crowbar"))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_crowbar_fail")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_entrance_locked_from_other_side")));
	}
}

void SiderealOutside3_Waypoint_Inside::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_exit_unlocked")))
	{
		actionType = Type::Transition;
		GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("sidereal_outside_door2");
		doubleClickCondition = S("visited_sidereal_f0c3");
	}
	else
	{
		objectName = S("sidereal_outside_door");
		actionType = Type::NormalAction;
		GetComponent<SpriteRenderer>()->set_enabled(false);
		doubleClickCondition = String::Empty;
	}
}

void SiderealOutside3_Waypoint_Inside::clickAction2()
{
}

void SiderealOutside3_Waypoint_Inside::clickAction0()
{
}

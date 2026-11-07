#include "../game_all.h"

void Waypoint_Outpost6_7::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_control_room");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	doubleClickCondition = S("visited_outpost7");
}

void Waypoint_Outpost6_7::clickAction()
{
	if (GameDataController::gd->getObjective(S("outpost_control_room_open")))
	{
		PlayerController::pc->spawnName = S("Waypoint_Outpost7_6");
		CurtainController::cc->fadeOut(S("LocationOutpost7"), WalkController::Direction::S_);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_door_open);
		GameDataController::gd->setObjective(S("outpost_control_room_open"), true);
		updateAll();
	}
}

void Waypoint_Outpost6_7::rideDown()
{
}

void Waypoint_Outpost6_7::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_control_room_open")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		actionType = Type::NormalAction;
		characterAnimationName = S("action_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void Waypoint_Outpost6_7::clickAction2()
{
}

void Waypoint_Outpost6_7::clickAction0()
{
}

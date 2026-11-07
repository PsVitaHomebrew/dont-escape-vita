#include "../game_all.h"

void Waypoint_Outpost6_5::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_corridor2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	doubleClickCondition = S("visited_outpost5");
}

void Waypoint_Outpost6_5::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost5_6");
	CurtainController::cc->fadeOut(S("LocationOutpost5"), WalkController::Direction::S_);
}

void Waypoint_Outpost6_5::rideDown()
{
}

void Waypoint_Outpost6_5::updateState()
{
}

void Waypoint_Outpost6_5::clickAction2()
{
}

void Waypoint_Outpost6_5::clickAction0()
{
}

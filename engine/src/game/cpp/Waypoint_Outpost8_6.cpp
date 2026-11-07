#include "../game_all.h"

void Waypoint_Outpost8_6::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_staircase");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	doubleClickCondition = S("visited_outpost6");
}

void Waypoint_Outpost8_6::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost6_8");
	CurtainController::cc->fadeOut(S("LocationOutpost6"), WalkController::Direction::E);
}

void Waypoint_Outpost8_6::rideDown()
{
}

void Waypoint_Outpost8_6::updateState()
{
}

void Waypoint_Outpost8_6::clickAction2()
{
}

void Waypoint_Outpost8_6::clickAction0()
{
}

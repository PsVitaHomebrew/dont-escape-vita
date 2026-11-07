#include "../game_all.h"

void Waypoint_Outpost6_8::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_launchpad");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	range = 2.0f;
	doubleClickCondition = S("visited_outpost8");
}

void Waypoint_Outpost6_8::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost8_6");
	CurtainController::cc->fadeOut(S("LocationOutpost8"), WalkController::Direction::N);
}

void Waypoint_Outpost6_8::rideDown()
{
}

void Waypoint_Outpost6_8::updateState()
{
}

void Waypoint_Outpost6_8::clickAction2()
{
}

void Waypoint_Outpost6_8::clickAction0()
{
}

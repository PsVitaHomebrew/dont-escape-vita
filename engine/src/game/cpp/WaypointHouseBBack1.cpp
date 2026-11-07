#include "../game_all.h"

void WaypointHouseBBack1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_waypoint2");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_house_b_inside");
	trans_dir = WalkController::Direction::E;
}

void WaypointHouseBBack1::clickAction()
{
	PlayerController::pc->spawnName = S("WaypointHouseBInside1");
	CurtainController::cc->fadeOut(S("LocationHouseBInside"), WalkController::Direction::E);
}

void WaypointHouseBBack1::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointHouseBBack1::clickAction2()
{
}

void WaypointHouseBBack1::clickAction0()
{
}

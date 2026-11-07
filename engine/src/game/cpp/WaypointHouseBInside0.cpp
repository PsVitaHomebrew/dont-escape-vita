#include "../game_all.h"

void WaypointHouseBInside0::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_inside_waypoint0");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_house_b");
	trans_dir = WalkController::Direction::S_;
}

void WaypointHouseBInside0::clickAction()
{
	PlayerController::pc->spawnName = S("WaypointHouseB2");
	CurtainController::cc->fadeOut(S("LocationHouseB"), WalkController::Direction::S_);
}

void WaypointHouseBInside0::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointHouseBInside0::clickAction2()
{
}

void WaypointHouseBInside0::clickAction0()
{
}

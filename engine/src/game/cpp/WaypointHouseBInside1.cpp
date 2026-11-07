#include "../game_all.h"

void WaypointHouseBInside1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_inside_waypoint1");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_house_b_back");
}

void WaypointHouseBInside1::clickAction()
{
	PlayerController::pc->spawnName = S("WaypointHouseBBack1");
	CurtainController::cc->fadeOut(S("LocationHouseBBack"), WalkController::Direction::S_);
}

void WaypointHouseBInside1::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointHouseBInside1::clickAction2()
{
}

void WaypointHouseBInside1::clickAction0()
{
}

#include "../game_all.h"

void WaypointHouseBBack0::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_back_waypoint0");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_house_b");
	trans_dir = WalkController::Direction::E;
}

void WaypointHouseBBack0::clickAction()
{
	PlayerController::pc->spawnName = S("WaypointHouseB1");
	CurtainController::cc->fadeOut(S("LocationHouseB"), WalkController::Direction::W);
}

void WaypointHouseBBack0::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointHouseBBack0::clickAction2()
{
}

void WaypointHouseBBack0::clickAction0()
{
}

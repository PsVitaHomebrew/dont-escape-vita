#include "../game_all.h"

void WaypointOutside_3_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("down_hill");
	doubleClickCondition = S("visited_baseOutside1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
}

void WaypointOutside_3_1::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_1_3");
	CurtainController::cc->fadeOut(S("LocationBaseOutside1"), WalkController::Direction::W);
}

void WaypointOutside_3_1::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointOutside_3_1::clickAction2()
{
}

void WaypointOutside_3_1::clickAction0()
{
}

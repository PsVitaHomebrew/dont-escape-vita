#include "../game_all.h"

void WaypointOutside_3_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_path");
	doubleClickCondition = S("visited_baseOutside2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void WaypointOutside_3_2::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint2_3");
	CurtainController::cc->fadeOut(S("LocationBaseOutside2"), WalkController::Direction::W);
}

void WaypointOutside_3_2::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointOutside_3_2::clickAction2()
{
}

void WaypointOutside_3_2::clickAction0()
{
}

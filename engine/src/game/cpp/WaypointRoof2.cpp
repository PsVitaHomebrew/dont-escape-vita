#include "../game_all.h"

void WaypointRoof2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("roof_other_part");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_roof1");
	range = 10.0f;
	trans_dir = WalkController::Direction::E;
}

void WaypointRoof2::clickAction()
{
	PlayerController::pc->spawnName = S("WaypointRoof1");
	CurtainController::cc->fadeOut(S("LocationRoof1"), WalkController::Direction::E);
}

void WaypointRoof2::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointRoof2::clickAction2()
{
}

void WaypointRoof2::clickAction0()
{
}

#include "../game_all.h"

void WaypointRV21::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_exit");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_rv_inside");
	trans_dir = WalkController::Direction::S_;
	range = 2.0f;
}

void WaypointRV21::clickAction()
{
	PlayerController::pc->spawnName = S("WaypointRV12");
	CurtainController::cc->fadeOut(S("LocationRV"), WalkController::Direction::S_);
}

void WaypointRV21::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointRV21::clickAction2()
{
}

void WaypointRV21::clickAction0()
{
}

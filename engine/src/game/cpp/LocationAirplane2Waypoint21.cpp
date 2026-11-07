#include "../game_all.h"

void LocationAirplane2Waypoint21::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airplane_exit");
	doubleClickCondition = S("visited_airplane1");
	actionType = Type::Transition;
	trans_dir = WalkController_Direction::S_;
}

void LocationAirplane2Waypoint21::clickAction()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("LocationAirplane1Waypoint12");
	CurtainController::cc->fadeOut(S("LocationAirplane1"), WalkController_Direction::S_);
}

void LocationAirplane2Waypoint21::updateState()
{
	colliderManager->setCollider(0);
}

void LocationAirplane2Waypoint21::clickAction2()
{
}

void LocationAirplane2Waypoint21::clickAction0()
{
}

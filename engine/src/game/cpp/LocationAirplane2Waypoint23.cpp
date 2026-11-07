#include "../game_all.h"

void LocationAirplane2Waypoint23::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airplane_cabin");
	doubleClickCondition = S("visited_airplane3");
	actionType = Type::Transition;
	trans_dir = WalkController_Direction::E;
}

void LocationAirplane2Waypoint23::clickAction()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("LocationAirplane3Waypoint32");
	CurtainController::cc->fadeOut(S("LocationAirplane3"), WalkController_Direction::E);
}

void LocationAirplane2Waypoint23::updateState()
{
	colliderManager->setCollider(0);
}

void LocationAirplane2Waypoint23::clickAction2()
{
}

void LocationAirplane2Waypoint23::clickAction0()
{
}

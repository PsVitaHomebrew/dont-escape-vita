#include "../game_all.h"

void LocationAirplane3Waypoint32::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airplane_cargo");
	doubleClickCondition = S("visited_airplane2");
	actionType = Type::Transition;
	trans_dir = WalkController_Direction::W;
}

void LocationAirplane3Waypoint32::clickAction()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("LocationAirplane2Waypoint23");
	CurtainController::cc->fadeOut(S("LocationAirplane2"), WalkController_Direction::W);
}

void LocationAirplane3Waypoint32::updateState()
{
	colliderManager->setCollider(0);
}

void LocationAirplane3Waypoint32::clickAction2()
{
}

void LocationAirplane3Waypoint32::clickAction0()
{
}

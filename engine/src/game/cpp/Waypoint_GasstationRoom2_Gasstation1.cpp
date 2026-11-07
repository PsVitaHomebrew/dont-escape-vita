#include "../game_all.h"

void Waypoint_GasstationRoom2_Gasstation1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_exit");
	doubleClickCondition = S("visited_gasstation1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void Waypoint_GasstationRoom2_Gasstation1::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Gasstation1_GasstationRoom2");
	CurtainController::cc->fadeOut(S("LocationGasstation1"), WalkController::Direction::S_);
}

void Waypoint_GasstationRoom2_Gasstation1::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_GasstationRoom2_Gasstation1::clickAction2()
{
}

void Waypoint_GasstationRoom2_Gasstation1::clickAction0()
{
}

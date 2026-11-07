#include "../game_all.h"

void Waypoint_Crossroad_Base::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("up_hill");
	doubleClickCondition = S("visited_baseOutside1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void Waypoint_Crossroad_Base::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outside_Crossroad");
	CurtainController::cc->fadeOut(S("LocationBaseOutside1"), WalkController::Direction::N);
}

void Waypoint_Crossroad_Base::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_Crossroad_Base::clickAction2()
{
}

void Waypoint_Crossroad_Base::clickAction0()
{
}

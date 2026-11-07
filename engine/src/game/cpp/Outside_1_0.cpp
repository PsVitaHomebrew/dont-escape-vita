#include "../game_all.h"

void Outside_1_0::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("up_hill");
	doubleClickCondition = S("visited_baseOutside0");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void Outside_1_0::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_0_1");
	CurtainController::cc->fadeOut(S("LocationBaseOutside0"), WalkController::Direction::NE);
}

void Outside_1_0::updateState()
{
	colliderManager->setCollider(0);
}

void Outside_1_0::clickAction2()
{
}

void Outside_1_0::clickAction0()
{
}

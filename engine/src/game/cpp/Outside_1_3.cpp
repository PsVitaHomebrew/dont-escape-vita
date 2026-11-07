#include "../game_all.h"

void Outside_1_3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("up_hill");
	doubleClickCondition = S("visited_baseOutside3");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
}

void Outside_1_3::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_3_1");
	CurtainController::cc->fadeOut(S("LocationBaseOutside3"), WalkController::Direction::E);
}

void Outside_1_3::updateState()
{
	colliderManager->setCollider(0);
}

void Outside_1_3::clickAction2()
{
}

void Outside_1_3::clickAction0()
{
}

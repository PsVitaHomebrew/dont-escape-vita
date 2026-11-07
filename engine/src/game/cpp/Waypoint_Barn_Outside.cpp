#include "../game_all.h"

void Waypoint_Barn_Outside::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_exit");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_baseOutside3");
	trans_dir = WalkController::Direction::W;
}

void Waypoint_Barn_Outside::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outside_Barn");
	CurtainController::cc->fadeOut(S("LocationBaseOutside3"), WalkController::Direction::W);
}

void Waypoint_Barn_Outside::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_Barn_Outside::clickAction2()
{
}

void Waypoint_Barn_Outside::clickAction0()
{
}

#include "../game_all.h"

void Waypoint_0_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("down_hill");
	doubleClickCondition = S("visited_baseOutside1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Waypoint_0_1::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_1_0");
	CurtainController::cc->fadeOut(S("LocationBaseOutside1"), WalkController::Direction::SE);
}

void Waypoint_0_1::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_0_1::clickAction2()
{
}

void Waypoint_0_1::clickAction0()
{
}

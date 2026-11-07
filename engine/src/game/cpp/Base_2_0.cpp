#include "../game_all.h"

void Base_2_0::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_front");
	doubleClickCondition = S("visited_baseOutside0");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Base_2_0::clickAction()
{
	PlayerController::pc->spawnName = S("Base_0_2");
	CurtainController::cc->fadeOut(S("LocationBaseOutside0"), WalkController::Direction::W);
}

void Base_2_0::updateState()
{
	colliderManager->setCollider(0);
}

void Base_2_0::clickAction2()
{
}

void Base_2_0::clickAction0()
{
}

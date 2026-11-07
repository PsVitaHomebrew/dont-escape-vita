#include "../game_all.h"

void BaseExit2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_back");
	doubleClickCondition = S("visited_baseOutside2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
}

void BaseExit2::clickAction()
{
	PlayerController::pc->spawnName = S("Base_2_0");
	CurtainController::cc->fadeOut(S("LocationBaseOutside2"), WalkController::Direction::NE);
}

void BaseExit2::updateState()
{
	colliderManager->setCollider(0);
}

void BaseExit2::clickAction2()
{
}

void BaseExit2::clickAction0()
{
}

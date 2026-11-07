#include "../game_all.h"

void DreamStairsUpper::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("dream_stairs");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	doubleClickCondition = String::Empty;
}

void DreamStairsUpper::clickAction()
{
	GameDataController::gd->setObjective(S("dream_day_3b_started"), false);
	PlayerController::pc->spawnName = S("DreamStairs");
	CurtainController::cc->fadeOut(S("Dream3"), WalkController::Direction::W);
}

void DreamStairsUpper::climbCrane()
{
}

void DreamStairsUpper::updateState()
{
	setCollider(0);
}

void DreamStairsUpper::clickAction2()
{
}

void DreamStairsUpper::clickAction0()
{
}

#include "../game_all.h"

void MoonAirlockExit::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("leave");
	range = 1.0f;
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	doubleClickCondition = String::Empty;
}

void MoonAirlockExit::clickAction()
{
	PlayerController::pc->spawnName = S("LocationMoon2_Airlock");
	CurtainController::cc->fadeOut(S("Moon2"), WalkController::Direction::N);
}

void MoonAirlockExit::updateState()
{
}

void MoonAirlockExit::clickAction2()
{
}

void MoonAirlockExit::clickAction0()
{
}

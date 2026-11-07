#include "../game_all.h"

void LocationMoon1_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moonbase1");
	range = 1.0f;
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
}

void LocationMoon1_2::clickAction()
{
	PlayerController::pc->spawnName = S("LocationMoon2_1");
	CurtainController::cc->fadeOut(S("Moon2"), WalkController::Direction::N);
}

void LocationMoon1_2::updateState()
{
}

void LocationMoon1_2::clickAction2()
{
}

void LocationMoon1_2::clickAction0()
{
}

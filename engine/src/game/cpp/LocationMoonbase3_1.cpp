#include "../game_all.h"

void LocationMoonbase3_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moonbase_passage");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	doubleClickCondition = S("moon_allow_fast_travel_now");
}

void LocationMoonbase3_1::clickAction()
{
	PlayerController::pc->spawnName = S("LocationMoonbase1_3");
	CurtainController::cc->fadeOut(S("LocationMoonbase1"), WalkController::Direction::E);
}

void LocationMoonbase3_1::updateState()
{
}

void LocationMoonbase3_1::clickAction2()
{
}

void LocationMoonbase3_1::clickAction0()
{
}

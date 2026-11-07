#include "../game_all.h"

void Waypoint_Crashsite1_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("crashsite_cars");
	doubleClickCondition = S("visited_crashsite2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void Waypoint_Crashsite1_2::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Crashsite2_1");
	CurtainController::cc->fadeOut(S("LocationCrashsite2"), WalkController::Direction::E);
}

void Waypoint_Crashsite1_2::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_Crashsite1_2::clickAction2()
{
}

void Waypoint_Crashsite1_2::clickAction0()
{
}

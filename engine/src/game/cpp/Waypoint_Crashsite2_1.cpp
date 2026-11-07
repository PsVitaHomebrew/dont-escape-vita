#include "../game_all.h"

void Waypoint_Crashsite2_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("road_west");
	doubleClickCondition = S("visited_crashsite1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Waypoint_Crashsite2_1::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Crashsite1_2");
	CurtainController::cc->fadeOut(S("LocationCrashsite1"), WalkController::Direction::S_);
}

void Waypoint_Crashsite2_1::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_Crashsite2_1::clickAction2()
{
}

void Waypoint_Crashsite2_1::clickAction0()
{
}

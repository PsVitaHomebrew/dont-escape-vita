#include "../game_all.h"

void Waypoint_Pesttruck_Crashsite2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_exit");
	doubleClickCondition = S("visited_crashsite2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Waypoint_Pesttruck_Crashsite2::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Crashsite2_Pesttruck");
	CurtainController::cc->fadeOut(S("LocationCrashsite2"), WalkController::Direction::W);
}

void Waypoint_Pesttruck_Crashsite2::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_Pesttruck_Crashsite2::clickAction2()
{
}

void Waypoint_Pesttruck_Crashsite2::clickAction0()
{
}

#include "../game_all.h"

void LocationDesertFence3Waypoint2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tent_waypoint");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
}

void LocationDesertFence3Waypoint2::clickAction()
{
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("sky_paralax"), WalkController::Direction::S_);
}

void LocationDesertFence3Waypoint2::updateState()
{
}

void LocationDesertFence3Waypoint2::clickAction2()
{
}

void LocationDesertFence3Waypoint2::clickAction0()
{
}

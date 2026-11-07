#include "../game_all.h"

void LocationDesertFence1Wall::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	range = 10.0f;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tutorial_wall_far");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void LocationDesertFence1Wall::clickAction()
{
	PlayerController::pc->spawnName = S("Fence2Waypoint1");
	CurtainController::cc->fadeOut(S("LocationDesertFence2"), WalkController::Direction::N, S("stand_n"));
}

void LocationDesertFence1Wall::updateState()
{
}

void LocationDesertFence1Wall::clickAction2()
{
}

void LocationDesertFence1Wall::clickAction0()
{
}

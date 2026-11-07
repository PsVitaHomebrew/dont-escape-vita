#include "../game_all.h"

void LocationDesertFence3Waypoint1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tutorial_wall2");
	doubleClickCondition = S("visited_fence2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void LocationDesertFence3Waypoint1::clickAction()
{
	PlayerController::pc->spawnName = S("wall");
	CurtainController::cc->fadeOut(S("LocationDesertFence2"), WalkController::Direction::W, S("window_jump"));
}

void LocationDesertFence3Waypoint1::updateState()
{
	colliderManager->setCollider(0);
}

void LocationDesertFence3Waypoint1::clickAction2()
{
}

void LocationDesertFence3Waypoint1::clickAction0()
{
}

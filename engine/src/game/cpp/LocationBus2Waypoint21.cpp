#include "../game_all.h"

void LocationBus2Waypoint21::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bus_exit");
	doubleClickCondition = S("visited_bus1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
}

void LocationBus2Waypoint21::clickAction()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("LocationBus2Waypoint12");
	CurtainController::cc->fadeOut(S("LocationBus1"), WalkController::Direction::S_);
}

void LocationBus2Waypoint21::updateState()
{
	colliderManager->setCollider(0);
}

void LocationBus2Waypoint21::clickAction2()
{
}

void LocationBus2Waypoint21::clickAction0()
{
}

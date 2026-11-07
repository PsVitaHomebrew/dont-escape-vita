#include "../game_all.h"

void LocationBus2Waypoint12::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bus_entrance");
	doubleClickCondition = S("visited_bus2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void LocationBus2Waypoint12::clickAction()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("LocationBus2Waypoint21");
	CurtainController::cc->fadeOut(S("LocationBus2"), WalkController::Direction::N);
}

void LocationBus2Waypoint12::updateState()
{
	colliderManager->setCollider(0);
}

void LocationBus2Waypoint12::clickAction2()
{
}

void LocationBus2Waypoint12::clickAction0()
{
}

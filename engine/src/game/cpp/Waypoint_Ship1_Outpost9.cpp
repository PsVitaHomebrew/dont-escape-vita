#include "../game_all.h"

void Waypoint_Ship1_Outpost9::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship_outside");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	doubleClickCondition = S("visited_outpost9");
}

void Waypoint_Ship1_Outpost9::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost9_Ship1");
	CurtainController::cc->fadeOut(S("LocationOutpost9"), WalkController::Direction::E);
}

void Waypoint_Ship1_Outpost9::rideDown()
{
}

void Waypoint_Ship1_Outpost9::updateState()
{
}

void Waypoint_Ship1_Outpost9::clickAction2()
{
}

void Waypoint_Ship1_Outpost9::clickAction0()
{
}

#include "../game_all.h"

void Waypoint_Outpost9_Ship1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship_inside");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	range = 2.0f;
	doubleClickCondition = S("visited_ship1");
}

void Waypoint_Outpost9_Ship1::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Ship1_Outpost9");
	CurtainController::cc->fadeOut(S("LocationShip1"), WalkController::Direction::S_);
}

void Waypoint_Outpost9_Ship1::rideDown()
{
}

void Waypoint_Outpost9_Ship1::updateState()
{
}

void Waypoint_Outpost9_Ship1::clickAction2()
{
}

void Waypoint_Outpost9_Ship1::clickAction0()
{
}

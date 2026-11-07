#include "../game_all.h"

void Waypoint_Ship2_Ship1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("climb_ladder_up");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ship_ladder_up");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 0.0f;
	doubleClickCondition = S("visited_outpost_ship1");
}

void Waypoint_Ship2_Ship1::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Ship1_Ship2");
	CurtainController::cc->fadeOut(S("LocationShip1"), WalkController::Direction::E);
}

void Waypoint_Ship2_Ship1::rideDown()
{
}

void Waypoint_Ship2_Ship1::updateState()
{
}

void Waypoint_Ship2_Ship1::clickAction2()
{
}

void Waypoint_Ship2_Ship1::clickAction0()
{
}

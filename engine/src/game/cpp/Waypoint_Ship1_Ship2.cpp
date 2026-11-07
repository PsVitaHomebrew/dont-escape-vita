#include "../game_all.h"

void Waypoint_Ship1_Ship2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("climb_ladder_down");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ship_ladder_down");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	range = 0.0f;
	doubleClickCondition = S("visited_ship2");
}

void Waypoint_Ship1_Ship2::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Ship2_Ship1");
	CurtainController::cc->fadeOut(S("LocationShip2"), WalkController::Direction::SE, S("window_jump"));
}

void Waypoint_Ship1_Ship2::rideDown()
{
}

void Waypoint_Ship1_Ship2::updateState()
{
}

void Waypoint_Ship1_Ship2::clickAction2()
{
}

void Waypoint_Ship1_Ship2::clickAction0()
{
	loss->clambino = true;
}

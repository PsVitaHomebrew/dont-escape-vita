#include "../game_all.h"

void WaypointRestaurant13::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_waypoint13");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_restaurant_inside");
	range = 3.0f;
	trans_dir = WalkController::Direction::N;
}

void WaypointRestaurant13::clickAction()
{
	PlayerController::pc->spawnName = S("WaypointRestaurant3_1");
	CurtainController::cc->fadeOut(S("LocationRestaurant3"), WalkController::Direction::N);
}

void WaypointRestaurant13::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointRestaurant13::clickAction2()
{
}

void WaypointRestaurant13::clickAction0()
{
}

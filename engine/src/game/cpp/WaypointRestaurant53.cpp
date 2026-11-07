#include "../game_all.h"

void WaypointRestaurant53::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_waypoint31");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_restaurant_wc");
	range = 20.0f;
	trans_dir = WalkController::Direction::N;
}

void WaypointRestaurant53::clickAction()
{
	PlayerController::pc->spawnName = S("WaypointRestaurant3_5");
	CurtainController::cc->fadeOut(S("LocationRestaurant3"), WalkController::Direction::E);
}

void WaypointRestaurant53::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointRestaurant53::clickAction2()
{
}

void WaypointRestaurant53::clickAction0()
{
}

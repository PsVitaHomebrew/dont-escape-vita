#include "../game_all.h"

void WaypointRestaurant21::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_waypoint21");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_restaurant_front");
	range = 5.0f;
	trans_dir = WalkController::Direction::E;
}

void WaypointRestaurant21::clickAction()
{
	PlayerController::pc->spawnName = S("WaypointRestaurant1_2");
	CurtainController::cc->fadeOut(S("LocationRestaurant1"), WalkController::Direction::E);
}

void WaypointRestaurant21::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointRestaurant21::clickAction2()
{
}

void WaypointRestaurant21::clickAction0()
{
}

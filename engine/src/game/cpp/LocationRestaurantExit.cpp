#include "../game_all.h"

void LocationRestaurantExit::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_waypoint0");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_restaurant_front");
	range = 70.0f;
	trans_dir = WalkController::Direction::E;
}

void LocationRestaurantExit::clickAction()
{
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
}

void LocationRestaurantExit::updateState()
{
	colliderManager->setCollider(0);
}

void LocationRestaurantExit::clickAction2()
{
}

void LocationRestaurantExit::clickAction0()
{
}

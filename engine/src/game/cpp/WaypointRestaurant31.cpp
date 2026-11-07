#include "../game_all.h"

void WaypointRestaurant31::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_waypoint31");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_restaurant_front");
	range = 2.0f;
	trans_dir = WalkController::Direction::S_;
}

void WaypointRestaurant31::clickAction()
{
	if (GameDataController::gd->getObjective(S("restaurant_door_opened")))
	{
		GameDataController::gd->setObjective(S("restaurant_door_opened_teamed"), true);
	}
	PlayerController::pc->spawnName = S("WaypointRestaurant1_3");
	CurtainController::cc->fadeOut(S("LocationRestaurant1"), WalkController::Direction::S_);
}

void WaypointRestaurant31::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointRestaurant31::clickAction2()
{
}

void WaypointRestaurant31::clickAction0()
{
}

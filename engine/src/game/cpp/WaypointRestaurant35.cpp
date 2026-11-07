#include "../game_all.h"

void WaypointRestaurant35::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_waypoint35");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_restaurant_wc");
	range = 20.0f;
	trans_dir = WalkController::Direction::W;
}

void WaypointRestaurant35::clickAction()
{
	if (GameDataController::gd->getCurrentDay() != 2 || GameDataController::gd->getObjective(S("restaurant_door_opened2")))
	{
		if (GameDataController::gd->getObjective(S("restaurant_door_opened")))
		{
			GameDataController::gd->setObjective(S("restaurant_door_opened_teamed"), true);
		}
		PlayerController::pc->spawnName = S("WaypointRestaurant5_3");
		CurtainController::cc->fadeOut(S("LocationRestaurant5"), WalkController::Direction::S_);
	}
}

void WaypointRestaurant35::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getCurrentDay() == 2 && !GameDataController::gd->getObjective(S("restaurant_door_opened2")))
	{
		range = 10.0f;
		characterAnimationName = S("action_stnd_");
	}
	else
	{
		range = 20.0f;
		characterAnimationName = S("stop");
	}
}

void WaypointRestaurant35::clickAction2()
{
}

void WaypointRestaurant35::clickAction0()
{
}

#include "../game_all.h"

void WaypointRestaurant34::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_waypoint34");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_restaurant_kitchen");
	range = 2.0f;
	trans_dir = WalkController::Direction::N;
}

void WaypointRestaurant34::clickAction()
{
	if (GameDataController::gd->getObjective(S("restaurant_door_opened")))
	{
		GameDataController::gd->setObjective(S("restaurant_door_opened_teamed"), true);
		PlayerController::pc->spawnName = S("WaypointRestaurant4_3");
		CurtainController::cc->fadeOut(S("LocationRestaurant4"), WalkController::Direction::W);
	}
	else if (GameDataController::gd->getCurrentDay() == 2)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("restaurant_door_locked")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("restaurant_door_locked2")));
	}
}

void WaypointRestaurant34::updateState()
{
	if (!GameDataController::gd->getObjective(S("restaurant_door_opened")))
	{
		colliderManager->setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(locked);
		range = 2000.0f;
		actionType = Type::NormalAction;
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(open);
		colliderManager->setCollider(1);
		range = 2.0f;
		actionType = Type::Transition;
	}
	if (GameDataController::gd->getCurrentDay() > 2)
	{
		colliderManager->setCollider(1);
		range = 2.0f;
	}
}

void WaypointRestaurant34::clickAction2()
{
}

void WaypointRestaurant34::clickAction0()
{
}

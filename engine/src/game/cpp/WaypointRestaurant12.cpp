#include "../game_all.h"

void WaypointRestaurant12::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_waypoint12");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_restaurant_back");
	trans_dir = WalkController::Direction::W;
	range = 10.0f;
}

void WaypointRestaurant12::clickAction()
{
	if (!GameDataController::gd->getObjective(S("dialogue_cody_intro")) && GameDataController::gd->getCurrentDay() == 2)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("restaurant_first_check_front")));
		return;
	}
	PlayerController::pc->spawnName = S("WaypointRestaurant2_1");
	CurtainController::cc->fadeOut(S("LocationRestaurant2"), WalkController::Direction::N);
}

void WaypointRestaurant12::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getCurrentDay() == 2 && !GameDataController::gd->getObjective(S("dialogue_cody_intro")))
	{
		range = 1.0f;
		characterAnimationName = S("action_stnd_");
	}
	else
	{
		range = 10.0f;
		characterAnimationName = S("stop");
	}
}

void WaypointRestaurant12::clickAction2()
{
}

void WaypointRestaurant12::clickAction0()
{
}

#include "../game_all.h"

void Restaurant2Window::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_window");
	range = 10.0f;
}

void Restaurant2Window::clickAction()
{
	if (GameDataController::gd->getObjective(S("visited_restaurant_kitchen")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("rather_door")), true);
		return;
	}
	if (!GameDataController::gd->getObjective(S("restaurant_trash_moved")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_window")), true);
		return;
	}
	PlayerController::pc->spawnName = S("WaypointRestaurant4_2");
	CurtainController::cc->fadeOut(S("LocationRestaurant4"), WalkController::Direction::S_, S("window_jump"));
}

void Restaurant2Window::updateState()
{
	if (GameDataController::gd->getObjective(S("visited_restaurant_kitchen")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 100.0f;
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(open);
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 10.0f;
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(closed);
	}
	if (!GameDataController::gd->getObjective(S("visited_restaurant_kitchen")) && GameDataController::gd->getObjective(S("restaurant_trash_moved")))
	{
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = false;
		range = 10.0f;
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::E;
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 10.0f;
		actionType = Type::NormalAction;
	}
}

void Restaurant2Window::clickAction2()
{
}

void Restaurant2Window::clickAction0()
{
}

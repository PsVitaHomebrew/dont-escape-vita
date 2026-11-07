#include "../game_all.h"

void WaypointRestaurant43::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_waypoint43l");
	actionType = Type::Transition;
	doubleClickCondition = S("restaurant_door_opened");
	range = 2.0f;
	trans_dir = WalkController::Direction::E;
}

void WaypointRestaurant43::clickAction()
{
	if (!GameDataController::gd->getObjective(S("dialogue_cody_door_opened")) && ItemsManager::im->getItem(S("foodcan"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("foodcanopen"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && GameDataController::gd->getCurrentDay() == 2)
	{
		PlayerController::pc->setBusy(false);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("take_foodcan_plz")), true);
		PlayerController::wc->dir = WalkController::Direction::W;
		CursorController::cc->showCursor(CursorController::PixelCursor::NORMAL);
		return;
	}
	if (!GameDataController::gd->getObjective(S("restaurant_door_opened")))
	{
		GameDataController::gd->setObjective(S("restaurant_door_opened"), true);
		updateState();
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_creak1);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->crowbar_pry_open);
	}
	PlayerController::pc->spawnName = S("WaypointRestaurant3_4");
	CurtainController::cc->fadeOut(S("LocationRestaurant3"), WalkController::Direction::S_);
}

void WaypointRestaurant43::updateState()
{
	if (!GameDataController::gd->getObjective(S("restaurant_door_opened")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("restaurant_waypoint43l");
		actionType = Type::NormalAction;
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		objectName = S("restaurant_waypoint43o");
		actionType = Type::Transition;
	}
	colliderManager->setCollider(0);
}

void WaypointRestaurant43::whatOnClick()
{
	if (!GameDataController::gd->getObjective(S("dialogue_cody_door_opened")) && ItemsManager::im->getItem(S("foodcan"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && ItemsManager::im->getItem(S("foodcanopen"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1)
	{
		characterAnimationName = S("action_stnd_");
		range = 200.0f;
		PlayerController::wc->range = (int)range;
	}
	else
	{
		characterAnimationName = S("stop");
		range = 2.0f;
		PlayerController::wc->range = (int)range;
	}
}

void WaypointRestaurant43::clickAction2()
{
}

void WaypointRestaurant43::clickAction0()
{
}

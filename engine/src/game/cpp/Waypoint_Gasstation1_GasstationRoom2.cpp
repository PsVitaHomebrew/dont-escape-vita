#include "../game_all.h"

void Waypoint_Gasstation1_GasstationRoom2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_entry1");
	doubleClickCondition = S("visited_gasstationRoom2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void Waypoint_Gasstation1_GasstationRoom2::clickAction()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")))
	{
		PlayerController::pc->setBusy(false);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_nospider")), true);
		CursorController::cc->showCursor(CursorController::PixelCursor::NORMAL);
	}
	else
	{
		PlayerController::pc->spawnName = S("Waypoint_GasstationRoom2_Gasstation1");
		CurtainController::cc->fadeOut(S("LocationGasstationRoom2"), WalkController::Direction::S_);
	}
}

void Waypoint_Gasstation1_GasstationRoom2::updateState()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && ItemsManager::im->getItem(S("rifle_6"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
	{
		colliderManager->setCollider(-1);
	}
	else
	{
		colliderManager->setCollider(0);
	}
}

void Waypoint_Gasstation1_GasstationRoom2::whatOnClick0()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")))
	{
		range = 100.0f;
		doubleClickCondition = S("gasstation_spider_shot");
	}
	else
	{
		doubleClickCondition = S("visited_gasstationRoom2");
		range = 1.0f;
	}
}

void Waypoint_Gasstation1_GasstationRoom2::clickAction2()
{
}

void Waypoint_Gasstation1_GasstationRoom2::clickAction0()
{
}

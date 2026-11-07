#include "../game_all.h"

void Waypoint_GasstationRoom1_GasstationRoom2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_room1_entry");
	doubleClickCondition = S("visited_gasstationRoom2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
}

void Waypoint_GasstationRoom1_GasstationRoom2::clickAction()
{
	if (characterAnimationName == S("stop"))
	{
		PlayerController::pc->spawnName = S("Waypoint_GasstationRoom2_GasstationRoom1");
		CurtainController::cc->fadeOut(S("LocationGasstationRoom2"), WalkController::Direction::E);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_nospider")), true);
		PlayerController::wc->dir = WalkController::Direction::E;
		CursorController::cc->showCursor(CursorController::PixelCursor::NORMAL);
	}
}

void Waypoint_GasstationRoom1_GasstationRoom2::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")) && GameDataController::gd->getObjectiveDetail(S("gasstation_spider_discovered")) == 2)
	{
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
		range = 100.0f;
		doubleClickCondition = S("gasstation_spider_baited");
	}
	else if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_blocking")), true);
		PlayerController::wc->fullStop(true);
		range = 1.0f;
		doubleClickCondition = S("gasstation_spider_baited");
	}
	else
	{
		doubleClickCondition = S("visited_gasstationRoom2");
	}
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")))
	{
		characterAnimationName = S("action_stnd_");
		range = 100.0f;
		doubleClickCondition = S("gasstation_spider_shot");
	}
	else
	{
		characterAnimationName = S("stop");
		range = 1.0f;
		doubleClickCondition = S("visited_gasstationRoom2");
	}
}

void Waypoint_GasstationRoom1_GasstationRoom2::whatOnClick0()
{
}

void Waypoint_GasstationRoom1_GasstationRoom2::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")))
	{
		range = 100.0f;
	}
	else
	{
		range = 1.0f;
	}
}

void Waypoint_GasstationRoom1_GasstationRoom2::clickAction2()
{
}

void Waypoint_GasstationRoom1_GasstationRoom2::clickAction0()
{
}

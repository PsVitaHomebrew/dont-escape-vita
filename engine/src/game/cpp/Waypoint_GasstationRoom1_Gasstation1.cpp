#include "../game_all.h"

void Waypoint_GasstationRoom1_Gasstation1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	teleport = false;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_exit");
	doubleClickCondition = S("visited_gasstation1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 1.0f;
}

void Waypoint_GasstationRoom1_Gasstation1::clickAction()
{
	if (characterAnimationName == S("stop"))
	{
		PlayerController::pc->spawnName = S("Waypoint_Gasstation1_GasstationRoom1");
		if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && ItemsManager::im->getItem(S("rifle_6"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
		{
			CurtainController::cc->fadeOut(S("LocationGasstation1"), WalkController::Direction::W, S("sit_fall"), nullptr, true);
		}
		else
		{
			CurtainController::cc->fadeOut(S("LocationGasstation1"), WalkController::Direction::S_);
		}
	}
	else
	{
		PlayerController::pc->setBusy(false);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("take_gun_plz")), true);
		PlayerController::wc->dir = WalkController::Direction::N;
		CursorController::cc->showCursor(CursorController::PixelCursor::NORMAL);
	}
}

void Waypoint_GasstationRoom1_Gasstation1::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")) && GameDataController::gd->getObjectiveDetail(S("gasstation_spider_discovered")) == 1)
	{
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
		range = 100.0f;
		Debug::LogWarning(S("range = 100"));
		doubleClickCondition = S("gasstation_spider_baited");
	}
	else if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		range = 1.0f;
		Debug::LogWarning(S("range = 1"));
		PlayerController::wc->fullStop(true);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_blocking")), true);
		doubleClickCondition = S("gasstation_spider_baited");
	}
	else
	{
		doubleClickCondition = S("visited_gasstation1");
	}
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && ItemsManager::im->getItem(S("rifle_6"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) == -1 && !GameDataController::gd->getObjective(S("gasstation_spider_shot")))
	{
		characterAnimationName = S("action_stnd_s");
		doubleClickCondition = S("gasstation_spider_shot");
	}
	else
	{
		characterAnimationName = S("stop");
		doubleClickCondition = S("visited_gasstation1");
	}
}

void Waypoint_GasstationRoom1_Gasstation1::whatOnClick0()
{
}

void Waypoint_GasstationRoom1_Gasstation1::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_GasstationRoom1_Gasstation1::clickAction2()
{
}

void Waypoint_GasstationRoom1_Gasstation1::clickAction0()
{
}

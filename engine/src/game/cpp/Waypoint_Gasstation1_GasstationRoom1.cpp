#include "../game_all.h"

void Waypoint_Gasstation1_GasstationRoom1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_entry1");
	doubleClickCondition = S("visited_gasstationRoom1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 1.0f;
}

void Waypoint_Gasstation1_GasstationRoom1::clickAction()
{
	GameDataController::gd->setObjectiveDetail(S("gasstation_spider_discovered"), 1);
	PlayerController::pc->spawnName = S("Waypoint_GasstationRoom1_Gasstation1");
	String animation = nullptr;
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		animation = S("action_stnd_s");
	}
	CurtainController::cc->fadeOut(S("LocationGasstationRoom1"), WalkController::Direction::S_, animation);
}

void Waypoint_Gasstation1_GasstationRoom1::updateState()
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

void Waypoint_Gasstation1_GasstationRoom1::clickAction2()
{
}

void Waypoint_Gasstation1_GasstationRoom1::clickAction0()
{
}

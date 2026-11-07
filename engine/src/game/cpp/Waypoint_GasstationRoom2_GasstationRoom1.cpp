#include "../game_all.h"

void Waypoint_GasstationRoom2_GasstationRoom1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_room1_entry");
	doubleClickCondition = S("visited_gasstationRoom1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Waypoint_GasstationRoom2_GasstationRoom1::clickAction()
{
	GameDataController::gd->setObjectiveDetail(S("gasstation_spider_discovered"), 2);
	PlayerController::pc->spawnName = S("Waypoint_GasstationRoom1_GasstationRoom2");
	String animation = nullptr;
	bool flipX = false;
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		animation = S("action_stnd_se");
		flipX = true;
	}
	CurtainController::cc->fadeOut(S("LocationGasstationRoom1"), WalkController::Direction::W, animation, nullptr, flipX);
}

void Waypoint_GasstationRoom2_GasstationRoom1::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_GasstationRoom2_GasstationRoom1::clickAction2()
{
}

void Waypoint_GasstationRoom2_GasstationRoom1::clickAction0()
{
}

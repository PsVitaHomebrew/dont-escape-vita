#include "../game_all.h"

void CS3_Waypoint2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_in_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_waypoint_2_3");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = S("visited_cs_2");
}

void CS3_Waypoint2::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && !GameDataController::gd->getObjective(S("cs_rain_enter_left")) && !GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
		return;
	}
	GameDataController::gd->setObjective(S("cs_arrive_from_inside"), true);
	if (!GameDataController::gd->getObjective(S("cs_safe")))
	{
		GameDataController::gd->setObjective(S("cs_crow_away"), false);
	}
	else
	{
		GameDataController::gd->setObjective(S("cs_crow_away"), true);
	}
	PlayerController::pc->spawnName = S("CS2_Waypoint_3");
	CurtainController::cc->fadeOut(S("CS2"), WalkController::Direction::S_);
}

void CS3_Waypoint2::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && !GameDataController::gd->getObjective(S("cs_rain_enter_left")) && !GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 200.0f;
		doubleClickCondition = String::Empty;
	}
	else
	{
		characterAnimationName = S("kneel_in_n");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
		doubleClickCondition = S("visited_cs_2");
	}
}

void CS3_Waypoint2::clickAction2()
{
}

void CS3_Waypoint2::clickAction0()
{
}

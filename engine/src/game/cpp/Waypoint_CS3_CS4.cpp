#include "../game_all.h"

void Waypoint_CS3_CS4::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("construction_site_2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 10.0f;
}

void Waypoint_CS3_CS4::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && GameDataController::gd->getObjective(S("cs_rain_enter_left")) && !GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 0 || GameDataController::gd->getCurrentDay() != 3)
	{
		PlayerController::pc->spawnName = S("Waypoint_CS4_CS3");
		CurtainController::cc->fadeOut(S("CS4"), WalkController::Direction::W);
	}
}

void Waypoint_CS3_CS4::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && GameDataController::gd->getObjective(S("cs_rain_enter_left")) && !GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 200.0f;
		doubleClickCondition = String::Empty;
	}
	else
	{
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		range = 1.0f;
		doubleClickCondition = S("visited_cs_3");
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 3)
	{
		setCollider(-1);
	}
	else
	{
		setCollider(0);
	}
}

void Waypoint_CS3_CS4::clickAction2()
{
}

void Waypoint_CS3_CS4::clickAction0()
{
}

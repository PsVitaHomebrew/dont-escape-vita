#include "../game_all.h"

void SiderealOutside1_Waypoint_Map::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("back_to_road");
	doubleClickCondition = S("visited_sidereal_outside_1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
}

void SiderealOutside1_Waypoint_Map::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		PlayerController::pc->setBusy(true);
		PlayerController::pc->spawnName = S("InfoExit");
		CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::S_);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_cant_leave")));
	}
}

void SiderealOutside1_Waypoint_Map::whatOnClick0()
{
	if (!GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		range = 100.0f;
	}
	else
	{
		range = 2.0f;
	}
}

void SiderealOutside1_Waypoint_Map::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("car_location")) != 8)
	{
		colliderManager->setCollider(1);
	}
}

void SiderealOutside1_Waypoint_Map::clickAction2()
{
}

void SiderealOutside1_Waypoint_Map::clickAction0()
{
}

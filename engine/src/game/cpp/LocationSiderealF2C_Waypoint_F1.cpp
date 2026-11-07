#include "../game_all.h"

void LocationSiderealF2C_Waypoint_F1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_stairs_down");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
}

void LocationSiderealF2C_Waypoint_F1::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("map_outpost_revealed")) == TravelAgency::LOCATION_STATUS_UNDISCOVERED)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_cant_go_yet")));
		return;
	}
	PlayerController::pc->spawnName = S("LocationSiderealF1C_Waypoint_F2");
	CurtainController::cc->fadeOut(S("SiderealF1C"), WalkController::Direction::S_);
}

void LocationSiderealF2C_Waypoint_F1::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("map_outpost_revealed")) == TravelAgency::LOCATION_STATUS_UNDISCOVERED)
	{
		doubleClickCondition = String::Empty;
	}
	else
	{
		doubleClickCondition = S("visited_sidereal_f1c");
	}
}

void LocationSiderealF2C_Waypoint_F1::clickAction2()
{
}

void LocationSiderealF2C_Waypoint_F1::clickAction0()
{
}

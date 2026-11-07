#include "../game_all.h"

void LocationSiderealLab_Waypoint_C::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_corridor");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	doubleClickCondition = S("visited_sidereal_lab");
}

void LocationSiderealLab_Waypoint_C::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF0Ca_Waypoint_Lab");
	CurtainController::cc->fadeOut(S("SiderealF0C0a"), WalkController::Direction::S_);
}

void LocationSiderealLab_Waypoint_C::updateState()
{
}

void LocationSiderealLab_Waypoint_C::clickAction2()
{
}

void LocationSiderealLab_Waypoint_C::clickAction0()
{
}

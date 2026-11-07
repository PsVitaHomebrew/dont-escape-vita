#include "../game_all.h"

void LocationSiderealF0Ca_Waypoint_F0C::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_corridor");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	doubleClickCondition = S("visited_sidereal_f0c");
}

void LocationSiderealF0Ca_Waypoint_F0C::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF0C_Waypoint_F0c0a");
	CurtainController::cc->fadeOut(S("SiderealF0C"), WalkController::Direction::E);
}

void LocationSiderealF0Ca_Waypoint_F0C::updateState()
{
}

void LocationSiderealF0Ca_Waypoint_F0C::clickAction2()
{
}

void LocationSiderealF0Ca_Waypoint_F0C::clickAction0()
{
}

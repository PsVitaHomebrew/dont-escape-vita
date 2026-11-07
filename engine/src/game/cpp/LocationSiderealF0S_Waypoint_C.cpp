#include "../game_all.h"

void LocationSiderealF0S_Waypoint_C::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_exit3");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	doubleClickCondition = S("visited_sidereal_f0c");
}

void LocationSiderealF0S_Waypoint_C::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF0C_Waypoint_S");
	CurtainController::cc->fadeOut(S("SiderealF0C0a"), WalkController::Direction::E);
}

void LocationSiderealF0S_Waypoint_C::updateState()
{
}

void LocationSiderealF0S_Waypoint_C::clickAction2()
{
}

void LocationSiderealF0S_Waypoint_C::clickAction0()
{
}

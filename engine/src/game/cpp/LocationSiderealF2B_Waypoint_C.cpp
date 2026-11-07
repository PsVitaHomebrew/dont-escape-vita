#include "../game_all.h"

void LocationSiderealF2B_Waypoint_C::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_exit3");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	doubleClickCondition = S("visited_sidereal_f2c");
}

void LocationSiderealF2B_Waypoint_C::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF2C_Waypoint_B");
	CurtainController::cc->fadeOut(S("SiderealF2C"), WalkController::Direction::S_);
}

void LocationSiderealF2B_Waypoint_C::updateState()
{
}

void LocationSiderealF2B_Waypoint_C::clickAction2()
{
}

void LocationSiderealF2B_Waypoint_C::clickAction0()
{
}

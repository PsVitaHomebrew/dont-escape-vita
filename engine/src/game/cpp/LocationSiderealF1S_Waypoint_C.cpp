#include "../game_all.h"

void LocationSiderealF1S_Waypoint_C::Start()
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
	doubleClickCondition = S("visited_sidereal_f1c");
}

void LocationSiderealF1S_Waypoint_C::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF1C_Waypoint_S");
	CurtainController::cc->fadeOut(S("SiderealF1C"), WalkController::Direction::E);
}

void LocationSiderealF1S_Waypoint_C::updateState()
{
}

void LocationSiderealF1S_Waypoint_C::clickAction2()
{
}

void LocationSiderealF1S_Waypoint_C::clickAction0()
{
}

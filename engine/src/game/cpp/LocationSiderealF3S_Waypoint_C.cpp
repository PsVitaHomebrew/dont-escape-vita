#include "../game_all.h"

void LocationSiderealF3S_Waypoint_C::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_door1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	doubleClickCondition = S("visited_sidereal_f3c");
}

void LocationSiderealF3S_Waypoint_C::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF3C_Waypoint_S");
	CurtainController::cc->fadeOut(S("SiderealF3C"), WalkController::Direction::E);
}

void LocationSiderealF3S_Waypoint_C::updateState()
{
}

void LocationSiderealF3S_Waypoint_C::clickAction2()
{
}

void LocationSiderealF3S_Waypoint_C::clickAction0()
{
}

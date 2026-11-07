#include "../game_all.h"

void LocationSiderealF0C2_Waypoint_C1::Start()
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
	doubleClickCondition = S("visited_sidereal_f0c1");
}

void LocationSiderealF0C2_Waypoint_C1::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF0C1_Waypoint_F2");
	CurtainController::cc->fadeOut(S("SiderealF0C1"), WalkController::Direction::E);
}

void LocationSiderealF0C2_Waypoint_C1::updateState()
{
}

void LocationSiderealF0C2_Waypoint_C1::clickAction2()
{
}

void LocationSiderealF0C2_Waypoint_C1::clickAction0()
{
}

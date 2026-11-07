#include "../game_all.h"

void LocationSiderealF0C1_Waypoint_F2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_exit3");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = S("visited_sidereal_f0c1");
}

void LocationSiderealF0C1_Waypoint_F2::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF0C2_Waypoint_C1");
	CurtainController::cc->fadeOut(S("SiderealF0C2"), WalkController::Direction::W);
}

void LocationSiderealF0C1_Waypoint_F2::updateState()
{
}

void LocationSiderealF0C1_Waypoint_F2::clickAction2()
{
}

void LocationSiderealF0C1_Waypoint_F2::clickAction0()
{
}

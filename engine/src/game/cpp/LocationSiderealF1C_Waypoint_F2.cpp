#include "../game_all.h"

void LocationSiderealF1C_Waypoint_F2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_stairs_up");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = S("visited_sidereal_f2c");
}

void LocationSiderealF1C_Waypoint_F2::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF2C_Waypoint_F1");
	CurtainController::cc->fadeOut(S("SiderealF2C"), WalkController::Direction::S_);
}

void LocationSiderealF1C_Waypoint_F2::updateState()
{
}

void LocationSiderealF1C_Waypoint_F2::clickAction2()
{
}

void LocationSiderealF1C_Waypoint_F2::clickAction0()
{
}

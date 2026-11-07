#include "../game_all.h"

void LocationSiderealF2C_Waypoint_F3::Start()
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
	doubleClickCondition = S("visited_sidereal_f3c");
}

void LocationSiderealF2C_Waypoint_F3::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF3C_Waypoint_F2");
	CurtainController::cc->fadeOut(S("SiderealF3C"), WalkController::Direction::S_);
}

void LocationSiderealF2C_Waypoint_F3::updateState()
{
}

void LocationSiderealF2C_Waypoint_F3::clickAction2()
{
}

void LocationSiderealF2C_Waypoint_F3::clickAction0()
{
}

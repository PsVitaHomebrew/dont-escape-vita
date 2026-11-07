#include "../game_all.h"

void LocationSiderealF3C_Waypoint_F2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_stairs_down");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	doubleClickCondition = S("visited_sidereal_f2c");
}

void LocationSiderealF3C_Waypoint_F2::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF2C_Waypoint_F3");
	CurtainController::cc->fadeOut(S("SiderealF2C"), WalkController::Direction::S_, S("stand_s"));
}

void LocationSiderealF3C_Waypoint_F2::updateState()
{
}

void LocationSiderealF3C_Waypoint_F2::clickAction2()
{
}

void LocationSiderealF3C_Waypoint_F2::clickAction0()
{
}

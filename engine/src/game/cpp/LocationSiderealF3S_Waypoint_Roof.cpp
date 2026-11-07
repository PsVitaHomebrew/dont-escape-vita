#include "../game_all.h"

void LocationSiderealF3S_Waypoint_Roof::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_hole_outside");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = S("visited_sidereal_roof");
}

void LocationSiderealF3S_Waypoint_Roof::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealRoof_Waypoint_F3S");
	CurtainController::cc->fadeOut(S("LocationSiderealRoof"), WalkController::Direction::W);
}

void LocationSiderealF3S_Waypoint_Roof::updateState()
{
}

void LocationSiderealF3S_Waypoint_Roof::clickAction2()
{
}

void LocationSiderealF3S_Waypoint_Roof::clickAction0()
{
}

#include "../game_all.h"

void LocationSiderealClimb_Waypoint_Roof::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_climb3");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	range = 2.0f;
}

void LocationSiderealClimb_Waypoint_Roof::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealRoof_Waypoint_Climb");
	CurtainController::cc->fadeOut(S("LocationSiderealRoof"), WalkController::Direction::E);
}

void LocationSiderealClimb_Waypoint_Roof::updateState()
{
}

void LocationSiderealClimb_Waypoint_Roof::clickAction2()
{
}

void LocationSiderealClimb_Waypoint_Roof::clickAction0()
{
}

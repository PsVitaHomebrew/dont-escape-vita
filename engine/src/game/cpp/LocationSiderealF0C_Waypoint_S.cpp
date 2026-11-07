#include "../game_all.h"

void LocationSiderealF0C_Waypoint_S::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_corridor");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = S("visited_sidereal_f0s");
}

void LocationSiderealF0C_Waypoint_S::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF0S_Waypoint_C");
	CurtainController::cc->fadeOut(S("SiderealF0S"), WalkController::Direction::W);
}

void LocationSiderealF0C_Waypoint_S::updateState()
{
}

void LocationSiderealF0C_Waypoint_S::clickAction2()
{
}

void LocationSiderealF0C_Waypoint_S::clickAction0()
{
}

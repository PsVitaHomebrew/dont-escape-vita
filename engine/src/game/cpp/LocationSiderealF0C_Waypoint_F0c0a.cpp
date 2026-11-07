#include "../game_all.h"

void LocationSiderealF0C_Waypoint_F0c0a::Start()
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
	doubleClickCondition = S("visited_sidereal_f0c0a");
}

void LocationSiderealF0C_Waypoint_F0c0a::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF0Ca_Waypoint_F0C");
	CurtainController::cc->fadeOut(S("SiderealF0C0a"), WalkController::Direction::W);
}

void LocationSiderealF0C_Waypoint_F0c0a::updateState()
{
}

void LocationSiderealF0C_Waypoint_F0c0a::clickAction2()
{
}

void LocationSiderealF0C_Waypoint_F0c0a::clickAction0()
{
}

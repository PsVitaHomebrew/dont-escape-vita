#include "../game_all.h"

void LocationSiderealF2C_Waypoint_S::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_exit4");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = S("visited_sidereal_f2s");
}

void LocationSiderealF2C_Waypoint_S::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealF2S_Waypoint_C");
	CurtainController::cc->fadeOut(S("SiderealF2S"), WalkController::Direction::W);
}

void LocationSiderealF2C_Waypoint_S::updateState()
{
}

void LocationSiderealF2C_Waypoint_S::clickAction2()
{
}

void LocationSiderealF2C_Waypoint_S::clickAction0()
{
}

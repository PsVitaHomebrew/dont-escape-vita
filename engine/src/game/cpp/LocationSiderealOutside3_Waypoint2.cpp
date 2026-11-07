#include "../game_all.h"

void LocationSiderealOutside3_Waypoint2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_dune2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	range = 20.0f;
}

void LocationSiderealOutside3_Waypoint2::clickAction()
{
	PlayerController::pc->spawnName = S("SiderealOutside2_Waypoint_3");
	CurtainController::cc->fadeOut(S("SiderealOutside2"), WalkController::Direction::W);
}

void LocationSiderealOutside3_Waypoint2::updateState()
{
}

void LocationSiderealOutside3_Waypoint2::clickAction2()
{
}

void LocationSiderealOutside3_Waypoint2::clickAction0()
{
}

#include "../game_all.h"

void LocationSiderealRoof_Waypoint_Climb::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_climb");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	range = 2.0f;
}

void LocationSiderealRoof_Waypoint_Climb::clickAction()
{
	PlayerController::pc->spawnName = S("LocationSiderealClimb_Waypoint_Roof");
	CurtainController::cc->fadeOut(S("SiderealClimb"), WalkController::Direction::W);
}

void LocationSiderealRoof_Waypoint_Climb::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_roof_collapsed")))
	{
		colliderManager->setCollider(-1);
	}
	else
	{
		colliderManager->setCollider(0);
	}
}

void LocationSiderealRoof_Waypoint_Climb::clickAction2()
{
}

void LocationSiderealRoof_Waypoint_Climb::clickAction0()
{
}

#include "../game_all.h"

void SiderealOutside1_Waypoint_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_outside_front");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = S("visited_sidereal_outside_2");
}

void SiderealOutside1_Waypoint_2::clickAction()
{
	PlayerController::pc->spawnName = S("SiderealOutside2_Waypoint_1");
	CurtainController::cc->fadeOut(S("SiderealOutside2"), WalkController::Direction::NE);
}

void SiderealOutside1_Waypoint_2::updateState()
{
}

void SiderealOutside1_Waypoint_2::clickAction2()
{
}

void SiderealOutside1_Waypoint_2::clickAction0()
{
}

#include "../game_all.h"

void SiderealOutside2_Waypoint_3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_outside_back2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	doubleClickCondition = S("visited_sidereal_outside_3");
}

void SiderealOutside2_Waypoint_3::clickAction()
{
	PlayerController::pc->spawnName = S("SiderealOutside3_Waypoint_2");
	CurtainController::cc->fadeOut(S("SiderealOutside3"), WalkController::Direction::E);
}

void SiderealOutside2_Waypoint_3::updateState()
{
}

void SiderealOutside2_Waypoint_3::clickAction2()
{
}

void SiderealOutside2_Waypoint_3::clickAction0()
{
}

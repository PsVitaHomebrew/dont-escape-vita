#include "../game_all.h"

void SiderealOutside2_Waypoint_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_outside_back");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	range = 20.0f;
	doubleClickCondition = S("visited_sidereal_outside_1");
}

void SiderealOutside2_Waypoint_1::clickAction()
{
	PlayerController::pc->spawnName = S("SiderealOutside1_Waypoint_2");
	CurtainController::cc->fadeOut(S("SiderealOutside1"), WalkController::Direction::S_);
}

void SiderealOutside2_Waypoint_1::updateState()
{
}

void SiderealOutside2_Waypoint_1::clickAction2()
{
}

void SiderealOutside2_Waypoint_1::clickAction0()
{
}

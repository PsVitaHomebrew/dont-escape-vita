#include "../game_all.h"

void Waypoint_Outpost2_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_outside_back");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	doubleClickCondition = S("visited_outpost3");
}

void Waypoint_Outpost2_1::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost1_2");
	CurtainController::cc->fadeOut(S("LocationOutpostOutside1"), WalkController::Direction::S_);
}

void Waypoint_Outpost2_1::updateState()
{
}

void Waypoint_Outpost2_1::clickAction2()
{
}

void Waypoint_Outpost2_1::clickAction0()
{
}

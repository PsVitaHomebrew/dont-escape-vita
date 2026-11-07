#include "../game_all.h"

void Waypoint_Outpost1_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_approach");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = S("visited_outpost2");
}

void Waypoint_Outpost1_2::clickAction()
{
	gothere(String::Empty);
}

void Waypoint_Outpost1_2::gothere(String aaa)
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost2_1");
	CurtainController::cc->fadeOut(S("LocationOutpostOutside2"), WalkController::Direction::NE);
}

void Waypoint_Outpost1_2::updateState()
{
}

void Waypoint_Outpost1_2::clickAction2()
{
}

void Waypoint_Outpost1_2::clickAction0()
{
}

#include "../game_all.h"

void Waypoint_Outpost5_4::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_corridor2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	range = 2.0f;
	doubleClickCondition = S("visited_outpost4");
}

void Waypoint_Outpost5_4::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost4_5");
	CurtainController::cc->fadeOut(S("LocationOutpost4"), WalkController::Direction::E);
}

void Waypoint_Outpost5_4::rideDown()
{
}

void Waypoint_Outpost5_4::updateState()
{
}

void Waypoint_Outpost5_4::clickAction2()
{
}

void Waypoint_Outpost5_4::clickAction0()
{
}

#include "../game_all.h"

void Waypoint_Outpost11_4::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_back_corridor");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	range = 2.0f;
	doubleClickCondition = S("visited_outpost4");
}

void Waypoint_Outpost11_4::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost4_11");
	CurtainController::cc->fadeOut(S("LocationOutpost4"), WalkController::Direction::S_);
}

void Waypoint_Outpost11_4::rideDown()
{
}

void Waypoint_Outpost11_4::updateState()
{
}

void Waypoint_Outpost11_4::clickAction2()
{
}

void Waypoint_Outpost11_4::clickAction0()
{
}

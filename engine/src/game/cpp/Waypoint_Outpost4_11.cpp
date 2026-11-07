#include "../game_all.h"

void Waypoint_Outpost4_11::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_doorway");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	doubleClickCondition = S("visited_outpost11");
}

void Waypoint_Outpost4_11::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost11_4");
	CurtainController::cc->fadeOut(S("LocationOutpost11"), WalkController::Direction::N);
}

void Waypoint_Outpost4_11::rideDown()
{
}

void Waypoint_Outpost4_11::updateState()
{
}

void Waypoint_Outpost4_11::clickAction2()
{
}

void Waypoint_Outpost4_11::clickAction0()
{
}

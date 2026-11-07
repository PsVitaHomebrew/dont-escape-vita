#include "../game_all.h"

void Waypoint_Outpost4_5::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_corridor2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	range = 2.0f;
	doubleClickCondition = S("visited_outpost5");
}

void Waypoint_Outpost4_5::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost5_4");
	if (GameDataController::gd->getObjective(S("visited_outpost5")))
	{
		CurtainController::cc->fadeOut(S("LocationOutpost5"), WalkController::Direction::W);
	}
	else
	{
		CurtainController::cc->fadeOut(S("LocationOutpost5"), WalkController::Direction::W, S("walk_e"), nullptr, true);
	}
}

void Waypoint_Outpost4_5::rideDown()
{
}

void Waypoint_Outpost4_5::updateState()
{
}

void Waypoint_Outpost4_5::clickAction2()
{
}

void Waypoint_Outpost4_5::clickAction0()
{
}

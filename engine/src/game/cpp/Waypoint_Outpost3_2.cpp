#include "../game_all.h"

void Waypoint_Outpost3_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_exit");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = S("visited_outpost2");
}

void Waypoint_Outpost3_2::clickAction()
{
	if (!GameDataController::gd->getObjective(S("outpost_door_powered")))
	{
		PlayerController::pc->spawnName = S("Waypoint_Outpost2_3");
		CurtainController::cc->fadeOut(S("LocationOutpostOutside2"), WalkController::Direction::W);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_door_powered")));
	}
}

void Waypoint_Outpost3_2::updateState()
{
	if (!GameDataController::gd->getObjective(S("outpost_door_powered")))
	{
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
		doubleClickCondition = S("visited_outpost2");
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		actionType = Type::NormalAction;
		trans_dir = WalkController::Direction::N;
		doubleClickCondition = String::Empty;
	}
}

void Waypoint_Outpost3_2::clickAction2()
{
}

void Waypoint_Outpost3_2::clickAction0()
{
}

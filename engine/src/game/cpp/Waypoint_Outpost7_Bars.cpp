#include "../game_all.h"

void Waypoint_Outpost7_Bars::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_computer_bars1");
	actionType = Type::NormalAction;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	doubleClickCondition = String::Empty;
}

void Waypoint_Outpost7_Bars::clickAction()
{
	PlayerController::pc->spawnName = S("OutpostBarsExit");
	CurtainController::cc->fadeOut(S("LocationBarsPuzzle"), WalkController::Direction::S_);
}

void Waypoint_Outpost7_Bars::rideDown()
{
}

void Waypoint_Outpost7_Bars::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1)
	{
		objectName = S("outpost_computer_bars1");
	}
	else
	{
		objectName = S("outpost_computer_bars2");
	}
}

void Waypoint_Outpost7_Bars::clickAction2()
{
}

void Waypoint_Outpost7_Bars::clickAction0()
{
}

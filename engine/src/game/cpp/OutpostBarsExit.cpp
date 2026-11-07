#include "../game_all.h"

void OutpostBarsExit::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("leave");
	actionType = Type::Transition;
	trans_dir = WalkController_Direction::S_;
	range = 2.0f;
	doubleClickCondition = String::Empty;
}

void OutpostBarsExit::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Outpost7_Bars");
	CurtainController::cc->fadeOut(S("LocationOutpost7"), WalkController_Direction::SW);
}

void OutpostBarsExit::updateState()
{
}

void OutpostBarsExit::clickAction2()
{
}

void OutpostBarsExit::clickAction0()
{
}

#include "../game_all.h"

void GasstationRoom2_Spy::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_window");
	actionType = Type::NormalAction;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	teleport = false;
}

void GasstationRoom2_Spy::clickAction()
{
	GameDataController::gd->setObjective(S("gasstation_spy_mode"), true);
	PlayerController::pc->spawnName = S("Gasstation2SpyWaypoint");
	CurtainController::cc->fadeOut(S("LocationGasstation2"), WalkController::Direction::E);
}

void GasstationRoom2_Spy::goThere(String s)
{
}

void GasstationRoom2_Spy::updateState()
{
}

void GasstationRoom2_Spy::clickAction2()
{
}

void GasstationRoom2_Spy::clickAction0()
{
}

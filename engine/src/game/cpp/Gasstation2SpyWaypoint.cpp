#include "../game_all.h"

void Gasstation2SpyWaypoint::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_window_away");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	range = 200.0f;
	teleport = true;
}

void Gasstation2SpyWaypoint::clickAction()
{
	GameDataController::gd->setObjective(S("gasstation_spy_mode"), false);
	PlayerController::pc->spawnName = S("Waypoint_GasstationRoom2_Spy");
	CurtainController::cc->fadeOut(S("LocationGasstationRoom2"), WalkController::Direction::E);
}

void Gasstation2SpyWaypoint::goThere(String s)
{
}

void Gasstation2SpyWaypoint::updateState()
{
	setCollider(-1);
	if (GameDataController::gd->getObjective(S("gasstation_spy_mode")))
	{
		setCollider(0);
	}
}

void Gasstation2SpyWaypoint::clickAction2()
{
}

void Gasstation2SpyWaypoint::clickAction0()
{
}

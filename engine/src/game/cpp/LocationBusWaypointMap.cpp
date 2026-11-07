#include "../game_all.h"

void LocationBusWaypointMap::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("exit_wasteland");
	doubleClickCondition = S("visited_bus1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	range = 10.0f;
}

void LocationBusWaypointMap::clickAction()
{
	PlayerController::pc->setBusy(true);
	GameDataController::gd->setObjectiveDetail(S("map_bus_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
}

void LocationBusWaypointMap::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("car_location")) != 11)
	{
		colliderManager->setCollider(1);
	}
}

void LocationBusWaypointMap::clickAction2()
{
}

void LocationBusWaypointMap::clickAction0()
{
}

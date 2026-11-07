#include "../game_all.h"

void Waypoint_Airplane_Map::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("exit_wasteland");
	doubleClickCondition = S("visited_airplane1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	range = 10.0f;
}

void Waypoint_Airplane_Map::clickAction()
{
	PlayerController::pc->setBusy(true);
	GameDataController::gd->setObjectiveDetail(S("map_airplane_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
}

void Waypoint_Airplane_Map::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("car_location")) != 12)
	{
		colliderManager->setCollider(1);
	}
}

void Waypoint_Airplane_Map::clickAction2()
{
}

void Waypoint_Airplane_Map::clickAction0()
{
}

#include "../game_all.h"

void Waypoint_RV_Crashsite::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_exit");
	doubleClickCondition = S("visited_rv");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	range = 10.0f;
}

void Waypoint_RV_Crashsite::clickAction()
{
	PlayerController::pc->setBusy(true);
	GameDataController::gd->setObjectiveDetail(S("map_rv_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
}

void Waypoint_RV_Crashsite::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("car_location")) == 6)
	{
		setCollider(1);
	}
	else
	{
		setCollider(0);
	}
}

void Waypoint_RV_Crashsite::clickAction2()
{
}

void Waypoint_RV_Crashsite::clickAction0()
{
}

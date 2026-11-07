#include "../game_all.h"

void OutpostOutside1_Waypoint_Map::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("exit_wasteland");
	doubleClickCondition = S("visited_outpost1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	range = 10.0f;
}

void OutpostOutside1_Waypoint_Map::clickAction()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
}

void OutpostOutside1_Waypoint_Map::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("car_location")) != 10)
	{
		colliderManager->setCollider(1);
	}
}

void OutpostOutside1_Waypoint_Map::clickAction2()
{
}

void OutpostOutside1_Waypoint_Map::clickAction0()
{
}

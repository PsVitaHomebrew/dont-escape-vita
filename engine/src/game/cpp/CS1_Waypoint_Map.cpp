#include "../game_all.h"

void CS1_Waypoint_Map::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("back_to_road");
	doubleClickCondition = S("visited_cs_1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
}

void CS1_Waypoint_Map::clickAction()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::S_);
}

void CS1_Waypoint_Map::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("car_location")) == 9)
	{
		colliderManager->setCollider(1);
	}
}

void CS1_Waypoint_Map::clickAction2()
{
}

void CS1_Waypoint_Map::clickAction0()
{
}

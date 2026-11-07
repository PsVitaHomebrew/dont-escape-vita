#include "../game_all.h"

void HuntersLodgeOutside1_Waypoint_Map::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_exit");
	doubleClickCondition = S("visited_hunters_lodge_1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
}

void HuntersLodgeOutside1_Waypoint_Map::clickAction()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::S_);
}

void HuntersLodgeOutside1_Waypoint_Map::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("car_location")) == 7)
	{
		colliderManager->setCollider(1);
	}
}

void HuntersLodgeOutside1_Waypoint_Map::clickAction2()
{
}

void HuntersLodgeOutside1_Waypoint_Map::clickAction0()
{
}

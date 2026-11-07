#include "../game_all.h"

void Waypoint_Crossroad_Gasstation::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("road_west");
	doubleClickCondition = S("visited_bridge");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Waypoint_Crossroad_Gasstation::clickAction()
{
	if (GameDataController::gd->getObjective(S("base_discovered")))
	{
		if (GameDataController::gd->getCurrentDay() != 3 || GameDataController::gd->getObjective(S("sidereal_base_located")))
		{
			GameDataController::gd->setObjectiveDetail(S("map_bridge_revealed"), 1);
		}
		GameDataController::gd->setObjective(S("crossroads_left"), true);
		PlayerController::pc->setBusy(true);
		PlayerController::pc->spawnName = S("InfoExit");
		CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
	}
	else
	{
		PlayerController::pc->setBusy(false);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("story_no_go")), true);
	}
}

void Waypoint_Crossroad_Gasstation::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_Crossroad_Gasstation::clickAction2()
{
}

void Waypoint_Crossroad_Gasstation::clickAction0()
{
}

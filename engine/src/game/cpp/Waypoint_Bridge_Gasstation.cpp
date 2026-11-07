#include "../game_all.h"

void Waypoint_Bridge_Gasstation::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("road_west");
	doubleClickCondition = S("visited_gasstation");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Waypoint_Bridge_Gasstation::clickAction()
{
	if (!GameDataController::gd->getObjective(S("bridge_westside")) && !GameDataController::gd->getObjective(S("bridge_planks_used_1")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("ravine_wrong_side")), true);
		return;
	}
	GameDataController::gd->setObjective(S("bridge_westside"), true);
	GameDataController::gd->setObjectiveDetail(S("map_gasstation_revealed"), 1);
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
}

void Waypoint_Bridge_Gasstation::whatOnClick()
{
}

void Waypoint_Bridge_Gasstation::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("bridge_westside")) && !GameDataController::gd->getObjective(S("bridge_planks_used_1")))
	{
		doubleClickCondition = String::Empty;
		range = 2000.0f;
	}
	else
	{
		doubleClickCondition = S("visited_gasstation");
		range = 4.0f;
	}
}

void Waypoint_Bridge_Gasstation::clickAction2()
{
}

void Waypoint_Bridge_Gasstation::clickAction0()
{
}

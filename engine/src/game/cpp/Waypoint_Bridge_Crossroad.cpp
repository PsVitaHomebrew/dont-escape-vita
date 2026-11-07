#include "../game_all.h"

void Waypoint_Bridge_Crossroad::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("road_east");
	doubleClickCondition = S("visited_crossroad");
	range = 1.0f;
	teleport = false;
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
}

void Waypoint_Bridge_Crossroad::clickAction()
{
	if (GameDataController::gd->getObjective(S("bridge_westside")) && !GameDataController::gd->getObjective(S("bridge_planks_used_1")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("ravine_wrong_side")), true);
		return;
	}
	GameDataController::gd->setObjective(S("bridge_westside"), false);
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
}

void Waypoint_Bridge_Crossroad::whatOnClick()
{
}

void Waypoint_Bridge_Crossroad::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("bridge_westside")) && !GameDataController::gd->getObjective(S("bridge_planks_used_1")))
	{
		doubleClickCondition = String::Empty;
		range = 2000.0f;
	}
	else
	{
		doubleClickCondition = S("visited_crossroad");
		range = 17.0f;
	}
}

void Waypoint_Bridge_Crossroad::clickAction2()
{
}

void Waypoint_Bridge_Crossroad::clickAction0()
{
}

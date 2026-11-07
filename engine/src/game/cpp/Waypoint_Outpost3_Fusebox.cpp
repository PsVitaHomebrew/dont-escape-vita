#include "../game_all.h"

void Waypoint_Outpost3_Fusebox::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("fusebox");
	actionType = Type::NormalAction;
	range = 2.0f;
	sr = gameObject->GetComponent<SpriteRenderer>();
}

void Waypoint_Outpost3_Fusebox::clickAction()
{
	if (GameDataController::gd->getObjective(S("outpost_elevator_powered")) && !GameDataController::gd->getObjective(S("outpost_door_powered")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_fusebox_done")));
	}
	else if (GameDataController::gd->getObjective(S("outpost_fusebox_open")))
	{
		PlayerController::pc->spawnName = S("ElectricExit");
		CurtainController::cc->fadeOut(S("LocationFuseBox"), WalkController::Direction::W);
		GameDataController::gd->setObjective(S("outpost_elevator_open"), false);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->locker_01);
		GameDataController::gd->setObjective(S("outpost_fusebox_open"), true);
		updateAll();
	}
}

void Waypoint_Outpost3_Fusebox::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_fusebox_open")))
	{
		sr->set_enabled(true);
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		sr->set_enabled(false);
		characterAnimationName = S("action1_e");
		animationFlip = true;
		useCurrentDirection = false;
	}
}

void Waypoint_Outpost3_Fusebox::clickAction2()
{
}

void Waypoint_Outpost3_Fusebox::clickAction0()
{
}

#include "../game_all.h"

void Waypoint_Outpost5_6::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_doorway");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	doubleClickCondition = S("visited_outpost6");
}

void Waypoint_Outpost5_6::clickAction()
{
	if (GameDataController::gd->getObjective(S("outpost_hall_open")))
	{
		PlayerController::pc->spawnName = S("Waypoint_Outpost6_5");
		CurtainController::cc->fadeOut(S("LocationOutpost6"), WalkController::Direction::S_);
	}
	else if (GameDataController::gd->getObjective(S("outpost_hall_unlocked")))
	{
		GameDataController::gd->setObjective(S("outpost_hall_open"), true);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_door_open);
		updateAll();
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_door_locked);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("generic_locked")));
	}
}

void Waypoint_Outpost5_6::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_hall_open")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("outpost_hall_open")))
	{
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
		range = 2.0f;
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = false;
		objectName = S("outpost_staircase");
		return;
	}
	objectName = S("outpost_doorway");
	actionType = Type::NormalAction;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	if (GameDataController::gd->getObjective(S("outpost_hall_unlocked")))
	{
		characterAnimationName = S("open_n");
	}
	else
	{
		characterAnimationName = S("action_n");
	}
	animationFlip = false;
	useCurrentDirection = false;
}

void Waypoint_Outpost5_6::clickAction2()
{
}

void Waypoint_Outpost5_6::clickAction0()
{
}

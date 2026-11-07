#include "../game_all.h"

void Waypoint_Outpost4_10::Start()
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
	doubleClickCondition = S("visited_outpost10");
}

void Waypoint_Outpost4_10::clickAction()
{
	if (GameDataController::gd->getObjective(S("outpost_storage_open")))
	{
		PlayerController::pc->spawnName = S("Waypoint_Outpost10_4");
		CurtainController::cc->fadeOut(S("LocationOutpost10"), WalkController::Direction::N);
	}
	else if (GameDataController::gd->getObjective(S("outpost_fingerprint_unlocked")))
	{
		GameDataController::gd->setObjective(S("outpost_storage_open"), true);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_door_open);
		updateAll();
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_door_locked);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("locked_fingerprint")));
	}
}

void Waypoint_Outpost4_10::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_storage_open")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("outpost_storage_open")))
	{
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
		range = 2.0f;
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = false;
		return;
	}
	actionType = Type::NormalAction;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	if (GameDataController::gd->getObjective(S("outpost_fingerprint_unlocked")))
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

void Waypoint_Outpost4_10::clickAction2()
{
}

void Waypoint_Outpost4_10::clickAction0()
{
}

#include "../game_all.h"

void WaypointRV12::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_door");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_rv2");
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
}

void WaypointRV12::clickAction()
{
	if (GameDataController::gd->getObjective(S("rv_door_open")))
	{
		PlayerController::pc->spawnName = S("WaypointRV21");
		CurtainController::cc->fadeOut(S("LocationRV2"), WalkController::Direction::N);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fridge);
		GameDataController::gd->setObjective(S("rv_door_open"), true);
		updateAll();
	}
}

void WaypointRV12::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_door_open")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(doorOpen);
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		actionType = Type::Transition;
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(doorClosed);
		characterAnimationName = S("action_open_ne");
		animationFlip = true;
		useCurrentDirection = false;
		actionType = Type::NormalAction;
	}
}

void WaypointRV12::clickAction2()
{
}

void WaypointRV12::clickAction0()
{
}

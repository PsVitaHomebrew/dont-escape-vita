#include "../game_all.h"

void Attic1Door::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("attic_door");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_attic2");
	range = 5.0f;
	trans_dir = WalkController::Direction::W;
}

void Attic1Door::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Attic2Door");
	if (!GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
	{
		CurtainController::cc->fadeOut(S("LocationAttic2"), WalkController::Direction::W, S("walk_e"), nullptr, true);
	}
	else
	{
		CurtainController::cc->fadeOut(S("LocationAttic2"), WalkController::Direction::W);
	}
}

void Attic1Door::updateState()
{
	colliderManager->setCollider(0);
}

void Attic1Door::clickAction2()
{
}

void Attic1Door::clickAction0()
{
}

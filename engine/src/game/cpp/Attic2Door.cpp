#include "../game_all.h"

void Attic2Door::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("attic_door");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_attic1");
	trans_dir = WalkController::Direction::E;
}

void Attic2Door::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Attic1Door");
	CurtainController::cc->fadeOut(S("LocationAttic1"), WalkController::Direction::E);
}

void Attic2Door::updateState()
{
	colliderManager->setCollider(0);
}

void Attic2Door::clickAction2()
{
}

void Attic2Door::clickAction0()
{
}

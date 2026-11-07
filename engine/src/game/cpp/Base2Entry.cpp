#include "../game_all.h"

void Base2Entry::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("kitchen_entry");
	doubleClickCondition = S("visited_location2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Base2Entry::clickAction()
{
	PlayerController::pc->spawnName = S("KitchenExitWay");
	CurtainController::cc->fadeOut(S("Location2"), WalkController::Direction::W);
}

void Base2Entry::updateState()
{
	if (GameDataController::gd->getObjective(S("location02_door_open")))
	{
		colliderManager->setCollider(0);
	}
	else
	{
		colliderManager->setCollider(-1);
	}
}

void Base2Entry::clickAction2()
{
}

void Base2Entry::clickAction0()
{
}

#include "../game_all.h"

void KitchenExit::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("kitchen_exit");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_baseOutside2");
	trans_dir = WalkController_Direction::E;
}

void KitchenExit::clickAction()
{
	PlayerController::pc->spawnName = S("Base_Entry");
	CurtainController::cc->fadeOut(S("LocationBaseOutside2"), WalkController_Direction::E);
}

void KitchenExit::updateState()
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

void KitchenExit::clickAction2()
{
}

void KitchenExit::clickAction0()
{
}

#include "../game_all.h"

void Door2_Exit::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_exit");
	doubleClickCondition = S("visited_baseOutside0");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Door2_Exit::clickAction()
{
	PlayerController::pc->spawnName = S("Base_Entry");
	CurtainController::cc->fadeOut(S("LocationBaseOutside0"), WalkController::Direction::SW);
}

void Door2_Exit::updateState()
{
	if (GameDataController::gd->getObjective(S("location01_door2_open")))
	{
		colliderManager->setCollider(0);
	}
	else
	{
		colliderManager->setCollider(-1);
	}
}

void Door2_Exit::clickAction2()
{
}

void Door2_Exit::Update()
{
}

void Door2_Exit::clickAction0()
{
}

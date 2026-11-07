#include "../game_all.h"

void BaseEntry::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_entry");
	doubleClickCondition = S("visited_location1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
}

void BaseEntry::clickAction()
{
	PlayerController::pc->spawnName = S("Door2_Exit");
	CurtainController::cc->fadeOut(S("Location1"), WalkController::Direction::E);
}

void BaseEntry::updateState()
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

void BaseEntry::clickAction2()
{
}

void BaseEntry::clickAction0()
{
}

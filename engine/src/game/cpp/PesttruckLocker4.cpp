#include "../game_all.h"

void PesttruckLocker4::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_open_ne");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pesttruck_locker");
}

void PesttruckLocker4::clickAction()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->locker_01);
}

void PesttruckLocker4::updateState()
{
	if (GameDataController::gd->getObjective(S("pesttruck_locker4_open")))
	{
		characterAnimationName = S("open_n");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(-1);
	}
	else
	{
		characterAnimationName = S("open_n");
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(0);
	}
}

void PesttruckLocker4::clickAction2()
{
	GameDataController::gd->setObjective(S("pesttruck_locker4_open"), !GameDataController::gd->getObjective(S("pesttruck_locker4_open")));
	updateState();
	updateAll();
}

void PesttruckLocker4::clickAction0()
{
}

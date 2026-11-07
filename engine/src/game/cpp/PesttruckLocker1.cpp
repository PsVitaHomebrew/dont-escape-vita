#include "../game_all.h"

void PesttruckLocker1::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("open_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pesttruck_locker");
}

void PesttruckLocker1::clickAction()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->locker_01);
}

void PesttruckLocker1::updateState()
{
	if (GameDataController::gd->getObjective(S("pesttruck_locker1_open")))
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

void PesttruckLocker1::clickAction2()
{
	GameDataController::gd->setObjective(S("pesttruck_locker1_open"), true);
	updateState();
	updateAll();
}

void PesttruckLocker1::clickAction0()
{
}

#include "../game_all.h"

void PesttruckLocker3::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("open_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pesttruck_locker");
}

void PesttruckLocker3::clickAction()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->locker_01);
}

void PesttruckLocker3::updateState()
{
	if (GameDataController::gd->getObjective(S("pesttruck_locker3_open")))
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

void PesttruckLocker3::clickAction2()
{
	GameDataController::gd->setObjective(S("pesttruck_locker3_open"), !GameDataController::gd->getObjective(S("pesttruck_locker3_open")));
	updateState();
	updateAll();
}

void PesttruckLocker3::clickAction0()
{
}

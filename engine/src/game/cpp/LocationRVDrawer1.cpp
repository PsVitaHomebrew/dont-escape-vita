#include "../game_all.h"

void LocationRVDrawer1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_up_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_drawer");
	range = 1.0f;
}

void LocationRVDrawer1::clickAction()
{
	GameDataController::gd->setObjective(S("rv_shelf1_open"), true);
	updateAll();
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->cabinet_open);
}

void LocationRVDrawer1::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_shelf1_open")))
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void LocationRVDrawer1::clickAction2()
{
}

void LocationRVDrawer1::clickAction0()
{
}

void LocationRVDrawer1::whatOnClick0()
{
}

void LocationRVDrawer1::whatOnClick()
{
}

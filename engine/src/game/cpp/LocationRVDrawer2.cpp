#include "../game_all.h"

void LocationRVDrawer2::Start()
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

void LocationRVDrawer2::clickAction()
{
	GameDataController::gd->setObjective(S("rv_shelf2_open"), true);
	updateAll();
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->cabinet_open);
}

void LocationRVDrawer2::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_shelf2_open")))
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

void LocationRVDrawer2::clickAction2()
{
}

void LocationRVDrawer2::clickAction0()
{
}

void LocationRVDrawer2::whatOnClick0()
{
}

void LocationRVDrawer2::whatOnClick()
{
}

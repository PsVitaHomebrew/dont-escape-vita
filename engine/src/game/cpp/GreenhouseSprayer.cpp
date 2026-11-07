#include "../game_all.h"

void GreenhouseSprayer::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("greenhouse_sprayer");
	range = 5.0f;
}

void GreenhouseSprayer::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("watersprayer"))))
	{
		GameDataController::gd->setObjective(S("greenhouse_sprayer_taken"), true);
		updateAll();
	}
}

void GreenhouseSprayer::whatOnClick()
{
	if (PlayerController::wc->currentXY.y < 69.0f)
	{
		characterAnimationName = S("action_n");
	}
	else
	{
		characterAnimationName = S("action_s");
	}
}

void GreenhouseSprayer::updateState()
{
	if (GameDataController::gd->getObjective(S("greenhouse_sprayer_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
}

void GreenhouseSprayer::clickAction2()
{
}

void GreenhouseSprayer::clickAction0()
{
}

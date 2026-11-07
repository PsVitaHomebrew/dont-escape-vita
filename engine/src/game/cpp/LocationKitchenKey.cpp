#include "../game_all.h"

void LocationKitchenKey::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_key");
	shined = false;
}

void LocationKitchenKey::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("key2"))))
	{
		GameDataController::gd->setObjective(S("house_key_taken"), true);
		updateAll();
	}
}

void LocationKitchenKey::updateState()
{
	if (GameDataController::gd->getObjective(S("house_key_taken")))
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

void LocationKitchenKey::clickAction2()
{
}

void LocationKitchenKey::clickAction0()
{
}

void LocationKitchenKey::shine()
{
	if (!shined)
	{
		shined = true;
	}
	else if ((double)Random::get_value() > 0.25)
	{
		gameObject->GetComponent<Animator>()->Play(S("Location2KeyShine"), 0, 0.0f);
	}
}

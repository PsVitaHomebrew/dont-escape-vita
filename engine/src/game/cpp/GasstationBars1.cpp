#include "../game_all.h"

void GasstationBars1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_bars");
}

void GasstationBars1::clickAction()
{
	if (!GameDataController::gd->getObjective(S("gasstation_bars1_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("window_bars1"))))
	{
		GameDataController::gd->setObjective(S("gasstation_bars1_taken"), true);
		updateState();
	}
}

void GasstationBars1::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("gasstation_bars1_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		characterAnimationName = S("kneel_e");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void GasstationBars1::clickAction2()
{
}

void GasstationBars1::clickAction0()
{
}

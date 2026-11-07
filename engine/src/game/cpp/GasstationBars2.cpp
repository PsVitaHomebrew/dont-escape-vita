#include "../game_all.h"

void GasstationBars2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_bars");
}

void GasstationBars2::clickAction()
{
	if (!GameDataController::gd->getObjective(S("gasstation_bars2_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("window_bars2"))))
	{
		GameDataController::gd->setObjective(S("gasstation_bars2_taken"), true);
		updateState();
	}
}

void GasstationBars2::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("gasstation_bars2_taken")))
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

void GasstationBars2::clickAction2()
{
}

void GasstationBars2::clickAction0()
{
}

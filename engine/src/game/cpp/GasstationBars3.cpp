#include "../game_all.h"

void GasstationBars3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_bars");
}

void GasstationBars3::clickAction()
{
	if (!GameDataController::gd->getObjective(S("gasstation_bars3_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("window_bars3"))))
	{
		GameDataController::gd->setObjective(S("gasstation_bars3_taken"), true);
		updateState();
	}
}

void GasstationBars3::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("gasstation_bars3_taken")))
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

void GasstationBars3::clickAction2()
{
}

void GasstationBars3::clickAction0()
{
}

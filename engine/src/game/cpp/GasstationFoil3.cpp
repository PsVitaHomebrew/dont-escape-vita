#include "../game_all.h"

void GasstationFoil3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_foil");
}

void GasstationFoil3::clickAction()
{
	if (!GameDataController::gd->getObjective(S("gasstation_foil3_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("window_foil3"))))
	{
		GameDataController::gd->setObjective(S("gasstation_foil3_taken"), true);
		updateState();
	}
}

void GasstationFoil3::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("gasstation_foil3_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void GasstationFoil3::clickAction2()
{
}

void GasstationFoil3::clickAction0()
{
}

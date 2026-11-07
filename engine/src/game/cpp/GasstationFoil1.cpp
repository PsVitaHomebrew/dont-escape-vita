#include "../game_all.h"

void GasstationFoil1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_foil");
}

void GasstationFoil1::clickAction()
{
	if (!GameDataController::gd->getObjective(S("gasstation_foil1_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("window_foil1"))))
	{
		GameDataController::gd->setObjective(S("gasstation_foil1_taken"), true);
		updateState();
	}
}

void GasstationFoil1::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("gasstation_foil1_taken")))
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

void GasstationFoil1::clickAction2()
{
}

void GasstationFoil1::clickAction0()
{
}

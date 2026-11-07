#include "../game_all.h"

void GasstationNet2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_net");
}

void GasstationNet2::clickAction()
{
	if (!GameDataController::gd->getObjective(S("gasstation_net2_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("window_net2"))))
	{
		GameDataController::gd->setObjective(S("gasstation_net2_taken"), true);
		updateState();
	}
}

void GasstationNet2::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("gasstation_net2_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		characterAnimationName = S("action_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void GasstationNet2::clickAction2()
{
}

void GasstationNet2::clickAction0()
{
}

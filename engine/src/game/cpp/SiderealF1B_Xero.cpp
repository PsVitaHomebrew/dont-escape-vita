#include "../game_all.h"

void SiderealF1B_Xero::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_xero");
	range = 2.0f;
	updateState();
}

void SiderealF1B_Xero::clickAction()
{
	pickItUp(nullptr);
}

void SiderealF1B_Xero::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sidereal_xero"))))
	{
		ItemsManager::exmineItem(ItemsManager::im->getItem(S("sidereal_xero")));
		GameDataController::gd->setObjective(S("sidereal_xero_taken"), true);
		updateAll();
	}
}

void SiderealF1B_Xero::whatOnClick()
{
}

void SiderealF1B_Xero::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_xero_taken")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(-1);
		return;
	}
	GetComponent<SpriteRenderer>()->set_enabled(true);
	range = 2.0f;
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action1_e");
	setCollider(0);
}

void SiderealF1B_Xero::clickAction2()
{
}

void SiderealF1B_Xero::clickAction0()
{
}

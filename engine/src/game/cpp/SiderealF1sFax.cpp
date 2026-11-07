#include "../game_all.h"

void SiderealF1sFax::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_secrets");
	range = 2.0f;
	updateState();
}

void SiderealF1sFax::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_secrets_taken")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_fax")));
	}
	else
	{
		pickItUp(nullptr);
	}
}

void SiderealF1sFax::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sidereal_secrets"))))
	{
		ItemsManager::exmineItem(ItemsManager::im->getItem(S("sidereal_secrets")));
		GameDataController::gd->setObjective(S("sidereal_secrets_taken"), true);
		updateAll();
	}
}

void SiderealF1sFax::whatOnClick()
{
}

void SiderealF1sFax::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_secrets_taken")))
	{
		range = 50.0f;
		animationFlip = false;
		useCurrentDirection = true;
		characterAnimationName = S("action_stnd_");
		GetComponent<SpriteRenderer>()->set_enabled(false);
		objectName = S("sidereal_fax");
	}
	else
	{
		range = 2.0f;
		animationFlip = false;
		useCurrentDirection = false;
		GetComponent<SpriteRenderer>()->set_enabled(true);
		characterAnimationName = S("action_n");
		objectName = S("sidereal_secrets");
	}
}

void SiderealF1sFax::clickAction2()
{
}

void SiderealF1sFax::clickAction0()
{
}

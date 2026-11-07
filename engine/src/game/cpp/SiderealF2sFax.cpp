#include "../game_all.h"

void SiderealF2sFax::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_fax");
	range = 2.0f;
	updateState();
}

void SiderealF2sFax::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_papers_taken")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_fax")));
	}
	else
	{
		pickItUp(nullptr);
	}
}

void SiderealF2sFax::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sidereal_docs"))))
	{
		ItemsManager::exmineItem(ItemsManager::im->getItem(S("sidereal_docs")));
		GameDataController::gd->setObjective(S("sidereal_papers_taken"), true);
		updateAll();
	}
}

void SiderealF2sFax::whatOnClick()
{
}

void SiderealF2sFax::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_papers_taken")))
	{
		range = 50.0f;
		animationFlip = false;
		useCurrentDirection = true;
		characterAnimationName = S("action_stnd_");
	}
	else
	{
		range = 2.0f;
		animationFlip = false;
		useCurrentDirection = false;
		characterAnimationName = S("action_n");
	}
}

void SiderealF2sFax::clickAction2()
{
}

void SiderealF2sFax::clickAction0()
{
}

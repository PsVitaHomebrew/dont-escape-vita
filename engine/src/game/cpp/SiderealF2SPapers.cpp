#include "../game_all.h"

void SiderealF2SPapers::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_papers");
	range = 2.0f;
	updateState();
}

void SiderealF2SPapers::clickAction()
{
	pickItUp(nullptr);
}

void SiderealF2SPapers::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sidereal_docs"))))
	{
		ItemsManager::exmineItem(ItemsManager::im->getItem(S("sidereal_docs")));
		GameDataController::gd->setObjective(S("sidereal_papers_taken"), true);
		updateAll();
	}
}

void SiderealF2SPapers::whatOnClick()
{
}

void SiderealF2SPapers::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_papers_taken")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void SiderealF2SPapers::clickAction2()
{
}

void SiderealF2SPapers::clickAction0()
{
}

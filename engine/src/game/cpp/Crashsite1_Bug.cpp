#include "../game_all.h"

void Crashsite1_Bug::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kneel_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("crashsite_bug");
	updateState();
}

void Crashsite1_Bug::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("bug"))))
	{
		GameDataController::gd->setObjective(S("crashsite_bug_taken"), true);
		ExamineSprite::es->show(ItemsManager::im->getItem(S("bug"))->examineSprite, ItemsManager::im->getItem(S("bug"))->examineSprite_1, ItemsManager::im->getItem(S("bug"))->examineSprite_2, ItemsManager::im->getItem(S("bug"))->examineSprite_3, ItemsManager::im->getItem(S("bug"))->examineSprite_4);
		updateState();
	}
}

void Crashsite1_Bug::updateState()
{
	if (!GameDataController::gd->getObjective(S("crashsite_bug_taken")) && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		characterAnimationName = S("kneel_");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void Crashsite1_Bug::clickAction2()
{
}

void Crashsite1_Bug::clickAction0()
{
}

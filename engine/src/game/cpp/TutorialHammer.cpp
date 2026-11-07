#include "../game_all.h"

void TutorialHammer::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tutorial_hammerhead");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("sledge_handle"), GameStrings::getString(GameStrings::actions, S("generic_pick_it_up")), nullptr, String::Empty));
}

void TutorialHammer::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sledge_head"))))
	{
		GameDataController::gd->setObjective(S("tutorial_hammer_taken"), true);
		updateAll();
	}
}

void TutorialHammer::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("tutorial_hammer_taken")) || !GameDataController::gd->getObjective(S("tutorial_door_opened")))
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void TutorialHammer::clickAction2()
{
}

void TutorialHammer::clickAction0()
{
}

void TutorialHammer::whatOnClick0()
{
}

void TutorialHammer::whatOnClick()
{
}

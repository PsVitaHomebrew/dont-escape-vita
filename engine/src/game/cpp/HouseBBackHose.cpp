#include "../game_all.h"

void HouseBBackHose::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_back_hose_1");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("screwdriver"), GameStrings::getString(GameStrings::actions, S("hose_screwdriver")), nullptr, String::Empty));
}

void HouseBBackHose::clickAction()
{
	if (!GameDataController::gd->getObjective(S("house_b_hose_disconnected")) && usedItem == S("wrench"))
	{
		GameDataController::gd->setObjective(S("house_b_hose_disconnected"), true);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_hose_disconnected")), true);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->screw);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hose);
		updateState();
	}
	else if (GameDataController::gd->getObjective(S("house_b_hose_disconnected")) && !GameDataController::gd->getObjective(S("house_b_hose_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("hose"))))
		{
			GameDataController::gd->setObjective(S("house_b_hose_taken"), true);
			updateState();
		}
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_hose_connected")), true);
	}
}

void HouseBBackHose::updateState()
{
	if (!GameDataController::gd->getObjective(S("house_b_hose_disconnected")))
	{
		colliderManager->setCollider(0);
		characterAnimationName = S("kneel_n");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite1);
		objectName = S("house_b_back_hose_1");
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	}
	else if (!GameDataController::gd->getObjective(S("house_b_hose_taken")))
	{
		colliderManager->setCollider(1);
		characterAnimationName = S("kneel_n");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite2);
		objectName = S("house_b_back_hose_2");
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("house_b_hose_already_disconnected")), nullptr, String::Empty));
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void HouseBBackHose::clickAction2()
{
}

void HouseBBackHose::clickAction0()
{
}

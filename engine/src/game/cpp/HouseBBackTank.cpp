#include "../game_all.h"

void HouseBBackTank::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_back_tank");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
}

void HouseBBackTank::clickAction()
{
	if (!GameDataController::gd->getObjective(S("house_b_hose_disconnected")) && usedItem == S("wrench"))
	{
		GameDataController::gd->setObjective(S("house_b_hose_disconnected"), true);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_hose_disconnected")), true);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->screw);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hose);
		updateAll();
	}
	else if (GameDataController::gd->getObjective(S("house_b_hose_disconnected")) && !GameDataController::gd->getObjective(S("house_b_tank_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("gas_tank"))))
		{
			GameDataController::gd->setObjective(S("house_b_tank_taken"), true);
			updateState();
		}
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_hose_connected")), true);
	}
}

void HouseBBackTank::updateState()
{
	if (!GameDataController::gd->getObjective(S("house_b_hose_disconnected")))
	{
		colliderManager->setCollider(0);
		characterAnimationName = S("kneel_n");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	}
	else if (!GameDataController::gd->getObjective(S("house_b_tank_taken")))
	{
		colliderManager->setCollider(0);
		characterAnimationName = S("kneel_n");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("house_b_hose_already_disconnected")), nullptr, String::Empty));
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void HouseBBackTank::clickAction2()
{
}

void HouseBBackTank::clickAction0()
{
}

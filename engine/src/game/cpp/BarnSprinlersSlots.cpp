#include "../game_all.h"

void BarnSprinlersSlots::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kick_ne");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sprinklers_slots_empty");
	setCollider(0);
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("pest1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pest2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chem_glass_12"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chem_glass_13"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chem_glass_23"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("spiderpest1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("spiderpest2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("spiderpest3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("spiderpest4"), String::Empty, nullptr, String::Empty));
}

void BarnSprinlersSlots::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		if (!GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
		{
			setCollider(0);
			objectName = S("sprinklers_slots_empty");
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(barn_sprinkles_empty);
		}
		else if (!GameDataController::gd->getObjective(S("barn_sprinklers_fed2")))
		{
			setCollider(0);
			objectName = S("sprinklers_slots_filled1");
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(barn_sprinkles_1);
		}
		else
		{
			setCollider(0);
			objectName = S("sprinklers_slots_filled2");
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(barn_sprinkles_2);
		}
	}
	else if (GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
	{
		objectName = S("sprinklers_slots_filled3");
		setCollider(1);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(barn_sprinkles_single_filled);
	}
	else if (GameDataController::gd->getCurrentDay() > 1 && (ItemsManager::im->getItem(S("chem_glass_12"))->dataRef->droppedLocation == S("sprinklers") || ItemsManager::im->getItem(S("chem_glass_13"))->dataRef->droppedLocation == S("sprinklers") || ItemsManager::im->getItem(S("chem_glass_23"))->dataRef->droppedLocation == S("sprinklers")))
	{
		objectName = S("sprinklers_slots_empty");
		setCollider(1);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(barn_sprinkles_single_mix_used);
	}
	else if (ItemsManager::im->getItem(S("chem_glass_12"))->dataRef->droppedLocation == S("sprinklers"))
	{
		objectName = S("sprinklers_slots_chem");
		setCollider(1);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(barn_sprinkles_single_12);
	}
	else if (ItemsManager::im->getItem(S("chem_glass_23"))->dataRef->droppedLocation == S("sprinklers"))
	{
		objectName = S("sprinklers_slots_chem");
		setCollider(1);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(barn_sprinkles_single_23);
	}
	else if (ItemsManager::im->getItem(S("chem_glass_13"))->dataRef->droppedLocation == S("sprinklers"))
	{
		objectName = S("sprinklers_slots_chem");
		setCollider(1);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(barn_sprinkles_single_13);
	}
	else
	{
		objectName = S("sprinklers_slots_empty");
		setCollider(1);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(barn_sprinkles_single_empty);
	}
}

void BarnSprinlersSlots::whatOnClick()
{
	if (!GameDataController::gd->getObjective(S("base_discovered")))
	{
		characterAnimationName = S("action_stnd_n");
	}
	else if (usedItem != String::Empty || GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
	{
		characterAnimationName = S("action_n");
	}
	else
	{
		characterAnimationName = S("action_stnd_n");
	}
}

void BarnSprinlersSlots::clickAction()
{
	if (!GameDataController::gd->getObjective(S("base_discovered")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pipe_first")));
		return;
	}
	if (GameDataController::gd->getCurrentDay() > 1)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sprinklers_dont_want")));
		return;
	}
	if (usedItem == S("chem_glass_12") || usedItem == S("chem_glass_13") || usedItem == S("chem_glass_23"))
	{
		InventoryController::ic->removeItem(usedItem);
		ItemsManager::im->updateItem(usedItem, S("sprinklers"), 0, 0);
	}
	else if (usedItem == S("pest1"))
	{
		InventoryController::ic->removeItem(S("pest1"));
		ItemsManager::im->updateItem(S("pest1"), S("sprinklers"), 0, 0);
		if (!GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
		{
			GameDataController::gd->setObjective(S("barn_sprinklers_fed1"), true);
		}
		else
		{
			GameDataController::gd->setObjective(S("barn_sprinklers_fed2"), true);
		}
	}
	else if (usedItem == S("pest2"))
	{
		InventoryController::ic->removeItem(S("pest2"));
		ItemsManager::im->updateItem(S("pest2"), S("sprinklers"), 0, 0);
		if (!GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
		{
			GameDataController::gd->setObjective(S("barn_sprinklers_fed1"), true);
		}
		else
		{
			GameDataController::gd->setObjective(S("barn_sprinklers_fed2"), true);
		}
	}
	else if (usedItem == S("spiderpest1") || usedItem == S("spiderpest2") || usedItem == S("spiderpest3") || usedItem == S("spiderpest4"))
	{
		if (ItemsManager::im->getItem(S("spiderpest1"))->dataRef->droppedLocation == S("sprinklers") || ItemsManager::im->getItem(S("spiderpest2"))->dataRef->droppedLocation == S("sprinklers") || ItemsManager::im->getItem(S("spiderpest3"))->dataRef->droppedLocation == S("sprinklers") || ItemsManager::im->getItem(S("spiderpest4"))->dataRef->droppedLocation == S("sprinklers"))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_sprinklers_full")));
			return;
		}
		GameDataController::gd->setObjective(S("barn_sprinklers_fed1"), true);
		InventoryController::ic->removeItem(usedItem);
		ItemsManager::im->updateItem(usedItem, S("sprinklers"), 0, 0);
	}
	else if (ItemsManager::im->getItem(S("chem_glass_12"))->dataRef->droppedLocation == S("sprinklers"))
	{
		if (!InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("chem_glass_12"))))
		{
		}
	}
	else if (ItemsManager::im->getItem(S("chem_glass_23"))->dataRef->droppedLocation == S("sprinklers"))
	{
		if (!InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("chem_glass_23"))))
		{
		}
	}
	else if (ItemsManager::im->getItem(S("chem_glass_13"))->dataRef->droppedLocation == S("sprinklers"))
	{
		if (!InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("chem_glass_13"))))
		{
		}
	}
	else if (ItemsManager::im->getItem(S("pest1"))->dataRef->droppedLocation == S("sprinklers"))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("pest1"))))
		{
			if (GameDataController::gd->getObjective(S("barn_sprinklers_fed2")))
			{
				GameDataController::gd->setObjective(S("barn_sprinklers_fed2"), false);
			}
			else if (GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
			{
				GameDataController::gd->setObjective(S("barn_sprinklers_fed1"), false);
			}
		}
	}
	else if (ItemsManager::im->getItem(S("pest2"))->dataRef->droppedLocation == S("sprinklers"))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("pest2"))))
		{
			if (GameDataController::gd->getObjective(S("barn_sprinklers_fed2")))
			{
				GameDataController::gd->setObjective(S("barn_sprinklers_fed2"), false);
			}
			else if (GameDataController::gd->getObjective(S("barn_sprinklers_fed1")))
			{
				GameDataController::gd->setObjective(S("barn_sprinklers_fed1"), false);
			}
		}
	}
	else if (ItemsManager::im->getItem(S("spiderpest1"))->dataRef->droppedLocation == S("sprinklers"))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("spiderpest1"))))
		{
			GameDataController::gd->setObjective(S("barn_sprinklers_fed1"), false);
		}
	}
	else if (ItemsManager::im->getItem(S("spiderpest2"))->dataRef->droppedLocation == S("sprinklers"))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("spiderpest2"))))
		{
			GameDataController::gd->setObjective(S("barn_sprinklers_fed1"), false);
		}
	}
	else if (ItemsManager::im->getItem(S("spiderpest3"))->dataRef->droppedLocation == S("sprinklers"))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("spiderpest3"))))
		{
			GameDataController::gd->setObjective(S("barn_sprinklers_fed1"), false);
		}
	}
	else if (ItemsManager::im->getItem(S("spiderpest4"))->dataRef->droppedLocation == S("sprinklers"))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("spiderpest4"))))
		{
			GameDataController::gd->setObjective(S("barn_sprinklers_fed1"), false);
		}
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_sprinklers_inlet")), true);
	}
	updateAll();
	PlayerController::wc->forceDirection(WalkController::Direction::NE);
}

void BarnSprinlersSlots::clickAction2()
{
}

void BarnSprinlersSlots::clickAction0()
{
}

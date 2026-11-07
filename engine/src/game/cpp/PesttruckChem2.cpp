#include "../game_all.h"

void PesttruckChem2::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pesttruck_chem_2");
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("chem_glass"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chem_glass_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chem_glass_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chem_glass_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chem_glass_12"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chem_glass_13"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chem_glass_23"), String::Empty, nullptr, String::Empty));
}

void PesttruckChem2::clickAction()
{
	if (usedItem == S("chem_glass") || usedItem == S("chem_glass_1") || usedItem == S("chem_glass_3"))
	{
		InventoryController::ic->removeItem(usedItem);
		if (usedItem == S("chem_glass"))
		{
			InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("chem_glass_2")));
		}
		else if (usedItem == S("chem_glass_1"))
		{
			InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("chem_glass_12")));
		}
		else if (usedItem == S("chem_glass_3"))
		{
			InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("chem_glass_23")));
		}
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour_small);
	}
	else if (usedItem == S("chem_glass_2"))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("chem_glass_already")), true);
	}
	else if (usedItem.IndexOf(S("chem_glass_")) != -1)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("chem_glass_full")), true);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("chem_no_glass")), true);
	}
}

void PesttruckChem2::whatOnClick()
{
	if (usedItem == S("chem_glass") || usedItem == S("chem_glass_1") || usedItem == S("chem_glass_3"))
	{
		characterAnimationName = S("action_n");
	}
	else
	{
		characterAnimationName = S("action_stnd_n");
	}
}

void PesttruckChem2::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 1)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(-1);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
	}
}

void PesttruckChem2::clickAction2()
{
}

void PesttruckChem2::clickAction0()
{
}

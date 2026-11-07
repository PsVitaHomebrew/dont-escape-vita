#include "../game_all.h"

void PesttruckChemDisp::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pesttruck_chem_disp");
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

void PesttruckChemDisp::clickAction()
{
	if (usedItem == S("chem_glass_1") || usedItem == S("chem_glass_2") || usedItem == S("chem_glass_3") || usedItem == S("chem_glass_12") || usedItem == S("chem_glass_13") || usedItem == S("chem_glass_23"))
	{
		InventoryController::ic->removeItem(usedItem);
		InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("chem_glass")));
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("chem_glass_emptied")), true);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour_small);
	}
	else if (usedItem == S("chem_glass"))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("chem_glass_empty")), true);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("chem_disposal")), true);
	}
}

void PesttruckChemDisp::whatOnClick()
{
	if (usedItem == S("chem_glass_1") || usedItem == S("chem_glass_2") || usedItem == S("chem_glass_3") || usedItem == S("chem_glass_12") || usedItem == S("chem_glass_13") || usedItem == S("chem_glass_23"))
	{
		characterAnimationName = S("action_n");
	}
	else
	{
		characterAnimationName = S("action_stnd_n");
	}
}

void PesttruckChemDisp::updateState()
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

void PesttruckChemDisp::clickAction2()
{
}

void PesttruckChemDisp::clickAction0()
{
}

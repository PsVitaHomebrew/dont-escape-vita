#include "../game_all.h"

void LocationBridgePlanks::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bridge_planks");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("hammer"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails5"), String::Empty, nullptr, String::Empty));
}

void LocationBridgePlanks::clickAction()
{
	if (usedItem == S("hammer") || usedItem == S("nails1") || usedItem == S("nails2") || usedItem == S("nails3") || usedItem == S("nails4") || usedItem == S("nails5"))
	{
		if (ItemsManager::im->getItem(S("nails1"))->dataRef->droppedLocation != S("inventory") && ItemsManager::im->getItem(S("nails2"))->dataRef->droppedLocation != S("inventory") && ItemsManager::im->getItem(S("nails3"))->dataRef->droppedLocation != S("inventory") && ItemsManager::im->getItem(S("nails4"))->dataRef->droppedLocation != S("inventory") && ItemsManager::im->getItem(S("nails5"))->dataRef->droppedLocation != S("inventory"))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("no_nails")), true);
		}
		else if (ItemsManager::im->getItem(S("hammer"))->dataRef->droppedLocation != S("inventory"))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nails_fail")), true);
		}
		else if (!GameDataController::gd->getObjective(S("bridge_planks_used_1")))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("bridge_planks1")), QuestionController::PopupType::QUESTION, [this]() { yesClicked(); }, 90, 20);
		}
		else if (!GameDataController::gd->getObjective(S("bridge_planks_used_2")))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("bridge_planks2")), QuestionController::PopupType::QUESTION, [this]() { yesClicked(); }, 120, 20);
		}
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("bridge_planks")), true, false, false, 150);
	}
}

void LocationBridgePlanks::yesClicked()
{
	Array<P<Item>> array = Array<P<Item>>::Of({
		ItemsManager::im->getItem(S("nails1")),
		ItemsManager::im->getItem(S("nails2")),
		ItemsManager::im->getItem(S("nails3")),
		ItemsManager::im->getItem(S("nails4")),
		ItemsManager::im->getItem(S("nails5"))
	});
	P<Item> item = nullptr;
	for (int i = 0; i < array.Length(); i++)
	{
		if (array[i]->dataRef->droppedLocation == S("inventory"))
		{
			item = array[i];
			break;
		}
	}
	ItemsManager::im->updateItem(item->id, S("window1"), 0, 0);
	InventoryController::ic->removeItem(item->id);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->nailed);
	if (!GameDataController::gd->getObjective(S("bridge_planks_used_1")))
	{
		GameDataController::gd->setObjective(S("bridge_planks_used_1"), true);
	}
	else if (!GameDataController::gd->getObjective(S("bridge_planks_used_2")))
	{
		GameDataController::gd->setObjective(S("bridge_planks_used_2"), true);
	}
	PlayerController::wc->forceAnimation(S("kneel_n"));
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("kneel_n"));
}

void LocationBridgePlanks::whatOnClick0()
{
	MonoBehaviour::print(S("IM WHAT ON CLICK ") + usedItem);
	if (usedItem == S("hammer"))
	{
		range = 1.0f;
		MonoBehaviour::print(S("THE RANGE IS SET TO 1"));
	}
	else
	{
		range = 100.0f;
	}
}

void LocationBridgePlanks::updateState()
{
	if (!GameDataController::gd->getObjective(S("bridge_planks_used_1")))
	{
		colliderManager->setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationBridge/bridge_planks")));
	}
	else if (!GameDataController::gd->getObjective(S("bridge_planks_used_2")))
	{
		colliderManager->setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationBridge/bridge_planks2")));
	}
	else
	{
		colliderManager->setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void LocationBridgePlanks::clickAction2()
{
}

void LocationBridgePlanks::clickAction0()
{
}

#include "../game_all.h"

void Door2::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = true;
	characterAnimationName = S("action1_e");
	actionMarker = gameObject->transform->Find(S("Action_Open"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("basedoor");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("key2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("towel_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("towel_2"), String::Empty, nullptr, String::Empty));
	updateState();
}

void Door2::clickAction()
{
	if (usedItem == S("key2"))
	{
		if (GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("generic_close_first")), true);
			return;
		}
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_lock_unlock);
		GameDataController::gd->setObjective(S("location01_door2_locked"), !GameDataController::gd->getObjective(S("location01_door2_locked")));
	}
	else if (usedItem == S("towel_1") || usedItem == S("towel_2"))
	{
		if (GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("generic_close_first")), true);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("towel_already")), true);
			return;
		}
		if (usedItem == S("towel_1"))
		{
			InventoryController::ic->removeItem(S("towel_1"));
			ItemsManager::im->updateItem(S("towel_1"), S("nowhere"), 0, 0);
			PlayerController::pc->aS->PlayOneShot(ItemsManager::im->getItem(S("towel_1"))->sound);
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("towel_placed")), true);
			GameDataController::gd->setObjectiveDetail(S("towel_1_at_door"), 1);
		}
		else if (usedItem == S("towel_2"))
		{
			InventoryController::ic->removeItem(S("towel_2"));
			ItemsManager::im->updateItem(S("towel_2"), S("nowhere"), 0, 0);
			PlayerController::pc->aS->PlayOneShot(ItemsManager::im->getItem(S("towel_1"))->sound);
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("towel_placed")), true);
			GameDataController::gd->setObjectiveDetail(S("towel_2_at_door"), 1);
		}
		updateState();
	}
	else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
	{
		if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("towel_1"))))
		{
			GameDataController::gd->setObjectiveDetail(S("towel_1_at_door"), 0);
			GameObject::Find(S("towels"))->transform->Find(S("towel_1_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
		if (GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1 && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("towel_2"))))
		{
			GameDataController::gd->setObjectiveDetail(S("towel_2_at_door"), 0);
			GameObject::Find(S("towels"))->transform->Find(S("towel_2_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
	else if (GameDataController::gd->getObjective(S("location01_door2_locked")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_locked);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("generic_locked")), true);
	}
	else
	{
		if (GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			gameObject->GetComponent<Animator>()->Play(S("door2_close"), 0);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_close_02);
		}
		else
		{
			gameObject->GetComponent<Animator>()->Play(S("door2_open"), 0);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_open_02);
		}
		GameDataController::gd->setObjective(S("location01_door2_open"), !GameDataController::gd->getObjective(S("location01_door2_open")));
		GameObject::Find(S("Door2_Exit"))->GetComponent<Door2_Exit>()->updateState();
	}
}

void Door2::updateState()
{
	MonoBehaviour::print(S("UPDATING DOOR STATE"));
	if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1)
	{
		GameObject::Find(S("towels"))->transform->Find(S("towel_1_r1"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("towels"))->transform->Find(S("towel_2_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
	{
		GameObject::Find(S("towels"))->transform->Find(S("towel_2_r1"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("towels"))->transform->Find(S("towel_1_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		GameObject::Find(S("towels"))->transform->Find(S("towel_2_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("towels"))->transform->Find(S("towel_1_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("location01_door2_open")))
	{
		characterAnimationName = S("action2_ne");
		actionMarker = gameObject->transform->Find(S("Action_Close"))->gameObject;
		gameObject->GetComponent<Animator>()->Play(S("door2_opened"), 0);
		colliderManager->setCollider(1);
	}
	else
	{
		characterAnimationName = S("action1_e");
		actionMarker = gameObject->transform->Find(S("Action_Open"))->gameObject;
		gameObject->GetComponent<Animator>()->Play(S("door2_closed"), 0);
		colliderManager->setCollider(0);
	}
	GameObject::Find(S("Door2_Exit"))->GetComponent<Door2_Exit>()->updateState();
}

void Door2::whatOnClick()
{
	if (usedItem == S("towel_1") || usedItem == S("towel_2"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
		{
			characterAnimationName = S("action_stnd_e");
		}
		else
		{
			characterAnimationName = S("kneel_e");
		}
	}
	else if (usedItem == S("key2"))
	{
		if (GameDataController::gd->getObjective(S("location01_door2_open")))
		{
			characterAnimationName = S("action_stnd_e");
		}
		else
		{
			characterAnimationName = S("action1_e_lock");
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
	{
		characterAnimationName = S("kneel_e");
	}
	else if (GameDataController::gd->getObjective(S("location01_door2_locked")))
	{
		characterAnimationName = S("action1_e_lock");
	}
	else if (GameDataController::gd->getObjective(S("location01_door2_open")))
	{
		characterAnimationName = S("action2_ne");
	}
	else
	{
		characterAnimationName = S("action1_e");
	}
}

void Door2::clickAction2()
{
}

void Door2::clickAction0()
{
}

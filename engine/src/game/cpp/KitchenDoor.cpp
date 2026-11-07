#include "../game_all.h"

void KitchenDoor::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action1_e");
	actionMarker = gameObject->transform->Find(S("Action_Open"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("kitchen_door");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("key2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("towel_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("towel_2"), String::Empty, nullptr, String::Empty));
	darkness = GameObject::Find(S("Location"))->transform->Find(S("darkness"))->GetComponent<SpriteRenderer>();
	darkness2 = GameObject::Find(S("Location"))->transform->Find(S("darkness2"))->GetComponent<SpriteRenderer>();
	lightt = GameObject::Find(S("Location"))->transform->Find(S("light"))->GetComponent<SpriteRenderer>();
	rainbow = GameObject::Find(S("Location"))->transform->Find(S("rainbow"))->GetComponent<SpriteRenderer>();
	kae = GameObject::Find(S("Location"))->GetComponent<KitchenAreaEffect>();
}

void KitchenDoor::clickAction()
{
	if (usedItem == S("key2"))
	{
		if (GameDataController::gd->getObjective(S("location02_door_open")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("generic_close_first")), true);
			return;
		}
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_lock_unlock);
		GameDataController::gd->setObjective(S("location02_door_locked"), !GameDataController::gd->getObjective(S("location02_door_locked")));
	}
	else if (usedItem == S("towel_1") || usedItem == S("towel_2"))
	{
		if (GameDataController::gd->getObjective(S("location02_door_open")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("generic_close_first")), true);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
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
			GameDataController::gd->setObjectiveDetail(S("towel_1_at_door"), 2);
		}
		else if (usedItem == S("towel_2"))
		{
			InventoryController::ic->removeItem(S("towel_2"));
			ItemsManager::im->updateItem(S("towel_2"), S("nowhere"), 0, 0);
			PlayerController::pc->aS->PlayOneShot(ItemsManager::im->getItem(S("towel_1"))->sound);
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("towel_placed")), true);
			GameDataController::gd->setObjectiveDetail(S("towel_2_at_door"), 2);
		}
		updateState();
	}
	else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
	{
		if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("towel_1"))))
		{
			GameDataController::gd->setObjectiveDetail(S("towel_1_at_door"), 0);
			GameObject::Find(S("towels"))->transform->Find(S("towel_1_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
		if (GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2 && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("towel_2"))))
		{
			GameDataController::gd->setObjectiveDetail(S("towel_2_at_door"), 0);
			GameObject::Find(S("towels"))->transform->Find(S("towel_2_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
	else if (GameDataController::gd->getObjective(S("location02_door_locked")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_locked);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("generic_locked")), true);
	}
	else
	{
		if (GameDataController::gd->getObjective(S("location02_door_open")))
		{
			gameObject->GetComponent<Animator>()->Play(S("KitchenDoorClose"), 0);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_close_01);
		}
		else
		{
			gameObject->GetComponent<Animator>()->Play(S("KitchenDoorOpen"), 0);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_open_01);
		}
		GameDataController::gd->setObjective(S("location02_door_open"), !GameDataController::gd->getObjective(S("location02_door_open")));
		GameObject::Find(S("KitchenExitWay"))->GetComponent<KitchenExit>()->updateState();
	}
}

void KitchenDoor::updateState()
{
	MonoBehaviour::print(S("UPDATING DOOR STATE"));
	if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2)
	{
		GameObject::Find(S("towels"))->transform->Find(S("towel_1_r1"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("towels"))->transform->Find(S("towel_2_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
	{
		GameObject::Find(S("towels"))->transform->Find(S("towel_2_r1"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("towels"))->transform->Find(S("towel_1_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		GameObject::Find(S("towels"))->transform->Find(S("towel_2_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("towels"))->transform->Find(S("towel_1_r1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("location02_door_open")))
	{
		characterAnimationName = S("open_door2");
		actionMarker = gameObject->transform->Find(S("Action_Close"))->gameObject;
		gameObject->GetComponent<Animator>()->Play(S("KitchenDoorOpened"), 0);
		colliderManager->setCollider(1);
		gameObject->transform->Find(S("Z_Marker2"))->GetComponent<ObjectZController>()->set_enabled(true);
		gameObject->transform->Find(S("Z_Marker"))->GetComponent<ObjectZController>()->set_enabled(false);
		darkness->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
		darkness2->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
		lightt->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
		rainbow->set_sprite(rainbow_4);
		rainbow->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	}
	else
	{
		darkness->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
		darkness2->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
		lightt->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
		rainbow->set_sprite(rainbow_0);
		rainbow->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
		characterAnimationName = S("action1_e");
		actionMarker = gameObject->transform->Find(S("Action_Open"))->gameObject;
		gameObject->GetComponent<Animator>()->Play(S("KitchenDoorClosed"), 0);
		colliderManager->setCollider(0);
		gameObject->transform->Find(S("Z_Marker2"))->GetComponent<ObjectZController>()->set_enabled(false);
		gameObject->transform->Find(S("Z_Marker"))->GetComponent<ObjectZController>()->set_enabled(true);
	}
	GameObject::Find(S("KitchenExitWay"))->GetComponent<KitchenExit>()->updateState();
}

void KitchenDoor::whatOnClick()
{
	if (usedItem == S("towel_1") || usedItem == S("towel_2"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
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
		if (GameDataController::gd->getObjective(S("location02_door_open")))
		{
			characterAnimationName = S("action_stnd_e");
		}
		else
		{
			characterAnimationName = S("action1_e_lock");
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
	{
		characterAnimationName = S("kneel_e");
	}
	else if (GameDataController::gd->getObjective(S("location02_door_locked")))
	{
		characterAnimationName = S("action1_e_lock");
	}
	else if (GameDataController::gd->getObjective(S("location02_door_open")))
	{
		characterAnimationName = S("open_door2");
	}
	else
	{
		characterAnimationName = S("action1_e");
	}
}

void KitchenDoor::clickAction2()
{
}

void KitchenDoor::clickAction0()
{
}

void KitchenDoor::shadowy(float shadowAmount)
{
	darkness->set_color(Color(1.0f, 1.0f, 1.0f, shadowAmount));
	darkness2->set_color(Color(1.0f, 1.0f, 1.0f, shadowAmount));
	lightt->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f - shadowAmount));
	rainbow->set_color(Color(1.0f, 1.0f, 1.0f, shadowAmount));
	if (shadowAmount >= 0.8f)
	{
		rainbow->set_sprite(rainbow_0);
	}
	else if (shadowAmount >= 0.6f)
	{
		rainbow->set_sprite(rainbow_1);
	}
	else if (shadowAmount >= 0.4f)
	{
		rainbow->set_sprite(rainbow_2);
	}
	else if (shadowAmount >= 0.2f)
	{
		rainbow->set_sprite(rainbow_3);
	}
	else
	{
		rainbow->set_sprite(rainbow_4);
	}
	kae->refresh();
}

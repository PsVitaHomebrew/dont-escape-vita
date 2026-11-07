#include "../game_all.h"

void Outside2Door::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = true;
	characterAnimationName = S("action1_e");
	actionMarker = gameObject->transform->Find(S("Action_Open"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("kitchen_door");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("key2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("pipe_door")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("crowbar_door")), nullptr, String::Empty));
}

void Outside2Door::clickAction()
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
		return;
	}
	if (GameDataController::gd->getObjective(S("location02_door_locked")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_locked);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("generic_locked")), true);
		return;
	}
	if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("generic_blocked")), true);
		return;
	}
	if (GameDataController::gd->getObjective(S("location02_door_open")))
	{
		gameObject->GetComponent<Animator>()->Play(S("DoorClose"), 0);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_close_01);
	}
	else
	{
		gameObject->GetComponent<Animator>()->Play(S("DoorOpen"), 0);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_open_01);
	}
	GameDataController::gd->setObjective(S("location02_door_open"), !GameDataController::gd->getObjective(S("location02_door_open")));
	GameObject::Find(S("Base_Entry"))->GetComponent<Base2Entry>()->updateState();
}

void Outside2Door::updateState()
{
	MonoBehaviour::print(S("UPDATING DOOR STATE"));
	if (GameDataController::gd->getObjective(S("location02_door_open")))
	{
		characterAnimationName = S("open_door2");
		actionMarker = gameObject->transform->Find(S("Action_Close"))->gameObject;
		gameObject->GetComponent<Animator>()->Play(S("DoorOpened"), 0);
		colliderManager->setCollider(1);
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("key2"), String::Empty, nullptr, String::Empty));
	}
	else
	{
		characterAnimationName = S("action1_e");
		actionMarker = gameObject->transform->Find(S("Action_Open"))->gameObject;
		gameObject->GetComponent<Animator>()->Play(S("DoorClosed"), 0);
		colliderManager->setCollider(0);
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("key2"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("pipe_door")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("crowbar_door")), nullptr, String::Empty));
	}
	GameObject::Find(S("Base_Entry"))->GetComponent<Base2Entry>()->updateState();
}

void Outside2Door::clickAction2()
{
}

void Outside2Door::clickAction0()
{
}

void Outside2Door::whatOnClick()
{
	if (usedItem == S("key2"))
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
	else if (GameDataController::gd->getObjective(S("location02_door_locked")) || GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
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

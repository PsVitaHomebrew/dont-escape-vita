#include "../game_all.h"

void Outside0BaseDoor::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action1_e");
	actionMarker = gameObject->transform->Find(S("Action_Open"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("basedoor");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("key2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("pipe_door")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("crowbar_door")), nullptr, String::Empty));
}

void Outside0BaseDoor::clickAction()
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
		return;
	}
	if (GameDataController::gd->getObjective(S("location01_door2_locked")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_locked);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("generic_locked")), true);
		return;
	}
	if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("generic_blocked")), true);
		return;
	}
	if (GameDataController::gd->getObjective(S("location01_door2_open")))
	{
		gameObject->GetComponent<Animator>()->Play(S("DoorClose"), 0);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_close_02);
	}
	else
	{
		gameObject->GetComponent<Animator>()->Play(S("DoorOpen"), 0);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_open_02);
	}
	GameDataController::gd->setObjective(S("location01_door2_open"), !GameDataController::gd->getObjective(S("location01_door2_open")));
	GameObject::Find(S("Base_Entry"))->GetComponent<BaseEntry>()->updateState();
}

void Outside0BaseDoor::updateState()
{
	MonoBehaviour::print(S("UPDATING DOOR STATE"));
	if (GameDataController::gd->getObjective(S("location01_door2_open")))
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
	GameObject::Find(S("Base_Entry"))->GetComponent<BaseEntry>()->updateState();
}

void Outside0BaseDoor::clickAction2()
{
}

void Outside0BaseDoor::clickAction0()
{
}

void Outside0BaseDoor::whatOnClick()
{
	if (usedItem == S("key2"))
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
	else if (GameDataController::gd->getObjective(S("location01_door2_locked")) || GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1 || GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
	{
		characterAnimationName = S("action1_e_lock");
	}
	else if (GameDataController::gd->getObjective(S("location01_door2_open")))
	{
		characterAnimationName = S("open_door2");
	}
	else
	{
		characterAnimationName = S("action1_e");
	}
}

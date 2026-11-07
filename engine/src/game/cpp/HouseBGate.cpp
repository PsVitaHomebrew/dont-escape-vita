#include "../game_all.h"

void HouseBGate::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_garage");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("key1"), GameStrings::getString(GameStrings::actions, S("generic_key")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("key2"), GameStrings::getString(GameStrings::actions, S("generic_key")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("key3"), GameStrings::getString(GameStrings::actions, S("generic_key")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("key4"), String::Empty, nullptr, String::Empty));
}

void HouseBGate::clickAction()
{
	if (usedItem == String::Empty)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_garage")), true, false, false, 150);
		return;
	}
	GameDataController::gd->setObjective(S("house_b_garage_open"), true);
	InventoryController::ic->removeItem(S("key4"));
	updateAll();
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_slide);
}

void HouseBGate::gateIsOpen()
{
	updateState();
	GameObject::Find(S("Shovel"))->GetComponent<HouseBShovel>()->updateState();
}

void HouseBGate::gateIsOpening()
{
}

void HouseBGate::updateState()
{
	if (GameDataController::gd->getObjective(S("house_b_garage_open")))
	{
		gameObject->GetComponent<Animator>()->Play(S("gate_2"), 0);
		setCollider(-1);
	}
	else
	{
		setCollider(0);
		gameObject->GetComponent<Animator>()->Play(S("gate_0"), 0);
	}
}

void HouseBGate::clickAction2()
{
}

void HouseBGate::clickAction0()
{
}

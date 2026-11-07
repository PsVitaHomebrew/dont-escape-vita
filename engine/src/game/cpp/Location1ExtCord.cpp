#include "../game_all.h"

void Location1ExtCord::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ext_cord_placed");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("heater"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("heater_broken"), GameStrings::getString(GameStrings::actions, S("heater_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan_broken"), GameStrings::getString(GameStrings::actions, S("fan_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("ext_cord_ac_machine1")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac_cord"), String::Empty, nullptr, String::Empty));
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
}

void Location1ExtCord::Update()
{
}

void Location1ExtCord::clickAction()
{
	if (usedItem == S("heater"))
	{
		InventoryController::ic->removeItem(S("heater"));
		GameDataController::gd->setObjective(S("base_heater_cord_plugged"), true);
		updateAll();
	}
	else if (usedItem == S("fan"))
	{
		InventoryController::ic->removeItem(S("fan"));
		GameDataController::gd->setObjective(S("base_fan_cord_plugged"), true);
		updateAll();
	}
	else if (usedItem == S("ac_cord"))
	{
		GameDataController::gd->setObjective(S("base_ac_cord_plugged"), true);
		updateAll();
	}
	else if (GameDataController::gd->getObjective(S("base_heater_cord_plugged")) || GameDataController::gd->getObjective(S("base_fan_cord_plugged")) || GameDataController::gd->getObjective(S("base_ac_cord_plugged")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ext_cord_plugged")));
	}
	else
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("ext_cord_where_put"));
		timelineAction->function = [this](String param) { takeCord(param); };
		Timeline::t->addAction(timelineAction);
	}
}

void Location1ExtCord::takeCord(String param)
{
	cursorController->selectItem(ItemsManager::im->getItem(S("ext_cord_place")));
}

void Location1ExtCord::updateState()
{
	if (GameDataController::gd->getObjective(S("kitchen_cord_dragged")))
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(cord);
	}
	else
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void Location1ExtCord::clickAction2()
{
}

void Location1ExtCord::clickAction0()
{
}

void Location1ExtCord::whatOnClick0()
{
}

void Location1ExtCord::whatOnClick()
{
}

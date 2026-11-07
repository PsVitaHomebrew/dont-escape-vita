#include "../game_all.h"

String Cave_Socket_Placed::get_Test()
{
	return test;
}

void Cave_Socket_Placed::set_Test(String value)
{
	test = value;
}

void Cave_Socket_Placed::Start()
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
	interactions.Add(New<ItemInteraction>(S("heater_broken"), GameStrings::getString(GameStrings::actions, S("heater_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan_broken"), GameStrings::getString(GameStrings::actions, S("fan_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("heater"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("ext_cord_ac_machine2")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac_cord"), String::Empty, nullptr, String::Empty));
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
}

void Cave_Socket_Placed::Update()
{
}

void Cave_Socket_Placed::clickAction()
{
	if (usedItem == String::Empty && (GameDataController::gd->getObjective(S("cave_heater_cord_plugged")) || GameDataController::gd->getObjective(S("cave_fan_cord_plugged")) || GameDataController::gd->getObjective(S("cave_ac_cord_plugged"))))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ext_cord_plugged")));
	}
	else if (usedItem == S("heater"))
	{
		InventoryController::ic->removeItem(S("heater"));
		GameDataController::gd->setObjective(S("cave_heater_cord_plugged"), true);
		updateAll();
	}
	else if (usedItem == S("fan"))
	{
		InventoryController::ic->removeItem(S("fan"));
		GameDataController::gd->setObjective(S("cave_fan_cord_plugged"), true);
		updateAll();
	}
	else if (usedItem == S("ac_cord"))
	{
		GameDataController::gd->setObjective(S("cave_ac_cord_plugged"), true);
		updateAll();
	}
	else
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("ext_cord_where_put"));
		timelineAction->function = [this](String param) { takeCord(param); };
		Timeline::t->addAction(timelineAction);
	}
}

void Cave_Socket_Placed::takeCord(String param)
{
	cursorController->selectItem(ItemsManager::im->getItem(S("ext_cord_place")));
}

void Cave_Socket_Placed::updateState()
{
	if (GameDataController::gd->getObjective(S("rv_cord_caved")))
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void Cave_Socket_Placed::clickAction2()
{
}

void Cave_Socket_Placed::clickAction0()
{
}

void Cave_Socket_Placed::whatOnClick0()
{
}

void Cave_Socket_Placed::whatOnClick()
{
}

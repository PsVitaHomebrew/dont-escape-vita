#include "../game_all.h"

void Location1ACPlug::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ac_plug");
	range = 1.0f;
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ext_cord_place"), String::Empty, nullptr, String::Empty));
}

void Location1ACPlug::Update()
{
}

void Location1ACPlug::clickAction()
{
	if (usedItem == S("ext_cord_place"))
	{
		CursorController::cc->deselectItem();
		GameDataController::gd->setObjective(S("base_ac_cord_plugged"), true);
		updateAll();
	}
	else if (GameDataController::gd->getObjective(S("window1_ac_placed")) && !GameDataController::gd->getObjective(S("base_ac_cord_plugged")))
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("ac_cord_where_put"));
		timelineAction->function = [this](String param) { takeCord(param); };
		Timeline::t->addAction(timelineAction);
	}
	else if (GameDataController::gd->getObjective(S("window1_ac_placed")) && GameDataController::gd->getObjective(S("base_ac_cord_plugged")))
	{
		GameDataController::gd->setObjective(S("base_ac_cord_plugged"), false);
		updateAll();
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ac_unplugged")));
	}
}

void Location1ACPlug::takeCord(String param)
{
	cursorController->selectItem(ItemsManager::im->getItem(S("ac_cord")));
}

void Location1ACPlug::updateState()
{
	if (GameDataController::gd->getObjective(S("window1_ac_placed")) && !GameDataController::gd->getObjective(S("base_ac_cord_plugged")))
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(cord1);
	}
	else if (GameDataController::gd->getObjective(S("window1_ac_placed")) && GameDataController::gd->getObjective(S("base_ac_cord_plugged")))
	{
		colliderManager->setCollider(1);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(cord2);
	}
	else
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void Location1ACPlug::clickAction2()
{
}

void Location1ACPlug::clickAction0()
{
}

void Location1ACPlug::whatOnClick0()
{
}

void Location1ACPlug::whatOnClick()
{
}

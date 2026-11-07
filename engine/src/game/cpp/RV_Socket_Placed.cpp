#include "../game_all.h"

void RV_Socket_Placed::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ext_cord_placed");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("heater_broken"), GameStrings::getString(GameStrings::actions, S("heater_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan_broken"), GameStrings::getString(GameStrings::actions, S("fan_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("heater"), GameStrings::getString(GameStrings::actions, S("ext_cord_wrong")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan"), GameStrings::getString(GameStrings::actions, S("ext_cord_wrong")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac_plug"), GameStrings::getString(GameStrings::actions, S("ext_cord_wrong")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac_machine"), GameStrings::getString(GameStrings::actions, S("ext_cord_wrong")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("ext_cord_wrong")), nullptr, String::Empty));
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
}

void RV_Socket_Placed::Update()
{
}

void RV_Socket_Placed::clickAction()
{
	if (usedItem == String::Empty)
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("ext_cord_where_put"));
		timelineAction->function = [this](String p) { takeCord(p); };
		Timeline::t->addAction(timelineAction);
	}
}

void RV_Socket_Placed::takeCord(String param)
{
	cursorController->selectItem(ItemsManager::im->getItem(S("ext_cord_place")));
}

void RV_Socket_Placed::updateState()
{
	if (GameDataController::gd->getObjective(S("rv_cord_plugged")) && !GameDataController::gd->getObjective(S("rv_cord_caged")))
	{
		setCollider(0);
	}
	else
	{
		setCollider(-1);
	}
}

void RV_Socket_Placed::clickAction2()
{
}

void RV_Socket_Placed::clickAction0()
{
}

void RV_Socket_Placed::whatOnClick0()
{
}

void RV_Socket_Placed::whatOnClick()
{
}

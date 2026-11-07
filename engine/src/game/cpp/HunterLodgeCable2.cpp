#include "../game_all.h"

void HunterLodgeCable2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_cord");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("heater_broken"), GameStrings::getString(GameStrings::actions, S("heater_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan_broken"), GameStrings::getString(GameStrings::actions, S("fan_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("heater"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher1"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher2"), GameStrings::getString(GameStrings::actions, S("plug_not_needed")), nullptr, String::Empty));
	updateState();
}

void HunterLodgeCable2::Update()
{
}

void HunterLodgeCable2::clickAction()
{
	if (usedItem == String::Empty)
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("ext_cord_where_put"));
		timelineAction->function = [this](String param) { takeCord(param); };
		Timeline::t->addAction(timelineAction);
	}
}

void HunterLodgeCable2::takeCord(String param)
{
	CursorController::cc->selectItem(ItemsManager::im->getItem(S("ext_cord_place")));
}

void HunterLodgeCable2::updateState()
{
	if (GameDataController::gd->getObjective(S("lodge_cord_climbed")))
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(cord2);
	}
	else if (GameDataController::gd->getObjective(S("lodge_cord_dragged")))
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(cord);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(-1);
	}
}

void HunterLodgeCable2::clickAction2()
{
}

void HunterLodgeCable2::clickAction0()
{
}

void HunterLodgeCable2::whatOnClick0()
{
}

void HunterLodgeCable2::whatOnClick()
{
}

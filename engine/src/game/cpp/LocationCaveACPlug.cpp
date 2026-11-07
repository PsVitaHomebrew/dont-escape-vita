#include "../game_all.h"

void LocationCaveACPlug::Start()
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
}

void LocationCaveACPlug::Update()
{
}

void LocationCaveACPlug::clickAction()
{
	if (GameDataController::gd->getObjective(S("cave_ac_placed")) && !GameDataController::gd->getObjective(S("cave_ac_cord_plugged")))
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("ext_cord_where_put"));
		timelineAction->function = [this](String param) { takeCord(param); };
		Timeline::t->addAction(timelineAction);
	}
	else if (GameDataController::gd->getObjective(S("cave_ac_placed")) && GameDataController::gd->getObjective(S("cave_ac_cord_plugged")))
	{
		GameDataController::gd->setObjective(S("cave_ac_cord_plugged"), false);
		updateAll();
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ac_unplugged")));
	}
}

void LocationCaveACPlug::takeCord(String param)
{
	cursorController->selectItem(ItemsManager::im->getItem(S("ac_cord")));
}

void LocationCaveACPlug::updateState()
{
	if (GameDataController::gd->getObjective(S("cave_ac_placed")) && !GameDataController::gd->getObjective(S("cave_ac_cord_plugged")))
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(cord1);
	}
	else if (GameDataController::gd->getObjective(S("cave_ac_placed")) && GameDataController::gd->getObjective(S("cave_ac_cord_plugged")))
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

void LocationCaveACPlug::clickAction2()
{
}

void LocationCaveACPlug::clickAction0()
{
}

void LocationCaveACPlug::whatOnClick0()
{
}

void LocationCaveACPlug::whatOnClick()
{
}

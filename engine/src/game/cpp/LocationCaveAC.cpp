#include "../game_all.h"

void LocationCaveAC::Start()
{
	colliderManager->setTarget(gameObject);
	range = 1.0f;
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ac_cave");
	range = 1.0f;
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
}

void LocationCaveAC::Update()
{
}

void LocationCaveAC::clickAction()
{
	if (GameDataController::gd->getObjective(S("cave_ac_cord_plugged")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("unplug_first")));
	}
	else if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("ac"))))
	{
		GameDataController::gd->setObjective(S("cave_ac_placed"), false);
		updateAll();
	}
}

void LocationCaveAC::updateState()
{
	if (GameDataController::gd->getObjective(S("cave_ac_placed")))
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
		GetComponent<AudioSource>()->Stop();
	}
	if (GameDataController::gd->getObjective(S("cave_ac_cord_plugged")) && GameDataController::gd->getObjective(S("rv_power")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(powered_ac);
		range = 100.0f;
		characterAnimationName = S("action_stnd_");
		GetComponent<AudioSource>()->set_loop(true);
		GetComponent<AudioSource>()->set_volume(0.3f);
		GetComponent<AudioSource>()->Play();
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(unpowered_ac);
		range = 1.0f;
		characterAnimationName = S("kneel_");
		GetComponent<AudioSource>()->Stop();
	}
}

void LocationCaveAC::clickAction2()
{
}

void LocationCaveAC::clickAction0()
{
}

void LocationCaveAC::whatOnClick0()
{
}

void LocationCaveAC::whatOnClick()
{
}

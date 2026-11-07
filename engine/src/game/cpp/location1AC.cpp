#include "../game_all.h"

void location1AC::Start()
{
	colliderManager->setTarget(gameObject);
	range = 1.0f;
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ac_window");
	range = 1.0f;
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
}

void location1AC::Update()
{
}

void location1AC::clickAction()
{
	if (GameDataController::gd->getObjective(S("base_ac_cord_plugged")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("unplug_first")));
	}
	else if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("ac"))))
	{
		GameDataController::gd->setObjective(S("window1_ac_placed"), false);
		updateAll();
	}
}

void location1AC::updateState()
{
	if (GameDataController::gd->getObjective(S("window1_ac_placed")))
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
	if (GameDataController::gd->getObjective(S("base_ac_cord_plugged")))
	{
		range = 100.0f;
		characterAnimationName = S("action_stnd_");
		if (GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
		{
			GetComponent<SpriteRenderer>()->set_sprite(powered_ac);
			GetComponent<AudioSource>()->set_loop(true);
			GetComponent<AudioSource>()->set_volume(0.3f);
			GetComponent<AudioSource>()->Play();
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_sprite(unpowered_ac);
			GetComponent<AudioSource>()->Stop();
		}
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(unpowered_ac);
		range = 1.0f;
		characterAnimationName = S("kneel_");
		GetComponent<AudioSource>()->Stop();
	}
}

void location1AC::clickAction2()
{
}

void location1AC::clickAction0()
{
}

void location1AC::whatOnClick0()
{
}

void location1AC::whatOnClick()
{
}

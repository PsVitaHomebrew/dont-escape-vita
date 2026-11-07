#include "../game_all.h"

void BarnPump::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n_long");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_generator_disabled");
	setCollider(0);
	engineStart = SoundsManagerController::sm->engine_start;
	engineRun = SoundsManagerController::sm->engine_run;
	engineDie = SoundsManagerController::sm->engine_die;
	aS = gameObject->AddComponent<AudioSource>();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("canister_full"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister_empty"), GameStrings::getString(GameStrings::actions, S("canister_is_empty")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_full"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_empty"), GameStrings::getString(GameStrings::actions, S("canister_is_empty")), nullptr, String::Empty));
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) > 0 && GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		aS->set_clip(engineRun);
		aS->set_loop(true);
		aS->set_volume(0.3f);
		aS->Play();
	}
}

void BarnPump::updateState()
{
	if (!GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		objectName = S("barn_generator_disabled");
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("barn_generator_enabled");
	}
}

void BarnPump::whatOnClick0()
{
	if (!GameDataController::gd->getObjective(S("base_discovered")))
	{
		characterAnimationName = S("action_stnd_n");
	}
	else if (usedItem != String::Empty)
	{
		characterAnimationName = S("action_n_long");
		actionMarker = am2;
	}
	else
	{
		actionMarker = am1;
		characterAnimationName = S("action_n");
	}
}

void BarnPump::whatOnClick()
{
}

void BarnPump::clickAction()
{
	if (!GameDataController::gd->getObjective(S("base_discovered")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pipe_first")));
		return;
	}
	if (usedItem != S("canister_full") && usedItem != S("canister_empty") && usedItem != S("canister2_full") && usedItem != S("canister2_empty"))
	{
		PlayerController::pc->spawnName = S("BarnConsoleExit");
		CurtainController::cc->fadeOut(S("BarnGenerator"), WalkController::Direction::W);
	}
	else if (usedItem == S("canister_full"))
	{
		if (!GameDataController::gd->getObjective(S("barn_pump_fueled")))
		{
			InventoryController::ic->removeItem(S("canister_full"));
			ItemsManager::im->updateItem(S("canister_full"), S("nowhere"), 0, 0);
			InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("canister_empty")));
			GameDataController::gd->setObjective(S("barn_pump_fueled"), true);
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_pump_fuel")), true);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_pump_already_fueled")), true);
		}
	}
	else if (usedItem == S("canister2_full"))
	{
		if (!GameDataController::gd->getObjective(S("barn_pump_fueled")))
		{
			InventoryController::ic->removeItem(S("canister2_full"));
			ItemsManager::im->updateItem(S("canister2_full"), S("nowhere"), 0, 0);
			InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("canister2_empty")));
			GameDataController::gd->setObjective(S("barn_pump_fueled"), true);
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_pump_fuel")), true);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_pump_already_fueled")), true);
		}
	}
	PlayerController::wc->forceDirection(WalkController::Direction::NE);
}

void BarnPump::restore()
{
	setCollider(0);
}

void BarnPump::clickAction2()
{
}

void BarnPump::clickAction0()
{
}

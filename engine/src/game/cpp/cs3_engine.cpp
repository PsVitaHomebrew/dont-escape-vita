#include "../game_all.h"

void cs3_engine::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_s");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_engine");
	range = 1.0f;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("canister_full"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister_empty"), GameStrings::getString(GameStrings::actions, S("canister_is_empty")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_full"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_empty"), GameStrings::getString(GameStrings::actions, S("canister_is_empty")), nullptr, String::Empty));
}

void cs3_engine::Update()
{
}

void cs3_engine::clickAction()
{
	if (!GameDataController::gd->getObjective(S("cs_rain_enter_left")) && !GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
	}
	else if (usedItem != String::Empty)
	{
		if (GameDataController::gd->getObjective(S("cs_engine_fueled")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pump_already_fueled")));
			return;
		}
		if (usedItem == S("canister_full"))
		{
			InventoryController::ic->removeItem(S("canister_full"));
			ItemsManager::im->updateItem(S("canister_full"), S("nowhere"), 0, 0);
			InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("canister_empty")));
		}
		else if (usedItem == S("canister2_full"))
		{
			InventoryController::ic->removeItem(S("canister2_full"));
			ItemsManager::im->updateItem(S("canister2_full"), S("nowhere"), 0, 0);
			InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("canister2_empty")));
		}
		GameDataController::gd->setObjective(S("cs_engine_fueled"), true);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour_med);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pump_fuel")));
	}
	else if (GameDataController::gd->getObjective(S("cs_engine_started")))
	{
		GameDataController::gd->setObjective(S("cs_engine_started"), false);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->engine_die, 0.25f);
		updateState();
	}
	else if (GameDataController::gd->getObjective(S("cs_engine_fueled")))
	{
		GameDataController::gd->setObjective(S("cs_engine_started"), true);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rv_engine_start);
		Invoke(S("startSoundANdSmoke"), 1.0f);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pump_no_fuel")));
		PlayerController::pc->aS->Stop();
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rv_engine_fail);
	}
}

void cs3_engine::updateState()
{
	if (GameDataController::gd->getObjective(S("cs_engine_started")))
	{
		GetComponent<AudioSource>()->set_clip(SoundsManagerController::sm->rv_engine_loop);
		GetComponent<AudioSource>()->set_loop(true);
		GetComponent<AudioSource>()->Play();
		GetComponent<Animator>()->Play(S("cs_engine"));
		GetComponent<Animator>()->set_enabled(true);
		GetComponent<ParticleGenerator>()->started = true;
		characterAnimationName = S("action_s");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
	}
	else
	{
		characterAnimationName = S("action_s");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
		GetComponent<Animator>()->set_enabled(false);
		GetComponent<ParticleGenerator>()->started = false;
		GetComponent<AudioSource>()->Stop();
	}
	if (!GameDataController::gd->getObjective(S("cs_rain_enter_left")) && !GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		range = 100.0f;
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 1)
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void cs3_engine::startSoundANdSmoke()
{
	updateAll();
}

void cs3_engine::clickAction2()
{
}

void cs3_engine::clickAction0()
{
}

void cs3_engine::whatOnClick0()
{
}

void cs3_engine::whatOnClick()
{
}

#include "../game_all.h"

void CraneCables::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action1_e");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_cables_box");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("stormcatcher1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("screwdriver"), GameStrings::getString(GameStrings::actions, S("cable_box_screwdriver")), nullptr, String::Empty));
	updateState();
}

void CraneCables::Update()
{
}

void CraneCables::clickAction()
{
	if (usedItem == String::Empty)
	{
		if (GameDataController::gd->getObjective(S("cs_stormcatcher_installed")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_stormcatcher_installed")));
		}
		else if (!GameDataController::gd->getObjective(S("cs_cables_open")))
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->cabinet_open);
			GameDataController::gd->setObjective(S("cs_cables_open"), true);
			updateState();
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_cable_box_open")));
		}
	}
	else if (GameDataController::gd->getObjective(S("cs_stormcatcher_installed")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("stormcatcher_already")));
	}
	else if (!GameDataController::gd->getObjective(S("cs_cables_open")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_cables_open")));
	}
	else if (GameDataController::gd->getObjective(S("cs_engine_started")))
	{
		sparks->GetComponent<ParticleGenerator>()->started = true;
		Invoke(S("stopSparks"), 1.0f);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->electric);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_cables_sparks")));
	}
	else
	{
		InventoryController::ic->removeItem(usedItem);
		GameDataController::gd->setObjective(S("cs_stormcatcher_installed"), true);
		updateState();
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_stormcatcher_placed")));
	}
}

void CraneCables::stopSparks()
{
	sparks->GetComponent<ParticleGenerator>()->started = false;
	sparks->GetComponent<ParticleGenerator>()->removeParticles();
}

void CraneCables::updateState()
{
	colliderManager->setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	glow->set_enabled(false);
	if (GameDataController::gd->getObjective(S("cs_stormcatcher_installed")) && GameDataController::gd->getObjective(S("cs_engine_started")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(stormcatcher_on);
		glow->set_enabled(true);
	}
	else if (GameDataController::gd->getObjective(S("cs_stormcatcher_installed")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(stormcatcher_off);
	}
	else if (GameDataController::gd->getObjective(S("cs_cables_open")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(cord);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void CraneCables::clickAction2()
{
}

void CraneCables::clickAction0()
{
}

void CraneCables::whatOnClick0()
{
	characterAnimationName = S("action1_e");
	animationFlip = true;
	useCurrentDirection = false;
	if (usedItem != String::Empty && !GameDataController::gd->getObjective(S("cs_cables_open")))
	{
		characterAnimationName = S("action_stnd_e");
		animationFlip = true;
		useCurrentDirection = false;
	}
	if (usedItem == String::Empty && GameDataController::gd->getObjective(S("cs_cables_open")))
	{
		characterAnimationName = S("action_stnd_e");
		animationFlip = true;
		useCurrentDirection = false;
	}
}

void CraneCables::whatOnClick()
{
}

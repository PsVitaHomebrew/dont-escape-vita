#include "../game_all.h"

void LocationCaveHeaterOrFan::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_s");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("fan");
	range = 1.0f;
	updateState();
}

void LocationCaveHeaterOrFan::Update()
{
	if (GameDataController::gd->getObjective(S("cave_heater_cord_plugged")))
	{
		if (GameDataController::gd->getObjective(S("cave_heater_cord_plugged")) && lightAlfa < 1.0f && GameDataController::gd->getObjective(S("rv_power")))
		{
			lightAlfa += Time::get_deltaTime() * 0.1f;
		}
		if ((lightAlfa > 0.0f && !GameDataController::gd->getObjective(S("rv_power"))) || !GameDataController::gd->getObjective(S("cave_heater_cord_plugged")))
		{
			lightAlfa -= Time::get_deltaTime() * 0.1f;
		}
		if (lightAlfa < 0.0f)
		{
			lightAlfa = 0.0f;
		}
		if (lightAlfa > 1.0f)
		{
			lightAlfa = 1.0f;
		}
		lightAlfa2 += Random::Range(-0.1f, 0.1f);
		if (lightAlfa2 < 0.0f)
		{
			lightAlfa2 = 0.0f;
		}
		if (lightAlfa2 > 1.0f)
		{
			lightAlfa2 = 1.0f;
		}
		heaterGlow->set_color(Color(1.0f, 1.0f, 1.0f, lightAlfa * 0.75f + lightAlfa * lightAlfa2 * 0.25f));
		heater->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else if (!GameDataController::gd->getObjective(S("cave_fan_cord_plugged")))
	{
	}
}

void LocationCaveHeaterOrFan::clickAction()
{
	if (GameDataController::gd->getObjective(S("cave_fan_cord_plugged")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("fan"))))
		{
			GameDataController::gd->setObjective(S("cave_fan_cord_plugged"), false);
			updateAll();
		}
	}
	else if (GameDataController::gd->getObjective(S("cave_heater_cord_plugged")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("heater"))))
	{
		GameDataController::gd->setObjective(S("cave_heater_cord_plugged"), false);
		updateAll();
	}
}

void LocationCaveHeaterOrFan::updateState()
{
	if (GameDataController::gd->getObjective(S("cave_fan_cord_plugged")))
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		heaterGlow->set_enabled(false);
		heater->set_enabled(false);
		if (GameDataController::gd->getObjective(S("rv_power")))
		{
			fanstill->set_enabled(false);
			fango->set_enabled(true);
			GetComponent<AudioSource>()->set_clip(fanSound);
			GetComponent<AudioSource>()->set_loop(true);
			GetComponent<AudioSource>()->Play();
			objectName = S("cave_fan_on");
		}
		else
		{
			fanstill->set_enabled(true);
			fango->set_enabled(false);
			GetComponent<AudioSource>()->Stop();
			objectName = S("cave_fan_off");
		}
	}
	else if (GameDataController::gd->getObjective(S("cave_heater_cord_plugged")))
	{
		colliderManager->setCollider(1);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		heater->set_enabled(true);
		fanstill->set_enabled(false);
		fango->set_enabled(false);
		if (GameDataController::gd->getObjective(S("rv_power")))
		{
			GetComponent<AudioSource>()->set_clip(heaterSound);
			GetComponent<AudioSource>()->set_loop(true);
			GetComponent<AudioSource>()->Play();
			heaterGlow->set_enabled(true);
			objectName = S("cave_heater_on");
		}
		else
		{
			GetComponent<AudioSource>()->Stop();
			heaterGlow->set_enabled(false);
			objectName = S("cave_heater_off");
		}
	}
	else
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
		heaterGlow->set_enabled(false);
		heater->set_enabled(false);
		GetComponent<AudioSource>()->Stop();
		fanstill->set_enabled(false);
		fango->set_enabled(false);
	}
}

void LocationCaveHeaterOrFan::clickAction2()
{
}

void LocationCaveHeaterOrFan::clickAction0()
{
}

void LocationCaveHeaterOrFan::whatOnClick0()
{
}

void LocationCaveHeaterOrFan::whatOnClick()
{
}

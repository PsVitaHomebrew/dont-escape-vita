#include "../game_all.h"

void KitchenSocket::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("kitchen_socket");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("heater"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ext_cord"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("heater_broken"), GameStrings::getString(GameStrings::actions, S("heater_broken")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan_broken"), GameStrings::getString(GameStrings::actions, S("fan_broken")), nullptr, String::Empty));
	if (GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
	{
		isPowerThere = true;
	}
	else
	{
		isPowerThere = false;
	}
	isheaterThere = GameDataController::gd->getObjective(S("kitchen_heater_plugged"));
	updateState();
}

void KitchenSocket::Update()
{
	if (isheaterThere && isPowerThere && lightAlfa < 1.0f)
	{
		lightAlfa += Time::get_deltaTime() * 0.1f;
	}
	if (lightAlfa > 0.0f && (!isPowerThere || !isheaterThere))
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
	heaterLight->set_color(Color(1.0f, 1.0f, 1.0f, lightAlfa * 0.75f + lightAlfa * lightAlfa2 * 0.25f));
}

void KitchenSocket::clickAction()
{
	if (usedItem == S("ext_cord"))
	{
		if (GameDataController::gd->getObjective(S("kitchen_heater_plugged")) || GameDataController::gd->getObjective(S("kitchen_fan_plugged")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("socket_busy")));
			return;
		}
		InventoryController::ic->removeItem(S("ext_cord"));
		GameDataController::gd->setObjective(S("kitchen_cord_plugged"), true);
		updateAll();
	}
	else if (usedItem == S("heater"))
	{
		if (GameDataController::gd->getObjective(S("kitchen_cord_plugged")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("heater_cant_plug_here")));
			return;
		}
		InventoryController::ic->removeItem(S("heater"));
		GameDataController::gd->setObjective(S("kitchen_heater_plugged"), true);
		isheaterThere = GameDataController::gd->getObjective(S("kitchen_heater_plugged"));
		updateAll();
	}
	else if (usedItem == S("fan"))
	{
		if (GameDataController::gd->getObjective(S("kitchen_cord_plugged")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("fan_cant_plug_here")));
			return;
		}
		InventoryController::ic->removeItem(S("fan"));
		GameDataController::gd->setObjective(S("kitchen_fan_plugged"), true);
		updateAll();
	}
	else if (GameDataController::gd->getObjective(S("kitchen_cord_plugged")) && GameDataController::gd->getObjective(S("kitchen_cord_dragged")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cord_dragged")));
	}
	else if (GameDataController::gd->getObjective(S("kitchen_cord_plugged")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("ext_cord"))))
		{
			GameDataController::gd->setObjective(S("kitchen_cord_plugged"), false);
			updateAll();
		}
	}
	else if (GameDataController::gd->getObjective(S("kitchen_heater_plugged")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("heater"))))
		{
			GameDataController::gd->setObjective(S("kitchen_heater_plugged"), false);
			isheaterThere = GameDataController::gd->getObjective(S("kitchen_heater_plugged"));
			updateAll();
		}
	}
	else if (GameDataController::gd->getObjective(S("kitchen_fan_plugged")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("fan"))))
		{
			GameDataController::gd->setObjective(S("kitchen_fan_plugged"), false);
			updateAll();
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("socket_empty")));
	}
}

void KitchenSocket::updateState()
{
	colliderManager->setCollider(0);
	fan1->set_enabled(false);
	fan2->set_enabled(false);
	fanas->Stop();
	if (GameDataController::gd->getObjective(S("kitchen_cord_plugged")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (!GameDataController::gd->getObjective(S("kitchen_cord_dragged")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(cord);
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_sprite(cord2);
		}
		heaterLight->set_enabled(false);
		setCollider(1);
		objectName = S("plugged_cord");
	}
	else if (GameDataController::gd->getObjective(S("kitchen_heater_plugged")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(heater);
		heaterLight->set_enabled(true);
		setCollider(2);
		if (GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
		{
			fanas->set_clip(SoundsManagerController::sm->heater2);
			fanas->Play();
			fanas->set_loop(true);
			objectName = S("plugged_heater_on");
		}
		else
		{
			objectName = S("plugged_heater_off");
		}
	}
	else if (GameDataController::gd->getObjective(S("kitchen_fan_plugged")))
	{
		setCollider(2);
		GetComponent<SpriteRenderer>()->set_enabled(false);
		if (GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
		{
			objectName = S("plugged_fan_on");
			fan1->set_enabled(false);
			fan2->set_enabled(true);
			fanas->set_clip(SoundsManagerController::sm->fan);
			fanas->Play();
			fanas->set_loop(true);
		}
		else
		{
			fan1->set_enabled(true);
			fan2->set_enabled(false);
			objectName = S("plugged_fan_off");
		}
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		heaterLight->set_enabled(false);
		setCollider(0);
		objectName = S("kitchen_socket");
	}
}

void KitchenSocket::clickAction2()
{
}

void KitchenSocket::clickAction0()
{
}

void KitchenSocket::whatOnClick0()
{
}

void KitchenSocket::whatOnClick()
{
}

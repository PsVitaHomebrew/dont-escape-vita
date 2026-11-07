#include "../game_all.h"

void GasstationFuelTank::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_tank");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister_empty"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_empty"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister_full"), GameStrings::getString(GameStrings::actions, S("tank_canister_full")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_full"), GameStrings::getString(GameStrings::actions, S("tank_canister_full")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("watersprayer"), GameStrings::getString(GameStrings::actions, S("tank_sprayer")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flamethrower_empty"), GameStrings::getString(GameStrings::actions, S("tank_sprayer")), nullptr, String::Empty));
}

void GasstationFuelTank::whatOnClick()
{
	if (usedItem == S("wrench") && !GameDataController::gd->getObjective(S("gasstation_canister_placed_under_tank")) && !GameDataController::gd->getObjective(S("gasstation_canister2_placed_under_tank")))
	{
		characterAnimationName = S("fuel_spill");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else if (usedItem == S("wrench") && ((GameDataController::gd->getObjective(S("gasstation_canister_placed_under_tank")) && !GameDataController::gd->getObjective(S("gasstation_canister_filled"))) || (GameDataController::gd->getObjective(S("gasstation_canister2_placed_under_tank")) && !GameDataController::gd->getObjective(S("gasstation_canister2_filled")))))
	{
		characterAnimationName = S("fuel_canster");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else if (usedItem == S("canister_empty"))
	{
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else if (usedItem == S("canister2_empty"))
	{
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else if (GameDataController::gd->getObjective(S("gasstation_canister_placed_under_tank")) && usedItem == String::Empty)
	{
		if (GameDataController::gd->getObjective(S("gasstation_canister_filled")))
		{
			characterAnimationName = S("kneel_n");
			animationFlip = false;
			useCurrentDirection = false;
		}
		else
		{
			characterAnimationName = S("action_n");
			animationFlip = false;
			useCurrentDirection = false;
		}
	}
	else if (GameDataController::gd->getObjective(S("gasstation_canister2_placed_under_tank")) && usedItem == String::Empty)
	{
		if (GameDataController::gd->getObjective(S("gasstation_canister2_filled")))
		{
			characterAnimationName = S("kneel_n");
			animationFlip = false;
			useCurrentDirection = false;
		}
		else
		{
			characterAnimationName = S("action_n");
			animationFlip = false;
			useCurrentDirection = false;
		}
	}
	else
	{
		characterAnimationName = S("action_stnd_se");
		animationFlip = true;
		useCurrentDirection = false;
	}
}

void GasstationFuelTank::clickAction()
{
	if (usedItem == S("wrench"))
	{
		if (GameDataController::gd->getObjective(S("gasstation_canister_placed_under_tank")) && GameDataController::gd->getObjective(S("gasstation_canister_filled")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tank_canister_full")), true);
		}
		else if (GameDataController::gd->getObjective(S("gasstation_canister2_placed_under_tank")) && GameDataController::gd->getObjective(S("gasstation_canister2_filled")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tank_canister_full")), true);
		}
		else if (GameDataController::gd->getObjective(S("gasstation_canister_placed_under_tank")) && !GameDataController::gd->getObjective(S("gasstation_canister_filled")))
		{
			GameDataController::gd->setObjective(S("gasstation_canister_filled"), true);
		}
		else if (GameDataController::gd->getObjective(S("gasstation_canister2_placed_under_tank")) && !GameDataController::gd->getObjective(S("gasstation_canister2_filled")))
		{
			GameDataController::gd->setObjective(S("gasstation_canister2_filled"), true);
		}
	}
	else if (usedItem == S("canister_empty"))
	{
		if (!GameDataController::gd->getObjective(S("gasstation_canister2_placed_under_tank")))
		{
			InventoryController::ic->removeItem(usedItem);
			GameDataController::gd->setObjective(S("gasstation_canister_placed_under_tank"), true);
			GameDataController::gd->setObjective(S("gasstation_canister_filled"), false);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tank_canister_already")), true);
		}
	}
	else if (usedItem == S("canister2_empty"))
	{
		if (!GameDataController::gd->getObjective(S("gasstation_canister_placed_under_tank")))
		{
			InventoryController::ic->removeItem(usedItem);
			GameDataController::gd->setObjective(S("gasstation_canister2_placed_under_tank"), true);
			GameDataController::gd->setObjective(S("gasstation_canister2_filled"), false);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tank_canister_already")), true);
		}
	}
	else if (usedItem == S("canister_full"))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tank_canister_full")), true);
	}
	else if (usedItem == S("canister2_full"))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tank_canister_full")), true);
	}
	else if (GameDataController::gd->getObjective(S("gasstation_canister_placed_under_tank")))
	{
		if (GameDataController::gd->getObjective(S("gasstation_canister_filled")))
		{
			if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("canister_full"))))
			{
				GameDataController::gd->setObjective(S("gasstation_canister_placed_under_tank"), false);
				GameDataController::gd->setObjective(S("gasstation_canister_filled"), false);
			}
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("fuel_valves_closed")));
		}
	}
	else if (GameDataController::gd->getObjective(S("gasstation_canister2_placed_under_tank")))
	{
		if (GameDataController::gd->getObjective(S("gasstation_canister2_filled")))
		{
			if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("canister2_full"))))
			{
				GameDataController::gd->setObjective(S("gasstation_canister2_placed_under_tank"), false);
				GameDataController::gd->setObjective(S("gasstation_canister2_filled"), false);
			}
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("fuel_valves_closed")));
		}
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_tank_wrench")), true);
	}
	updateState();
}

void GasstationFuelTank::updateState()
{
	if (!GameDataController::gd->getObjective(S("gasstation_canister_placed_under_tank")) && !GameDataController::gd->getObjective(S("gasstation_canister2_placed_under_tank")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(0);
		objectName = S("gasstation_tank");
	}
	else if (!GameDataController::gd->getObjective(S("gasstation_canister2_placed_under_tank")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(s1);
		colliderManager->setCollider(1);
		if (GameDataController::gd->getObjective(S("gasstation_canister_filled")))
		{
			objectName = S("gasstation_tank_canister_full");
		}
		else
		{
			objectName = S("gasstation_tank_canister");
		}
	}
	else if (!GameDataController::gd->getObjective(S("gasstation_canister_placed_under_tank")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(s2);
		colliderManager->setCollider(2);
		if (GameDataController::gd->getObjective(S("gasstation_canister2_filled")))
		{
			objectName = S("gasstation_tank_canister_full");
		}
		else
		{
			objectName = S("gasstation_tank_canister");
		}
	}
	if (GameDataController::gd->getObjective(S("gasstation_spy_mode")))
	{
		setCollider(-1);
	}
}

void GasstationFuelTank::clickAction2()
{
	if (usedItem == S("wrench"))
	{
		valvePlay();
		Invoke(S("openTap"), 0.2f);
	}
}

void GasstationFuelTank::openTap()
{
	if (!GameDataController::gd->getObjective(S("gasstation_canister2_placed_under_tank")) && !GameDataController::gd->getObjective(S("gasstation_canister_placed_under_tank")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_spill);
		Invoke(S("valvePlay"), 2.0f);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour);
		Invoke(S("valvePlay"), 4.5f);
	}
}

void GasstationFuelTank::valvePlay()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->valve);
}

void GasstationFuelTank::clickAction0()
{
}

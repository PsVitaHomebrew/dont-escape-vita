#include "../game_all.h"

void rv_fuel::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_fuel_inlet");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("canister_full"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister_empty"), GameStrings::getString(GameStrings::actions, S("canister_is_empty")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_full"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_empty"), GameStrings::getString(GameStrings::actions, S("canister_is_empty")), nullptr, String::Empty));
}

void rv_fuel::clickAction()
{
	if (usedItem != String::Empty)
	{
		if (usedItem == S("canister_full"))
		{
			if (!GameDataController::gd->getObjective(S("rv_fueled")))
			{
				GameDataController::gd->setObjective(S("rv_fueled"), true);
				InventoryController::ic->removeItem(S("canister_full"));
				ItemsManager::im->updateItem(S("canister_full"), S("nowhere"), 0, 0);
				InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("canister_empty")));
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_already_fueled")));
			}
		}
		else if (usedItem == S("canister2_full"))
		{
			if (!GameDataController::gd->getObjective(S("rv_fueled")))
			{
				GameDataController::gd->setObjective(S("rv_fueled"), true);
				InventoryController::ic->removeItem(S("canister2_full"));
				ItemsManager::im->updateItem(S("canister2_full"), S("nowhere"), 0, 0);
				InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("canister2_empty")));
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_already_fueled")));
			}
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_fuel_inlet")));
	}
}

void rv_fuel::updateState()
{
}

void rv_fuel::whatOnClick0()
{
	if (usedItem != String::Empty && !GameDataController::gd->getObjective(S("rv_fueled")))
	{
		characterAnimationName = S("action_n_long");
		useCurrentDirection = false;
		range = 1.0f;
	}
	else
	{
		range = 100.0f;
		characterAnimationName = S("action_stnd_");
		useCurrentDirection = true;
	}
}

void rv_fuel::clickAction2()
{
}

void rv_fuel::clickAction0()
{
}

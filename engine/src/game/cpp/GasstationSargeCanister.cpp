#include "../game_all.h"

void GasstationSargeCanister::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_canister");
	range = 10.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
}

void GasstationSargeCanister::whatOnClick()
{
	if (usedItem == S("wrench"))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 30.0f;
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		characterAnimationName = S("kneel_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 1.0f;
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 300.0f;
	}
}

void GasstationSargeCanister::clickAction()
{
	if (usedItem == S("wrench"))
	{
		if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
		{
			if (GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
			{
				PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tank_canister_full")), true);
			}
			else
			{
				PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tank_canister_take_first")), true);
			}
		}
		else
		{
			GameObject::Find(S("sargeObject"))->GetComponent<GasstationSargeObject>()->talkWrench();
		}
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		if (GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
		{
			if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("canister2_full"))))
			{
				GameDataController::gd->setObjective(S("gasstation_sarge_canister_taken"), true);
				updateAll();
			}
		}
		else if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("canister2_empty"))))
		{
			GameDataController::gd->setObjective(S("gasstation_sarge_canister_taken"), true);
			updateAll();
		}
	}
	else
	{
		GameObject::Find(S("sargeObject"))->GetComponent<GasstationSargeObject>()->dontTouchThat();
	}
}

void GasstationSargeCanister::updateState()
{
	setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	if (GameDataController::gd->getObjective(S("gasstation_spy_mode")))
	{
		setCollider(-1);
	}
	if (GameDataController::gd->getCurrentDay() == 3 && !GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")) && !GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		setCollider(-1);
	}
	if (GameDataController::gd->getObjective(S("gasstation_sarge_convinced")))
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("gasstation_sarge_canister_taken")) || GameDataController::gd->getObjective(S("gasstation_sarge_convinced")) || GameDataController::gd->getCurrentDay() < 3 || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 0 || !GameDataController::gd->getObjective(S("sidereal_base_located")) || (GameDataController::gd->getCurrentDay() > 3 && !GameDataController::gd->getObjective(S("gasstation_sarge_shot"))))
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void GasstationSargeCanister::clickAction0()
{
}

void GasstationSargeCanister::clickAction2()
{
}

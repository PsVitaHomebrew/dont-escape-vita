#include "../game_all.h"

void PesttruckChemsuit1::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("chemsuit_dmg");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("mask_filter"), GameStrings::getString(GameStrings::actions, S("pest_chemsuit_repair")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ducttape"), GameStrings::getString(GameStrings::actions, S("pest_chemsuit_repair")), nullptr, String::Empty));
	updateState();
}

void PesttruckChemsuit1::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("chemsuit_dmg_dmg"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_chemsuit_dmg_taken"), !GameDataController::gd->getObjective(S("pesttruck_chemsuit_dmg_taken")));
		updateState();
	}
}

void PesttruckChemsuit1::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 1)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("pesttruck_chemsuit_dmg_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker1_open")))
	{
		characterAnimationName = S("action_n");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void PesttruckChemsuit1::clickAction2()
{
}

void PesttruckChemsuit1::clickAction0()
{
}

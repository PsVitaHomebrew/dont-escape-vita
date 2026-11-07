#include "../game_all.h"

void GasstationCanister::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_canister");
}

void GasstationCanister::clickAction()
{
	if ((GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited"))) && !GameDataController::gd->getObjective(S("gasstation_canister_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("canister_empty"))))
	{
		GameDataController::gd->setObjective(S("gasstation_canister_taken"), true);
		updateState();
	}
}

void GasstationCanister::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("gasstation_canister_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void GasstationCanister::clickAction2()
{
	if (GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_canister")), true);
	}
}

void GasstationCanister::clickAction0()
{
}

void GasstationCanister::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_blocking")), true);
		PlayerController::wc->fullStop(true);
	}
}

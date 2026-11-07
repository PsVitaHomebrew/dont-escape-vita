#include "../game_all.h"

void GasstationMoney::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_cash");
}

void GasstationMoney::clickAction()
{
	if ((GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited"))) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("wad_of_cash"))))
	{
		GameDataController::gd->setObjective(S("gasstation_cash_taken"), true);
		updateAll();
	}
}

void GasstationMoney::updateState()
{
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		characterAnimationName = S("stand_");
		animationFlip = true;
	}
	if (GameDataController::gd->getObjective(S("gasstation_cash_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
}

void GasstationMoney::clickAction2()
{
}

void GasstationMoney::clickAction0()
{
	if (GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_cash")), true);
	}
}

void GasstationMoney::whatOnClick0()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_blocking")), true);
	}
}

void GasstationMoney::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::wc->fullStop(true);
	}
}

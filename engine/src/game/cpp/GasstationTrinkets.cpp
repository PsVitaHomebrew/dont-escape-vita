#include "../game_all.h"

void GasstationTrinkets::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_trinkets");
}

void GasstationTrinkets::clickAction()
{
	if ((GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited"))) && !GameDataController::gd->getObjective(S("gasstation_lighter_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("lighter"))))
	{
		GameDataController::gd->setObjective(S("gasstation_lighter_taken"), true);
	}
}

void GasstationTrinkets::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("gasstation_lighter_taken")))
	{
		characterAnimationName = S("action1_e");
		animationFlip = true;
		useCurrentDirection = false;
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void GasstationTrinkets::clickAction2()
{
}

void GasstationTrinkets::clickAction0()
{
	if (GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		if (!GameDataController::gd->getObjective(S("gasstation_lighter_taken")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_trinkets_lighter")), true);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_trinkets_empty")), true);
		}
	}
}

void GasstationTrinkets::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_blocking")), true);
		PlayerController::wc->fullStop(true);
	}
	if (!GameDataController::gd->getObjective(S("gasstation_lighter_taken")))
	{
		characterAnimationName = S("action1_e");
		animationFlip = true;
		useCurrentDirection = false;
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void GasstationTrinkets::whatOnClick0()
{
}

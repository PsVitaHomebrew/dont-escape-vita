#include "../game_all.h"

void RifleGasstation::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_rifle");
	updateState();
}

void RifleGasstation::clickAction()
{
	if ((GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited"))) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("rifle_6"))))
	{
		GameDataController::gd->setObjective(S("gasstation_rifle_taken"), true);
		P<Item> item = ItemsManager::im->getItem(S("rifle_6"));
		updateState();
	}
}

void RifleGasstation::updateState()
{
	if (!GameDataController::gd->getObjective(S("gasstation_rifle_taken")))
	{
		setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void RifleGasstation::clickAction2()
{
}

void RifleGasstation::clickAction0()
{
}

void RifleGasstation::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_blocking")), true);
		PlayerController::wc->fullStop(true);
	}
}

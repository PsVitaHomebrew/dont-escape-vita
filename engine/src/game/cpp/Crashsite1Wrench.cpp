#include "../game_all.h"

void Crashsite1Wrench::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		objectName = S("crashsite_wrench_bugs");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		objectName = S("crashsite_wrench_gas");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		objectName = S("crashsite_wrench_spiders");
	}
}

void Crashsite1Wrench::clickAction()
{
	if (!GameDataController::gd->getObjective(S("crashsite_wrench_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("wrench"))))
	{
		GameDataController::gd->setObjective(S("crashsite_wrench_taken"), true);
		updateAll();
	}
}

void Crashsite1Wrench::updateState()
{
	if (GameDataController::gd->getObjective(S("crashsite_wrench_taken")))
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

void Crashsite1Wrench::clickAction2()
{
}

void Crashsite1Wrench::clickAction0()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_wrench")), true);
}

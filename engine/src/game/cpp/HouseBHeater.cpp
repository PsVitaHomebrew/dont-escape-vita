#include "../game_all.h"

void HouseBHeater::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_heater");
}

void HouseBHeater::clickAction()
{
	if (!GameDataController::gd->getObjective(S("house_b_heater_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("heater_broken"))))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("heater_broken_pick")));
		GameDataController::gd->setObjective(S("house_b_heater_taken"), true);
		updateState();
	}
}

void HouseBHeater::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1 && !GameDataController::gd->getObjective(S("house_b_heater_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		return;
	}
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	colliderManager->setCollider(-1);
}

void HouseBHeater::clickAction2()
{
}

void HouseBHeater::clickAction0()
{
}

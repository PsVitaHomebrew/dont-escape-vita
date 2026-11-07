#include "../game_all.h"

void HouseBFan::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_fan");
}

void HouseBFan::clickAction()
{
	if (!GameDataController::gd->getObjective(S("house_b_fan_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("fan_broken"))))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("fan_broken_pick")));
		GameDataController::gd->setObjective(S("house_b_fan_taken"), true);
		updateState();
	}
}

void HouseBFan::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0 && !GameDataController::gd->getObjective(S("house_b_fan_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		return;
	}
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	colliderManager->setCollider(-1);
}

void HouseBFan::clickAction2()
{
}

void HouseBFan::clickAction0()
{
}

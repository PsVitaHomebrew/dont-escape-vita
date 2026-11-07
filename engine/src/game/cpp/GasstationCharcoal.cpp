#include "../game_all.h"

void GasstationCharcoal::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_charcoal");
}

void GasstationCharcoal::clickAction()
{
	if ((GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited"))) && !GameDataController::gd->getObjective(S("gasstation_charcoal_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("charcoal"))))
	{
		GameDataController::gd->setObjective(S("gasstation_charcoal_taken"), true);
		updateState();
	}
}

void GasstationCharcoal::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("gasstation_charcoal_taken")))
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

void GasstationCharcoal::clickAction2()
{
	if ((GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited"))) && GameDataController::gd->getCurrentDay() == 1)
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>());
		timelineAction->text = S("[") + GameStrings::getString(GameStrings::gui, S("items_hint")) + S("]");
		timelineAction->actionWithText = true;
		timelineAction->textWidth = 170;
		timelineAction->blockG = true;
		Timeline::t->addAction(timelineAction);
	}
}

void GasstationCharcoal::clickAction0()
{
}

void GasstationCharcoal::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_blocking")), true);
		PlayerController::wc->fullStop(true);
	}
}

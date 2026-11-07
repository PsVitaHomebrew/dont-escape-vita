#include "../game_all.h"

void GasstationCrowbar::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_crowbar");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("hammer"), String::Empty, nullptr, String::Empty));
	range = 1.0f;
}

void GasstationCrowbar::clickAction()
{
	if (GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		if (usedItem == S("hammer"))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("gasstation_hammer_crowbar")), QuestionController::PopupType::QUESTION, [this]() { giveCrowbar(); }, 1);
		}
		else
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("gasstation_force_crowbar")), QuestionController::PopupType::QUESTION, [this]() { giveCrowbar(); }, 5);
		}
	}
}

void GasstationCrowbar::updateState()
{
	if (GameDataController::gd->getObjective(S("gasstation_crowbar_free")))
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

void GasstationCrowbar::clickAction2()
{
}

void GasstationCrowbar::clickAction0()
{
}

void GasstationCrowbar::giveCrowbar()
{
	drop();
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::E);
}

void GasstationCrowbar::drop()
{
	GameDataController::gd->setObjective(S("gasstation_crowbar_free"), true);
	P<Item> item = ItemsManager::im->getItem(S("crowbar"));
	updateState();
	InventoryController::ic->pickOrDropItem(item);
}

void GasstationCrowbar::whatOnClick0()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_blocking")), true);
	}
}

void GasstationCrowbar::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::wc->fullStop(true);
	}
}

#include "../game_all.h"

void GasstationNewspaper::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_newspaper");
}

void GasstationNewspaper::clickAction()
{
	if (GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		ExamineSprite::es->textField->shift.x = -4.0f;
		ExamineSprite::es->textField->shift.y = 58.0f;
		ExamineSprite::es->readyText(List<String>::New({
			GameStrings::getString(GameStrings::world_labels, S("gasstation_newspaper1")),
			GameStrings::getString(GameStrings::world_labels, S("gasstation_newspaper2")),
			GameStrings::getString(GameStrings::world_labels, S("gasstation_newspaper3")),
			GameStrings::getString(GameStrings::world_labels, S("gasstation_newspaper4")),
			GameStrings::getString(GameStrings::world_labels, S("gasstation_newspaper5")),
			GameStrings::getString(GameStrings::world_labels, S("gasstation_newspaper6")),
			GameStrings::getString(GameStrings::world_labels, S("gasstation_newspaper7")),
			GameStrings::getString(GameStrings::world_labels, S("gasstation_newspaper8")),
			GameStrings::getString(GameStrings::world_labels, S("gasstation_newspaper9")),
			GameStrings::getString(GameStrings::world_labels, S("gasstation_newspaper10"))
		}), 120, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		ExamineSprite::es->show(newspaper);
	}
}

void GasstationNewspaper::updateState()
{
	colliderManager->setCollider(0);
}

void GasstationNewspaper::clickAction2()
{
	if (GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_newspaper_start")), true);
	}
}

void GasstationNewspaper::clickAction0()
{
	if (GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_newspaper_start")), true);
	}
}

void GasstationNewspaper::whatOnClick0()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_blocking")), true);
		PlayerController::wc->fullStop(true);
		PlayerController::pc->setBusy(false);
		characterAnimationName = S("stand_");
		animationFlip = true;
	}
	else
	{
		characterAnimationName = S("stop");
		animationFlip = false;
	}
}

void GasstationNewspaper::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::wc->fullStop(true);
		PlayerController::pc->setBusy(false);
	}
}

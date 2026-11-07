#include "../game_all.h"

void GasstationCorpse::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_s");
	animationFlip = false;
	useCurrentDirection = false;
	range = 100.0f;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_corpse");
	updateState();
}

void GasstationCorpse::clickAction()
{
	if (GameDataController::gd->getCurrentDay() != 1 || GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_corpse")), true);
	}
}

void GasstationCorpse::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		setCollider(0);
	}
	else
	{
		setCollider(-1);
	}
}

void GasstationCorpse::clickAction2()
{
}

void GasstationCorpse::clickAction0()
{
}

void GasstationCorpse::whatOnClick0()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_blocking")), true);
	}
}

void GasstationCorpse::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::wc->fullStop(true);
	}
}

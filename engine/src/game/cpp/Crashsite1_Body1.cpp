#include "../game_all.h"

void Crashsite1_Body1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		objectName = S("crashsite_body1_bugs_a");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		objectName = S("crashsite_body1_gas_a");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		objectName = S("crashsite_body1_spiders_a");
	}
	updateState();
}

void Crashsite1_Body1::showIt()
{
	colliderManager->setCollider(0);
}

void Crashsite1_Body1::hideIt()
{
	colliderManager->setCollider(-1);
}

void Crashsite1_Body1::clickAction2()
{
}

void Crashsite1_Body1::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		if (!GameDataController::gd->getObjective(S("crashsite_sonic_remote_taken")))
		{
			characterAnimationName = S("kneel_n");
			useCurrentDirection = false;
			objectName = S("crashsite_body1_bugs_a");
		}
		else
		{
			characterAnimationName = S("action_stnd_");
			useCurrentDirection = true;
			objectName = S("crashsite_body1_bugs_b");
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		if (!GameDataController::gd->getObjective(S("mask_filter_taken")))
		{
			characterAnimationName = S("kneel_n");
			objectName = S("crashsite_body1_gas_a");
			useCurrentDirection = false;
		}
		else
		{
			characterAnimationName = S("action_stnd_");
			objectName = S("crashsite_body1_gas_b");
			useCurrentDirection = true;
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		characterAnimationName = S("kneel_in_n");
		objectName = S("crashsite_body1_spiders_a");
		useCurrentDirection = false;
	}
	if (GameDataController::gd->getCurrentDay() > 1)
	{
		hideIt();
	}
	else
	{
		showIt();
	}
}

void Crashsite1_Body1::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		if (!GameDataController::gd->getObjective(S("crashsite_sonic_remote_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sonic_remote"))))
		{
			GameDataController::gd->setObjective(S("crashsite_sonic_remote_taken"), true);
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_body1_bugs_remote2")), true);
			updateState();
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		if (!GameDataController::gd->getObjective(S("mask_filter_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("mask_filter"))))
		{
			GameDataController::gd->setObjective(S("mask_filter_taken"), true);
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_body1_gas_filter2")), true);
			updateState();
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		P<Sprite> sprite = nullptr;
		if (GameDataController::gd->getObjectiveDetail(S("spiders_type")) == 0)
		{
			sprite = bite1;
		}
		if (GameDataController::gd->getObjectiveDetail(S("spiders_type")) == 1)
		{
			sprite = bite2;
		}
		if (GameDataController::gd->getObjectiveDetail(S("spiders_type")) == 2)
		{
			sprite = bite3;
		}
		if (GameDataController::gd->getObjectiveDetail(S("spiders_type")) == 3)
		{
			sprite = bite4;
		}
		ExamineSprite::es->closingAnimation = S("kneel_out_n");
		ExamineSprite::es->show(biteBackground, sprite);
	}
}

void Crashsite1_Body1::clickAction0()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		if (!GameDataController::gd->getObjective(S("crashsite_sonic_remote_taken")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_body1_bugs_remote1")), true);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_body1_bugs_remote3")), true);
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		if (!GameDataController::gd->getObjective(S("mask_filter_taken")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_body1_gas_filter1")), true);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_body1_gas_filter3")), true);
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_spider_body_start")), true);
	}
}

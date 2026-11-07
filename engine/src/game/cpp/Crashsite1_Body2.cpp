#include "../game_all.h"

void Crashsite1_Body2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e_in");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		objectName = S("crashsite_body2_bugs");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		objectName = S("crashsite_body2_gas");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		objectName = S("crashsite_body2_spiders");
	}
}

void Crashsite1_Body2::clickAction()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->page_turn_03);
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::world_labels, S("crashsite_body2_bugs_note")), true, true, true, 200, 0.0f, 0.0f, 0.0f, 237.0f / 255.0f, 222.0f / 255.0f, 154.0f / 255.0f, 1.0f, false, true);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		ExamineSprite::es->textField->shift.y = 50.0f;
		ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("crashsite_body2_gas_note")) }), 200, 0.0f, 0.0f, 0.0f, 237.0f / 255.0f, 222.0f / 255.0f, 154.0f / 255.0f, 1.0f);
		ExamineSprite::es->closingAnimation = S("kneel_e_out");
		ExamineSprite::es->show(nullptr, nullptr, nullptr, nullptr, nullptr, [this]() { aaa(); }, false);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::world_labels, S("crashsite_body2_spiders_note")), true, true, true, 200, 0.0f, 0.0f, 0.0f, 237.0f / 255.0f, 222.0f / 255.0f, 154.0f / 255.0f, 1.0f, false, true);
	}
}

void Crashsite1_Body2::showIt()
{
	colliderManager->setCollider(0);
}

void Crashsite1_Body2::hideIt()
{
	colliderManager->setCollider(-1);
}

void Crashsite1_Body2::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getCurrentDay() > 1)
	{
		hideIt();
	}
	else
	{
		showIt();
	}
}

void Crashsite1_Body2::aaa()
{
	MonoBehaviour::print(S("THIS ACTION 2 ================================================ +++++++++++++++++++++++++++++++ &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"));
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		GameDataController::gd->setObjective(S("crashsite_gas_note_read"), true);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_body2_gas_long2")), true);
	}
}

void Crashsite1_Body2::clickAction2()
{
}

void Crashsite1_Body2::clickAction0()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::objects, S("crashsite_body2_bugs_long")), true);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::objects, S("crashsite_body2_gas_long")), true);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::objects, S("crashsite_body2_spiders_long")), true);
	}
}

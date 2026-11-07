#include "../game_all.h"

void OutpostFAQ::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_faq");
	range = 1.0f;
}

void OutpostFAQ::clickAction()
{
	ExamineSprite::es->textField->shift.x = -110.0f;
	ExamineSprite::es->textField->shift.y = 55.0f;
	ExamineSprite::es->readyText(List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("outpost_faq_1")),
		GameStrings::getString(GameStrings::world_labels, S("outpost_faq_2")),
		GameStrings::getString(GameStrings::world_labels, S("outpost_faq_3")),
		GameStrings::getString(GameStrings::world_labels, S("outpost_faq_4")),
		GameStrings::getString(GameStrings::world_labels, S("outpost_faq_5")),
		GameStrings::getString(GameStrings::world_labels, S("outpost_faq_6")),
		GameStrings::getString(GameStrings::world_labels, S("outpost_faq_7")),
		GameStrings::getString(GameStrings::world_labels, S("outpost_faq_8")),
		GameStrings::getString(GameStrings::world_labels, S("outpost_faq_9")),
		GameStrings::getString(GameStrings::world_labels, S("outpost_faq_10"))
	}), 190, 0.2f, 0.2f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f);
	ExamineSprite::es->ac = SoundsManagerController::sm->page_turn_01;
	ExamineSprite::es->show(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, false);
}

void OutpostFAQ::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_switch_pressed")))
	{
		setCollider(0);
	}
	else
	{
		setCollider(-1);
	}
}

void OutpostFAQ::clickAction2()
{
}

void OutpostFAQ::clickAction0()
{
}

void OutpostFAQ::whatOnClick0()
{
}

void OutpostFAQ::whatOnClick()
{
}

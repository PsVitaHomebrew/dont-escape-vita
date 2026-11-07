#include "../game_all.h"

void ConstructionConspiracy::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("construction_conspiracy");
	range = 1.0f;
}

void ConstructionConspiracy::clickAction()
{
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
		return;
	}
	ExamineSprite::es->textField->shift.x = -3.0f;
	ExamineSprite::es->textField->shift.y = 55.0f;
	ExamineSprite::es->readyText(List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("conspiracy2_1")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy2_2")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy2_3")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy2_4")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy2_5")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy2_6")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy2_7")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy2_8")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy2_9")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy2_10"))
	}), 120, 0.2f, 0.2f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f);
	ExamineSprite::es->ac = SoundsManagerController::sm->page_turn_04;
	ExamineSprite::es->show(painting, nullptr, nullptr, nullptr, nullptr, [this]() { talkWithCate(); }, false);
}

void ConstructionConspiracy::talkWithCate()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("cate_construction_conspiracy"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	Timeline::t->doNotUnlock = true;
}

void ConstructionConspiracy::updateState()
{
	if (!GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		range = 1.0f;
		characterAnimationName = S("action_stnd_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		range = 100.0f;
		characterAnimationName = S("action_stnd_se");
		animationFlip = true;
		useCurrentDirection = false;
	}
}

void ConstructionConspiracy::clickAction2()
{
}

void ConstructionConspiracy::clickAction0()
{
}

void ConstructionConspiracy::whatOnClick0()
{
}

void ConstructionConspiracy::whatOnClick()
{
}

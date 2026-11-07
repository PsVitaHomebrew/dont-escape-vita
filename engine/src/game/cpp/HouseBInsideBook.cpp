#include "../game_all.h"

void HouseBInsideBook::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_lucid_book");
	range = 1.0f;
}

void HouseBInsideBook::clickAction()
{
	ExamineSprite::es->textField->shift.x = -3.0f;
	ExamineSprite::es->textField->shift.y = 50.0f;
	ExamineSprite::es->readyText(List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("book_lucid_1")),
		GameStrings::getString(GameStrings::world_labels, S("book_lucid_2")),
		GameStrings::getString(GameStrings::world_labels, S("book_lucid_3")),
		GameStrings::getString(GameStrings::world_labels, S("book_lucid_4")),
		GameStrings::getString(GameStrings::world_labels, S("book_lucid_5")),
		GameStrings::getString(GameStrings::world_labels, S("book_lucid_6")),
		GameStrings::getString(GameStrings::world_labels, S("book_lucid_7")),
		GameStrings::getString(GameStrings::world_labels, S("book_lucid_8"))
	}), 120, 0.2f, 0.2f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f);
	ExamineSprite::es->ac = SoundsManagerController::sm->page_turn_02;
	ExamineSprite::es->show(painting);
}

void HouseBInsideBook::updateState()
{
	colliderManager->setCollider(0);
}

void HouseBInsideBook::clickAction2()
{
}

void HouseBInsideBook::clickAction0()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("house_lucid_book")));
}

void HouseBInsideBook::whatOnClick0()
{
}

void HouseBInsideBook::whatOnClick()
{
}

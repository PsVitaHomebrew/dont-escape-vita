#include "../game_all.h"

void SiderealLabNote::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_e");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_lab_note");
	range = 1.0f;
}

void SiderealLabNote::clickAction()
{
	ExamineSprite::es->textField->shift.x = -45.0f;
	ExamineSprite::es->textField->shift.y = -5.0f;
	ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("sideral_warning_note")) }), 150, 0.2f, 0.2f, 0.2f, 1.0f, 1.0f, 1.0f, 0.0f);
	ExamineSprite::es->ac = SoundsManagerController::sm->page_turn_02;
	ExamineSprite::es->show(painting);
}

void SiderealLabNote::updateState()
{
}

void SiderealLabNote::clickAction2()
{
}

void SiderealLabNote::clickAction0()
{
}

void SiderealLabNote::whatOnClick0()
{
}

void SiderealLabNote::whatOnClick()
{
}

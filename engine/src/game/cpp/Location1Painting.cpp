#include "../game_all.h"

void Location1Painting::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_painting");
	range = 15.0f;
}

void Location1Painting::clickAction()
{
	ExamineSprite::es->textField->shift.x = -110.0f;
	ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::actions, S("base_painting")) }), 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f);
	ExamineSprite::es->show(painting);
}

void Location1Painting::updateState()
{
	colliderManager->setCollider(0);
}

void Location1Painting::clickAction2()
{
}

void Location1Painting::clickAction0()
{
}

void Location1Painting::whatOnClick0()
{
}

void Location1Painting::whatOnClick()
{
}

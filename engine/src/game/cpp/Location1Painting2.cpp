#include "../game_all.h"

void Location1Painting2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_painting2");
	range = 5.0f;
}

void Location1Painting2::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("base_painting2")), true);
}

void Location1Painting2::updateState()
{
	colliderManager->setCollider(0);
}

void Location1Painting2::clickAction2()
{
}

void Location1Painting2::clickAction0()
{
}

void Location1Painting2::whatOnClick0()
{
}

void Location1Painting2::whatOnClick()
{
}

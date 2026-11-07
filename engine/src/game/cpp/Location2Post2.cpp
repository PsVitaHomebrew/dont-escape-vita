#include "../game_all.h"

void Location2Post2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_fridge_note1");
	range = 10.0f;
}

void Location2Post2::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("base_fridge_note2")), true);
}

void Location2Post2::updateState()
{
	colliderManager->setCollider(0);
}

void Location2Post2::clickAction2()
{
}

void Location2Post2::clickAction0()
{
}

void Location2Post2::whatOnClick0()
{
}

void Location2Post2::whatOnClick()
{
}

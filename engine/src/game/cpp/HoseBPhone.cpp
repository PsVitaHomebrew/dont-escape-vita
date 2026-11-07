#include "../game_all.h"

void HoseBPhone::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_phone");
	range = 200.0f;
}

void HoseBPhone::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_phone")), true, false, false, 150);
}

void HoseBPhone::gateIsOpen()
{
}

void HoseBPhone::gateIsOpening()
{
}

void HoseBPhone::updateState()
{
}

void HoseBPhone::clickAction2()
{
}

void HoseBPhone::clickAction0()
{
}

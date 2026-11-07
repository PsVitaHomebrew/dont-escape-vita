#include "../game_all.h"

void Location2Post1::Start()
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

void Location2Post1::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("base_fridge_note1")), true);
}

void Location2Post1::updateState()
{
	colliderManager->setCollider(0);
}

void Location2Post1::clickAction2()
{
}

void Location2Post1::clickAction0()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->page_turn_04);
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::world_labels, S("postnote1")), true, true, true, 200, 0.0f, 0.0f, 0.0f, 237.0f / 255.0f, 222.0f / 255.0f, 154.0f / 255.0f, 1.0f, false, true);
}

void Location2Post1::whatOnClick0()
{
}

void Location2Post1::whatOnClick()
{
}

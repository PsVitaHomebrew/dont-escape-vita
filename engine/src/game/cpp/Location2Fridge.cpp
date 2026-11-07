#include "../game_all.h"

void Location2Fridge::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action2_ne");
	animationFlip = true;
	useCurrentDirection = false;
	range = 1.0f;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_fridge");
	updateState();
}

void Location2Fridge::clickAction()
{
	PlayerController::wc->forceAnimation(S("stand_n"));
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("base_fridge"));
	timelineAction->actionWithText = false;
	timelineAction->function = [this](String a) { closeFridge(a); };
	Timeline::t->doNotUnlock = true;
	Timeline::t->addAction(timelineAction);
}

void Location2Fridge::closeSound()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fridge);
}

void Location2Fridge::closeFridge(String param)
{
	PlayerController::wc->forceAnimation(S("action2_ne"), true);
	gameObject->GetComponent<Animator>()->Play(S("FridgeDoorClose"));
}

void Location2Fridge::updateState()
{
}

void Location2Fridge::clickAction2()
{
}

void Location2Fridge::clickAction0()
{
	gameObject->GetComponent<Animator>()->Play(S("FridgeDoor"));
}

void Location2Fridge::whatOnClick0()
{
}

void Location2Fridge::whatOnClick()
{
}

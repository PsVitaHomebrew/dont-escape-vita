#include "../game_all.h"

void HuntersLodgeScratches::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_in_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_scratches");
	range = 1.0f;
}

void HuntersLodgeScratches::clickAction()
{
	GameDataController::gd->setObjective(S("hunters_lodge_scratches_found"), true);
	P<DialogueLine> dialogueLine = New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::actions, S("hunters_lodge_scratches")), [this](String param) { standup(param); });
	dialogueLine->actionWithText = false;
	Timeline::t->addDialogue(dialogueLine);
	Timeline::t->doNotUnlock = true;
	updateAll();
}

void HuntersLodgeScratches::standup(String param)
{
	PlayerController::pc->setBusy(true);
	PlayerController::wc->forceAnimation(S("kneel_out_n"));
}

void HuntersLodgeScratches::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("hunters_lodge_couch_moved")))
	{
		colliderManager->setCollider(-1);
	}
}

void HuntersLodgeScratches::clickAction2()
{
}

void HuntersLodgeScratches::clickAction0()
{
}

void HuntersLodgeScratches::whatOnClick0()
{
}

void HuntersLodgeScratches::whatOnClick()
{
}

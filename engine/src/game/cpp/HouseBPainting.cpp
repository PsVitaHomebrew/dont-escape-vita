#include "../game_all.h"

void HouseBPainting::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_painting");
	range = 10.0f;
}

void HouseBPainting::clickAction()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("house_b_painting"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	Timeline::t->addDialogueLines(list);
}

void HouseBPainting::gateIsOpen()
{
}

void HouseBPainting::gateIsOpening()
{
}

void HouseBPainting::updateState()
{
}

void HouseBPainting::clickAction2()
{
}

void HouseBPainting::clickAction0()
{
}

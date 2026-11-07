#include "../game_all.h"

void Outpost8EmptyPad::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = true;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_empty_pad");
	range = 100.0f;
}

void Outpost8EmptyPad::clickAction()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("outpost_empty_pad"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void Outpost8EmptyPad::updateState()
{
}

void Outpost8EmptyPad::clickAction2()
{
}

void Outpost8EmptyPad::clickAction0()
{
}

void Outpost8EmptyPad::whatOnClick0()
{
}

void Outpost8EmptyPad::whatOnClick()
{
}

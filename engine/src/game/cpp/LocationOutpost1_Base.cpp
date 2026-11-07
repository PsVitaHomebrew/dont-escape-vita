#include "../game_all.h"

void LocationOutpost1_Base::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_base_far");
	range = 100.0f;
}

void LocationOutpost1_Base::clickAction()
{
	if (!GameDataController::gd->getObjective(S("visited_outpost4")))
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("outpost_base_far"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
	else
	{
		List<P<DialogueLine>> list2 = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list2, S("outpost_base_far2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
		for (int j = 0; j < list2.Count(); j++)
		{
			Timeline::t->addDialogue(list2[j]);
		}
	}
}

void LocationOutpost1_Base::updateState()
{
}

void LocationOutpost1_Base::clickAction2()
{
}

void LocationOutpost1_Base::clickAction0()
{
}

void LocationOutpost1_Base::whatOnClick0()
{
}

void LocationOutpost1_Base::whatOnClick()
{
}

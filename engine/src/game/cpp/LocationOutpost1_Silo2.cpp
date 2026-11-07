#include "../game_all.h"

void LocationOutpost1_Silo2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_silo_far");
	range = 100.0f;
}

void LocationOutpost1_Silo2::clickAction()
{
	if (!GameDataController::gd->getObjective(S("visited_outpost4")))
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("outpost_silo_far2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
	else
	{
		List<P<DialogueLine>> list2 = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list2, S("outpost_silo_far4"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
		for (int j = 0; j < list2.Count(); j++)
		{
			Timeline::t->addDialogue(list2[j]);
		}
	}
}

void LocationOutpost1_Silo2::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_hatch_open")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void LocationOutpost1_Silo2::clickAction2()
{
}

void LocationOutpost1_Silo2::clickAction0()
{
}

void LocationOutpost1_Silo2::whatOnClick0()
{
}

void LocationOutpost1_Silo2::whatOnClick()
{
}

#include "../game_all.h"

void LocationOutpost1_Silo1::Start()
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

void LocationOutpost1_Silo1::clickAction()
{
	if (!GameDataController::gd->getObjective(S("visited_outpost4")))
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("outpost_silo_far1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
		{
			Vector3 color2 = Npc3Controller::getColor();
			P<TextFieldController> component2 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
			list.Add(New<DialogueLine>(component2, color2, GameStrings::getString(GameStrings::dialogues, S("outpost_silo_far1_cody")), nullptr));
		}
		if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
		{
			Vector3 color3 = Npc2Controller::getColor();
			P<TextFieldController> component3 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
			list.Add(New<DialogueLine>(component3, color3, GameStrings::getString(GameStrings::dialogues, S("outpost_silo_far1_barry")), nullptr));
		}
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
	else
	{
		List<P<DialogueLine>> list2 = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list2, S("outpost_silo_far3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
		for (int j = 0; j < list2.Count(); j++)
		{
			Timeline::t->addDialogue(list2[j]);
		}
	}
}

void LocationOutpost1_Silo1::updateState()
{
}

void LocationOutpost1_Silo1::clickAction2()
{
}

void LocationOutpost1_Silo1::clickAction0()
{
}

void LocationOutpost1_Silo1::whatOnClick0()
{
}

void LocationOutpost1_Silo1::whatOnClick()
{
}

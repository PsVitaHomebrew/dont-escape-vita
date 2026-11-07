#include "../game_all.h"

void CS1_Waypoint_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("machine_park");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 20.0f;
}

void CS1_Waypoint_2::clickAction()
{
	if (!GameDataController::gd->getObjective(S("cs_park_nogo")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 3)
	{
		P<DialogueLine> dl = New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::dialogues, S("cs_park_start")), nullptr);
		Timeline::t->addDialogue(dl);
		GameDataController::gd->setObjective(S("cs_park_nogo"), true);
		if ((GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive"))) || (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive"))))
		{
			dl = New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::dialogues, S("cs_park_multi")), nullptr);
			Timeline::t->addDialogue(dl);
		}
		else
		{
			dl = New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::dialogues, S("cs_park_single")), nullptr);
			Timeline::t->addDialogue(dl);
		}
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("cs_park_nogo"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
		{
			Vector3 color2 = GingerActionController::getColor();
			Vector3 color3 = Npc2Controller::getColor();
			component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
			P<TextFieldController> component2 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
			DialogueController::dc->initDialogue(list, S("cs_park_nogo_plus_barry"), component2, color3, component, color2);
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
		{
			Vector3 color4 = Npc3Controller::getColor();
			P<TextFieldController> component3 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
			DialogueController::dc->initDialogue(list, S("cs_park_nogo_plus_cody"), component3, color4, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
		}
		for (int i = 0; i < list.Count() - 1; i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		list[list.Count() - 1]->action = [this](String s) { goThere(s); };
		Timeline::t->addDialogue(list[list.Count() - 1]);
	}
	else
	{
		goThere(String::Empty);
	}
}

void CS1_Waypoint_2::goThere(String s)
{
	GameDataController::gd->setObjective(S("cs_arrive_from_inside"), false);
	if (!GameDataController::gd->getObjective(S("cs_safe")))
	{
		GameDataController::gd->setObjective(S("cs_crow_away"), false);
	}
	else
	{
		GameDataController::gd->setObjective(S("cs_crow_away"), true);
	}
	PlayerController::pc->spawnName = S("CS2_Waypoint_1");
	CurtainController::cc->fadeOut(S("CS2"), WalkController::Direction::E);
}

void CS1_Waypoint_2::updateState()
{
	if (!GameDataController::gd->getObjective(S("cs_park_nogo")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 3)
	{
		doubleClickCondition = S("impossible");
	}
	else
	{
		doubleClickCondition = S("visited_cs_2");
	}
}

void CS1_Waypoint_2::clickAction2()
{
}

void CS1_Waypoint_2::clickAction0()
{
}

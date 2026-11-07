#include "../game_all.h"

void Outpost7_RadarScreen::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_radar_screen");
	actionType = Type::NormalAction;
	trans_dir = WalkController_Direction::N;
	range = 1.0f;
	endView(String::Empty);
}

void Outpost7_RadarScreen::turn(String s)
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceDirection(NPCWalkController_Direction::E);
}

void Outpost7_RadarScreen::talkAboutRadarOnPlaneOn()
{
	String prefix = S("radar_repaired2");
	if (GameDataController::gd->getObjectiveDetail(S("map_airplane_revealed")) == TravelAgency::LOCATION_STATUS_UNDISCOVERED)
	{
		prefix = S("radar_repaired");
		GameDataController::gd->setObjectiveDetail(S("map_airplane_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
		GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceDirection(NPCWalkController_Direction::E);
	}
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	list[list.Count() - 1]->action = [this](String var) { endView(var); };
	for (int i = 0; i < list.Count(); i++)
	{
		if (i < list.Count() - 1)
		{
			list[i]->action = [this](String s) { turn(s); };
		}
		Timeline::t->addDialogue(list[i]);
	}
}

void Outpost7_RadarScreen::talkAboutRadarOnPlaneOff()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("radar_disabled"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	list[list.Count() - 1]->action = [this](String var) { endView(var); };
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void Outpost7_RadarScreen::talkAboutRadarOff()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceDirection(NPCWalkController_Direction::E);
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("radar_broken"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color, PlayerController::pc->textField, Vector3(1.0f, 0.5f, 0.5f));
	list[list.Count() - 1]->action = [this](String var) { endView(var); };
	for (int i = 0; i < list.Count(); i++)
	{
		if (i < list.Count() - 1)
		{
			list[i]->action = [this](String s) { turn(s); };
		}
		Timeline::t->addDialogue(list[i]);
	}
}

void Outpost7_RadarScreen::clickAction()
{
	radar_background->set_enabled(true);
	radar_dot->set_enabled(false);
	radar_swipe1->set_enabled(false);
	radar_swipe2->set_enabled(false);
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss(true);
	if (!GameDataController::gd->getObjective(S("plane_transponder_disabled")) && GameDataController::gd->getObjective(S("outpost_radar_repaired")))
	{
		radar_swipe1->set_enabled(true);
		radar_swipe2->set_enabled(true);
		radar_dot->set_enabled(true);
		aS->set_volume(1.0f);
		talkAboutRadarOnPlaneOn();
	}
	else if (GameDataController::gd->getObjective(S("plane_transponder_disabled")) && GameDataController::gd->getObjective(S("outpost_radar_repaired")))
	{
		radar_swipe1->set_enabled(true);
		radar_swipe2->set_enabled(true);
		radar_dot->set_enabled(false);
		talkAboutRadarOnPlaneOff();
	}
	else
	{
		talkAboutRadarOff();
	}
}

void Outpost7_RadarScreen::endView(String var)
{
	radar_background->set_enabled(false);
	radar_dot->set_enabled(false);
	radar_swipe1->set_enabled(false);
	radar_swipe2->set_enabled(false);
	updateState();
}

void Outpost7_RadarScreen::updateState()
{
	if (!GameDataController::gd->getObjective(S("plane_transponder_disabled")) && GameDataController::gd->getObjective(S("outpost_radar_repaired")))
	{
		GetComponent<Animator>()->Play(S("small_radar"));
		aS->set_volume(0.75f);
	}
	else if (GameDataController::gd->getObjective(S("plane_transponder_disabled")) && GameDataController::gd->getObjective(S("outpost_radar_repaired")))
	{
		GetComponent<Animator>()->Play(S("small_radar"));
		aS->set_volume(0.0f);
	}
	else
	{
		GetComponent<Animator>()->Play(S("small_radar_broken"));
		aS->set_volume(0.0f);
	}
}

void Outpost7_RadarScreen::clickAction2()
{
}

void Outpost7_RadarScreen::clickAction0()
{
}

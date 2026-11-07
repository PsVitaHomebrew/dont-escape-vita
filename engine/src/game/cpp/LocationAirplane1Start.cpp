#include "../game_all.h"

void LocationAirplane1Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 15.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("dirt"));
	PlayerController::wc->shadow->scaleFactor = 0.25f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	if (!GameDataController::gd->getObjective(S("visited_airplane1")))
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("airplane_welcome"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
		{
			Vector3 color2 = GingerActionController::getColor();
			Vector3 color3 = Npc2Controller::getColor();
			component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
			P<TextFieldController> component2 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
			DialogueController::dc->initDialogue(list, S("airplane_welcome_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color2, component2, color3);
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
		{
			Vector3 color4 = Npc3Controller::getColor();
			P<TextFieldController> component3 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
			DialogueController::dc->initDialogue(list, S("airplane_welcome_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color4, component3, color4);
		}
		for (int i = 0; i < list.Count() - 1; i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		Timeline::t->addDialogue(list[list.Count() - 1]);
	}
	GameDataController::gd->setObjective(S("visited_airplane1"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_4a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_metal, 0.9f);
}

void LocationAirplane1Start::Update()
{
}

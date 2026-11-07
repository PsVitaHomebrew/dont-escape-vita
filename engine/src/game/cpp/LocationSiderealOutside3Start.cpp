#include "../game_all.h"

void LocationSiderealOutside3Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.01f;
	PlayerController::wc->shadow->fadeRateH = 0.001f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 20.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.4f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 240.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Off);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && !GameDataController::gd->getObjective(S("restaurant_sarge_encountered")) && GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		GameDataController::gd->setObjective(S("restaurant_sarge_awaits"), true);
	}
	GameDataController::gd->setObjective(S("visited_sidereal_outside_3"), true);
	if (!GameDataController::gd->getObjective(S("sidereal_roof_collapsed")) || GameDataController::gd->getObjective(S("dialogue_ginger_reunited")))
	{
		return;
	}
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	List<P<DialogueLine>> list2 = List<P<DialogueLine>>::New();
	List<P<DialogueLine>> list3 = List<P<DialogueLine>>::New();
	if (GameDataController::gd->getObjective(S("cody_warned")))
	{
		DialogueController::dc->initDialogue(list2, S("cody_sidereal_reunion"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
		if (GameDataController::gd->getObjective(S("barry_warned")))
		{
			list2[1]->text = GameStrings::getString(GameStrings::dialogues, S("cody_sidereal_reunion_alt"));
		}
	}
	if (GameDataController::gd->getObjective(S("barry_warned")))
	{
		DialogueController::dc->initDialogue(list3, S("barry_sidereal_reunion"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
		if (GameDataController::gd->getObjective(S("cody_warned")))
		{
			list3[0]->text = GameStrings::getString(GameStrings::dialogues, S("barry_sidereal_reunion_alt"));
		}
	}
	String prefix = ((GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1) ? S("ginger_sidereal_reunion_barry") : ((GameDataController::gd->getObjectiveDetail(S("npc3_alive")) != 1) ? S("ginger_sidereal_reunion") : S("ginger_sidereal_reunion_cody")));
	DialogueController::dc->initDialogue(list, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	DialogueController::dc->initDialogue(list, S("ginger_sidereal_reunion_map"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		DialogueController::dc->initDialogue(list, S("ginger_sidereal_reunion_bandits"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	}
	else
	{
		DialogueController::dc->initDialogue(list, S("ginger_sidereal_reunion_storm"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	}
	list[2]->action = [this](String a) { uuuu(a); };
	for (int i = 0; i < list2.Count(); i++)
	{
		Timeline::t->addDialogue(list2[i]);
	}
	for (int j = 0; j < list3.Count(); j++)
	{
		Timeline::t->addDialogue(list3[j]);
	}
	for (int k = 0; k < list.Count(); k++)
	{
		Timeline::t->addDialogue(list[k]);
	}
}

void LocationSiderealOutside3Start::uuuu(String a)
{
	GameDataController::gd->setObjective(S("dialogue_ginger_reunited"), true);
	GameDataController::gd->setObjective(S("cody_warned"), false);
	GameDataController::gd->setObjective(S("barry_warned"), false);
}

void LocationSiderealOutside3Start::Update()
{
}

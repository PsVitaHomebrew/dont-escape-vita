#include "../game_all.h"

void LocationSiderealF2CStart::Start()
{
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::StoneCorridor);
	GameDataController::gd->setObjective(S("visited_sidereal_f2c"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_mystery);
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) == 50 && GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) == 10)
	{
		darkness->set_enabled(false);
		overLight->set_enabled(true);
		light1->set_enabled(true);
		doorlight->set_enabled(true);
		PlayerController::wc->shadow->fadeRateV = 0.001f;
		PlayerController::wc->shadow->fadeRateH = 0.005f;
		PlayerController::wc->shadowOffsetY = 2;
		PlayerController::wc->shadow->skewFactor = 40.0f;
		PlayerController::wc->shadow->skewFactor2 = 0.0f;
		PlayerController::wc->shadow->startAlpha = 0.75f;
		PlayerController::wc->shadow->scaleFactor = 0.5f;
		PlayerController::wc->shadow->downwards = true;
		PlayerController::wc->shadow->source = 10.0f;
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->buzz, 0.5f);
	}
	else
	{
		darkness->set_enabled(true);
		light1->set_enabled(false);
		overLight->set_enabled(false);
		doorlight->set_enabled(false);
		PlayerController::wc->shadow->fadeRateV = 0.01f;
		PlayerController::wc->shadow->fadeRateH = 0.005f;
		PlayerController::wc->shadowOffsetY = 2;
		PlayerController::wc->shadow->skewFactor = 40.0f;
		PlayerController::wc->shadow->skewFactor2 = 0.0f;
		PlayerController::wc->shadow->startAlpha = 0.5f;
		PlayerController::wc->shadow->scaleFactor = 0.5f;
		PlayerController::wc->shadow->downwards = true;
		PlayerController::wc->shadow->source = 130.0f;
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
	}
	PlayerController::pc->copySettingsToNPCs();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("place_sidereal_auto_cody")))
	{
		GameDataController::gd->setObjective(S("place_sidereal_auto_cody"), true);
		GameDataController::gd->setObjective(S("place_sidereal_auto_barry"), true);
		Vector3 color = GingerActionController::getColor();
		Vector3 color2 = Npc3Controller::getColor();
		PlayerController::pc->forceAnimation(S("stand_s"));
		P<TextFieldController> component = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("place_sidereal_auto_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color, component, color2);
		list[4]->action = [this](String s) { codyRun(s); };
		list[0]->action = [this](String var) { turn_south(var); };
		list[0]->actionWithText = true;
	}
	if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("place_sidereal_auto_barry")))
	{
		GameDataController::gd->setObjective(S("place_sidereal_auto_barry"), true);
		GameDataController::gd->setObjective(S("place_sidereal_auto_cody"), true);
		Vector3 color3 = GingerActionController::getColor();
		Vector3 color4 = Npc2Controller::getColor();
		PlayerController::pc->forceAnimation(S("stand_s"));
		P<TextFieldController> component2 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("place_sidereal_auto_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color3, component2, color4);
		list[0]->action = [this](String var) { turn_south(var); };
		list[0]->actionWithText = true;
	}
	if (GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1 && GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("place_sidereal_auto2_cody")) && GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		GameDataController::gd->setObjective(S("place_sidereal_auto2_cody"), true);
		GameDataController::gd->setObjective(S("place_sidereal_auto2_barry"), true);
		Vector3 color5 = GingerActionController::getColor();
		Vector3 color6 = Npc3Controller::getColor();
		PlayerController::pc->forceAnimation(S("stand_se"));
		P<TextFieldController> component3 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("place_sidereal_auto2_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color5, component3, color6);
		list[0]->action = [this](String var) { turn_south_east(var); };
		list[0]->actionWithText = true;
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1 && GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("place_sidereal_auto2_barry")) && GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		GameDataController::gd->setObjective(S("place_sidereal_auto2_barry"), true);
		GameDataController::gd->setObjective(S("place_sidereal_auto2_cody"), true);
		Vector3 color7 = GingerActionController::getColor();
		Vector3 color8 = Npc2Controller::getColor();
		P<TextFieldController> component4 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("place_sidereal_auto2_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color7, component4, color8);
		list[0]->action = [this](String var) { turn_south_east(var); };
		list[0]->actionWithText = true;
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	if (list.Count() == 0)
	{
		PlayerController::pc->setBusy(false);
	}
}

void LocationSiderealF2CStart::codyRun(String s)
{
	cody = GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>();
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setSimpleTargetV3(GameObject::Find(S("CodyRunAway"))->transform->get_position());
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("cody_run"), true);
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->speed = GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->MAX_SPEED * 1.5f;
}

void LocationSiderealF2CStart::Update()
{
	if (cody != nullptr && Mathf::Abs(cody->currentXY.x - PlayerController::wc->currentXY.x) < 12.0f && cody->currentXY.y - PlayerController::wc->currentXY.y > 0.0f)
	{
		cody->forceAnimation(S("stand_se"));
		cody = nullptr;
	}
}

void LocationSiderealF2CStart::turn_south(String var)
{
	PlayerController::pc->forceAnimation(S("stand_s"));
}

void LocationSiderealF2CStart::turn_south_east(String var)
{
	PlayerController::pc->forceAnimation(S("stand_se"));
}

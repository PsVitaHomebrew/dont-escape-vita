#include "../game_all.h"

void LocationOutpost5Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.006f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 70.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 200.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Hallway);
	PlayerController::wc->shadow->scaleFactor = 0.25f;
	PlayerController::wc->shadow->downwards = true;
	codyRun = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	firstTime = false;
	lights = GameDataController::gd->getObjectiveDetail(S("outpost_underground_light"));
	light1->set_enabled(false);
	light2->set_enabled(false);
	light3->set_enabled(false);
	if (!GameDataController::gd->getObjective(S("visited_outpost5")))
	{
		firstTime = true;
		PlayerController::pc->setBusy(true);
		Invoke(S("walkthere"), 0.01f);
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.8f;
		light1->set_enabled(true);
		light2->set_enabled(false);
		light3->set_enabled(false);
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->speed = 2.0f;
		}
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->neon_on);
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_main, false);
	}
	else
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	}
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->buzz, 0.3f);
}

void LocationOutpost5Start::forceTalk1()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	Vector3 color2 = Npc2Controller::getColor();
	Vector3 color3 = Npc3Controller::getColor();
	P<TextFieldController> component2 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
	P<TextFieldController> component3 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		list.Add(New<DialogueLine>(component3, color3, GameStrings::getString(GameStrings::dialogues, S("outpost_spaceship_discovered_Cody_1")), nullptr));
	}
	DialogueController::dc->initDialogue(list, S("outpost_spaceship_discovered_A"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		list.Add(New<DialogueLine>(component3, color3, GameStrings::getString(GameStrings::dialogues, S("outpost_spaceship_discovered_Cody_2")), nullptr));
	}
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		list.Add(New<DialogueLine>(component2, color2, GameStrings::getString(GameStrings::dialogues, S("outpost_spaceship_discovered_Barry_1")), nullptr));
	}
	DialogueController::dc->initDialogue(list, S("outpost_spaceship_discovered_B"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		list.Add(New<DialogueLine>(component3, color3, GameStrings::getString(GameStrings::dialogues, S("outpost_spaceship_discovered_Cody_3")), nullptr));
	}
	DialogueController::dc->initDialogue(list, S("outpost_spaceship_discovered_C"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		list.Add(New<DialogueLine>(component2, color2, GameStrings::getString(GameStrings::dialogues, S("outpost_spaceship_discovered_Barry_2")), nullptr));
		list.Add(New<DialogueLine>(component2, color2, GameStrings::getString(GameStrings::dialogues, S("outpost_spaceship_discovered_Barry_3")), nullptr));
	}
	DialogueController::dc->initDialogue(list, S("outpost_spaceship_discovered_D"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		list.Add(New<DialogueLine>(component3, color3, GameStrings::getString(GameStrings::dialogues, S("outpost_spaceship_discovered_Cody_4")), nullptr));
	}
	DialogueController::dc->initDialogue(list, S("outpost_spaceship_discovered_E"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		list.Add(New<DialogueLine>(component2, color2, GameStrings::getString(GameStrings::dialogues, S("outpost_spaceship_discovered_Barry_4")), nullptr));
	}
	else
	{
		DialogueController::dc->initDialogue(list, S("outpost_spaceship_discovered_F"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	}
	DialogueController::dc->initDialogue(list, S("outpost_spaceship_discovered_G"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void LocationOutpost5Start::walkthere()
{
	PlayerController::wc->setSimpleTargetV3(playerTarget->transform->get_position());
	PlayerController::pc->setBusy(true);
}

void LocationOutpost5Start::Update()
{
	if (!firstTime)
	{
		return;
	}
	if (lights == 2 && PlayerController::wc->currentXY.x < 160.0f)
	{
		GameDataController::gd->setObjectiveDetail(S("outpost_underground_light"), 3);
		lights = 3;
		light1->set_enabled(false);
		light2->set_enabled(true);
		light3->set_enabled(false);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->spotlight);
	}
	if (lights == 3 && PlayerController::wc->currentXY.x < 140.0f)
	{
		GameDataController::gd->setObjectiveDetail(S("outpost_underground_light"), 4);
		lights = 4;
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setSimpleTargetV3(GameObject::Find(S("CodyTarget"))->transform->get_position());
			GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->speed = 5.0f;
			GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("cody_run"), true);
			codyRun = true;
			codyWalker = GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>();
		}
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->spotlight);
		light1->set_enabled(false);
		light2->set_enabled(false);
		light3->set_enabled(true);
		forceTalk1();
	}
	if (codyRun && codyWalker->currentXY.x < 115.0f)
	{
		codyRun = false;
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("cody_run_glass"), true);
	}
	if (lights == 4 && PlayerController::wc->currentXY.x < 120.0f)
	{
		GameDataController::gd->setObjectiveDetail(S("outpost_underground_light"), 5);
		lights = 5;
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->spotlight);
		light1->set_enabled(false);
		light2->set_enabled(false);
		light3->set_enabled(false);
	}
	if (PlayerController::wc->currentXY.x < 60.0f)
	{
		GameDataController::gd->setObjective(S("visited_outpost5"), true);
		GameDataController::gd->setObjective(S("outpost_spaceship_discovered"), false);
		firstTime = false;
		PlayerController::pc->setBusy(false);
		PlayerController::wc->fullStop();
		PlayerController::wc->forceAnimation(S("stand_ne"), true);
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	}
}

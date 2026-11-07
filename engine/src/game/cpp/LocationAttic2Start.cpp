#include "../game_all.h"

void LocationAttic2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.04f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -20.0f;
	PlayerController::wc->shadow->startAlpha = 0.75f;
	PlayerController::wc->shadow->source = 140.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::WOOD);
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_attic2"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_5a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.5f);
	if (!GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
	{
		PlayerController::pc->setBusy(true);
		Invoke(S("forceTalk0"), 0.01f);
		Invoke(S("forceTalk"), 1.15f);
		PlayerController::wc->currentXY = ScreenControler::roundToNearestFullPixel(GameObject::Find(S("WalkToGunStart"))->transform->get_position());
	}
	destroyed->set_enabled(false);
	shadow->set_enabled(true);
	shadow2->set_enabled(false);
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
	{
		destroyed->set_enabled(true);
		shadow->set_enabled(false);
		shadow2->set_enabled(true);
		holes->set_enabled(false);
		rays->set_enabled(false);
	}
	else if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		holes->set_enabled(true);
		rays->set_enabled(true);
	}
	else
	{
		holes->set_enabled(false);
		rays->set_enabled(false);
	}
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("helicopter_cody")))
	{
		GameDataController::gd->setObjective(S("helicopter_cody"), true);
		Vector3 color = GingerActionController::getColor();
		Vector3 color2 = Npc3Controller::getColor();
		P<TextFieldController> component = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("helicopter_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color, component, color2);
	}
	if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("helicopter_barry")))
	{
		GameDataController::gd->setObjective(S("helicopter_barry"), true);
		Vector3 color3 = GingerActionController::getColor();
		Vector3 color4 = Npc2Controller::getColor();
		P<TextFieldController> component2 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("helicopter_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color3, component2, color4);
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void LocationAttic2Start::Update()
{
	if (!GameDataController::gd->getObjective(S("dialogue_ginger_intro")) && PlayerController::wc->currentXY.x <= ScreenControler::roundToNearestFullPixel(GameObject::Find(S("WalkToGun"))->transform->get_position()).x)
	{
		PlayerController::wc->forceAnimation(S("stand_se"), true);
	}
}

void LocationAttic2Start::forceTalk0()
{
	PlayerController::pc->setBusy(true);
	PlayerController::wc->setSimpleTarget(ScreenControler::roundToNearestFullPixel(GameObject::Find(S("WalkToGun"))->transform->get_position()));
}

void LocationAttic2Start::forceTalk()
{
	PlayerController::pc->setBusy(true);
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->npcClickAction(String::Empty);
}

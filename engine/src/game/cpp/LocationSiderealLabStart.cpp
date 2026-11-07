#include "../game_all.h"

void LocationSiderealLabStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.03f;
	PlayerController::wc->shadow->fadeRateH = 0.01f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 40.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.7f;
	PlayerController::wc->shadow->scaleFactor = 0.4f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 120.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Cave);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
	GameDataController::gd->setObjective(S("visited_sidereal_lab13"), true);
	if (GameDataController::gd->getItemData(S("pills"))->droppedLocation == S("inventory") && !GameDataController::gd->getObjective(S("dialogue_ginger_pills")))
	{
		GameDataController::gd->setObjective(S("dialogue_ginger_pills"), true);
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("ginger_pills_here"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor());
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
}

void LocationSiderealLabStart::Update()
{
}

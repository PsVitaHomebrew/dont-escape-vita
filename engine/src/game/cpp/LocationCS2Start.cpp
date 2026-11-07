#include "../game_all.h"

void LocationCS2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.01f;
	PlayerController::wc->shadow->fadeRateH = 0.001f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 10.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.4f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 240.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::ROAD, AudioReverbPreset::Off);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_metal, 1.0f);
	GameDataController::gd->setObjective(S("visited_cs_2"), true);
	shootArea = false;
	Invoke(S("shootOrNot"), 0.25f);
	if (GameDataController::gd->getObjective(S("cs_crow_away")))
	{
		crow->Play(S("crow_empty"));
	}
	else
	{
		crow->Play(S("crow_peck"));
	}
	if (!GameDataController::gd->getObjective(S("cs_thug_shot")) && GameDataController::gd->getObjective(S("cs_arrive_from_inside")) && !GameDataController::gd->getObjective(S("cs_safe")))
	{
		thug->Play(S("thug_reload"));
	}
	else if (!GameDataController::gd->getObjective(S("cs_thug_shot")) && !GameDataController::gd->getObjective(S("cs_safe")))
	{
		thug->Play(S("thug_watch"));
	}
	else
	{
		thug->gameObject->GetComponent<CSThugSprite>()->hide();
	}
	if (GameDataController::gd->getObjective(S("cs_thug_shot")) || GameDataController::gd->getCurrentDay() != 3 || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 0)
	{
		exitcs1->doubleClickCondition = S("visited_cs_1");
		exitcs3->doubleClickCondition = S("visited_cs_3");
	}
	else if (PlayerController::wc->currentXY.x > 120.0f)
	{
		exitcs1->doubleClickCondition = String::Empty;
		exitcs3->doubleClickCondition = S("visited_cs_3");
	}
	else
	{
		exitcs1->doubleClickCondition = S("visited_cs_1");
		exitcs3->doubleClickCondition = String::Empty;
	}
}

void LocationCS2Start::shootOrNot()
{
	MonoBehaviour::print(S("Shoot or not"));
	if (!GameDataController::gd->getObjective(S("cs_safe")))
	{
		if (shootArea && !playerShot && !GameDataController::gd->getObjective(S("cs_guard_distracted")) && !GameDataController::gd->getObjective(S("cs_arrive_from_inside")) && !GameDataController::gd->getObjective(S("cs_thug_shot")))
		{
			PlayerController::wc->fullStop(true);
			PlayerController::pc->setBusy(true);
			PlayerController::wc->forceAnimation(S("surprised_ne"), true);
			PlayerController::pc->interruptDialogueProbablyToKillPlayer();
			thug->Play(S("thug_shoot"));
			shootArea = false;
			playerShot = true;
		}
		Invoke(S("shootOrNot"), 0.5f);
	}
}

void LocationCS2Start::Update()
{
}

#include "../game_all.h"

void LoctionAttic1Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.1f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 5.0f;
	PlayerController::wc->shadow->startAlpha = 0.75f;
	PlayerController::wc->shadow->source = 240.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::WOOD);
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_attic1"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_5a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.5f);
	backgroundCheck();
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
	{
		destroyed->set_enabled(true);
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
}

void LoctionAttic1Start::Update()
{
}

void LoctionAttic1Start::backgroundCheck()
{
	if (!GameDataController::gd->getObjective(S("attic_hatch_open")))
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane00a"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane00b"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane00a"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane00b"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

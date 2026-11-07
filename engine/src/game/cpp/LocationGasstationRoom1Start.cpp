#include "../game_all.h"

void LocationGasstationRoom1Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.004f;
	PlayerController::wc->shadow->fadeRateH = 0.004f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 20.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 100.0f;
	PlayerController::ssg->setStepType(S("normal"));
	GameDataController::gd->setObjective(S("visited_gasstationRoom1"), true);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.25f);
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane00"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane00b"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane00_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane00b_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane01_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane00"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane00b"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane00_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane00b_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane01_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::wc->speed = 0.0f;
	}
	if (GameDataController::gd->getCurrentDay() == 1 && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_scare_loop, true, 1.0f, 3.0f);
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getObjective(S("sidereal_base_located")) && !GameDataController::gd->getObjective(S("gasstation_sarge_reason")))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		JukeboxMusic::jb->changeMusic(nullptr);
	}
	else
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_3a);
	}
}

void LocationGasstationRoom1Start::Update()
{
}

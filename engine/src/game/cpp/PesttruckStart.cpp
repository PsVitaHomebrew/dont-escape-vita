#include "../game_all.h"

void PesttruckStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.001f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -20.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 0.0f;
	PlayerController::ssg->setStepType(S("normal"));
	GameDataController::gd->setObjective(S("visited_pestTruck"), true);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_metal_inside, 1.0f);
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane_bugs"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane_gas"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane_bugs"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane_gas"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane_bugs"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane_gas"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void PesttruckStart::Update()
{
}

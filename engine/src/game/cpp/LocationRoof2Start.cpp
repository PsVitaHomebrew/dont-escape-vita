#include "../game_all.h"

void LocationRoof2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.1f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 5.0f;
	PlayerController::wc->shadow->startAlpha = 0.75f;
	PlayerController::wc->shadow->source = 240.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::METAL);
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED / 2.0f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.75f);
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_roof2"), true);
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.5f);
	if (GameDataController::gd->getObjective(S("base_fireplace_lit")))
	{
		GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->started = true;
		GameObject::Find(S("Smoke2"))->GetComponent<ParticleGenerator>()->started = true;
	}
	else if (!GameDataController::gd->getObjective(S("base_fireplace_lit")))
	{
		GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Smoke2"))->GetComponent<ParticleGenerator>()->started = false;
	}
	if (GameDataController::gd->getCurrentDay() == 2)
	{
		moon->set_sprite(moon2);
	}
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		moon->set_sprite(moon3);
	}
	if (GameDataController::gd->getCurrentDay() == 4)
	{
		moon->set_sprite(moon4);
	}
	if (GameDataController::gd->getCurrentDay() == 2)
	{
		moong->set_sprite(moon2g);
	}
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		moong->set_sprite(moon3g);
	}
	if (GameDataController::gd->getCurrentDay() == 4)
	{
		moong->set_sprite(moon4g);
	}
	if (GameDataController::gd->gameTime < 510 || GameDataController::gd->gameTime >= 1050)
	{
		moong->set_enabled(true);
	}
	else
	{
		moong->set_enabled(false);
	}
	destroyedRoof->set_enabled(false);
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		destroyedRoof->set_enabled(true);
	}
	PlayerController::pc->allowDrop = false;
}

void LocationRoof2Start::Update()
{
}

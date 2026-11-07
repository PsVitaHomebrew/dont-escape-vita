#include "../game_all.h"

void LocationBaseBathroomStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.004f;
	PlayerController::wc->shadow->fadeRateH = 0.004f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 40.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 140.0f;
	PlayerController::ssg->setStepType2(S("normal"), AudioReverbPreset::Bathroom);
	GameDataController::gd->setObjective(S("visited_baseBathroom"), true);
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_5a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.25f);
	GameObject::Find(S("thug"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("thug_to_kill_bathroom")))
	{
		GameObject::Find(S("thug"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("thug"))->GetComponent<Animator>()->set_enabled(true);
		startTalk();
	}
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("thug_killed_bathroom")))
	{
		GameObject::Find(S("thug"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("thug"))->GetComponent<Animator>()->set_enabled(false);
		GameObject::Find(S("thug"))->GetComponent<SpriteRenderer>()->set_sprite(ded);
	}
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		holes->set_enabled(true);
		rays->set_enabled(true);
		rays2->set_enabled(true);
	}
	else
	{
		holes->set_enabled(false);
		rays->set_enabled(false);
		rays2->set_enabled(false);
	}
}

void LocationBaseBathroomStart::startTalk()
{
	PlayerController::wc->forceAnimation(S("stand_se"), true);
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->npcClickAction(String::Empty);
}

void LocationBaseBathroomStart::Update()
{
}

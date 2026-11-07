#include "../game_all.h"

void LocationMoonbase2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 20.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->source = 120.0f;
	PlayerController::wc->shadow->scaleFactor = 0.7f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	audioSouruce->set_loop(true);
	audioSouruce->set_clip(SoundsManagerController::sm->moon);
	audioSouruce->set_volume(1.0f);
	audioSouruce->Play();
	if (GameDataController::gd->getObjective(S("moon_light_failed")))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_attack2, true, 0.0f, 1.0f);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->moon, 1.0f, AudioReverbPreset::Bathroom);
	}
	else
	{
		JukeboxMusic::jb->changeMusic(nullptr);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->pc_noise, 0.75f, AudioReverbPreset::Bathroom);
	}
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Bathroom);
	GameDataController::gd->setObjective(S("visited_moonbase2"), true);
	time = Random::Range(3.0f, 8.0f);
	for (int i = 0; i < kawalkiKsiezyca.Count(); i++)
	{
		kawalkiFinish[i] = kawalkiKsiezyca[i]->transform->get_position().y;
		kawalkiKsiezyca[i]->transform->set_position(Vector3(0.0f, 0.0f, kawalkiKsiezyca[i]->transform->get_position().z));
	}
	destIndex1 = GameDataController::gd->getObjectiveIndex(S("moonfall_progress_3"));
	destIndex2 = GameDataController::gd->getObjectiveIndex(S("moonfall_progress_4"));
	destructionProgress = GameDataController::gd->objectives[destIndex1]->detail;
	destructionProgress2 = GameDataController::gd->objectives[destIndex2]->detail;
	destructionProgress /= 1000.0f;
	destructionProgress2 /= 1000.0f;
	if (GameDataController::gd->getObjective(S("moon_card_taken")))
	{
		startdestruction1 = true;
	}
	else
	{
		startdestruction1 = false;
	}
	startdestruction2 = startdestruction1;
	cloudProgress1 = Random::Range(0.0f, 1.0f);
	cloudProgress2 = Random::Range(0.0f, 1.0f);
	windowMayCrack = false;
	if (GameDataController::gd->getObjective(S("moon_light_restored")) && !GameDataController::gd->getObjective(S("moon_window_cracked")))
	{
		windowMayCrack = true;
	}
}

void LocationMoonbase2Start::Update()
{
	secToSave += Time::get_deltaTime();
	if (secToSave > 1.0f)
	{
		int detail = (int)(destructionProgress * 1000.0f);
		int detail2 = (int)(destructionProgress2 * 1000.0f);
		secToSave = 0.0f;
		GameDataController::gd->objectives[destIndex1]->detail = detail;
		GameDataController::gd->objectives[destIndex2]->detail = detail2;
	}
	time -= Time::get_deltaTime();
	if (time <= 0.0f)
	{
		time = Random::Range(1.0f, 10.0f);
		float num = Random::Range(0.2f, 3.0f);
		if (num < 1.0f)
		{
			rumbler->PlayOneShot(SoundsManagerController::sm->rumble_2s);
		}
		else
		{
			rumbler->PlayOneShot(SoundsManagerController::sm->rumble_4s);
		}
		rumbler->set_pitch(Random::Range(0.9f, 1.1f));
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->needShake = num;
	}
	if (windowMayCrack && PlayerController::wc->currentXY.x < 160.0f)
	{
		windowMayCrack = false;
		GameDataController::gd->setObjective(S("moon_window_cracked"), true);
		GameObject::Find(S("Location"))->transform->Find(S("plane00a"))->GetComponent<LocationMoonbase2Window>()->crack();
	}
	pg1->maxParticles = (int)(destructionProgress2 * 100.0f) * 2;
	pg2->maxParticles = (int)(destructionProgress2 * 100.0f) * 2;
	pg1->speedYMax = (int)(destructionProgress2 * 10.0f) + 1;
	pg2->speedYMax = (int)(destructionProgress2 * 10.0f) + 1;
	pg3->maxParticles = (int)(destructionProgress2 * 40.0f) - 20;
	if (pg3->maxParticles < 0)
	{
		pg3->maxParticles = 0;
	}
	pg4->maxParticles = (int)(destructionProgress2 * 40.0f) - 20;
	if (pg4->maxParticles < 0)
	{
		pg4->maxParticles = 0;
	}
	cloudProgress1 += Time::get_deltaTime() * (0.23f * destructionProgress2 * 0.5f);
	cloudProgress2 += Time::get_deltaTime() * (0.19f * destructionProgress2 * 0.5f);
	if (cloudProgress1 >= 1.0f)
	{
		cloudProgress1--;
	}
	if (cloudProgress2 >= 1.0f)
	{
		cloudProgress2--;
	}
	if (startdestruction1)
	{
		if (destructionProgress2 < 0.25f)
		{
			destructionProgress2 += Time::get_deltaTime() * 0.02f;
		}
		else if (destructionProgress2 < 0.5f)
		{
			destructionProgress2 += Time::get_deltaTime() * 0.015f;
		}
		else if (destructionProgress2 < 0.75f)
		{
			destructionProgress2 += Time::get_deltaTime() * 0.01f;
		}
		else if (destructionProgress2 < 0.8f)
		{
			destructionProgress2 += Time::get_deltaTime() * 0.005f;
		}
		else
		{
			destructionProgress2 += Time::get_deltaTime() * 0.002f;
		}
	}
	if (startdestruction2 && (double)destructionProgress2 > 0.75)
	{
		destructionProgress += Time::get_deltaTime() * 0.05f;
	}
	if (destructionProgress > 1.0f)
	{
		destructionProgress = 1.0f;
	}
	if (destructionProgress2 > 1.0f)
	{
		destructionProgress2 = 1.0f;
	}
	for (int i = 0; i < 7; i++)
	{
		kawalkiKsiezyca[i]->transform->set_position(Vector3(0.0f, kawalkiFinish[i] * destructionProgress, kawalkiKsiezyca[i]->transform->get_position().z));
		kawalkiKsiezyca[i]->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(kawalkiKsiezyca[i]->transform->get_position().x, kawalkiKsiezyca[i]->transform->get_position().y, kawalkiKsiezyca[i]->transform->get_position().z)));
	}
	earth->transform->set_position(Vector3(0.0f, 1.0f * destructionProgress2, earth->transform->get_position().z));
	earth->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(earth->transform->get_position().x, earth->transform->get_position().y, earth->transform->get_position().z)));
	moon_shadow->transform->set_position(Vector3(0.0f, 1.025f * destructionProgress2, moon_shadow->transform->get_position().z));
	moon_shadow->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(moon_shadow->transform->get_position().x, moon_shadow->transform->get_position().y, moon_shadow->transform->get_position().z)));
	chmura1->transform->set_position(Vector3(-2.2f + cloudProgress1 * 4.4f, chmura1->transform->get_position().y, chmura1->transform->get_position().z));
	chmura1->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(chmura1->transform->get_position().x, earth->transform->get_position().y - 0.45f, 0.5f)));
	chmura2->transform->set_position(Vector3(2.2f - cloudProgress2 * 4.4f, earth->transform->get_position().y, chmura2->transform->get_position().z));
	chmura2->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(chmura2->transform->get_position().x, chmura2->transform->get_position().y - 0.45f, 0.55f)));
}

#include "../game_all.h"

void LocationMoon1Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 15.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::wc->shadow->scaleFactor = 0.25f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED / 2.0f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.5f);
	PlayerController::pc->copySettingsToNPCs();
	audioSouruce->set_loop(true);
	audioSouruce->set_clip(SoundsManagerController::sm->moon);
	audioSouruce->set_volume(1.0f);
	audioSouruce->Play();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->suit_breathing, 0.75f, AudioReverbPreset::Underwater);
	PlayerController::ssg->setStepType2(StepSoundGenerator::MOON, AudioReverbPreset::Underwater);
	time = Random::Range(3.0f, 8.0f);
	PlayerController::wc->suit = true;
	PlayerController::wc->forceAnimation(S("action_stnd_s"), false, false, false);
}

void LocationMoon1Start::Update()
{
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
}

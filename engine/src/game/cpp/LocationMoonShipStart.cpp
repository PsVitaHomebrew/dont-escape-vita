#include "../game_all.h"

void LocationMoonShipStart::Start()
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
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	audioSouruce->set_loop(true);
	audioSouruce->set_clip(SoundsManagerController::sm->moon);
	audioSouruce->set_volume(0.5f);
	audioSouruce->Play();
	GameDataController::gd->setObjective(S("visited_moon_ship"), true);
	updateThings();
}

void LocationMoonShipStart::updateThings()
{
	JukeboxMusic::jb->changeMusic(nullptr);
	if (GameDataController::gd->getObjective(S("moon_door_open")))
	{
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->suit_breathing, 1.0f, AudioReverbPreset::Underwater);
		GetComponent<AudioSource>()->Stop();
		PlayerController::ssg->setStepType2(S("rubber"), AudioReverbPreset::Underwater);
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED / 2.0f;
		audioSource3->Stop();
		audioSource2->Stop();
		PlayerController::wc->GetComponent<Animator>()->set_speed(0.5f);
	}
	else if (GameDataController::gd->getObjective(S("moon_suited_up")))
	{
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->suit_breathing, 1.0f, AudioReverbPreset::Underwater);
		GetComponent<AudioSource>()->Stop();
		GetComponent<AudioSource>()->set_clip(SoundsManagerController::sm->alert2);
		GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::Bathroom);
		GetComponent<AudioSource>()->set_volume(0.1f);
		GetComponent<AudioSource>()->set_loop(true);
		GetComponent<AudioSource>()->Play();
		PlayerController::ssg->setStepType2(S("rubber"), AudioReverbPreset::Underwater);
		audioSource2->set_clip(SoundsManagerController::sm->ambient_ship_crashed);
		audioSource2->gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::Underwater);
		audioSource2->set_volume(0.3f);
		audioSource2->set_loop(true);
		audioSource2->Play();
		audioSource3->set_clip(SoundsManagerController::sm->ambient_sparks);
		audioSource3->gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::PaddedCell);
		audioSource3->set_volume(0.2f);
		audioSource3->set_loop(true);
		audioSource3->Play();
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.75f;
		PlayerController::wc->GetComponent<Animator>()->set_speed(0.75f);
	}
	else
	{
		PlayerController::ssg->setStepType2(S("rubber"), AudioReverbPreset::CarpettedHallway);
		JukeboxAmbient::jb->changeAmbient(nullptr, 0.0f);
		PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
		GetComponent<AudioSource>()->Stop();
		GetComponent<AudioSource>()->set_clip(SoundsManagerController::sm->alert2);
		GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::CarpettedHallway);
		GetComponent<AudioSource>()->set_volume(0.2f);
		GetComponent<AudioSource>()->set_loop(true);
		GetComponent<AudioSource>()->Play();
		audioSource2->set_clip(SoundsManagerController::sm->ambient_ship_crashed);
		audioSource2->gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::Underwater);
		audioSource2->set_volume(0.5f);
		audioSource2->set_loop(true);
		audioSource2->Play();
		audioSource3->set_clip(SoundsManagerController::sm->ambient_sparks);
		audioSource3->gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::PaddedCell);
		audioSource3->set_volume(0.2f);
		audioSource3->set_loop(true);
		audioSource3->Play();
	}
	time = Random::Range(5.0f, 15.0f);
}

void LocationMoonShipStart::Update()
{
	time -= Time::get_deltaTime();
	if (time <= 0.0f)
	{
		time = Random::Range(5.0f, 20.0f);
		float needShake = Random::Range(0.2f, 2.0f);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->needShake = needShake;
		rumbler->PlayOneShot(SoundsManagerController::sm->rumble_2s);
		rumbler->set_pitch(Random::Range(0.85f, 1.15f));
	}
	for (int i = 0; i < times.Count(); i++)
	{
		times[i] += Time::get_deltaTime();
		if (!(times[i] >= 1.0f))
		{
			continue;
		}
		times[i] = Random::Range(0.0f, 0.75f);
		if (!(Random::Range(0.0f, 1.0f) > 0.5f))
		{
			continue;
		}
		if (!sparks[i]->started)
		{
			sparks[i]->started = true;
			continue;
		}
		sparks[i]->started = false;
		int num;
		for (num = 0; num < sparks[i]->particles.Count(); num++)
		{
			P<GameObject> obj = sparks[i]->particles[num]->get_gameObject();
			sparks[i]->particles.RemoveAt(num);
			Object::Destroy(obj);
			num--;
		}
	}
}

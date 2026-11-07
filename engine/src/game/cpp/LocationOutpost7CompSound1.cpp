#include "../game_all.h"

void LocationOutpost7CompSound1::Start()
{
	dzwieki = List<P<AudioClip>>::New();
	dzwieki.Add(SoundsManagerController::sm->hdd1);
	dzwieki.Add(SoundsManagerController::sm->hdd2);
	dzwieki.Add(SoundsManagerController::sm->hdd3);
	dzwieki.Add(SoundsManagerController::sm->hdd4);
	dzwieki.Add(SoundsManagerController::sm->hdd5);
	dzwieki.Add(SoundsManagerController::sm->hdd6);
	dzwieki.Add(SoundsManagerController::sm->hdd7);
	dzwieki.Add(SoundsManagerController::sm->comp_beeps6);
	dzwieki.Add(SoundsManagerController::sm->comp_beeps5);
	dzwieki.Add(SoundsManagerController::sm->comp_beeps4);
	dzwieki.Add(SoundsManagerController::sm->comp_beeps3);
	dzwieki.Add(SoundsManagerController::sm->comp_beeps2);
	dzwieki.Add(SoundsManagerController::sm->comp_beeps1);
	aS = GetComponent<AudioSource>();
	Invoke(S("makeDatSound"), Random::Range(2.0f, 8.0f));
	GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::Bathroom);
}

void LocationOutpost7CompSound1::Update()
{
}

void LocationOutpost7CompSound1::makeDatSound()
{
	aS->PlayOneShot(dzwieki[Random::Range(0, dzwieki.Count())]);
	aS->set_pitch(Random::Range(0.8f, 1.25f));
	Invoke(S("makeDatSound"), Random::Range(2.0f, 8.0f));
}

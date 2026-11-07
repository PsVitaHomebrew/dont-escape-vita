#include "../game_all.h"

void StepSoundGenerator::Start()
{
	aS = gameObject->GetComponent<AudioSource>();
	volumeMultip = 1.0f;
}

void StepSoundGenerator::Update()
{
}

void StepSoundGenerator::setDust(Array<P<Sprite>> dust)
{
	if (dust != nullptr && gameObject->GetComponent<ParticleGenerator>() != nullptr)
	{
		gameObject->GetComponent<ParticleGenerator>()->sprites = dust;
	}
}

void StepSoundGenerator::setStepType2(String type, AudioReverbPreset reverb)
{
	selectedStepsType = type;
	if (type.Equals(S("normal")))
	{
		currtenSteps = stepsNormal;
		volume = 0.2f;
		setDust(dustNormal);
	}
	if (type.Equals(S("dirt")))
	{
		currtenSteps = stepsDirt;
		volume = 0.8f;
		setDust(dustDirt);
	}
	if (type.Equals(S("none")))
	{
		currtenSteps = stepsNormal;
		volume = 0.0f;
		setDust(dustNormal);
	}
	if (type.Equals(S("road")))
	{
		currtenSteps = stepsRoad;
		volume = 0.8f;
		setDust(dustRoad);
	}
	if (type.Equals(WOOD))
	{
		currtenSteps = stepsWood;
		volume = 0.5f;
		setDust(dustWood);
	}
	if (type.Equals(S("metal")))
	{
		currtenSteps = stepsMetal;
		volume = 0.3f;
	}
	if (type.Equals(GRASS))
	{
		currtenSteps = stepsGrass;
		volume = 0.7f;
	}
	if (type.Equals(HAY))
	{
		currtenSteps = stepsHay;
		volume = 0.99f;
	}
	if (type.Equals(RUBBER))
	{
		currtenSteps = stepsRubber;
		volume = 0.99f;
	}
	if (type.Equals(DIRT_GLASS))
	{
		currtenSteps = stepsDirtGlass;
		volume = 0.99f;
	}
	if (type.Equals(FENCE))
	{
		currtenSteps = stepsFence;
		volume = 0.99f;
		setDust(dustDirt);
	}
	if (type.Equals(MOON))
	{
		currtenSteps = stepsMoon;
		volume = 0.99f;
		setDust(dustRoad);
	}
	gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(reverb);
	SoundsManagerController::sm->GetComponent<AudioReverbFilter>()->set_reverbPreset(reverb);
}

void StepSoundGenerator::setStepType(String type)
{
	setStepType2(type, AudioReverbPreset::Off);
}

void StepSoundGenerator::soundStep()
{
	P<AudioClip> audioClip = currtenSteps[0];
	int num = Random::Range(currtenSteps.Count() / 2, currtenSteps.Count());
	currtenSteps.RemoveAt(0);
	currtenSteps.Insert(num - 1, audioClip);
	if (secStep || !useDoubleStepSound)
	{
		aS->PlayOneShot(audioClip, volume * volumeMultip);
	}
	else
	{
		SoundsManagerController::sm->auxASPlayer->set_panStereo(gameObject->GetComponent<AudioSource>()->get_panStereo());
		SoundsManagerController::sm->auxASPlayer->PlayOneShot(audioClip, volume * volumeMultip);
	}
	secStep = !secStep;
}

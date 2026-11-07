#include "../game_all.h"

void SiderealComputerSound::Start()
{
}

void SiderealComputerSound::Update()
{
}

void SiderealComputerSound::beep()
{
	P<AudioClip> audioClip = sounds[0];
	int num = Random::Range(sounds.Count() / 2, sounds.Count());
	sounds.RemoveAt(0);
	sounds.Insert(num - 1, audioClip);
	aS->PlayOneShot(audioClip, 1.0f);
}

#include "../game_all.h"

P<AudioClip> JukeboxMusic::getCurrentMusic()
{
	return currentMusic;
}

void JukeboxMusic::Awake()
{
	if (jb == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		jb = this;
	}
	else if (jb != P<JukeboxMusic>(this))
	{
		Object::Destroy(gameObject);
	}
}

void JukeboxMusic::Start()
{
	audioSource->set_ignoreListenerPause(true);
	audioSource->set_ignoreListenerVolume(true);
}

void JukeboxMusic::Update()
{
	musicVolume = 1.0f * (float)PlayerPrefs::GetInt(S("music")) / 100.0f;
	if (targetPlaybackVolume > currentPlaybackVolume)
	{
		currentPlaybackVolume += step;
	}
	else if (targetPlaybackVolume < currentPlaybackVolume)
	{
		currentPlaybackVolume -= step;
	}
	if (Mathf::Abs(targetPlaybackVolume - currentPlaybackVolume) <= step)
	{
		currentPlaybackVolume = targetPlaybackVolume;
	}
	audioSource->set_volume(currentPlaybackVolume * musicVolume);
	if (currentPlaybackVolume <= 0.0f && targetPlaybackVolume == 0.0f && nextMusic != nullptr)
	{
		currentMusic = nextMusic;
		nextMusic = nullptr;
		audioSource->set_clip(currentMusic);
		audioSource->Play();
		audioSource->set_loop(false);
		targetPlaybackVolume = 1.0f;
	}
	else if (currentPlaybackVolume <= 0.0f && targetPlaybackVolume == 0.0f)
	{
		currentMusic = nullptr;
	}
	if (audioSource->get_isPlaying() || !loop)
	{
		return;
	}
	currentDelay += Time::get_deltaTime();
	if (currentDelay >= delay)
	{
		currentDelay = 0.0f;
		if (nextMusic != nullptr)
		{
			currentMusic = nextMusic;
			nextMusic = nullptr;
			audioSource->set_clip(currentMusic);
		}
		audioSource->Play();
		delay = Random::Range(delayMin, delayMax);
	}
}

void JukeboxMusic::changeMusic(P<AudioClip> newMusic, bool looping, float minTime, float maxTime, float newStep)
{
	if ((!(newMusic == nullptr) || looping || !(currentMusic != SoundsManagerController::sm->music_main)) && newMusic != currentMusic)
	{
		step = newStep;
		nextMusic = newMusic;
		targetPlaybackVolume = 0.0f;
		loop = looping;
		if (minTime <= 0.0f)
		{
			minTime = 0.1f;
		}
		if (maxTime <= 0.0f)
		{
			maxTime = 0.2f;
		}
		delayMin = minTime;
		delayMax = maxTime;
		if (currentDelay == 0.0f)
		{
			delay = Random::Range(delayMin, delayMax);
		}
	}
}

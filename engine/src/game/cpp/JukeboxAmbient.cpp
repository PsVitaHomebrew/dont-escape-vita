#include "../game_all.h"

void JukeboxAmbient::Awake()
{
	if (jb == nullptr)
	{
		jb = this;
	}
	else if (jb != P<JukeboxAmbient>(this))
	{
		Object::Destroy(gameObject);
	}
}

void JukeboxAmbient::Start()
{
	gameObject->AddComponent<AudioReverbFilter>();
}

void JukeboxAmbient::Update()
{
	ambientVolume = 0.5f;
	AudioListener::set_volume((float)PlayerPrefs::GetInt(S("sound")) / 100.0f);
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
	audioSource->set_volume(currentPlaybackVolume * ambientVolume);
	if (audioSource->get_volume() <= 0.0f && targetPlaybackVolume == 0.0f && next != nullptr)
	{
		current = next;
		next = nullptr;
		audioSource->set_clip(current);
		audioSource->Play();
		audioSource->set_loop(true);
		targetPlaybackVolume = nextTargetVolume;
	}
}

void JukeboxAmbient::changeAmbient(P<AudioClip> newAmb, float newVolume, AudioReverbPreset arp)
{
	MonoBehaviour::print(String::Concat(str(newAmb), S(" "), str(current)));
	if (newAmb != current)
	{
		next = newAmb;
		targetPlaybackVolume = 0.0f;
		nextTargetVolume = newVolume;
	}
	else
	{
		targetPlaybackVolume = newVolume;
	}
	if (newVolume != targetPlaybackVolume)
	{
		nextTargetVolume = newVolume;
	}
	gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(arp);
	MonoBehaviour::print(S("NEW AMBIENT!") + str(next) + S("@") + nextTargetVolume + S(" of ") + targetPlaybackVolume + S(" / ") + str(newAmb));
}

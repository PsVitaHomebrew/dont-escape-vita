#include "../game_all.h"

void JukeboxPlaylist::Awake()
{
	if (jB == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		jB = this;
	}
	else if (jB != P<JukeboxPlaylist>(this))
	{
		Object::Destroy(gameObject);
	}
}

void JukeboxPlaylist::Start()
{
	music = New<AudioSource>();
	playList = nullptr;
}

void JukeboxPlaylist::Update()
{
	if (!music->get_isPlaying() && playList != nullptr)
	{
		playNextClipOnPlayList();
	}
}

void JukeboxPlaylist::playNextClipOnPlayList()
{
	music->set_clip(playList[0]);
	music->Play();
	music->set_loop(false);
	targetVolume = 1.0f;
	P<AudioClip> item = playList[0];
	playList.RemoveAt(0);
	playList.Add(item);
}

void JukeboxPlaylist::changeMusic(P<AudioClip> newMusic, bool looping)
{
}

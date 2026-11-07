#include "../game_all.h"

void LocationMoonbase3Start::Start()
{
	walkingHere = false;
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
	if (!GameDataController::gd->getObjective(S("moon_david_sleeps")) && !GameDataController::gd->getObjective(S("moon_light_restored")) && !GameDataController::gd->getObjective(S("moon_light_failed")) && (GameDataController::gd->getObjective(S("moon_cate_sleeps")) || GameDataController::gd->getObjective(S("moon_cody_sleeps")) || GameDataController::gd->getObjective(S("moon_barry_sleeps"))))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_emotional);
	}
	else if (!GameDataController::gd->getObjective(S("moon_david_sleeps")) && GameDataController::gd->getObjective(S("moon_light_restored")))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_attack2, true, 0.0f, 1.0f);
	}
	else
	{
		JukeboxMusic::jb->changeMusic(nullptr);
	}
	if (GameDataController::gd->getObjective(S("moon_light_failed")))
	{
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->moon, 0.75f, AudioReverbPreset::Bathroom);
		audioSouruce2->set_clip(SoundsManagerController::sm->ambient_ship_crashed);
		audioSouruce2->gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::PaddedCell);
		audioSouruce2->set_volume(0.75f);
		audioSouruce2->set_loop(true);
		audioSouruce2->set_pitch(0.25f);
		audioSouruce2->set_time(audioSouruce2->get_clip()->get_length() * Random::Range(0.0f, 0.9f));
		audioSouruce2->Play();
	}
	else
	{
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->pc_noise, 0.75f, AudioReverbPreset::Bathroom);
	}
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Bathroom);
	GameDataController::gd->setObjective(S("visited_moonbase3"), true);
	time = Random::Range(3.0f, 8.0f);
	if (!GameDataController::gd->getObjective(S("moon_talk_pods")))
	{
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		String prefix = S("moonbase2_intro_cate");
		if (!GameDataController::gd->getObjective(S("npc1_alive")))
		{
			prefix = S("moonbase2_intro_no_cate");
		}
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor());
		if (GameDataController::gd->getObjective(S("npc1_alive")))
		{
			list[list.Count() - 1]->action = [this](String s) { startDialogue(s); };
		}
		list[0]->action = [this](String s) { walkToMiddle(s); };
		list[0]->actionWithText = true;
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		GameDataController::gd->setObjective(S("moon_talk_pods"), true);
	}
	if (GameDataController::gd->getObjective(S("moon_david_sleeps")))
	{
		Invoke(S("close_david_pod"), 3.0f);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->needShake = 5.0f;
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->needShake = 115.0f;
}

void LocationMoonbase3Start::walkToMiddle(String s)
{
	PlayerController::wc->setSimpleTargetV3(GameObject::Find(S("DavidWalkHere"))->transform->get_position());
	PlayerController::pc->setBusy(true);
	PlayerController::wc->forceAnimation(S("walk_e"), true);
	walkingHere = true;
}

void LocationMoonbase3Start::close_david_pod()
{
	GameObject::Find(S("Moonbase3Pad1"))->GetComponent<Moonbase3Pod>()->openIfNeeded(true);
	Invoke(S("go_to_sleep"), 5.0f);
}

void LocationMoonbase3Start::go_to_sleep()
{
	PlayerController::pc->spawnName = S("InfoExit");
	if (GameDataController::gd->getObjective(S("moon_disc1_used")) && GameDataController::gd->getObjective(S("moon_disc2_used")))
	{
		CurtainController::cc->fadeOut(S("LocationEndingGood"), WalkController::Direction::S_, nullptr, nullptr, false, nullptr, 1.0f);
	}
	else
	{
		CurtainController::cc->fadeOut(S("Ending4"), WalkController::Direction::S_, nullptr, nullptr, false, nullptr, 1.0f);
	}
}

void LocationMoonbase3Start::updateMLF()
{
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->moon, 0.75f, AudioReverbPreset::Bathroom);
	mlf->lightsFailed = true;
}

void LocationMoonbase3Start::startDialogue(String str_)
{
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->npcClickAction(String::Empty);
}

void LocationMoonbase3Start::Update()
{
	if (walkingHere && PlayerController::wc->currentXY.x < 120.0f)
	{
		walkingHere = false;
		PlayerController::wc->forceAnimation(S("stand_ne"), true, false, false);
		PlayerController::wc->fullStop(true);
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
}

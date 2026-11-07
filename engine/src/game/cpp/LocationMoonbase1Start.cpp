#include "../game_all.h"

void LocationMoonbase1Start::Start()
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
	suit_cate->set_enabled(false);
	suit_barry->set_enabled(false);
	suit_cody->set_enabled(false);
	suit_david->set_enabled(false);
	lm = GameObject::Find(S("Location"))->GetComponent<LocationManager>();
	if (GameDataController::gd->getObjective(S("moon_light_failed")) || GameDataController::gd->getObjective(S("moon_light_restored")))
	{
		startdestruction2 = true;
	}
	else
	{
		startdestruction2 = false;
	}
	if (GameDataController::gd->getObjective(S("moon_card_taken")))
	{
		startdestruction1 = true;
	}
	else
	{
		startdestruction1 = false;
	}
	startdestruction2 = startdestruction1;
	if (GameDataController::gd->getObjective(S("moon_light_failed")))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_attack2, true, 0.0f, 1.0f);
		audioSource2->set_clip(SoundsManagerController::sm->ambient_ship_crashed);
		audioSource2->gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::PaddedCell);
		audioSource2->set_volume(0.75f);
		audioSource2->set_loop(true);
		audioSource2->set_time(audioSource2->gameObject->GetComponent<AudioSource>()->get_clip()->get_length() * Random::Range(0.0f, 0.9f));
		audioSource2->Play();
	}
	else
	{
		JukeboxMusic::jb->changeMusic(nullptr);
	}
	if (GameDataController::gd->getObjective(S("moon_suited_up")))
	{
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->suit_breathing, 0.75f, AudioReverbPreset::Underwater);
		PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Underwater);
	}
	else
	{
		if (GameDataController::gd->getObjective(S("npc1_alive")))
		{
			suit_cate->set_enabled(true);
		}
		if (GameDataController::gd->getObjective(S("npc2_alive")))
		{
			suit_barry->set_enabled(true);
		}
		suit_david->set_enabled(true);
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			suit_cody->set_enabled(true);
		}
		if (GameDataController::gd->getObjective(S("moon_light_failed")) && !GameDataController::gd->getObjective(S("moon_light_restored")))
		{
			JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->moon, 1.0f, AudioReverbPreset::Bathroom);
		}
		else
		{
			JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->pc_noise, 0.75f, AudioReverbPreset::Bathroom);
		}
		PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Bathroom);
	}
	if (!GameDataController::gd->getObjective(S("visited_moonbase1")))
	{
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		suit_cody->set_enabled(false);
		suit_barry->set_enabled(false);
		suit_cate->set_enabled(false);
		suit_david->set_enabled(false);
		String prefix = S("moonbase1_intro_cate_p1");
		if (!GameDataController::gd->getObjective(S("npc1_alive")))
		{
			prefix = S("moonbase1_intro_no_cate_p1");
		}
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor());
		int index = 1;
		if (!GameDataController::gd->getObjective(S("npc1_alive")))
		{
			index = 0;
		}
		list[index]->action = [this](String val) { removeSuits(val); };
		list[index]->actionWithText = false;
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		Timeline::t->doNotUnlock = true;
		GameDataController::gd->setObjective(S("visited_moonbase1"), true);
	}
	else if (!GameDataController::gd->getObjective(S("moon_talk_base_enter")))
	{
		P<TextFieldController> component2 = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		String prefix2 = S("moonbase1_intro_cate_p2");
		if (!GameDataController::gd->getObjective(S("npc1_alive")))
		{
			prefix2 = S("moonbase1_intro_no_cate_p2");
		}
		List<P<DialogueLine>> list2 = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list2, prefix2, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component2, GingerActionController::getColor());
		if (!GameDataController::gd->getObjective(S("npc1_alive")))
		{
			list2[list2.Count() - 1]->action = [this](String s) { getnote(s); };
		}
		for (int j = 0; j < list2.Count(); j++)
		{
			Timeline::t->addDialogue(list2[j]);
		}
		GameDataController::gd->setObjective(S("moon_talk_base_enter"), true);
		if (InventoryController::ic->isItemInInventory(S("deadbird")))
		{
			GameDataController::Achievement(S("S_BIRD"));
		}
	}
	GameDataController::gd->setObjective(S("visited_moonbase1"), true);
	time = Random::Range(3.0f, 8.0f);
	for (int k = 0; k < kawalkiKsiezyca.Count(); k++)
	{
		kawalkiFinish[k] = kawalkiKsiezyca[k]->transform->get_position().y;
		kawalkiKsiezyca[k]->transform->set_position(Vector3(0.0f, 0.0f, kawalkiKsiezyca[k]->transform->get_position().z));
	}
	destIndex0 = GameDataController::gd->getObjectiveIndex(S("moonfall_progress_1"));
	destIndex1 = GameDataController::gd->getObjectiveIndex(S("moonfall_progress_2"));
	destIndex2 = GameDataController::gd->getObjectiveIndex(S("moonfall_progress_4"));
	destructionProgress0 = GameDataController::gd->objectives[destIndex0]->detail;
	destructionProgress1 = GameDataController::gd->objectives[destIndex1]->detail;
	destructionProgress2 = GameDataController::gd->objectives[destIndex2]->detail;
	destructionProgress0 /= 1000.0f;
	destructionProgress1 /= 1000.0f;
	destructionProgress2 /= 1000.0f;
	cloudProgress1 = Random::Range(0.0f, 1.0f);
	cloudProgress2 = Random::Range(0.0f, 1.0f);
	if (GameDataController::gd->getObjective(S("moon_window_cracked")) && !GameDataController::gd->getObjective(S("moon_door_closed")))
	{
		PlayerController::wc->setSimpleTargetV3(GameObject::Find(S("jump_here"))->transform->get_position());
		GameObject::Find(S("LocationMoonbase1_2"))->GetComponent<Animator>()->Play(S("moon_door_close"));
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->wind1);
		Invoke(S("sparkles1"), 3.2f);
		Invoke(S("sparkles2"), 4.8f);
		Invoke(S("sparkles3"), 5.1f);
		Invoke(S("sparkles4"), 5.7f);
		Invoke(S("sparkles5"), 6.0f);
		Invoke(S("unlock"), 5.0f);
		audioSource2->set_volume(1.0f);
	}
	else if (GameDataController::gd->getObjective(S("moon_window_cracked")) && GameDataController::gd->getObjective(S("moon_door_closed")))
	{
		audioSource3->set_clip(SoundsManagerController::sm->ambient_sparks);
		audioSource3->gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::PaddedCell);
		audioSource3->set_volume(0.3f);
		audioSource3->set_loop(true);
		audioSource3->Play();
		sparkstime = true;
		audioSource2->set_volume(1.0f);
	}
}

void LocationMoonbase1Start::getnote(String s)
{
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("cate_note")));
	ItemsManager::exmineItem(ItemsManager::im->getItem(S("cate_note")));
}

void LocationMoonbase1Start::unlock()
{
	sparkstime = true;
	GameDataController::gd->setObjective(S("moon_door_closed"), true);
	sparkles6();
	PlayerController::wc->forceAnimation(S("stand_se"), true, false, false);
	PlayerController::pc->setBusy(false);
	GameObject::Find(S("LocationMoonbase1_2"))->GetComponent<LocationMoonbase1_2>()->updateAll();
}

void LocationMoonbase1Start::sparkles1()
{
	sparkles[0]->started = true;
	audioSource3->set_clip(SoundsManagerController::sm->ambient_sparks);
	audioSource3->gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::PaddedCell);
	audioSource3->set_volume(0.3f);
	audioSource3->set_loop(true);
	audioSource3->Play();
}

void LocationMoonbase1Start::sparkles2()
{
	sparkles[1]->started = true;
}

void LocationMoonbase1Start::sparkles3()
{
	sparkles[2]->started = true;
}

void LocationMoonbase1Start::sparkles4()
{
	sparkles[3]->started = true;
}

void LocationMoonbase1Start::sparkles5()
{
	sparkles[4]->started = true;
}

void LocationMoonbase1Start::sparkles6()
{
	sparkles[5]->started = true;
}

void LocationMoonbase1Start::removeSuits(String val)
{
	GameDataController::gd->setObjective(S("moon_suited_up"), false);
	PlayerController::pc->spawnName = S("LocationMoon3_Moonbase1");
	PlayerController::wc->suit = false;
	CurtainController::cc->fadeOut(S("LocationMoonbase1"), WalkController::Direction::S_, S("stand_s"));
}

void LocationMoonbase1Start::Update()
{
	secToSave += Time::get_deltaTime();
	if (secToSave > 1.0f)
	{
		int detail = (int)(destructionProgress0 * 1000.0f);
		int detail2 = (int)(destructionProgress1 * 1000.0f);
		int detail3 = (int)(destructionProgress2 * 1000.0f);
		secToSave = 0.0f;
		GameDataController::gd->objectives[destIndex0]->detail = detail;
		GameDataController::gd->objectives[destIndex1]->detail = detail2;
		GameDataController::gd->objectives[destIndex2]->detail = detail3;
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
	if (sparkstime)
	{
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
			if (!sparkles[i]->started)
			{
				sparkles[i]->started = true;
				continue;
			}
			sparkles[i]->started = false;
			int num2;
			for (num2 = 0; num2 < sparkles[i]->particles.Count(); num2++)
			{
				P<GameObject> obj = sparkles[i]->particles[num2]->get_gameObject();
				sparkles[i]->particles.RemoveAt(num2);
				Object::Destroy(obj);
				num2--;
			}
		}
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
	if (startdestruction2)
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
		if ((double)destructionProgress2 > 0.75)
		{
			destructionProgress1 += Time::get_deltaTime() * 0.05f;
		}
	}
	if (startdestruction1)
	{
		destructionProgress0 += Time::get_deltaTime() * 0.06f;
	}
	if (destructionProgress0 > 1.0f)
	{
		destructionProgress0 = 1.0f;
	}
	if (destructionProgress1 > 1.0f)
	{
		destructionProgress1 = 1.0f;
	}
	if (destructionProgress2 > 1.0f)
	{
		destructionProgress2 = 1.0f;
	}
	for (int j = 0; j < 3; j++)
	{
		float num3 = destructionProgress0 * 1.05f - 0.05f;
		if (num3 < 0.0f)
		{
			num3 = 0.0f;
		}
		if (num3 > 0.0f && num3 < 0.25f)
		{
			lm->needShake = 4.0f;
		}
		kawalkiKsiezyca[j]->transform->set_position(Vector3(0.0f, kawalkiFinish[j] * num3, kawalkiKsiezyca[j]->transform->get_position().z));
		kawalkiKsiezyca[j]->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(kawalkiKsiezyca[j]->transform->get_position().x, kawalkiKsiezyca[j]->transform->get_position().y, kawalkiKsiezyca[j]->transform->get_position().z)));
	}
	for (int k = 3; k < kawalkiKsiezyca.Count(); k++)
	{
		kawalkiKsiezyca[k]->transform->set_position(Vector3(0.0f, kawalkiFinish[k] * destructionProgress1, kawalkiKsiezyca[k]->transform->get_position().z));
		kawalkiKsiezyca[k]->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(kawalkiKsiezyca[k]->transform->get_position().x, kawalkiKsiezyca[k]->transform->get_position().y, kawalkiKsiezyca[k]->transform->get_position().z)));
	}
	earth->transform->set_position(Vector3(0.0f, 1.0f * destructionProgress2, earth->transform->get_position().z));
	earth->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(earth->transform->get_position().x, earth->transform->get_position().y, earth->transform->get_position().z)));
	moon_shadow->transform->set_position(Vector3(0.0f, 1.025f * destructionProgress2, moon_shadow->transform->get_position().z));
	moon_shadow->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(moon_shadow->transform->get_position().x, moon_shadow->transform->get_position().y, moon_shadow->transform->get_position().z)));
	chmura1->transform->set_position(Vector3(-2.2f + cloudProgress1 * 4.4f, chmura1->transform->get_position().y, chmura1->transform->get_position().z));
	chmura1->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(chmura1->transform->get_position().x, earth->transform->get_position().y - 0.45f, 0.3f)));
	chmura2->transform->set_position(Vector3(2.2f - cloudProgress2 * 4.4f, earth->transform->get_position().y, chmura2->transform->get_position().z));
	chmura2->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(chmura2->transform->get_position().x, chmura2->transform->get_position().y - 0.45f, 0.4f)));
}

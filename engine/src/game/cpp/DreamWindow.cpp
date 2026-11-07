#include "../game_all.h"

void DreamWindow::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("bug_death");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("dream_window");
	range = 5.0f;
	teleport = false;
}

void DreamWindow::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		characterAnimationName = S("bug_death");
		animationFlip = true;
	}
	else if (GameDataController::gd->getCurrentDay() == 2)
	{
		animationFlip = true;
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			characterAnimationName = S("heat_death");
		}
		else
		{
			characterAnimationName = S("ice_death");
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 3)
	{
		animationFlip = true;
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
		{
			characterAnimationName = S("action_stnd_ne_busy");
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
		{
			characterAnimationName = S("action_stnd_ne_busy");
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 4)
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void DreamWindow::clickAction()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		PlayerController::wc->GetComponent<Animator>()->set_speed(1.75f);
	}
	else if (GameDataController::gd->getCurrentDay() < 4)
	{
		PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	}
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		if (!GameDataController::gd->getObjective(S("dream_day_1_window_broken")))
		{
			GameDataController::gd->setObjective(S("dream_day_1_window_broken"), true);
		}
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->break_window);
		PlayerController::pc->GetComponent<SpriteRenderer>()->set_flipX(false);
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->flies);
			Invoke(S("showBugs"), 1.4f);
			Array<P<GameObject>> array = GameObject::FindGameObjectsWithTag(S("insect"));
			for (int i = 0; i < array.Length(); i++)
			{
				array[i]->GetComponent<BugFly>()->startFly(i);
			}
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->gas);
			GameObject::Find(S("Gas"))->GetComponent<ParticleGenerator>()->started = true;
			Invoke(S("gasAfterWhile"), 0.75f);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			for (int j = 0; j < pajaki.Length(); j++)
			{
				pajaki[j]->GetComponent<SpiderFall>()->startFall();
			}
		}
		updateAll();
	}
	else if (GameDataController::gd->getCurrentDay() == 2)
	{
		if (!GameDataController::gd->getObjective(S("dream_day_2_window_broken")))
		{
			GameDataController::gd->setObjective(S("dream_day_2_window_broken"), true);
		}
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->break_window);
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->blizzard);
			Vector2 simpleTarget = Vector2(96.0f, 25.0f);
			PlayerController::wc->setSimpleTarget(simpleTarget);
			GameObject::Find(S("Location"))->transform->Find(S("cold"))->GetComponent<SpriteRenderer>()->set_enabled(true);
			Array<P<GameObject>> array2 = GameObject::FindGameObjectsWithTag(S("snow"));
			for (int k = 0; k < array2.Length(); k++)
			{
				array2[k]->GetComponent<ParticleGenerator>()->started = true;
			}
			Invoke(S("nextScene2"), 8.0f);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			Vector2 simpleTarget2 = Vector2(76.0f, 25.0f);
			PlayerController::wc->setSimpleTarget(simpleTarget2);
			GameObject::Find(S("Heat1"))->GetComponent<ParticleGenerator>()->started = true;
			GameObject::Find(S("Heat2"))->GetComponent<ParticleGenerator>()->started = true;
			GameObject::Find(S("Heat3"))->GetComponent<ParticleGenerator>()->started = true;
			GameObject::Find(S("Location"))->transform->Find(S("hot"))->GetComponent<SpriteRenderer>()->set_enabled(true);
			Invoke(S("makeSmoke"), 3.0f);
			Invoke(S("makeSmoke2"), 5.0f);
			Invoke(S("makeSmoke3"), 6.0f);
			Invoke(S("makeSmoke4"), 7.0f);
			Invoke(S("nextScene2"), 10.0f);
		}
		updateAll();
	}
	else if (GameDataController::gd->getCurrentDay() == 3)
	{
		if (!GameDataController::gd->getObjective(S("dream_day_3_window_broken")))
		{
			GameDataController::gd->setObjective(S("dream_day_3_window_broken"), true);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
		{
			GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->motor_incoming);
			Invoke(S("bangbangyouredead"), 2.0f);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
		{
			Invoke(S("thunderstorm"), 1.0f);
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 4)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("dream4_window")));
	}
}

void DreamWindow::thunderstorm()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->break_window);
	GameObject::Find(S("RainEmmiter0"))->GetComponent<ParticleGenerator>()->started = true;
	GameObject::Find(S("RainEmmiter1"))->GetComponent<ParticleGenerator>()->started = true;
	GameObject::Find(S("RainEmmiter2"))->GetComponent<ParticleGenerator>()->started = true;
	GameObject::Find(S("RainEmmiter3"))->GetComponent<ParticleGenerator>()->started = true;
	gameObject->GetComponent<Animator>()->set_enabled(true);
	gameObject->GetComponent<Animator>()->Play(S("window_flood"));
	PlayerController::wc->forceAnimation(S("bug_death"), true);
	Invoke(S("rainSmoke1"), 1.5f);
	Invoke(S("rainSmoke2"), 2.5f);
	Invoke(S("prestrike"), 3.0f);
	Invoke(S("strike"), 3.5f);
	Invoke(S("strikeEnd"), 5.0f);
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->rain_short);
}

void DreamWindow::rainSmoke1()
{
	PlayerController::wc->setSimpleTargetV3(GameObject::Find(S("FirstEncounter"))->transform->get_position());
	PlayerController::wc->forceAnimation(S("run_e"));
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.9f;
	GameObject::Find(S("RainSmokeEmmiter0"))->GetComponent<ParticleGenerator>()->started = true;
}

void DreamWindow::rainSmoke2()
{
	GameObject::Find(S("RainSmokeEmmiter1"))->GetComponent<ParticleGenerator>()->started = true;
}

void DreamWindow::prestrike()
{
	light->strike(SoundsManagerController::sm->thunder5, 0.5f, true);
}

void DreamWindow::strike()
{
	GameObject::Find(S("lighting01"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	PlayerController::wc->forceAnimation(S("electrocute"));
	P<GameObject> gameObject = GameObject::Find(S("PlayerElectro"));
	gameObject->transform->set_position(PlayerController::pc->gameObject->transform->get_position());
	gameObject->transform->set_position(Vector3(gameObject->transform->get_position().x, gameObject->transform->get_position().y, -3.0f));
	gameObject->GetComponent<SpriteRenderer>()->set_flipX(PlayerController::wc->sr->get_flipX());
	gameObject->GetComponent<Animator>()->Play(S("electrocute"));
}

void DreamWindow::strikeEnd()
{
	GameObject::Find(S("lighting01"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	PlayerController::pc->aS->Stop();
	Invoke(S("nextScene3"), 4.0f);
}

void DreamWindow::bangbangyouredead()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->break_window);
	gameObject->GetComponent<Animator>()->set_enabled(true);
	gameObject->GetComponent<Animator>()->Play(S("thugs_attack"));
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->rifle_shoot);
	PlayerController::wc->forceAnimation(S("shot_n"), true);
	Invoke(S("nextScene3"), 4.0f);
}

void DreamWindow::gasAfterWhile()
{
	GameObject::Find(S("Gas (1)"))->GetComponent<ParticleGenerator>()->started = true;
	GameObject::Find(S("Gas (2)"))->GetComponent<ParticleGenerator>()->started = true;
}

void DreamWindow::makeSmoke()
{
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->started = true;
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->maxParticles = 50;
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->minAlpha = 0.1f;
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->maxAlpha = 0.25f;
}

void DreamWindow::makeSmoke2()
{
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->maxParticles = 100;
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->minAlpha = 0.25f;
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->maxAlpha = 0.75f;
}

void DreamWindow::makeSmoke3()
{
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->maxParticles = 150;
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->minAlpha = 0.5f;
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->maxAlpha = 1.0f;
}

void DreamWindow::makeSmoke4()
{
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->maxParticles = 200;
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->minAlpha = 1.0f;
	GameObject::Find(S("Smoke1"))->GetComponent<ParticleGenerator>()->maxAlpha = 1.0f;
}

void DreamWindow::updateState()
{
	if ((bool)gameObject->GetComponent<Animator>())
	{
		gameObject->GetComponent<Animator>()->set_enabled(false);
	}
	if ((GameDataController::gd->getCurrentDay() == 1 && !GameDataController::gd->getObjective(S("dream_day_1_started"))) || (GameDataController::gd->getCurrentDay() == 2 && !GameDataController::gd->getObjective(S("dream_day_2_started"))) || (GameDataController::gd->getCurrentDay() == 3 && !GameDataController::gd->getObjective(S("dream_day_3_started"))) || (GameDataController::gd->getCurrentDay() == 4 && !GameDataController::gd->getObjective(S("dream_day_4_started"))))
	{
		colliderManager->setCollider(-1);
	}
	else if ((GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("dream_day_1_window_broken"))) || (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjective(S("dream_day_2_window_broken"))))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else if (GameDataController::gd->getCurrentDay() == 3)
	{
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(window);
		if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjective(S("dream_day_3_window_broken")))
		{
			gameObject->GetComponent<Animator>()->set_enabled(true);
			gameObject->GetComponent<Animator>()->Play(S("thugs_stare"));
		}
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
	else
	{
		colliderManager->setCollider(0);
	}
}

void DreamWindow::showBugs()
{
	GameObject::Find(S("bugs_feast_1"))->GetComponent<SpriteRenderer>()->set_enabled(true);
}

void DreamWindow::clickAction2()
{
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			GameObject::Find(S("bugs_feast_1"))->transform->set_position(ScreenControler::roundToNearestFullPixel2(GameObject::Find(S("bugs_feast_1"))->transform->get_position()));
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			GameObject::Find(S("Gas (3)"))->GetComponent<ParticleGenerator>()->started = true;
			GameObject::Find(S("Gas (4)"))->GetComponent<ParticleGenerator>()->started = true;
			GameObject::Find(S("Gas (5)"))->GetComponent<ParticleGenerator>()->started = true;
		}
		PlayerController::wc->forceAnimation(S("bug_death_2"));
		Invoke(S("nextScene"), 4.0f);
	}
}

void DreamWindow::nextScene()
{
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationTent"), WalkController::Direction::S_, nullptr, nullptr, false, nullptr, 0.5f);
}

void DreamWindow::nextScene2()
{
	PlayerController::pc->aS->Stop();
	PlayerController::pc->spawnName = S("WakeUp");
	if (GameDataController::gd->getObjectiveDetail(S("day1_complete")) >= 0)
	{
		CurtainController::cc->fadeOut(S("LocationBaseUpstairs"), WalkController::Direction::S_, S("stand_up"), nullptr, true, nullptr, 0.1f);
	}
	else
	{
		CurtainController::cc->fadeOut(S("LocationBaseUpstairs"), WalkController::Direction::S_, S("sleep"), nullptr, true, nullptr, 0.02f);
	}
}

void DreamWindow::nextScene3()
{
	if ((!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 0) || (!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 0))
	{
		GameDataController::gd->setObjective(S("location02_door_locked"), false);
		GameDataController::gd->setObjective(S("location02_door_open"), true);
		if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 2)
		{
			GameDataController::gd->setObjectiveDetail(S("towel_1_at_door"), 0);
			P<Item> item = ItemsManager::im->getItem(S("towel_1"));
			item->dataRef->locX = 175;
			item->dataRef->locY = 30;
			item->dataRef->droppedLocation = S("Location2");
		}
		if (GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 2)
		{
			GameDataController::gd->setObjectiveDetail(S("towel_2_at_door"), 0);
			P<Item> item2 = ItemsManager::im->getItem(S("towel_2"));
			item2->dataRef->locX = 175;
			item2->dataRef->locY = 30;
			item2->dataRef->droppedLocation = S("Location2");
		}
		GameDataController::gd->setObjectiveDetail(S("car_location"), 0);
		PlayerController::pc->spawnName = S("Funeral");
		CurtainController::cc->fadeOut(S("LocationBaseOutside2"), WalkController::Direction::NW, S("stand_ne"), nullptr, true, [this]() { startFuneral(); }, 0.1f);
	}
	else
	{
		PlayerController::pc->spawnName = S("Day3");
		if (GameDataController::gd->finishingLocation == S("LocationCave"))
		{
			CurtainController::cc->fadeOut(S("LocationRV"), WalkController::Direction::SW, S("stand_se"), nullptr, true, [this]() { startDreamTalk(); }, 0.1f);
		}
		else
		{
			CurtainController::cc->fadeOut(S("Location1"), WalkController::Direction::SW, S("stand_se"), nullptr, true, [this]() { startDreamTalk(); }, 0.1f);
		}
	}
}

void DreamWindow::startFuneral()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	String prefix = ((GameDataController::gd->getObjective(S("npc2_alive")) || !GameDataController::gd->getObjective(S("npc2_joined")) || GameDataController::gd->getObjectiveDetail(S("npc2_alive")) != 0) ? S("day3_funeral_cody") : S("day3_funeral_barry"));
	DialogueController::dc->initDialogue(list, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		list.Add(New<DialogueLine>(GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor(), GameStrings::getString(GameStrings::dialogues, S("day3_funeral_barry_cody")), nullptr));
	}
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		list.Add(New<DialogueLine>(GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc3Controller::getColor(), GameStrings::getString(GameStrings::dialogues, S("day3_funeral_cody_barry")), nullptr));
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	startDreamTalk();
}

void DreamWindow::startDreamTalk()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	String prefix = ((GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 0) ? S("day3_intro1") : S("day3_intro0"));
	DialogueController::dc->initDialogue(list, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && (!GameDataController::gd->getObjective(S("npc2_joined")) || GameDataController::gd->getObjective(S("npc2_alive"))))
	{
		DialogueController::dc->initDialogue(list, S("d2_dream_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
	}
	DialogueController::dc->initDialogue(list, S("day3_intro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	Timeline::t->actions[Timeline::t->actions.Count() - 1]->function = [this](String s) { transportToSidereal(s); };
}

void DreamWindow::transportToSidereal(String s)
{
	PlayerController::pc->setBusy(false);
	GameDataController::gd->setObjectiveDetail(S("map_sidereal_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
}

void DreamWindow::clickAction0()
{
}

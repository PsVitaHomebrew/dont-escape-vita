#include "../game_all.h"

void NPCSpawner::Start()
{
	npc = GameObject::Find(npcName)->GetComponent<NPCWalkController>();
	collider = npc->gameObject->GetComponent<BoxCollider2D>();
	spriteRenderer = npc->gameObject->GetComponent<SpriteRenderer>();
	hide();
	basicConditions = List<String>::New();
	if (npcName == S("Ginger"))
	{
		basicConditions.Add(S("npc1_alive"));
		mainCondition = S("npc1_alive");
		basicConditions.Add(S("dialogue_ginger_intro"));
		mainCondition = String::Empty;
	}
	if (npcName == S("Npc2"))
	{
		basicConditions.Add(S("npc2_joined"));
		basicConditions.Add(S("npc2_alive"));
		mainCondition = S("npc2_alive");
	}
	if (npcName == S("Npc3"))
	{
		basicConditions.Add(S("npc3_joined"));
		basicConditions.Add(S("npc3_alive"));
		mainCondition = S("npc3_alive");
	}
	if (!npc->spawned)
	{
		spawnOrNot();
	}
}

void NPCSpawner::spawnOrNot(bool resumingGame)
{
	spawn = true;
	String text = PlayerController::pc->spawnName;
	if (PlayerController::pc->spawnName.Equals(S("previous")) || PlayerController::pc->spawnName.Equals(String::Empty) || PlayerController::pc->spawnName.Equals(S("none")))
	{
		resumingGame = true;
		text = GameDataController::gd->usedSpawner;
	}
	if (ifEntriesMatch)
	{
		for (int i = 0; i < basicConditions.Count(); i++)
		{
			if (!GameDataController::gd->getObjective(basicConditions[i]))
			{
				spawn = false;
			}
		}
	}
	for (int j = 0; j < conditions.Count(); j++)
	{
		if (GameDataController::gd->getObjective(conditions[j]) == !conditionsValues[j])
		{
			spawn = false;
		}
	}
	if (mainCondition != String::Empty && !GameDataController::gd->getObjective(mainCondition))
	{
		spawn = false;
	}
	if (ifEntriesMatch && !text.Equals(gameObject->transform->get_parent()->get_name()))
	{
		spawn = false;
	}
	if (spawn)
	{
		npc->gameObject->transform->set_position(Vector3(0.0f, 0.0f, 0.0f));
		MonoBehaviour::print(S("ROUND TO NEAREST FULL PIXEL ") + ScreenControler::screenToGame(Camera::get_main()->WorldToScreenPoint(gameObject->transform->get_position())).ToString());
		npc->currentXY = ScreenControler::roundToNearestFullPixel(gameObject->transform->get_position());
		npc->clearTarget();
		if (PlayerController::pc->spawnName == S("car"))
		{
			rand_del_max /= 2.0f;
			rand_del_min /= 4.0f;
		}
		if (!PlayerController::pc->npcShouldAppearRightOnSpot)
		{
			Invoke(S("arrive"), Random::Range(rand_del_min, rand_del_max));
		}
		else
		{
			Invoke(S("arrive"), Random::Range(0.0f, 0.01f));
		}
		flipage();
		if (startAnimation != String::Empty)
		{
			npc->forceAnimation(startAnimation);
		}
		npc->gameObject->GetComponent<SpriteRenderer>()->set_flipX(flipX);
		npc->gameObject->GetComponent<NPCActionController>()->updateState();
		MonoBehaviour::print(S("SPAWNING NPC ") + npcName + S(" at ") + npc->currentXY.ToString() + S(" (") + gameObject->transform->get_position().ToString() + S(") resumingGame? ") + str(resumingGame) + S(" "));
		MonoBehaviour::print(S("SPAWNING NPC at ") + gameObject->transform->get_parent()->get_name() + S("  because ") + PlayerController::pc->spawnName);
		MonoBehaviour::print(S("SPAWNING NPC with starting animation ") + startAnimation + S(" AND FLIP X ") + flipX);
	}
}

void NPCSpawner::flipage()
{
	if (!flipX)
	{
		npc->gameObject->GetComponent<NPCWalkController>()->forceDirection(NPCWalkController::Direction::SE);
	}
	else
	{
		npc->gameObject->GetComponent<NPCWalkController>()->forceDirection(NPCWalkController::Direction::SW);
	}
}

void NPCSpawner::hide(bool fast)
{
	collider->set_enabled(false);
	targetAlpha = 0.0f;
	if (fast)
	{
		spriteRenderer->set_enabled(false);
		npc->colorAlpha = 0.0f;
		npc->shadow->alphaMod = 0.0f;
		alpha = 0.0f;
		spriteRenderer->set_color(Color(npc->colorRed, npc->colorGreen, npc->colorBlue, 0.0f));
	}
}

void NPCSpawner::show(bool fast)
{
	MonoBehaviour::print(S("SHOW ") + npcName + S(" fast? ") + fast + S(" at ") + gameObject->transform->get_parent()->gameObject->get_name());
	collider->set_enabled(true);
	npc->spawned = true;
	targetAlpha = 1.0f;
	spriteRenderer->set_enabled(true);
	if (fast)
	{
		alpha = 1.0f;
		npc->colorAlpha = 1.0f;
		npc->shadow->alphaMod = 1.0f;
		spriteRenderer->set_color(Color(npc->colorRed, npc->colorGreen, npc->colorBlue, 1.0f));
	}
}

void NPCSpawner::arrive()
{
	show(PlayerController::pc->npcShouldAppearRightOnSpot);
	if (PlayerController::pc->spawnName == S("car"))
	{
		int num = Random::Range(0, 3);
		if (num == 0)
		{
			npc->gameObject->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->car_close);
		}
		if (num == 1)
		{
			npc->gameObject->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->car_close2);
		}
		if (num == 2)
		{
			npc->gameObject->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->car_close3);
		}
	}
	if (currentLocationManager == nullptr)
	{
		currentLocationManager = GameObject::Find(S("Location"))->GetComponent<LocationManager>();
	}
	if (PlayerController::pc->npcShouldAppearRightOnSpot)
	{
		MonoBehaviour::print(S("ROUND TO NEAREST FULL PIXEL B ") + ScreenControler::screenToGame(Camera::get_main()->WorldToScreenPoint(gameObject->transform->Find(S("NPCTarget"))->transform->get_position())).ToString());
		npc->currentXY = ScreenControler::roundToNearestFullPixel(gameObject->transform->Find(S("NPCTarget"))->transform->get_position());
		npc->clearTarget();
		if (gameObject->transform->Find(S("NPCTarget"))->transform->get_position().x < gameObject->transform->get_position().x)
		{
			flipX = true;
		}
		else
		{
			flipX = false;
		}
		flipage();
	}
	else
	{
		List<Vector2> list = currentLocationManager->Search2(currentLocationManager->findNearestClearNode(currentLocationManager->getNodeLocation(npc->currentXY)), currentLocationManager->findNearestClearNode(currentLocationManager->getNodeLocation(ScreenControler::roundToNearestFullPixel(gameObject->transform->Find(S("NPCTarget"))->transform->get_position()))));
		list.Insert(0, npc->currentXY);
		npc->setTarget(list);
	}
	npc->gameObject->GetComponent<NPCActionController>()->updateState();
}

void NPCSpawner::Update()
{
	if (!spawn)
	{
		return;
	}
	float num = 2.5f * Time::get_deltaTime();
	if (Mathf::Abs(targetAlpha - alpha) < num)
	{
		alpha = targetAlpha;
		npc->colorAlpha = alpha;
		spriteRenderer->set_color(Color(npc->colorRed, npc->colorGreen, npc->colorBlue, alpha));
		npc->shadow->alphaMod = alpha;
	}
	else if (targetAlpha != alpha)
	{
		if (targetAlpha > alpha)
		{
			alpha += num;
		}
		else if (targetAlpha < alpha)
		{
			alpha -= num;
		}
		npc->colorAlpha = alpha;
		npc->shadow->alphaMod = alpha;
		spriteRenderer->set_color(Color(npc->colorRed, npc->colorGreen, npc->colorBlue, alpha));
	}
}

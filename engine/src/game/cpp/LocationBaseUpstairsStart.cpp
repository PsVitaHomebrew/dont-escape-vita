#include "../game_all.h"

void LocationBaseUpstairsStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.002f;
	PlayerController::wc->shadow->fadeRateH = 0.002f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 25.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 150.0f;
	PlayerController::ssg->setStepType(S("wood"));
	GameDataController::gd->setObjective(S("visited_baseUpstairs"), true);
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_5a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.25f);
	GameObject::Find(S("Ladder"))->transform->Find(S("faller"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	GameObject::Find(S("Ladder"))->transform->Find(S("faller"))->GetComponent<Animator>()->Play(S("klapa_0"));
	if (!GameDataController::gd->getObjective(S("dream_day_2_awake")) && GameDataController::gd->getCurrentDay() == 2)
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->heli_crash);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->needShake = 1.75f;
		GameObject::Find(S("Duster"))->GetComponent<ParticleGenerator>()->started = true;
		GameObject::Find(S("Duster2"))->GetComponent<ParticleGenerator>()->started = true;
		GameDataController::gd->setObjective(S("dream_day_2_awake"), true);
		PlayerController::pc->haltSoftLockProbe();
		if (GameDataController::gd->getObjectiveDetail(S("day1_complete")) >= 0)
		{
			PlayerController::wc->setSimpleTarget(Vector2(165.0f, 35.0f));
			Invoke(S("unlockPlayer"), 4.0f);
		}
		else
		{
			Invoke(S("continueSleeping"), 4.0f);
		}
		Invoke(S("fallKlapa"), 2.0f);
	}
	else if (GameDataController::gd->getObjective(S("dream_day_2_awake")) && GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day1_complete")) < 0 && !GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
	{
		PlayerController::wc->forceAnimation(S("stand_up"));
		PlayerController::wc->setSimpleTarget(Vector2(165.0f, 29.0f));
		GameObject::Find(S("WakeUp"))->transform->Find(S("GingerSpawner"))->GetComponent<NPCSpawner>()->spawnOrNot();
		GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->npcClickAction(String::Empty);
		GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setFlipped(true);
		GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->dir = NPCWalkController::Direction::SW;
		PlayerController::wc->dir = WalkController::Direction::SE;
	}
	if (!GameDataController::gd->getObjective(S("dream_day_4_awake")) && GameDataController::gd->getCurrentDay() == 4)
	{
		GameDataController::gd->setObjective(S("dream_day_4_awake"), true);
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
		{
			PlayerController::pc->haltSoftLockProbe();
			PlayerController::wc->setSimpleTarget(Vector2(165.0f, 35.0f));
			Invoke(S("unlockPlayer2"), 2.0f);
		}
		else
		{
			PlayerController::pc->setBusy(false);
		}
	}
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		darknessNormal->set_enabled(true);
		darknessNoRoof->set_enabled(false);
		if (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1)
		{
			darknessNormal->set_enabled(false);
			darknessNoRoof->set_enabled(true);
		}
		holes->set_enabled(true);
		rays->set_enabled(true);
		rays2->set_enabled(true);
	}
	else
	{
		darknessNormal->set_enabled(true);
		darknessNoRoof->set_enabled(false);
		holes->set_enabled(false);
		rays->set_enabled(false);
		rays2->set_enabled(false);
	}
}

void LocationBaseUpstairsStart::ignoreClicks(String a)
{
	PlayerController::pc->clickedAlreadyForSomething = true;
	PlayerController::pc->clickedSomething = true;
}

void LocationBaseUpstairsStart::continueSleeping()
{
	GameObject::Find(S("Stairs_Exit"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	GameObject::Find(S("Duster2"))->GetComponent<ParticleGenerator>()->started = false;
	PlayerController::pc->clickedSomething = true;
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("day2_overslept"), GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>(), Vector3(1.0f, 1.0f, 1.0f));
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->maxWidth = 200;
	list[list.Count() - 1]->actionWithText = false;
	list[list.Count() - 1]->action = [this](String val) { continueSleeping2(val); };
	list[0]->actionWithText = false;
	list[0]->action = [this](String a) { ignoreClicks(a); };
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	Timeline::t->doNotUnlock = true;
}

void LocationBaseUpstairsStart::continueSleeping2(String val)
{
	Timeline::t->doNotUnlock = true;
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->terminate();
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss(true);
	GameDataController::gd->setObjective(S("ginger_from_attic"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, S("sleep"), nullptr, false, nullptr, 0.02f);
	Invoke(S("Start"), 1.5f);
}

void LocationBaseUpstairsStart::unlockPlayer2()
{
	PlayerController::pc->setBusy(false);
	PlayerController::pc->resumeSoftLockProbe();
	if (GameDataController::gd->getObjective(S("npc3_alive")) || GameDataController::gd->getObjective(S("npc2_alive")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("dream4_ended_multi")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("dream4_ended_cate")));
	}
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		GameDataController::gd->setObjective(S("thug_to_kill_bathroom"), true);
	}
}

void LocationBaseUpstairsStart::unlockPlayer()
{
	PlayerController::pc->setBusy(false);
	PlayerController::pc->resumeSoftLockProbe();
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("heli_crash_what")));
	GameObject::Find(S("Stairs_Exit"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	GameObject::Find(S("Duster2"))->GetComponent<ParticleGenerator>()->started = false;
}

void LocationBaseUpstairsStart::fallKlapa()
{
	GameObject::Find(S("Duster"))->GetComponent<ParticleGenerator>()->started = false;
	GameObject::Find(S("Ladder"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	GameObject::Find(S("Ladder"))->transform->Find(S("faller"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	GameObject::Find(S("Ladder"))->transform->Find(S("faller"))->GetComponent<Animator>()->Play(S("klapa_fall"));
}

void LocationBaseUpstairsStart::Update()
{
}

#include "../game_all.h"

void LocationDream3Start::Start()
{
	plane0bla = GameObject::Find(S("plane0bla"))->GetComponent<SpriteRenderer>();
	window = GameObject::Find(S("Window"))->GetComponent<SpriteRenderer>();
	plane01 = GameObject::Find(S("plane01"))->GetComponent<SpriteRenderer>();
	plane01->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	alpha = 0.0f;
	alpha1 = 2.0f;
	alpha2 = 0.0f;
	PlayerController::wc->shadow->fadeRateV = 0.002f;
	PlayerController::wc->shadow->fadeRateH = 0.002f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 30.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 60.0f;
	PlayerController::ssg->setStepType2(S("wood"), AudioReverbPreset::Psychotic);
	PlayerController::pc->copySettingsToNPCs();
	MonoBehaviour::print(S("............................. LOCATION INFO  .................................."));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.5f);
	GameDataController::gd->traveledTime = 0;
	GameDataController::gd->workedTime = 0;
	GameObject::Find(S("StairEmmiter"))->GetComponent<ParticleGenerator>()->started = false;
	if (GameDataController::gd->getCurrentDay() == 3 && !GameDataController::gd->getObjective(S("dream_day_3_started")))
	{
		PlayerController::wc->currentXY.x = 180.0f;
		PlayerController::wc->currentXY.y = 20.0f;
		walkThere1();
		return;
	}
	alpha = 1.0f;
	alpha1 = 0.0f;
	alpha2 = 1.0f;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED / 2.0f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.75f);
	if ((GameDataController::gd->getObjective(S("previous_disc_barry")) || GameDataController::gd->getObjective(S("previous_disc_cody"))) && GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc2_joined")))
	{
		GameObject::Find(S("StairEmmiter"))->GetComponent<ParticleGenerator>()->started = true;
	}
}

void LocationDream3Start::walkThere1()
{
	Invoke(S("walkThere"), 0.25f);
}

void LocationDream3Start::walkThere()
{
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED / 2.0f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.75f);
	PlayerController::wc->currentXY.x = 150.0f;
	PlayerController::wc->currentXY.y = 25.0f;
	Vector2 simpleTarget = Vector2(98.0f, 25.0f);
	PlayerController::wc->setSimpleTarget(simpleTarget);
	PlayerController::wc->forceAnimation(S("walk_e"), true);
	if ((GameDataController::gd->getObjective(S("previous_disc_barry")) || GameDataController::gd->getObjective(S("previous_disc_cody"))) && GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc2_joined")))
	{
		GameObject::Find(S("StairEmmiter"))->GetComponent<ParticleGenerator>()->started = true;
	}
}

void LocationDream3Start::unlock()
{
	MonoBehaviour::print(S("UNLOCK"));
	GameObject::Find(S("Window"))->GetComponent<DreamWindow>()->updateAll();
	GameObject::Find(S("gears"))->GetComponent<GearsController>()->showGears();
	PlayerController::wc->fullStop();
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.75f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.75f);
	PlayerController::pc->setBusy(false);
	PlayerController::wc->forceAnimation(S("action_stnd_e"), true);
	PlayerController::wc->forceDirection(WalkController::Direction::SW);
	unlockThings(String::Empty);
}

void LocationDream3Start::unlockThings(String param)
{
	PlayerController::wc->forceAnimation(S("look_around"), true);
	Invoke(S("unlockThings2"), 0.25f);
}

void LocationDream3Start::unlockThings3(String param)
{
	GameObject::Find(S("FirstEncounter"))->GetComponent<FirstEncounterHouse>()->updateAll();
}

void LocationDream3Start::unlockThings2()
{
	if ((GameDataController::gd->getObjective(S("previous_disc_barry")) || GameDataController::gd->getObjective(S("previous_disc_cody"))) && GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc2_joined")))
	{
		PlayerController::wc->forceAnimation(S("stand_ne"));
		P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { unlockThings3(param); };
		timelineAction->actionWithText = false;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("day3_dream_stairs"));
		Timeline::t->addAction(timelineAction);
	}
	else
	{
		GameObject::Find(S("FirstEncounter"))->GetComponent<FirstEncounterHouse>()->updateAll();
	}
}

void LocationDream3Start::Update()
{
	if (PlayerController::wc->currentXY.x <= 100.0f && !GameDataController::gd->getObjective(S("dream_day_3_started")))
	{
		GameDataController::gd->setObjective(S("dream_day_3_started"), true);
		unlock();
	}
	window->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	plane01->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	stairs->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	float num = alpha1;
	if (num > 1.0f)
	{
		num = 1.0f;
	}
	plane0bla->set_color(Color(0.0f, 0.0f, 0.0f, num));
	if (alpha1 <= 0.0f && alpha < 1.0f)
	{
		alpha += 0.27f * Time::get_deltaTime();
	}
	if (alpha1 > 0.0f)
	{
		alpha1 -= 0.8f * Time::get_deltaTime();
	}
}

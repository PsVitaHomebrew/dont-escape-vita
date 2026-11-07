#include "../game_all.h"

void LocationDream4Start::Start()
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
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->moon, 0.5f);
	GameDataController::gd->traveledTime = 0;
	GameDataController::gd->workedTime = 0;
	alpha = 0.0f;
	alpha1 = 2.0f;
	alpha2 = 0.0f;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED / 2.0f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.75f);
	if (!GameDataController::gd->getObjective(S("dream_day_4_started")))
	{
		PlayerController::wc->currentXY.x = 180.0f;
		PlayerController::wc->currentXY.y = 20.0f;
		walkThere1();
	}
	else
	{
		alpha = 1.0f;
		alpha1 = 0.0f;
		alpha2 = 1.0f;
	}
	animationProgress0 = -1.0f;
}

void LocationDream4Start::walkThere1()
{
	Invoke(S("walkThere"), 0.25f);
}

void LocationDream4Start::walkThere()
{
	PlayerController::wc->currentXY.x = 150.0f;
	PlayerController::wc->currentXY.y = 25.0f;
	Vector2 simpleTarget = Vector2(98.0f, 25.0f);
	PlayerController::wc->setSimpleTarget(simpleTarget);
	PlayerController::wc->forceAnimation(S("walk_e"), true);
}

void LocationDream4Start::unlock()
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

void LocationDream4Start::unlockThings(String param)
{
	PlayerController::wc->forceAnimation(S("look_around"), true);
	Invoke(S("unlockThings2"), 0.25f);
}

void LocationDream4Start::unlockThings2()
{
	GameObject::Find(S("FirstEncounter"))->GetComponent<FirstEncounterHouse>()->updateAll();
}

void LocationDream4Start::fallMoon()
{
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->moon, 1.5f);
	PlayerController::wc->currentXY.x = -999.0f;
	PlayerController::wc->currentXY.y = -999.0f;
	PlayerController::wc->fullStop();
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->low_rumble2);
	GameObject::Find(S("SoundsManager"))->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->chorus2);
	animationProgress0 = 0.0f;
	Invoke(S("rumble"), 3.0f);
	Invoke(S("nextscene"), 10.0f);
}

void LocationDream4Start::rumble()
{
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->low_rumble);
}

void LocationDream4Start::nextscene()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		PlayerController::pc->spawnName = S("WakeUp");
		CurtainController::cc->fadeOut(S("LocationBaseUpstairs"), WalkController::Direction::S_, S("stand_up"), nullptr, true, nullptr, 0.2f);
		return;
	}
	GameDataController::gd->setObjective(S("location01_door2_locked"), false);
	GameDataController::gd->setObjective(S("location01_door2_open"), true);
	if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1)
	{
		GameDataController::gd->setObjectiveDetail(S("towel_1_at_door"), 0);
		P<Item> item = ItemsManager::im->getItem(S("towel_1"));
		item->dataRef->locX = 35;
		item->dataRef->locY = 35;
		item->dataRef->droppedLocation = S("Location1");
	}
	if (GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
	{
		GameDataController::gd->setObjectiveDetail(S("towel_2_at_door"), 0);
		P<Item> item2 = ItemsManager::im->getItem(S("towel_2"));
		item2->dataRef->locX = 35;
		item2->dataRef->locY = 35;
		item2->dataRef->droppedLocation = S("Location1");
	}
	PlayerController::pc->spawnName = S("Day4_morning");
	CurtainController::cc->fadeOut(S("LocationBaseOutside1"), WalkController::Direction::N);
}

void LocationDream4Start::Update()
{
	if (PlayerController::wc->currentXY.x <= 100.0f && !GameDataController::gd->getObjective(S("dream_day_4_started")))
	{
		GameDataController::gd->setObjective(S("dream_day_4_started"), true);
		unlock();
	}
	window->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	plane01->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	float num = alpha1;
	if (num > 1.0f)
	{
		num = 1.0f;
	}
	plane0bla->set_color(Color(0.0f, 0.0f, 0.0f, num));
	door->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	if (alpha1 <= 0.0f && alpha < 1.0f)
	{
		alpha += 0.27f * Time::get_deltaTime();
	}
	if (alpha1 > 0.0f)
	{
		alpha1 -= 0.8f * Time::get_deltaTime();
	}
	moon1->transform->set_position(Vector3(0.0f, 0.543f + -0.10099998f * animationProgress2, moon1->transform->get_position().z));
	moon2->transform->set_position(Vector3(0.0f, 0.65f + -0.802f * animationProgress, moon2->transform->get_position().z));
	moon3->transform->set_position(Vector3(0.0f, 1.096f + -1.9499999f * animationProgress, moon3->transform->get_position().z));
	meteor1->transform->set_position(Vector3(0.773f * animationProgress3 * 1.5f, 1.19f + -2.084f * animationProgress3 * 1.5f, meteor1->transform->get_position().z));
	meteor2->transform->set_position(Vector3(0.738f + -1.526f * animationProgress3 * 2.0f, 1.455f + -2.473f * animationProgress3 * 2.0f, meteor2->transform->get_position().z));
	moon1->transform->set_position(ScreenControler::roundToNearestFullPixel3(moon1->transform->get_position()));
	moon2->transform->set_position(ScreenControler::roundToNearestFullPixel3(moon2->transform->get_position()));
	moon3->transform->set_position(ScreenControler::roundToNearestFullPixel3(moon3->transform->get_position()));
	meteor1->transform->set_position(ScreenControler::roundToNearestFullPixel3(meteor1->transform->get_position()));
	meteor2->transform->set_position(ScreenControler::roundToNearestFullPixel3(meteor2->transform->get_position()));
	if (animationProgress0 < 0.0f)
	{
		moon1->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
		moon2->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
		moon3->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
		meteor1->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
		meteor2->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
		return;
	}
	moon1->set_color(Color(animationProgress0, animationProgress0, animationProgress0, 1.0f));
	moon2->set_color(Color(animationProgress0, animationProgress0, animationProgress0, 1.0f));
	moon3->set_color(Color(animationProgress0, animationProgress0, animationProgress0, 1.0f));
	meteor1->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
	meteor2->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
	animationProgress0 += Time::get_deltaTime() * 0.5f;
	if (animationProgress0 > 1.0f)
	{
		animationProgress0 = 1.0f;
	}
	animationProgress += Time::get_deltaTime() / 10.0f;
	if (animationProgress >= 1.0f)
	{
		animationProgress = 1.0f;
	}
	animationProgress3 += Time::get_deltaTime() / 5.0f;
	animationProgress2 += Time::get_deltaTime() / 5.0f;
	if (animationProgress2 >= 1.0f)
	{
		animationProgress2 = 1.0f;
	}
	if (animationProgress3 >= 1.0f)
	{
		animationProgress3 = 0.0f;
	}
}

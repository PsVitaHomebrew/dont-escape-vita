#include "../game_all.h"

void LocationDream3BStart::Start()
{
	reset();
}

void LocationDream3BStart::reset()
{
	plane0bla = GameObject::Find(S("plane0bla"))->GetComponent<SpriteRenderer>();
	plane01 = GameObject::Find(S("plane01"))->GetComponent<SpriteRenderer>();
	dream_stairs_front = GameObject::Find(S("dream_stairs_front"))->GetComponent<SpriteRenderer>();
	dream_stairs_front->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	plane01->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	alpha = 0.0f;
	alpha1 = 2.0f;
	alpha2 = 0.0f;
	zc1->set_enabled(true);
	zc2->set_enabled(false);
	PlayerController::wc->shadow->fadeRateV = 0.002f;
	PlayerController::wc->shadow->fadeRateH = 0.002f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 25.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 180.0f;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::ssg->setStepType2(S("wood"), AudioReverbPreset::Psychotic);
	PlayerController::pc->copySettingsToNPCs();
	MonoBehaviour::print(S("............................. LOCATION INFO  .................................."));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED / 4.0f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.5f);
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
	if (!GameDataController::gd->getObjective(S("dream_day_3b_started")))
	{
		PlayerController::wc->currentXY.x = 90.0f;
		PlayerController::wc->currentXY.y = 0.0f;
		walkThere1();
	}
	else
	{
		zc1->set_enabled(false);
		zc2->set_enabled(true);
		alpha = 1.0f;
		alpha1 = 0.0f;
		alpha2 = 1.0f;
	}
	GameDataController::gd->setObjective(S("dream_tiger_future"), false);
	GameDataController::gd->setObjective(S("dream_maggie_future"), false);
	GameObject::Find(S("DreamStairs"))->GetComponent<DreamStairsUpper>()->setCollider(-1);
	GameObject::Find(S("tiger"))->GetComponent<DreamTiger>()->setCollider(-1);
}

void LocationDream3BStart::walkThere1()
{
	Invoke(S("walkThere"), 0.25f);
}

void LocationDream3BStart::walkThere()
{
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED / 4.0f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.5f);
	Vector2 simpleTarget = Vector2(150.0f, 40.0f);
	PlayerController::wc->setSimpleTarget(simpleTarget);
	PlayerController::wc->forceAnimation(S("walk_e"));
}

void LocationDream3BStart::unlock()
{
	MonoBehaviour::print(S("UNLOCK"));
	zc1->set_enabled(false);
	zc2->set_enabled(true);
	PlayerController::wc->fullStop();
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.75f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.75f);
	PlayerController::pc->setBusy(false);
	PlayerController::wc->forceAnimation(S("action_stnd_e"));
	PlayerController::wc->forceDirection(WalkController::Direction::SW);
	unlockThings(String::Empty);
}

void LocationDream3BStart::unlockThings(String param)
{
	PlayerController::wc->forceAnimation(S("look_around"), true);
	Invoke(S("unlockThings2"), 0.25f);
}

void LocationDream3BStart::unlockThings2()
{
	GameObject::Find(S("DreamStairs"))->GetComponent<DreamStairsUpper>()->updateAll();
}

void LocationDream3BStart::Update()
{
	if (!GameDataController::gd->getObjective(S("dream_tiger_future")) && !GameDataController::gd->getObjective(S("dream_maggie_future")) && !(CurtainController::cc->targetLocaiton == S("Dream3")))
	{
		if (PlayerController::wc->currentXY.x >= 135.0f && !GameDataController::gd->getObjective(S("dream_day_3b_started")))
		{
			zc1->set_enabled(false);
			zc2->set_enabled(true);
		}
		if (PlayerController::wc->currentXY.x >= 140.0f && !GameDataController::gd->getObjective(S("dream_day_3b_started")))
		{
			GameDataController::gd->setObjective(S("dream_day_3b_started"), true);
			unlock();
		}
		plane01bed->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
		plane01->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
		dream_stairs_front->set_color(Color(alpha, alpha, alpha, 1.0f));
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
}

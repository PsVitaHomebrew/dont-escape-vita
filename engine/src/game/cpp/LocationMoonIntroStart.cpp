#include "../game_all.h"

void LocationMoonIntroStart::Start()
{
	speedMod = 0.0f;
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0015f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 8.0f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->source = 200.0f;
	PlayerController::ssg->setStepType(S("dirt"));
	PlayerController::wc->shadow->scaleFactor = 0.3f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	transition = false;
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->moon, 0.75f);
	PlayerController::wc->fullStop(true);
	realFakePlayerX = -0.9f;
}

void LocationMoonIntroStart::robSypuSypu()
{
	if (realX[0] > -3.32f)
	{
		int num = Random::Range(0, 4);
		if (num == 0)
		{
			aS->PlayOneShot(SoundsManagerController::sm->sand_pour1);
		}
		if (num == 1)
		{
			aS->PlayOneShot(SoundsManagerController::sm->sand_pour2);
		}
		if (num == 2)
		{
			aS->PlayOneShot(SoundsManagerController::sm->sand_pour3);
		}
		if (num == 3)
		{
			aS->PlayOneShot(SoundsManagerController::sm->sand_pour4);
		}
		Invoke(S("robSypuSypu"), Random::Range(0.25f, 1.25f));
	}
}

void LocationMoonIntroStart::Update()
{
	animProgress0 += Time::get_deltaTime() * 0.25f;
	if (animProgress0 > 0.2f && !jetStarted)
	{
		jetStarted = true;
		aS->PlayOneShot(SoundsManagerController::sm->jet2_mono);
	}
	if (animProgress0 >= 1.0f)
	{
		animProgress0 = 1.0f;
		animProgress1 += Time::get_deltaTime() * 0.5f;
		if (animProgress1 >= 1.0f)
		{
			animProgress1 = 1.0f;
		}
		animProgress2 += Time::get_deltaTime() * 0.25f;
		if (animProgress2 >= 1.0f)
		{
			animProgress2 = 1.0f;
			shuttleShadow->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
		}
		else
		{
			shuttleShadow->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 0.0f, 0.0f, animProgress2 * 0.75f));
		}
	}
	else
	{
		shuttleShadow->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
	}
	if (animProgress2 == 1.0f && !landed)
	{
		landed = true;
		shuttle->GetComponent<Animator>()->Play(S("shuttle_land"));
	}
	if ((double)realX[1] < 0.75 && !crashed)
	{
		crashed = true;
		shuttle->GetComponent<Animator>()->Play(S("shuttle_jump"));
		Invoke(S("robSypuSypu"), 1.0f);
	}
	if (crashed)
	{
		animProgress25 += Time::get_deltaTime() * 1.5f;
		if (animProgress25 >= 1.0f)
		{
			animProgress25 = 1.0f;
			animProgress3 += Time::get_deltaTime() * 3.0f;
			if (animProgress3 >= 1.0f)
			{
				animProgress3 = 1.0f;
				animProgress4 += Time::get_deltaTime() * 1.0f;
				if (animProgress4 >= 1.0f)
				{
					animProgress4 = 1.0f;
				}
			}
		}
	}
	if ((double)realX[0] < -2.0 && !stopping)
	{
		stopping = true;
		shuttle->GetComponent<Animator>()->Play(S("shuttle_stopping"));
		dust2->started = false;
		Invoke(S("nextScene"), 10.0f);
	}
	float num = animProgress1 / 2.0f + animProgress2 / 2.0f;
	float num2 = animProgress1 / 2.0f + animProgress2 / 2.0f - Mathf::Pow(0.0f - animProgress3 + animProgress4, 2.0f) * 0.1f;
	if (num > 1.0f)
	{
		num = 1.0f;
	}
	shuttle->transform->set_position(Vector3(-1.26f * (1.0f - num), 1.11f * (1.0f - num2), shuttle->transform->get_position().z));
	shuttle->transform->set_position(ScreenControler::roundToNearestFullPixel2(shuttle->transform->get_position()));
	shuttleShadow->transform->set_position(ScreenControler::roundToNearestFullPixel2(shuttleShadow->transform->get_position()));
	shuttleShadow->transform->set_position(Vector3(shuttle->transform->get_position().x, shuttle->transform->get_position().y * 0.25f, shuttle->transform->get_position().z + 0.1f));
	speedMod = 0.0f;
	speedMod += animProgress1;
	if (realX[1] < 0.5f)
	{
		speedMod *= 0.75f;
	}
	if (realX[0] < -2.5f)
	{
		speedMod *= 1.0f - (realX[0] + 2.5f) / -0.81999993f;
		if (speedMod < 0.1f)
		{
			speedMod = 0.1f;
		}
	}
	dust->maxParticles = 20 + (int)(20.0f * (1.0f - realX[0] / -3.32f));
	if (realX[0] <= -2.5f)
	{
		dust3->maxParticles = 10 + (int)(30.0f * (1.0f - realX[0] / -3.32f));
		dust4->maxParticles = 10 + (int)(30.0f * (1.0f - realX[0] / -3.32f));
		dust->started = false;
	}
	if (realX[0] <= -3.32f)
	{
		dust3->started = false;
		dust4->started = false;
		dust->started = false;
		speedMod = 0.0f;
	}
	for (int i = 0; i < 2; i++)
	{
		realX[i] -= speed[i] * Time::get_deltaTime() * speedMod;
		layer[i]->transform->set_position(Vector3(realX[i], layer[i]->transform->get_position().y, layer[i]->transform->get_position().z));
		layer[i]->transform->set_position(ScreenControler::roundToNearestFullPixel2(layer[i]->transform->get_position()));
	}
	bruzda->transform->set_position(Vector3(layer[0]->transform->get_position().x, layer[0]->transform->get_position().y, 0.4f));
}

void LocationMoonIntroStart::nextScene()
{
	GameDataController::gd->setObjective(S("moon_shocked1"), true);
	GameDataController::gd->setObjective(S("moon_shocked2"), true);
	GameDataController::gd->setObjective(S("moon_shocked3"), true);
	PlayerController::pc->spawnName = S("WakeUp");
	CurtainController::cc->fadeOut(S("MoonShip"), WalkController::Direction::E, S("wake_up"), nullptr, false, nullptr, 0.01f);
}

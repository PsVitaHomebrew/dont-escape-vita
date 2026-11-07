#include "../game_all.h"

void LocationSkyStart::Start()
{
	for (int i = 0; i < 4; i++)
	{
		realY[i] = layer[i]->transform->get_position().y;
	}
	speedMod = 0.0f;
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0015f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 8.0f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->source = 200.0f;
	PlayerController::ssg->setStepType(S("dirt"));
	GameObject::Find(S("FakePlayer"))->GetComponent<StepSoundGenerator>()->setStepType(S("dirt"));
	PlayerController::wc->shadow->scaleFactor = 0.3f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	transition = false;
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	PlayerController::wc->fullStop(true);
	realFakePlayerX = -0.9f;
	fakePlayer->GetComponent<StepSoundGenerator>()->useDoubleStepSound = false;
}

void LocationSkyStart::Update()
{
	if ((double)realY[3] < -0.9 && speedMod > 0.0f)
	{
		speedMod -= 0.3f * Time::get_deltaTime();
		if (speedMod < 0.0f)
		{
			speedMod = 0.0f;
		}
	}
	else if (speedMod < 1.0f)
	{
		speedMod += 0.3f * Time::get_deltaTime();
		if (speedMod > 1.0f)
		{
			speedMod = 1.0f;
		}
	}
	if (realFakePlayerX < 0.0f)
	{
		speedMod = 0.0f;
	}
	for (int i = 0; i < 4; i++)
	{
		realY[i] -= speed[i] * Time::get_deltaTime() * speedMod;
		layer[i]->transform->set_position(Vector3(layer[i]->transform->get_position().x, realY[i], layer[i]->transform->get_position().z));
		layer[i]->transform->set_position(ScreenControler::roundToNearestFullPixel2(layer[i]->transform->get_position()));
	}
	if (GameDataController::gd->getObjective(S("intro_desert_walked")))
	{
		realFakePlayerX += 0.19f * Time::get_deltaTime();
		float num = 1.5f - realFakePlayerX;
		if (num < 0.0f)
		{
			num = 0.0f;
		}
		if (num > 1.0f)
		{
			num = 1.0f;
		}
		fakePlayer->GetComponent<AudioSource>()->set_volume(num);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, num);
		fakePlayer->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(realFakePlayerX, fakePlayer->transform->get_position().y, fakePlayer->transform->get_position().z)));
	}
	else
	{
		GameObject::Find(S("FakePlayer"))->GetComponent<Animator>()->Play(S("FakePlayerStand"));
	}
	if (realFakePlayerX > 3.5f && !transition)
	{
		transition = true;
		PlayerController::pc->spawnName = S("InfoExit");
		CurtainController::cc->fadeOut(S("LocationDesertTitle"), WalkController::Direction::NULL_, nullptr, nullptr, false, nullptr, 1.0f);
	}
}

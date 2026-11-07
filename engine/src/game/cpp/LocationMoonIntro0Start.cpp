#include "../game_all.h"

void LocationMoonIntro0Start::Start()
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
	JukeboxMusic::jb->changeMusic(nullptr);
	PlayerController::wc->fullStop(true);
}

void LocationMoonIntro0Start::Update()
{
	animProgress0 += Time::get_deltaTime() * 0.5f;
	if (animProgress1 > 0.75f && !jetStarted)
	{
		jetStarted = true;
		aS->PlayOneShot(SoundsManagerController::sm->jet_mono);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->moon, 0.5f);
	}
	if (animProgress0 >= 1.0f)
	{
		animProgress0 = 1.0f;
		animProgress1 += Time::get_deltaTime() * 0.5f;
		if (animProgress1 >= 1.0f)
		{
			animProgress1 = 1.0f;
		}
	}
	if (realY[0] <= 1.0f && !landing)
	{
		landing = true;
		layer[4]->GetComponent<Animator>()->Play(S("shuttle_top_fly"));
	}
	speedMod = 0.0f;
	speedMod += animProgress1;
	if (realY[0] <= 2.0f)
	{
		speedMod = realY[0] / 2.0f;
		if (speedMod < 0.1f)
		{
			speedMod = 0.1f;
		}
	}
	if (realY[0] <= 0.7f)
	{
		speedMod = 0.0f;
	}
	if (realY[0] <= 0.7f && !transitioning)
	{
		transitioning = true;
		PlayerController::pc->spawnName = S("InfoExit");
		if (GameDataController::gd->getObjective(S("npc1_alive")))
		{
			CurtainController::cc->fadeOut(S("MoonIntro"), WalkController::Direction::N, nullptr, nullptr, false, nullptr, 0.1f);
		}
		else
		{
			CurtainController::cc->fadeOut(S("MoonIntroB"), WalkController::Direction::N, nullptr, nullptr, false, nullptr, 0.1f);
		}
	}
	for (int i = 0; i < realY.Count(); i++)
	{
		realY[i] -= speed[i] * Time::get_deltaTime() * speedMod;
		layer[i]->transform->set_position(Vector3(layer[i]->transform->get_position().x, realY[i], layer[i]->transform->get_position().z));
		layer[i]->transform->set_position(ScreenControler::roundToNearestFullPixel2(layer[i]->transform->get_position()));
	}
}

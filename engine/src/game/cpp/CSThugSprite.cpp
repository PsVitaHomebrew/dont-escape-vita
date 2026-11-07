#include "../game_all.h"

void CSThugSprite::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
}

void CSThugSprite::Update()
{
}

void CSThugSprite::hide()
{
	gameObject->GetComponent<Animator>()->Play(S("thug_dead"));
}

void CSThugSprite::show()
{
	gameObject->GetComponent<Animator>()->Play(S("thug_watch"));
}

void CSThugSprite::getShot()
{
	GameDataController::gd->setObjective(S("cs_thug_shot"), true);
	gameObject->GetComponent<Animator>()->Play(S("thug_shoot_dead"));
}

void CSThugSprite::shoot()
{
	aS->PlayOneShot(SoundsManagerController::sm->rifle_shoot);
	PlayerController::pc->setBusy(true);
	PlayerController::wc->forceAnimation(S("shot_n"), true);
}

void CSThugSprite::distracted()
{
	GameDataController::gd->setObjective(S("cs_guard_distracted"), true);
}

void CSThugSprite::distractedEnd()
{
	if (!GameDataController::gd->getObjective(S("cs_thug_shot")))
	{
		GameDataController::gd->setObjective(S("cs_guard_distracted"), false);
	}
}

void CSThugSprite::reset()
{
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("action1_e"), nullptr, true, [this]() { myk(); }, 0.01f);
}

void CSThugSprite::myk()
{
	cs2->playerShot = false;
	cs2->shootArea = false;
	PlayerController::wc->currentXY.x = 55.0f;
	PlayerController::wc->currentXY.y = 15.0f;
	PlayerController::wc->clearTarget();
}

#include "../game_all.h"

void GasstationSarge::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
}

void GasstationSarge::Update()
{
}

void GasstationSarge::lookLeft()
{
	GetComponent<SpriteRenderer>()->set_flipX(true);
}

void GasstationSarge::lookRight()
{
	GetComponent<SpriteRenderer>()->set_flipX(false);
}

void GasstationSarge::shot()
{
	if (!GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
	{
		GetComponent<Animator>()->Play(S("sarge_shot_back"));
	}
	else
	{
		GetComponent<Animator>()->Play(S("sarge_shot_front"));
	}
}

void GasstationSarge::decideRotation()
{
	if (PlayerController::wc->currentXY.x < 120.0f)
	{
		GetComponent<SpriteRenderer>()->set_flipX(true);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_flipX(false);
	}
}

void GasstationSarge::body_slam()
{
	aS->PlayOneShot(SoundsManagerController::sm->body_slam, 0.5f);
}

void GasstationSarge::body_thud()
{
	aS->PlayOneShot(SoundsManagerController::sm->body_thud, 0.5f);
}

void GasstationSarge::kneel()
{
	GetComponent<Animator>()->Play(S("sarge_kneel"));
}

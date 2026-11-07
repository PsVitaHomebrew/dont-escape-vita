#include "../game_all.h"

void LocationOutpost11Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.006f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 70.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 160.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Hallway);
	PlayerController::wc->shadow->scaleFactor = 0.25f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_outpost11"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
}

void LocationOutpost11Start::Update()
{
	playerMask->set_sprite(PlayerController::wc->sr->get_sprite());
	playerMask->transform->set_position(PlayerController::pc->transform->get_position());
	if (PlayerController::wc->sr->get_flipX())
	{
		playerMask->transform->set_localScale(Vector3(-1.0f, 1.0f, 1.0f));
	}
	else
	{
		playerMask->transform->set_localScale(Vector3(1.0f, 1.0f, 1.0f));
	}
	float num = PlayerController::wc->currentXY.y - 41.0f;
	num *= 0.01f;
	if (num < 0.0f)
	{
		num = 0.0f;
	}
	playerShadow->transform->set_position(PlayerController::pc->transform->get_position());
	playerShadow->transform->set_position(Vector3(playerShadow->transform->get_position().x - 0.02f, playerShadow->transform->get_position().y + 0.05f - num, -0.2f));
	playerShadow->set_sprite(PlayerController::wc->sr->get_sprite());
	playerShadow->set_flipX(PlayerController::wc->sr->get_flipX());
	playerShadow2->transform->set_position(PlayerController::pc->transform->get_position());
	playerShadow2->transform->set_position(Vector3(playerShadow2->transform->get_position().x - 0.01f, playerShadow2->transform->get_position().y + 0.05f - num, -0.2f));
	playerShadow2->set_sprite(PlayerController::wc->sr->get_sprite());
	playerShadow2->set_flipX(PlayerController::wc->sr->get_flipX());
	playerShadow2->transform->set_position(ScreenControler::roundToNearestFullPixel2(playerShadow2->transform->get_position()));
	playerShadow->transform->set_position(ScreenControler::roundToNearestFullPixel2(playerShadow->transform->get_position()));
	playerMask->transform->set_position(ScreenControler::roundToNearestFullPixel2(playerMask->transform->get_position()));
}

#include "../game_all.h"

void LocationCSCraneStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.01f;
	PlayerController::wc->shadow->fadeRateH = 0.001f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 10.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->scaleFactor = 0.3f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 240.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::METAL, AudioReverbPreset::Arena);
	craneThing->updateState();
	craneThing->currentX = craneThing->targetX;
	craneThing->currentY = craneThing->targetY;
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_metal, 1.0f);
	craneContrBack->set_enabled(false);
	l1->hideLever();
	l2->hideLever();
	l3->hideLever();
	firstTime = true;
}

void LocationCSCraneStart::zzz()
{
	l1->hideLever();
	l2->hideLever();
	l3->hideLever();
}

void LocationCSCraneStart::Update()
{
	if ((craneContrBack->get_enabled() || firstTime) && (PlayerController::wc->currentXY.x < 120.0f || firstTime))
	{
		firstTime = false;
		craneContrBack->set_enabled(false);
		l1->hideLever();
		l2->hideLever();
		l3->hideLever();
	}
}

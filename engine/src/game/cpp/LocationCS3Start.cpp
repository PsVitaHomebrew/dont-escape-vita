#include "../game_all.h"

void LocationCS3Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.01f;
	PlayerController::wc->shadow->fadeRateH = 0.001f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 20.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.4f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 240.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Off);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_metal, 1.0f);
	GameDataController::gd->setObjective(S("visited_cs_3"), true);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		GameDataController::gd->setObjective(S("cs_safe"), true);
		sciana1->set_enabled(false);
		sciana2->set_enabled(false);
		dzwig->set_enabled(true);
		tlo1->set_enabled(false);
		tlo2->set_enabled(true);
		if (GameDataController::gd->getObjective(S("cs_pack_lifted")))
		{
			areaRainFull->set_enabled(true);
			areaRain1->set_enabled(false);
			areaRain2->set_enabled(false);
			areaThugs->set_enabled(false);
		}
		else if (GameDataController::gd->getObjective(S("cs_rain_enter_left")))
		{
			areaRainFull->set_enabled(false);
			areaRain1->set_enabled(true);
			areaRain2->set_enabled(false);
			areaThugs->set_enabled(false);
		}
		else
		{
			areaRainFull->set_enabled(false);
			areaRain1->set_enabled(false);
			areaRain2->set_enabled(true);
			areaThugs->set_enabled(false);
		}
	}
	else
	{
		sciana1->set_enabled(true);
		sciana2->set_enabled(true);
		dzwig->set_enabled(false);
		tlo1->set_enabled(true);
		tlo2->set_enabled(false);
		areaRainFull->set_enabled(false);
		areaRain1->set_enabled(false);
		areaRain2->set_enabled(false);
		areaThugs->set_enabled(true);
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	if (!GameDataController::gd->getObjective(S("cs_safe")))
	{
		GameObject::Find(S("Smoker"))->GetComponent<ParticleGenerator>()->started = true;
	}
	else
	{
		GameObject::Find(S("Smoker"))->GetComponent<ParticleGenerator>()->started = false;
	}
}

void LocationCS3Start::Update()
{
	Vector3 vector = Vector3(PlayerController::wc->currentXY.x, 0.0f, PlayerController::pc->transform->get_position().z);
	if (!GameDataController::gd->getObjective(S("cs_safe")) && PlayerController::wc->currentXY.x > 145.0f)
	{
		PlayerController::wc->currentXY.x = 144.0f;
		PlayerController::wc->fullStop(true);
		PlayerController::wc->forceAnimation(S("stand_e"));
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("cs_dont_walk_there"));
		Timeline::t->addAction(timelineAction);
	}
}

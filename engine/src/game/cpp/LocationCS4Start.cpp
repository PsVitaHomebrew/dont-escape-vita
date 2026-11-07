#include "../game_all.h"

void LocationCS4Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.01f;
	PlayerController::wc->shadow->fadeRateH = 0.001f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 10.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.3f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 240.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Off);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_metal, 1.0f);
	GameDataController::gd->setObjective(S("visited_cs_4"), true);
	if (!GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("LocationOtherHitTest"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
	}
	else
	{
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("LocationOtherHitTest"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void LocationCS4Start::Update()
{
}

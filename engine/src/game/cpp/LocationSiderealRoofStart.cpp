#include "../game_all.h"

void LocationSiderealRoofStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -3.0f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->source = 140.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::ROAD);
	PlayerController::wc->shadow->scaleFactor = 0.6f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	PlayerController::pc->allowDrop = false;
	GameDataController::gd->setObjective(S("visited_sidereal_roof"), true);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_3, 1.0f);
	if (GameDataController::gd->getObjective(S("barry_warned")))
	{
		GameDataController::gd->setObjective(S("npc2_joined"), false);
	}
	if (GameDataController::gd->getObjective(S("cody_warned")))
	{
		GameDataController::gd->setObjective(S("npc3_joined"), false);
	}
	lf->hideAndWait();
	setWalkablePath();
	if (GameDataController::gd->getObjective(S("sidereal_roof_collapsed")))
	{
		lf->quickFall();
		if (GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
		{
			JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_action_loop, true, 0.0f, 0.0f);
		}
		else
		{
			JukeboxMusic::jb->changeMusic(nullptr);
		}
	}
	else
	{
		JukeboxMusic::jb->changeMusic(nullptr);
	}
}

void LocationSiderealRoofStart::setWalkablePath()
{
	if (!GameDataController::gd->getObjective(S("sidereal_roof_collapsed")))
	{
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("LocationCollapsed"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	}
	else
	{
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("LocationCollapsed"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	}
}

void LocationSiderealRoofStart::Update()
{
}

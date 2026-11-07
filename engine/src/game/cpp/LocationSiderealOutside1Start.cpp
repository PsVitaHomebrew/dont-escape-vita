#include "../game_all.h"

void LocationSiderealOutside1Start::Start()
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
	PlayerController::ssg->setStepType2(StepSoundGenerator::ROAD, AudioReverbPreset::Off);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	if (GameDataController::gd->getObjective(S("barry_warned")))
	{
		GameDataController::gd->setObjective(S("npc2_joined"), true);
	}
	if (GameDataController::gd->getObjective(S("cody_warned")))
	{
		GameDataController::gd->setObjective(S("npc3_joined"), true);
	}
	if (GameDataController::gd->getCurrentDay() == 4)
	{
		GameDataController::gd->setObjectiveDetail(S("map_outpost_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	}
	if (!GameDataController::gd->getObjective(S("visited_sidereal_outside_1")))
	{
		if (GameDataController::gd->getObjectiveDetail(S("visited_sidereal_outside_1")) == 0)
		{
			GameDataController::gd->setObjectiveDetail(S("visited_sidereal_outside_1"), 1);
			PlayerController::pc->spawnName = S("InfoExit");
			GameDataController::gd->previousLocation = SceneManager::GetActiveScene().get_name();
			GameDataController::gd->previousX = (int)PlayerController::wc->currentXY.x;
			GameDataController::gd->previousY = (int)PlayerController::wc->currentXY.y;
			CurtainController::cc->fadeOut(S("Day3Cutscene"));
		}
		else
		{
			PlayerController::pc->clickedAlreadyForSomething = false;
			PlayerController::pc->clickedSomething = false;
			PlayerController::pc->setBusy(true);
			Invoke(S("talkafterawhile"), 1.0f);
		}
	}
	if (GameDataController::gd->getObjective(S("sidereal_roof_collapsed")))
	{
		plane1->set_enabled(false);
		plane2->set_enabled(true);
	}
	else
	{
		plane1->set_enabled(true);
		plane2->set_enabled(false);
	}
}

void LocationSiderealOutside1Start::talkafterawhile()
{
	GameDataController::gd->setObjective(S("visited_sidereal_outside_1"), true);
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->npcClickAction(String::Empty);
}

void LocationSiderealOutside1Start::Update()
{
}

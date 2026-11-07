#include "../game_all.h"

void LocationFuseboxStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 1.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("rubber"));
	PlayerController::wc->shadow->scaleFactor = 0.5f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_metal_inside, 0.6f);
	if (!GameDataController::gd->getObjective(S("visited_fusebox")))
	{
		PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("outpost_fuse_briefning_1")));
		PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("outpost_fuse_briefning_2")));
		PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("outpost_fuse_briefning_3")));
		PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("outpost_fuse_briefning_4")));
	}
	GameDataController::gd->setObjective(S("visited_fusebox"), true);
}

void LocationFuseboxStart::Update()
{
}

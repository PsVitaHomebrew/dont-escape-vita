#include "../game_all.h"

void LocationMoonIntro0Ship::Start()
{
}

void LocationMoonIntro0Ship::Update()
{
}

void LocationMoonIntro0Ship::goToNextScene()
{
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("MoonIntro"), WalkController::Direction::N, nullptr, nullptr, false, nullptr, 0.1f);
}

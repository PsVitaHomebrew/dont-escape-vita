#include "../game_all.h"

void SnowController::Start()
{
	if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
	{
		int num = GameDataController::gd->timeLimit - GameDataController::gd->gameTime;
		int num2 = 120;
		num2 -= num / 6;
		if (num2 < 4)
		{
			num2 = 4;
		}
		s1->maxParticles = num2;
		s2->maxParticles = num2;
		s3->maxParticles = num2;
		s1->started = true;
		s2->started = true;
		s3->started = true;
		Invoke(S("snowRangeYChange"), 1.0f);
	}
	else
	{
		s1->started = false;
		s2->started = false;
		s3->started = false;
	}
}

void SnowController::snowRangeYChange()
{
	s1->ySpread = 0;
	s2->ySpread = 0;
	s3->ySpread = 0;
}

void SnowController::Update()
{
}

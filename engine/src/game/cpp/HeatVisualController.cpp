#include "../game_all.h"

void HeatVisualController::Start()
{
	sr = GetComponent<SpriteRenderer>();
	if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		sr->set_enabled(true);
		int num = GameDataController::gd->timeLimit - GameDataController::gd->gameTime;
		alfa = 1.0f - (float)num / 1000.0f;
		if (alfa < 0.0f)
		{
			alfa = 0.0f;
		}
		if (alfa > 1.0f)
		{
			alfa = 1.0f;
		}
		sr->set_color(Color(1.0f, 1.0f, 1.0f, alfa));
		MonoBehaviour::print(num + S(" ") + alfa);
	}
	else
	{
		sr->set_enabled(false);
	}
}

void HeatVisualController::Update()
{
	if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		if (delay <= 0.0f)
		{
			int num;
			do
			{
				num = Random::Range(0, 5);
			}
			while (num == lastran);
			lastran = num;
			switch (num)
			{
			case 0:
				sr->set_sprite(s1);
				break;
			case 1:
				sr->set_sprite(s2);
				break;
			case 2:
				sr->set_sprite(s3);
				break;
			case 3:
				sr->set_sprite(s4);
				break;
			case 4:
				sr->set_sprite(s5);
				break;
			}
			delay = 0.02f;
			sr->set_enabled(true);
			int num2 = GameDataController::gd->timeLimit - GameDataController::gd->gameTime;
			alfa = 1.2f - (float)num2 / 1500.0f;
			if (alfa < 0.0f)
			{
				alfa = 0.0f;
			}
			if (alfa > 1.0f)
			{
				alfa = 1.0f;
			}
			sr->set_color(Color(1.0f, 1.0f, 1.0f, alfa));
		}
		else
		{
			delay -= Time::get_deltaTime();
		}
	}
	else
	{
		sr->set_enabled(false);
	}
}

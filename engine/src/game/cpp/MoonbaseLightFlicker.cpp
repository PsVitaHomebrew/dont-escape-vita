#include "../game_all.h"

void MoonbaseLightFlicker::Start()
{
	time1 = Random::Range(1.0f, 2.0f);
	time2 = Random::Range(1.0f, 2.0f);
	if (GameDataController::gd->getObjective(S("moon_light_failed")) && !GameDataController::gd->getObjective(S("moon_light_restored")))
	{
		lightsFailed = true;
	}
	else
	{
		lightsFailed = false;
	}
	if (GameDataController::gd->getObjective(S("moon_light_restored")) && !GameDataController::gd->getObjective(S("moon_door_closed")))
	{
		time1 = 10.0f;
		time2 = 10.0f;
		lm->needShake = 0.0f;
		darkness->set_enabled(false);
	}
}

void MoonbaseLightFlicker::Update()
{
	if (lightsFailed)
	{
		darkness->set_enabled(true);
		if (darkness2 != nullptr)
		{
			darkness2->set_enabled(true);
		}
	}
	else if (lm->needShake > 0.0f)
	{
		if (time1 <= 0.0f)
		{
			lights->set_enabled(!lights->get_enabled());
			time1 = Random::Range(0.0f, 0.5f);
		}
		else
		{
			time1 -= Time::get_deltaTime();
		}
		if (time2 <= 0.0f)
		{
			darkness->set_enabled(!darkness->get_enabled());
			if (darkness2 != nullptr)
			{
				darkness2->set_enabled(!darkness2->get_enabled());
			}
			time2 = Random::Range(0.0f, 0.5f);
		}
		else
		{
			time2 -= Time::get_deltaTime();
		}
	}
	else
	{
		darkness->set_enabled(false);
		if (darkness2 != nullptr)
		{
			darkness2->set_enabled(false);
		}
		lights->set_enabled(true);
		time1 = Random::Range(0.0f, 1.0f);
		time2 = Random::Range(0.0f, 1.0f);
	}
	charLights();
}

void MoonbaseLightFlicker::charLights()
{
	float num = 1.0f;
	if (darkness->get_enabled())
	{
		num = 0.5f;
	}
	PlayerController::wc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(num, num, num));
	cody->colorBlue = num;
	cody->colorRed = num;
	cody->colorGreen = num;
	cody->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(cody->colorRed, cody->colorGreen, cody->colorBlue, cody->colorAlpha));
	cate->colorBlue = num;
	cate->colorRed = num;
	cate->colorGreen = num;
	cate->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(cate->colorRed, cate->colorGreen, cate->colorBlue, cate->colorAlpha));
	barry->colorBlue = num;
	barry->colorRed = num;
	barry->colorGreen = num;
	barry->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(barry->colorRed, barry->colorGreen, barry->colorBlue, barry->colorAlpha));
	if (moreObjects1 != nullptr)
	{
		moreObjects1->set_color(Color(num, num, num, 1.0f));
	}
	if (moreObjects2 != nullptr)
	{
		moreObjects2->set_color(Color(num, num, num, 1.0f));
	}
	if (moreObjects3 != nullptr)
	{
		moreObjects3->set_color(Color(num, num, num, 1.0f));
	}
	if (moreObjects4 != nullptr)
	{
		moreObjects4->set_color(Color(num, num, num, 1.0f));
	}
	if (moreObjects5 != nullptr)
	{
		moreObjects5->set_color(Color(num, num, num, 1.0f));
	}
}

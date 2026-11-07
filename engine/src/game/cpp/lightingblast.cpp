#include "../game_all.h"

void lightingblast::Start()
{
	light = GetComponent<SpriteRenderer>();
	aS = GetComponent<AudioSource>();
}

void lightingblast::initthis()
{
	light = GetComponent<SpriteRenderer>();
	aS = GetComponent<AudioSource>();
}

void lightingblast::strike(P<AudioClip> thunder, float pre, bool post, float vol, float ma)
{
	aS->set_pitch(Random::Range(0.8f, 1.2f));
	aS->PlayOneShot(thunder, vol);
	light->set_enabled(true);
	light->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
	if (pre == 0.0f && !post)
	{
		light->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	}
	maxAlpha = ma;
	prelight = pre;
	postlight = post;
}

void lightingblast::startAutoBlast()
{
	autoblastDelay = -50.0f;
}

void lightingblast::Update()
{
	if (light->get_enabled())
	{
		if (prelight > 0.0f)
		{
			prelight -= Time::get_deltaTime();
			light->set_color(Color(1.0f, 1.0f, 1.0f, Random::Range(0.0f, maxAlpha)));
			if (prelight <= 0.0f && postlight)
			{
				light->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (prelight <= 0.0f)
			{
				light->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
		else if (postlight)
		{
			light->set_color(Color(1.0f, 1.0f, 1.0f, light->get_color().a - Time::get_deltaTime()));
			if (light->get_color().a <= 0.0f)
			{
				light->set_enabled(false);
			}
		}
		else
		{
			light->set_enabled(false);
		}
	}
	if (autoblastDelay == -111.0f)
	{
		if (GameDataController::gd->gameTime > 1100)
		{
			autoblastDelay = (float)Random::Range(2, 10);
		}
		else if (GameDataController::gd->gameTime > 1000)
		{
			autoblastDelay = (float)Random::Range(4, 20);
		}
		else if (GameDataController::gd->gameTime > 900)
		{
			autoblastDelay = (float)Random::Range(6, 30);
		}
		else if (GameDataController::gd->gameTime > 800)
		{
			autoblastDelay = (float)Random::Range(8, 40);
		}
		else if (GameDataController::gd->gameTime > 700)
		{
			autoblastDelay = (float)Random::Range(10, 50);
		}
		else if (GameDataController::gd->gameTime > 600)
		{
			autoblastDelay = (float)Random::Range(15, 60);
		}
		else
		{
			autoblastDelay = (float)Random::Range(20, 70);
		}
	}
	if (autoblastDelay > 0.0f)
	{
		autoblastDelay -= Time::get_deltaTime();
	}
	else if (GameDataController::gd->gameTime > 1100)
	{
		autoblastDelay = (float)Random::Range(5, 20);
		P<AudioClip> thunder = nullptr;
		int num = Random::Range(0, 3);
		if (num == 0)
		{
			thunder = SoundsManagerController::sm->thunder4;
		}
		if (num == 1)
		{
			thunder = SoundsManagerController::sm->thunder5;
		}
		if (num == 2)
		{
			thunder = SoundsManagerController::sm->thunder3;
		}
		strike(thunder, Random::Range(0.5f, 1.2f), true, 0.6f);
	}
	else if (GameDataController::gd->gameTime > 1000)
	{
		autoblastDelay = (float)Random::Range(10, 40);
		P<AudioClip> thunder2 = nullptr;
		int num2 = Random::Range(0, 3);
		if (num2 == 0)
		{
			thunder2 = SoundsManagerController::sm->thunder4;
		}
		if (num2 == 1)
		{
			thunder2 = SoundsManagerController::sm->thunder3;
		}
		if (num2 == 2)
		{
			thunder2 = SoundsManagerController::sm->thunder3;
		}
		strike(thunder2, Random::Range(0.3f, 0.7f), true, 0.8f);
	}
	else if (GameDataController::gd->gameTime > 900)
	{
		autoblastDelay = (float)Random::Range(15, 45);
		P<AudioClip> thunder3 = nullptr;
		int num3 = Random::Range(0, 2);
		if (num3 == 0)
		{
			thunder3 = SoundsManagerController::sm->thunder3;
		}
		if (num3 == 1)
		{
			thunder3 = SoundsManagerController::sm->thunder2;
		}
		strike(thunder3, Random::Range(0.2f, 0.8f), false, 0.5f);
	}
	else if (GameDataController::gd->gameTime > 800)
	{
		autoblastDelay = (float)Random::Range(20, 55);
		P<AudioClip> thunder4 = nullptr;
		int num4 = Random::Range(0, 3);
		if (num4 == 0)
		{
			thunder4 = SoundsManagerController::sm->thunder1;
		}
		if (num4 == 1)
		{
			thunder4 = SoundsManagerController::sm->thunder2;
		}
		if (num4 == 2)
		{
			thunder4 = SoundsManagerController::sm->thunder3;
		}
		strike(thunder4, Random::Range(0.0f, 0.5f), false, 0.25f);
	}
	else if (GameDataController::gd->gameTime > 700)
	{
		autoblastDelay = (float)Random::Range(25, 70);
		P<AudioClip> thunder5 = nullptr;
		int num5 = Random::Range(0, 3);
		if (num5 == 0)
		{
			thunder5 = SoundsManagerController::sm->thunder1;
		}
		if (num5 == 1)
		{
			thunder5 = SoundsManagerController::sm->thunder2;
		}
		if (num5 == 2)
		{
			thunder5 = SoundsManagerController::sm->thunder3;
		}
		strike(thunder5, 0.0f, false);
	}
	else if (GameDataController::gd->gameTime > 600)
	{
		autoblastDelay = (float)Random::Range(30, 80);
		P<AudioClip> thunder6 = nullptr;
		int num6 = Random::Range(0, 2);
		if (num6 == 0)
		{
			thunder6 = SoundsManagerController::sm->thunder1;
		}
		if (num6 == 1)
		{
			thunder6 = SoundsManagerController::sm->thunder2;
		}
		strike(thunder6, 0.0f, false);
	}
	else
	{
		autoblastDelay = (float)Random::Range(20, 30);
	}
}

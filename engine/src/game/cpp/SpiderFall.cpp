#include "../game_all.h"

void SpiderFall::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	pos = gameObject->transform->get_position();
	gameObject->GetComponent<Animator>()->Play(S("fall"));
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	speedY = 0.7f;
	speedX = 0.4f;
	if (iii >= 3)
	{
		speedX = 1.0f;
	}
	started = false;
	delay = (iii - 1) * 5;
	pos = Vector3(gameObject->transform->get_position().x, gameObject->transform->get_position().y, gameObject->transform->get_position().z);
}

void SpiderFall::startFall()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hiss, 0.25f);
	if (iii >= 4)
	{
		Invoke(S("startFall2"), Random::Range(0.25f, 1.0f));
	}
	else
	{
		startFall2();
	}
}

void SpiderFall::startFall2()
{
	started = true;
	gameObject->GetComponent<Animator>()->Play(S("fall"));
}

void SpiderFall::Update()
{
	if (!started)
	{
		return;
	}
	if (delay > 0)
	{
		delay--;
		return;
	}
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	if (speedY > -0.6f)
	{
		speedY -= 0.1f * Time::get_deltaTime() * 60.0f;
	}
	if (pos.y < targetY)
	{
		speedY = 0.0f;
	}
	if (Mathf::Abs(pos.x - targetX) < 0.1f)
	{
		speedX = 0.0f;
	}
	if (pos.x < targetX)
	{
		pos.x += speedX * Time::get_deltaTime() * 2.0f;
	}
	if (pos.x > targetX)
	{
		pos.x -= speedX * Time::get_deltaTime() * 2.0f;
	}
	if (speedX == 0.0f && speedY == 0.0f && started && pos.y < targetY)
	{
		started = false;
		if (iii == 3)
		{
			gameObject->GetComponent<Animator>()->Play(S("hit_fast"));
		}
		else
		{
			gameObject->GetComponent<Animator>()->Play(S("eat_fast"));
		}
	}
	pos.y += speedY * Time::get_deltaTime() * 2.0f;
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(pos));
}

#include "../game_all.h"

void BugFly::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	started = false;
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	speedModY = 0.0f;
	speedModX = 0.0f;
	targetSpeedModX = 0.0f;
	targetSpeedModY = 0.0f;
	speed.x = 1.0f;
	speed.y = 1.0f;
	if (Random::get_value() > 0.5f)
	{
		speed.x = -1.0f;
	}
	if (Random::get_value() > 0.5f)
	{
		speed.y = -1.0f;
	}
	bounds.x -= Random::Range(0.0f, 0.2f);
	bounds.y -= Random::Range(0.0f, 0.2f);
	bounds.z += Random::Range(0.0f, 0.2f);
	bounds.w += Random::Range(0.0f, 0.2f);
}

void BugFly::startFly(int i)
{
	pos = Vector3(gameObject->transform->get_position().x, gameObject->transform->get_position().y, gameObject->transform->get_position().z);
	Invoke(S("startFly2"), (float)i * 0.03f);
}

void BugFly::startFly2()
{
	speed.x = 1.0f;
	speed.y = 1.0f;
	if (Random::get_value() > 0.5f)
	{
		speed.x = -1.0f;
	}
	if (Random::get_value() > 0.5f)
	{
		speed.y = -1.0f;
	}
	started = true;
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
}

void BugFly::Update()
{
	if (started)
	{
		if (pos.x < bounds.x && speed.x < 0.0f)
		{
			speed.x *= -1.0f;
		}
		if (pos.x > bounds.z && speed.x > 0.0f)
		{
			speed.x *= -1.0f;
		}
		if (pos.y < bounds.y && speed.y < 0.0f)
		{
			speed.y *= -1.0f;
		}
		if (pos.y > bounds.w && speed.y > 0.0f)
		{
			speed.y *= -1.0f;
		}
		if (speed.x < 0.0f)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
		}
		else
		{
			gameObject->GetComponent<SpriteRenderer>()->set_flipX(false);
		}
		pos.x += speed.x * speedModX * Time::get_deltaTime() * 120.0f;
		pos.y += speed.y * speedModY * Time::get_deltaTime() * 120.0f;
		gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(pos));
		if (Mathf::Abs(speedModX - targetSpeedModX) < 0.001f * Time::get_deltaTime() * 60.0f)
		{
			targetSpeedModX = Random::Range(0.003f, 0.02f);
		}
		else if (speedModX > targetSpeedModX)
		{
			speedModX -= 0.001f * Time::get_deltaTime() * 60.0f;
		}
		else if (speedModX < targetSpeedModX)
		{
			speedModX += 0.001f * Time::get_deltaTime() * 60.0f;
		}
		if (Mathf::Abs(speedModY - targetSpeedModY) < 0.001f * Time::get_deltaTime() * 60.0f)
		{
			targetSpeedModY = Random::Range(0.003f, 0.02f);
		}
		else if (speedModY > targetSpeedModY)
		{
			speedModY -= 0.001f * Time::get_deltaTime() * 60.0f;
		}
		else if (speedModY < targetSpeedModY)
		{
			speedModY += 0.001f * Time::get_deltaTime() * 60.0f;
		}
	}
}

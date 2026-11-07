#include "../game_all.h"

void ParticleController::Start()
{
	spriteR = gameObject->GetComponent<SpriteRenderer>();
	alpha = 0.0f;
	targetAlpha = Random::Range(minAlpha, maxAlpha);
}

void ParticleController::Update()
{
	if (globalized)
	{
		currentXY.x += ((float)currentSpeedX / speedDiv + WindBlower::globalSpeedX / speedDiv) * Time::get_deltaTime() * 60.0f;
		currentXY.y += ((float)currentSpeedY / speedDiv + WindBlower::globalSpeedY / speedDiv) * Time::get_deltaTime() * 60.0f;
	}
	else
	{
		currentXY.x += (float)currentSpeedX / speedDiv * Time::get_deltaTime() * 60.0f;
		currentXY.y += (float)currentSpeedY / speedDiv * Time::get_deltaTime() * 60.0f;
	}
	if ((double)Random::get_value() > 0.5)
	{
		currentSpeedX++;
	}
	else
	{
		currentSpeedX--;
	}
	if ((double)Random::get_value() > 0.5)
	{
		currentSpeedY++;
	}
	else
	{
		currentSpeedY--;
	}
	if (currentSpeedX > speedXMax)
	{
		currentSpeedX = speedXMax;
	}
	if (currentSpeedX < speedXMin)
	{
		currentSpeedX = speedXMin;
	}
	if (currentSpeedY > speedYMax)
	{
		currentSpeedY = speedYMax;
	}
	if (currentSpeedY < speedYMin)
	{
		currentSpeedY = speedYMin;
	}
	spriteR->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	currentLifetime += 60.0f * Time::get_deltaTime();
	if (currentLifetime > (float)lifetime)
	{
		alpha -= fadeOutStep;
		if (alpha <= 0.0f)
		{
			die = true;
		}
	}
	else if (alpha < targetAlpha)
	{
		alpha += fadeInStep;
	}
	Vector2 vector = ScreenControler::gameToScreen(currentXY);
	gameObject->transform->set_position(Camera::get_main()->ScreenToWorldPoint(vector));
}

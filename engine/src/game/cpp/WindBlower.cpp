#include "../game_all.h"

void WindBlower::Start()
{
	globalSpeedX = 0.0f;
	globalSpeedY = 0.0f;
}

void WindBlower::Update()
{
	if (currentDelta >= delta)
	{
		currentDelta = 0;
		delta = Random::Range(minDelta, maxDelta);
		targetSpeedX = Random::Range(minSpeedX, maxSpeedX);
		targetSpeedY = Random::Range(minSpeedY, maxSpeedY);
	}
	else
	{
		currentDelta++;
	}
	if (globalSpeedX < targetSpeedX)
	{
		globalSpeedX += deltaX;
	}
	if (globalSpeedX > targetSpeedX)
	{
		globalSpeedX -= deltaX;
	}
	if (Mathf::Abs(globalSpeedX - targetSpeedX) < deltaX)
	{
		globalSpeedX = targetSpeedX;
	}
	if (globalSpeedY < targetSpeedY)
	{
		globalSpeedY += deltaY;
	}
	if (globalSpeedY > targetSpeedY)
	{
		globalSpeedY -= deltaY;
	}
	if (Mathf::Abs(globalSpeedY - targetSpeedY) < deltaY)
	{
		globalSpeedY = targetSpeedY;
	}
}

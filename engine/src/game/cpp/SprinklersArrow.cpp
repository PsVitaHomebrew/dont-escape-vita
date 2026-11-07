#include "../game_all.h"

void SprinklersArrow::Start()
{
	sr = GetComponent<SpriteRenderer>();
	fastUpdate = true;
}

void SprinklersArrow::Update()
{
	int num = 0;
	if (GameDataController::gd->getObjective(S("barn_sprinklers_b1")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("barn_sprinklers_b2")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("barn_sprinklers_b3")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("barn_sprinklers_b4")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("barn_sprinklers_b5")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("barn_sprinklers_b6")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("barn_sprinklers_b7")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("barn_sprinklers_b8")))
	{
		num++;
	}
	num *= 2;
	if (fastUpdate)
	{
		currentDisplay = num;
		sr->set_sprite(arrows[currentDisplay]);
	}
	if (num == currentDisplay)
	{
		return;
	}
	if (delay >= maxDelay)
	{
		delay = 0;
		if (num < currentDisplay)
		{
			currentDisplay--;
		}
		else if (num > currentDisplay)
		{
			currentDisplay++;
		}
		sr->set_sprite(arrows[currentDisplay]);
	}
	else
	{
		delay++;
	}
}

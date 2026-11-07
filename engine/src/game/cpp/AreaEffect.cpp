#include "../game_all.h"

void AreaEffect::Awake()
{
}

void AreaEffect::Start()
{
	npcs = Object::FindObjectsOfType<NPCWalkController>();
	lastPos = Array<Vector2>::New(npcs.Length());
	playerPos = Vector2(0.0f, 0.0f);
}

void AreaEffect::refresh()
{
	playerPos = Vector2(0.0f, 0.0f);
	lastPos = Array<Vector2>::New(npcs.Length());
}

void AreaEffect::Update()
{
	if (playerPos.x != PlayerController::wc->currentXY.x || playerPos.y != PlayerController::wc->currentXY.y)
	{
		playerPos.x = PlayerController::wc->currentXY.x;
		playerPos.y = PlayerController::wc->currentXY.y;
		if ((bool)Physics2D::Linecast(Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(PlayerController::wc->currentXY)), Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(PlayerController::wc->currentXY)), actionLayer))
		{
			Action(PlayerController::wc, nullptr, nullptr);
		}
		else
		{
			Action2(PlayerController::wc, nullptr, nullptr);
		}
	}
	for (int i = 0; i < npcs.Length(); i++)
	{
		if (lastPos[i].x != npcs[i]->currentXY.x || lastPos[i].y != npcs[i]->currentXY.y)
		{
			lastPos[i].x = npcs[i]->currentXY.x;
			lastPos[i].y = npcs[i]->currentXY.y;
			if ((bool)Physics2D::Linecast(Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(npcs[i]->currentXY)), Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(npcs[i]->currentXY)), actionLayer))
			{
				Action(nullptr, npcs[i], nullptr);
			}
			else
			{
				Action2(nullptr, npcs[i], nullptr);
			}
		}
	}
}

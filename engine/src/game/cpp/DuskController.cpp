#include "../game_all.h"

void DuskController::Start()
{
	sr->set_enabled(true);
	sr->set_material(ml);
	if (GameDataController::gd->gameTime < 490 && GameDataController::gd->getCurrentDay() > 1)
	{
		sr->set_sprite(dawn1);
	}
	else if (GameDataController::gd->gameTime < 510 && GameDataController::gd->getCurrentDay() > 1)
	{
		sr->set_sprite(dawn2);
	}
	else if (GameDataController::gd->gameTime < 570 && GameDataController::gd->getCurrentDay() > 1)
	{
		sr->set_sprite(dawn3);
	}
	else if (GameDataController::gd->gameTime < 600)
	{
		sr->set_enabled(false);
	}
	else if (GameDataController::gd->gameTime < 720)
	{
		sr->set_sprite(dawn4);
		sr->set_material(ov);
	}
	else if (GameDataController::gd->gameTime < 750)
	{
		sr->set_sprite(dawn5);
		sr->set_material(ov);
	}
	else if (GameDataController::gd->gameTime < 780)
	{
		sr->set_sprite(dawn6);
		sr->set_material(ov);
	}
	else if (GameDataController::gd->gameTime < 810)
	{
		sr->set_sprite(dawn5);
		sr->set_material(ov);
	}
	else if (GameDataController::gd->gameTime < 840)
	{
		sr->set_sprite(dawn4);
		sr->set_material(ov);
	}
	else if (GameDataController::gd->gameTime < 1010)
	{
		sr->set_enabled(false);
	}
	else if (GameDataController::gd->gameTime < 1020)
	{
		sr->set_sprite(dusk1);
	}
	else if (GameDataController::gd->gameTime < 1090)
	{
		sr->set_sprite(dusk2);
	}
	else if (GameDataController::gd->gameTime < 1130)
	{
		sr->set_sprite(dusk3);
	}
	else if (GameDataController::gd->gameTime < 1170)
	{
		sr->set_sprite(dusk4);
	}
	else
	{
		sr->set_sprite(dusk5);
	}
	gameObject->transform->set_position(Vector3(0.0f, 0.0f, -1.5f));
}

void DuskController::Update()
{
}

void DuskController::manualUpdate()
{
	Start();
}

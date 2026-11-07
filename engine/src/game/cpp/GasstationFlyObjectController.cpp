#include "../game_all.h"

void GasstationFlyObjectController::Start()
{
	realX = -0.06f;
	realX = -0.111f;
	flying = false;
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
}

void GasstationFlyObjectController::Update()
{
	if (flying)
	{
		gameObject->transform->set_position(Vector3(realX, realY, gameObject->transform->get_position().z));
		gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
		realX -= 0.005f * Time::get_deltaTime() * 60.0f * 1.5f;
		realY -= 0.01f * Time::get_deltaTime() * 60.0f * 1.5f;
		if (realY < -0.5f)
		{
			realX = -0.065f;
			realY = -0.111f;
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
}

void GasstationFlyObjectController::fly(P<Item> item)
{
	gameObject->GetComponent<SpriteRenderer>()->set_sprite(item->groundSprite);
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	flying = true;
}

#include "../game_all.h"

void CS3ThugSprite::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	shadow = New<SpriteShadow>(gameObject);
	shadow->startAlpha = 0.5f;
	shadow->fadeRateV = 0.009f;
	shadow->fadeRateH = 0.004f;
	shadowOffsetY = 0;
	shadow->update(Vector3(10.0f, 10.0f, 0.0f), Vector2(10.0f, 10.0f), 0);
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	if (thisOneCanBeShot && GameDataController::gd->getObjective(S("cs_thug_shot")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("cs_safe")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void CS3ThugSprite::Update()
{
}

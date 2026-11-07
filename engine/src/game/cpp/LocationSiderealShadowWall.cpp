#include "../game_all.h"

void LocationSiderealShadowWall::Start()
{
	spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
	playerSprite = PlayerController::pc->gameObject->GetComponent<SpriteRenderer>();
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) == 50 && GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) == 10)
	{
		spriteRenderer->set_enabled(false);
	}
	else
	{
		spriteRenderer->set_enabled(true);
	}
}

void LocationSiderealShadowWall::Update()
{
	spriteRenderer->set_sprite(playerSprite->get_sprite());
	spriteRenderer->set_flipX(playerSprite->get_flipX());
	gameObject->transform->set_position(Vector3(PlayerController::pc->gameObject->transform->get_position().x, PlayerController::pc->gameObject->transform->get_position().y * 0.75f, gameObject->transform->get_position().z));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
}

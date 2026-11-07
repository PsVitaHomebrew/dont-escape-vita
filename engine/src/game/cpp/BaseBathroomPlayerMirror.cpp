#include "../game_all.h"

void BaseBathroomPlayerMirror::Start()
{
	spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
	playerSprite = PlayerController::pc->gameObject->GetComponent<SpriteRenderer>();
}

void BaseBathroomPlayerMirror::Update()
{
	spriteRenderer->set_sprite(playerSprite->get_sprite());
	spriteRenderer->set_flipX(playerSprite->get_flipX());
	gameObject->transform->set_position(Vector3(PlayerController::pc->gameObject->transform->get_position().x, PlayerController::pc->gameObject->transform->get_position().y + 0.075f, gameObject->transform->get_position().z));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
}

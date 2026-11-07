#include "../game_all.h"

void EndCredits::Start()
{
	hide();
}

void EndCredits::Update()
{
}

void EndCredits::hide()
{
	GetComponent<SpriteRenderer>()->set_enabled(false);
}

void EndCredits::showDontEscape()
{
	GetComponent<SpriteRenderer>()->set_enabled(true);
	gameObject->transform->set_position(Vector3(gameObject->transform->get_position().x, -0.625f, gameObject->transform->get_position().z));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel3(gameObject->transform->get_position()));
}

void EndCredits::showBlack()
{
	GetComponent<SpriteRenderer>()->set_enabled(true);
	gameObject->transform->set_position(Vector3(gameObject->transform->get_position().x, 0.625f, gameObject->transform->get_position().z));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel3(gameObject->transform->get_position()));
}

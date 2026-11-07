#include "../game_all.h"

void GasstationThug2Controller::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	truex = gameObject->transform->get_position().x;
	truey = gameObject->transform->get_position().y;
	speed = 0.25f;
}

void GasstationThug2Controller::Update()
{
	if (riding)
	{
		speed += Time::get_deltaTime();
		if (speed < 2.0f)
		{
			speed += Time::get_deltaTime();
		}
		if (speed < 1.5f)
		{
			speed += Time::get_deltaTime();
		}
		if (speed < 1.0f)
		{
			speed += Time::get_deltaTime();
		}
		if (speed > 3.0f)
		{
			speed = 3.0f;
		}
		truex -= speed * Time::get_deltaTime() * 0.75f;
		truey -= Time::get_deltaTime() * 0.1f * speed;
		gameObject->transform->set_position(Vector3(truex, truey, gameObject->transform->get_position().z));
		gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
		if (gameObject->transform->get_position().x < -2.0f)
		{
			riding = false;
		}
	}
}

void GasstationThug2Controller::ride()
{
	gameObject->GetComponent<Animator>()->Play(nameId + S("_ride"));
}

void GasstationThug2Controller::startMoving()
{
	riding = true;
}

void GasstationThug2Controller::brrrr()
{
	aS->PlayOneShot(SoundsManagerController::sm->motorbikes);
}

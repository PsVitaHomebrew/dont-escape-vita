#include "../game_all.h"

void LocationDay1WinHeli::Start()
{
	crashing = false;
	thisAnimator = gameObject->GetComponent<Animator>();
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	aS = gameObject->GetComponent<AudioSource>();
	thisAnimator->Play(S("heli_stop"));
}

void LocationDay1WinHeli::Update()
{
	if (crashing)
	{
		if (crashDel <= 0)
		{
			crashDel = 3;
			if (realPosition.y == targetY)
			{
				realPosition.y = targetY - 0.017f;
				house->realPosition.y = -0.017f;
			}
			else
			{
				realPosition.y = targetY;
				house->realPosition.y = 0.0f;
			}
		}
		else
		{
			crashDel--;
		}
	}
	if (launched)
	{
		realPosition.x += speed * Time::get_deltaTime();
		speed += 0.23f * Time::get_deltaTime();
		if (realPosition.x >= targetX)
		{
			realPosition.x = targetX;
		}
		gameObject->transform->set_position(Vector3(realPosition.x, realPosition.y, gameObject->transform->get_position().z));
		gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void LocationDay1WinHeli::crash()
{
	crashing = true;
	houseAnimator->Play(S("house_crash"));
	house->aS->PlayOneShot(SoundsManagerController::sm->heli_crash);
	aS->Stop();
}

void LocationDay1WinHeli::crash2()
{
	crashing = false;
	thisAnimator->Play(S("heli2"));
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationDream2"), WalkController::Direction::NULL_, nullptr, nullptr, false, nullptr, 0.01f);
}

#include "../game_all.h"

void LocationDay1WinHouse::Start()
{
	thisAnimator = gameObject->GetComponent<Animator>();
	thisAnimator->Play(S("house_wait"));
	aS = gameObject->GetComponent<AudioSource>();
}

void LocationDay1WinHouse::Update()
{
	gameObject->transform->set_position(Vector3(realPosition.x, realPosition.y, gameObject->transform->get_position().z));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
}

void LocationDay1WinHouse::startAnim()
{
	heli->aS->PlayOneShot(SoundsManagerController::sm->heli_fly);
	Invoke(S("startPan"), 3.0f);
}

void LocationDay1WinHouse::startPan()
{
	thisAnimator->Play(S("house"));
}

void LocationDay1WinHouse::afterPan()
{
	thisAnimator->Play(S("afterPan"));
	heli->launched = true;
	heli->thisAnimator->Play(S("heli"));
}

void LocationDay1WinHouse::afterCrash()
{
	thisAnimator->Play(S("afterCrash"));
}

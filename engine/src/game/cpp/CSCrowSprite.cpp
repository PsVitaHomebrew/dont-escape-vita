#include "../game_all.h"

void CSCrowSprite::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	gameObject->transform->set_position(Vector3(gameObject->transform->get_position().x, 0.0f, gameObject->transform->get_position().z));
	free = true;
}

void CSCrowSprite::Update()
{
}

void CSCrowSprite::crowAttack()
{
	free = true;
	if (!cs2->playerShot)
	{
		thug->Play(S("thug_bird"));
	}
	aS->PlayOneShot(SoundsManagerController::sm->metal_thud);
}

void CSCrowSprite::makeCrowSound()
{
	switch (Random::Range(0, 3))
	{
	case 0:
		aS->PlayOneShot(SoundsManagerController::sm->crow1);
		break;
	case 1:
		aS->PlayOneShot(SoundsManagerController::sm->crow2);
		break;
	default:
		aS->PlayOneShot(SoundsManagerController::sm->crow3);
		break;
	}
}

void CSCrowSprite::plask()
{
	aS->PlayOneShot(ItemsManager::im->getItem(S("maggot"))->sound);
}

void CSCrowSprite::makeFlappingSound()
{
	aS->PlayOneShot(SoundsManagerController::sm->bird_fly);
}

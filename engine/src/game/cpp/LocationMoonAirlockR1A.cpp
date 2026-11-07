#include "../game_all.h"

void LocationMoonAirlockR1A::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airlock_ring_") + number + S("_");
	if (left)
	{
		objectName += S("a");
	}
	else
	{
		objectName += S("b");
	}
	teleport = true;
	range = 2000.0f;
	audioSource = gameObject->GetComponent<AudioSource>();
}

void LocationMoonAirlockR1A::leave()
{
	PlayerController::pc->spawnName = S("LocationMoon2_Airlock");
	CurtainController::cc->fadeOut(S("Moon2"), WalkController::Direction::N);
}

void LocationMoonAirlockR1A::doorop()
{
	audioSource->PlayOneShot(SoundsManagerController::sm->slidedoor);
}

void LocationMoonAirlockR1A::unlock()
{
	PlayerController::pc->setBusy(false);
}

void LocationMoonAirlockR1A::clickAction()
{
	int objectiveDetail = GameDataController::gd->getObjectiveDetail(S("airlock_ring_") + number);
	objectiveDetail = (left ? (objectiveDetail - 1) : (objectiveDetail + 1));
	if (objectiveDetail < 0)
	{
		objectiveDetail = 7;
	}
	if (objectiveDetail >= 8)
	{
		objectiveDetail = 0;
	}
	GameDataController::gd->setObjectiveDetail(S("airlock_ring_") + number, objectiveDetail);
	audioSource->set_pitch(Random::Range(0.9f, 1.1f));
	switch (Random::Range(1, 4))
	{
	case 1:
		audioSource->set_clip(SoundsManagerController::sm->slide_1);
		break;
	case 2:
		audioSource->set_clip(SoundsManagerController::sm->slide_2);
		break;
	default:
		audioSource->set_clip(SoundsManagerController::sm->slide_3);
		break;
	}
	audioSource->Play();
	PlayerController::pc->setBusy(true);
	if (GameDataController::gd->getObjectiveDetail(S("airlock_ring_1")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_2")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_3")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_4")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_5")) == 0)
	{
		audioSource->PlayOneShot(SoundsManagerController::sm->unlock);
		Invoke(S("doorop"), 0.75f);
		Invoke(S("leave"), 2.5f);
	}
	else
	{
		Invoke(S("unlock"), 0.3f);
	}
	updateAll();
}

void LocationMoonAirlockR1A::updateState()
{
	int objectiveDetail = GameDataController::gd->getObjectiveDetail(S("airlock_ring_") + number);
	sr->set_sprite(sprites[objectiveDetail]);
}

void LocationMoonAirlockR1A::clickAction2()
{
}

void LocationMoonAirlockR1A::clickAction0()
{
}

void LocationMoonAirlockR1A::whatOnClick0()
{
}

void LocationMoonAirlockR1A::whatOnClick()
{
}

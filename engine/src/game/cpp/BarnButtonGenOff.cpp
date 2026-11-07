#include "../game_all.h"

void BarnButtonGenOff::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_generator_button_off");
	teleport = true;
	aS = gameObject->AddComponent<AudioSource>();
	engineStart = SoundsManagerController::sm->engine_start;
	engineRun = SoundsManagerController::sm->engine_run;
	engineDie = SoundsManagerController::sm->engine_die;
	if (GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		aS->set_clip(engineRun);
		aS->set_loop(true);
		aS->set_volume(0.4f);
		aS->Play();
	}
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
}

void BarnButtonGenOff::unlockIt()
{
	PlayerController::pc->setBusy(false);
}

void BarnButtonGenOff::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 0)
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
		if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 0 && GameDataController::gd->getObjective(S("barn_pump_started")))
		{
			aS->Stop();
			aS->set_volume(0.4f);
			aS->PlayOneShot(engineDie);
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_generator_off")));
		}
		GameDataController::gd->setObjectiveDetail(S("barn_pump_started"), 0);
		GameDataController::gd->setObjective(S("barn_pump_started"), false);
		updateAll();
		PlayerController::pc->setBusy(true);
		Invoke(S("unlockIt"), 0.1f);
	}
}

void BarnButtonGenOff::updateAfterAnimation()
{
	updateState();
}

void BarnButtonGenOff::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 0)
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void BarnButtonGenOff::clickAction2()
{
}

void BarnButtonGenOff::clickAction0()
{
}

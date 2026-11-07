#include "../game_all.h"

void BarnGeneratorPull::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_generator_starting_cord");
	teleport = true;
	bbgo = GameObject::Find(S("ButtonOff"))->GetComponent<BarnButtonGenOff>();
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
}

void BarnGeneratorPull::unlockIt()
{
	setCollider(0);
	PlayerController::pc->setBusy(false);
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 0 && GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		bbgo->aS->set_clip(bbgo->engineRun);
		bbgo->aS->set_loop(true);
		bbgo->aS->PlayDelayed(0.0f);
	}
	if (GameDataController::gd->getObjective(S("barn_pump_fueled")))
	{
		if (GameDataController::gd->getObjectiveDetail(S("barn_pump_start_try")) == 1)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_generator_try1")));
		}
		if (GameDataController::gd->getObjectiveDetail(S("barn_pump_start_try")) == 2)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_generator_try2")));
		}
		if (GameDataController::gd->getObjectiveDetail(S("barn_pump_start_try")) == 3)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_generator_try3")));
		}
		if (GameDataController::gd->getObjectiveDetail(S("barn_pump_start_try")) == 4 && GameDataController::gd->getObjective(S("barn_pump_started")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_generator_try4")));
		}
	}
}

void BarnGeneratorPull::no_pull_pull()
{
}

void BarnGeneratorPull::clickAction()
{
	if (GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pump_running")));
		return;
	}
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 0)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pump_no_output")));
		return;
	}
	gameObject->GetComponent<Animator>()->Play(S("b_pull_pull"), 0);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->pull_recoil);
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 0 && GameDataController::gd->getObjective(S("barn_pump_fueled")))
	{
		if (GameDataController::gd->getObjectiveDetail(S("barn_pump_start_try")) == 0)
		{
			bbgo->aS->Stop();
			bbgo->aS->set_loop(false);
			bbgo->aS->set_volume(0.25f);
			bbgo->aS->PlayOneShot(SoundsManagerController::sm->engine_fail);
			PlayerController::pc->setBusy(true);
			GameDataController::gd->setObjectiveDetail(S("barn_pump_start_try"), 1);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("barn_pump_start_try")) == 1)
		{
			bbgo->aS->Stop();
			bbgo->aS->set_volume(0.25f);
			bbgo->aS->set_loop(false);
			bbgo->aS->PlayOneShot(SoundsManagerController::sm->engine_fail);
			PlayerController::pc->setBusy(true);
			GameDataController::gd->setObjectiveDetail(S("barn_pump_start_try"), 2);
		}
		else
		{
			bbgo->aS->Stop();
			bbgo->aS->set_volume(0.25f);
			bbgo->aS->set_loop(false);
			bbgo->aS->PlayOneShot(SoundsManagerController::sm->engine_start);
			PlayerController::pc->setBusy(true);
			if (GameDataController::gd->getObjectiveDetail(S("barn_pump_start_try")) == 2)
			{
				GameDataController::gd->setObjectiveDetail(S("barn_pump_start_try"), 3);
			}
			else
			{
				GameDataController::gd->setObjectiveDetail(S("barn_pump_start_try"), 4);
			}
			GameDataController::gd->setObjective(S("barn_pump_started"), true);
		}
	}
	else if (!GameDataController::gd->getObjective(S("barn_pump_fueled")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pump_no_fuel")));
	}
	else if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 0)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pump_no_output")));
	}
	setCollider(-1);
	Invoke(S("unlockIt"), 1.5f);
	updateAll();
}

void BarnGeneratorPull::updateAfterAnimation()
{
	updateState();
}

void BarnGeneratorPull::updateState()
{
}

void BarnGeneratorPull::clickAction2()
{
}

void BarnGeneratorPull::clickAction0()
{
}

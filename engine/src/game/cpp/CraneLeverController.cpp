#include "../game_all.h"

void CraneLeverController::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action1_e_busy");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_crane_lever_") + leverNumber;
	range = 1.0f;
	if (leverNumber == 0)
	{
		varname = S("cs_crane_left");
	}
	else if (leverNumber == 1)
	{
		varname = S("cs_crane_down");
	}
	else
	{
		varname = S("cs_crane_closed");
	}
	updateState();
}

void CraneLeverController::Update()
{
}

void CraneLeverController::clickAction()
{
	if (GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("crane_lifted")));
		return;
	}
	if (varname == S("cs_crane_down") && GameDataController::gd->getObjective(S("cs_crane_left")) && GameDataController::gd->getObjective(S("cs_crane_down")) && GameDataController::gd->getObjective(S("cs_crane_closed")) && GameDataController::gd->getObjective(S("cs_engine_started")))
	{
		GameDataController::gd->setObjective(S("cs_pack_lifted"), true);
		updateAll();
	}
	GameDataController::gd->setObjective(varname, !GameDataController::gd->getObjective(varname));
	if (GameDataController::gd->getObjective(varname))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->lever1);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->lever2);
	}
	updateState();
	if (GameDataController::gd->getObjective(S("cs_engine_started")))
	{
		if (GameDataController::gd->getObjective(S("cs_pack_lifted")))
		{
			craneThing->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->hydra2);
			Invoke(S("unlockPlayer"), 3.0f);
		}
		else if (varname != S("cs_crane_closed"))
		{
			PlayerController::pc->haltSoftLockProbe();
			if (!GameDataController::gd->getObjective(S("cs_crane_left")) && GameDataController::gd->getObjective(S("cs_crane_closed")) && GameDataController::gd->getObjective(S("cs_crane_down")) && varname == S("cs_crane_left"))
			{
				GameDataController::gd->setObjective(S("cs_crane_left"), true);
				GameDataController::gd->setObjective(S("cs_crane_down"), true);
				GameDataController::gd->setObjective(S("cs_crane_closed"), true);
				craneThing->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->hydra1);
				Invoke(S("okokok"), 0.2f);
			}
			else
			{
				craneThing->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->hydra2);
				Invoke(S("unlockPlayer"), 3.2f);
			}
		}
		else
		{
			PlayerController::pc->haltSoftLockProbe();
			craneThing->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->hydra1);
			Invoke(S("unlockPlayer"), 1.0f);
		}
	}
	else
	{
		Invoke(S("noFuel"), 1.0f);
	}
}

void CraneLeverController::noFuel()
{
	GameDataController::gd->setObjective(varname, !GameDataController::gd->getObjective(varname));
	updateState();
	PlayerController::pc->setBusy(false);
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_leaver_no_power")));
	if (GameDataController::gd->getObjective(varname))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->lever1);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->lever2);
	}
}

void CraneLeverController::okokok()
{
	updateState();
	craneThing->updateState();
	Invoke(S("unlockPlayer2"), 1.0f);
}

void CraneLeverController::unlockPlayer2()
{
	PlayerController::pc->resumeSoftLockProbe();
	PlayerController::pc->setBusy(false);
}

void CraneLeverController::unlockPlayer()
{
	if ((GameDataController::gd->getObjective(S("cs_crane_left")) && GameDataController::gd->getObjective(S("cs_crane_closed")) && GameDataController::gd->getObjective(S("cs_crane_down")) && (varname == S("cs_crane_down") || varname == S("cs_crane_left"))) || (GameDataController::gd->getObjective(S("cs_crane_left")) && !GameDataController::gd->getObjective(S("cs_crane_closed")) && GameDataController::gd->getObjective(S("cs_crane_down")) && varname == S("cs_crane_left")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_bang1, 1.0f);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crane_collision")));
		GameDataController::gd->setObjective(varname, false);
		if (GameDataController::gd->getObjective(S("cs_pack_lifted")))
		{
			craneThing->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->hydra1);
		}
		else
		{
			craneThing->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->hydra2);
		}
		PlayerController::pc->setBusy(true);
		updateState();
		if (varname == S("cs_crane_closed"))
		{
			Invoke(S("unlockPlayer"), 1.0f);
		}
		else
		{
			Invoke(S("unlockPlayer"), 3.0f);
		}
	}
	else
	{
		PlayerController::pc->resumeSoftLockProbe();
		PlayerController::pc->textField->dissmiss(true);
		PlayerController::pc->setBusy(false);
	}
}

void CraneLeverController::updateState()
{
	if (GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		characterAnimationName = S("action1_e_busy");
		animationFlip = false;
		useCurrentDirection = false;
	}
	if (GameDataController::gd->getObjective(varname))
	{
		GetComponent<SpriteRenderer>()->set_sprite(position2);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(position1);
	}
	if (GameDataController::gd->getObjective(S("cs_engine_started")))
	{
		craneThing->updateState();
	}
}

void CraneLeverController::hideLever()
{
	setCollider(-1);
	GetComponent<SpriteRenderer>()->set_enabled(false);
}

void CraneLeverController::showLever()
{
	setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
}

void CraneLeverController::clickAction2()
{
}

void CraneLeverController::clickAction0()
{
}

void CraneLeverController::whatOnClick0()
{
}

void CraneLeverController::whatOnClick()
{
}

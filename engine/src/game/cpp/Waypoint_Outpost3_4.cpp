#include "../game_all.h"

void Waypoint_Outpost3_4::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_elevator");
	actionType = Type::NormalAction;
	range = 0.0f;
	aS = gameObject->GetComponent<AudioSource>();
	sr = gameObject->GetComponent<SpriteRenderer>();
	animator = gameObject->GetComponent<Animator>();
	doubleClickCondition = S("none");
}

void Waypoint_Outpost3_4::playAnimation(String param)
{
	animator->Play(param);
}

void Waypoint_Outpost3_4::clickAction()
{
	if (cickedAlready)
	{
		cickedAlready = false;
		return;
	}
	if (!GameDataController::gd->getObjective(S("outpost_elevator_powered")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_elevator_no_power")));
		clickIt();
	}
	if (!GameDataController::gd->getObjective(S("outpost_elevator_up")))
	{
		return;
	}
	if (GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		if (!GameDataController::gd->getObjective(S("outpost_door_powered")))
		{
			playSound(S("elevator_away"));
			Invoke(S("rideDown"), 1.0f);
			PlayerController::wc->forceAnimationForAnimationEvent(S("stand_n"));
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_elevator_no_doormat")));
		}
	}
	else
	{
		PlayerController::pc->setBusy(false);
	}
}

void Waypoint_Outpost3_4::rideDown0()
{
}

void Waypoint_Outpost3_4::rideDown()
{
	GameDataController::gd->setObjective(S("outpost_elevator_travel"), true);
	PlayerController::pc->spawnName = S("Waypoint_Outpost4_3");
	CurtainController::cc->fadeOut(S("LocationOutpost4"), WalkController::Direction::W);
}

void Waypoint_Outpost3_4::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_elevator_travel")))
	{
		playSound(S("elevator_ding"));
		playAnimation(S("elevator_open"));
		GameDataController::gd->setObjective(S("outpost_elevator_travel"), false);
		PlayerController::pc->setBusy(true);
		PlayerController::wc->forceAnimation(S("stand_se"), true);
		PlayerController::pc->resumeSoftLockProbe();
	}
	else if (!GameDataController::gd->getObjective(S("outpost_elevator_powered")))
	{
		playAnimation(S("elevator_closed0"));
	}
	else if (GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		playAnimation(S("elevator_opened"));
	}
	else if (GameDataController::gd->getObjective(S("outpost_elevator_up")))
	{
		playAnimation(S("elevator_closed1"));
	}
	else
	{
		playAnimation(S("elevator_closed0"));
	}
	updateElevatorLogic();
}

void Waypoint_Outpost3_4::playSound(String soundName)
{
	if (soundName == S("elevator_away"))
	{
		aS->PlayOneShot(SoundsManagerController::sm->elevator_away);
	}
	if (soundName == S("elevator_come"))
	{
		aS->PlayOneShot(SoundsManagerController::sm->elevator_come);
	}
	if (soundName == S("elevator_ding"))
	{
		aS->PlayOneShot(SoundsManagerController::sm->elevator_ding);
	}
	if (soundName == S("elevator_door"))
	{
		aS->PlayOneShot(SoundsManagerController::sm->elevator_door);
	}
}

void Waypoint_Outpost3_4::clickAction2()
{
}

void Waypoint_Outpost3_4::clickAction0()
{
	cickedAlready = false;
	PlayerController::pc->haltSoftLockProbe();
	if (!GameDataController::gd->getObjective(S("outpost_elevator_open")) && GameDataController::gd->getObjective(S("outpost_elevator_powered")))
	{
		if (GameDataController::gd->getObjective(S("outpost_elevator_up")))
		{
			cickedAlready = true;
			playAnimation(S("elevator_open"));
			GameDataController::gd->setObjective(S("outpost_elevator_open"), true);
		}
		else
		{
			cickedAlready = true;
			playAnimation(S("elevator_up"));
			GameDataController::gd->setObjective(S("outpost_elevator_up"), true);
			GameDataController::gd->setObjective(S("outpost_elevator_open"), true);
		}
	}
}

void Waypoint_Outpost3_4::elevatorReady()
{
	PlayerController::pc->resumeSoftLockProbe();
	PlayerController::wc->fullStop(true);
	PlayerController::pc->setBusy(false);
	PlayerController::wc->forceAnimationForAnimationEvent(S("action_stnd_n"));
	updateAll();
	closeDoorInFive();
}

void Waypoint_Outpost3_4::closeDoorInFive()
{
	Invoke(S("closeDoorKindly"), 5.0f);
}

void Waypoint_Outpost3_4::lookAtIt()
{
}

void Waypoint_Outpost3_4::clickIt()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click2);
}

void Waypoint_Outpost3_4::updateElevatorLogic()
{
	if (GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("ClosedElevator"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
		if (GameDataController::gd->getObjective(S("outpost_door_powered")))
		{
			characterAnimationName = S("action_stnd_");
			animationFlip = false;
			useCurrentDirection = true;
			range = 100.0f;
		}
		else
		{
			characterAnimationName = S("stop");
			animationFlip = false;
			useCurrentDirection = true;
			range = 0.0f;
		}
		setCollider(1);
		actionMarker = actionRide;
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::S_;
		objectName = S("outpost_elevator_open");
	}
	else
	{
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("ClosedElevator"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
		if (GameDataController::gd->getObjective(S("outpost_elevator_powered")))
		{
			characterAnimationName = S("action1_e_animation");
			animationFlip = false;
			useCurrentDirection = false;
		}
		else
		{
			characterAnimationName = S("action1_e");
			animationFlip = false;
			useCurrentDirection = false;
		}
		setCollider(0);
		actionType = Type::NormalAction;
		objectName = S("outpost_elevator");
		actionMarker = actionCall;
		range = 0.0f;
	}
}

void Waypoint_Outpost3_4::closeDoorQuickAndFast()
{
	GameDataController::gd->setObjective(S("outpost_elevator_open"), false);
	updateElevatorLogic();
	playAnimation(S("elevator_closed1"));
}

void Waypoint_Outpost3_4::closeDoorKindly()
{
	if (!GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		return;
	}
	if (PlayerController::wc->currentXY.x > 150.0f && PlayerController::wc->currentXY.y > 40.0f)
	{
		closeDoorInFive();
		return;
	}
	GameDataController::gd->setObjective(S("outpost_elevator_open"), false);
	updateElevatorLogic();
	playAnimation(S("elevator_close"));
	if (PlayerController::wc->getFinalTarget().x > 150.0f || (PlayerController::wc->currentXY.x > 150.0f && PlayerController::wc->currentXY.y > 40.0f))
	{
		PlayerController::wc->fullStop(true);
	}
}

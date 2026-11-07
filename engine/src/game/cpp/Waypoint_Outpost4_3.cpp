#include "../game_all.h"

void Waypoint_Outpost4_3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_elevator2");
	actionType = Type::NormalAction;
	range = 0.0f;
	aS = gameObject->GetComponent<AudioSource>();
	sr = gameObject->GetComponent<SpriteRenderer>();
	animator = gameObject->GetComponent<Animator>();
	doubleClickCondition = S("none");
}

void Waypoint_Outpost4_3::playAnimation(String param)
{
	animator->Play(param);
}

void Waypoint_Outpost4_3::clickAction()
{
	if (cickedAlready)
	{
		cickedAlready = false;
	}
	else if (GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		playSound(S("elevator_away"));
		Invoke(S("rideDown"), 1.0f);
		PlayerController::wc->forceAnimationForAnimationEvent(S("stand_n"));
	}
	else
	{
		PlayerController::pc->setBusy(false);
	}
}

void Waypoint_Outpost4_3::rideDown()
{
	GameDataController::gd->setObjective(S("outpost_elevator_travel"), true);
	PlayerController::pc->spawnName = S("Waypoint_Outpost3_4");
	CurtainController::cc->fadeOut(S("LocationOutpost3"), WalkController::Direction::W);
}

void Waypoint_Outpost4_3::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_elevator_travel")))
	{
		playSound(S("elevator_ding"));
		playAnimation(S("elevator2_open"));
		GameDataController::gd->setObjective(S("outpost_elevator_travel"), false);
		zindex->set_enabled(false);
		zindex2->set_enabled(true);
		PlayerController::pc->setBusy(true);
	}
	else if (GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		playAnimation(S("elevator2_opened"));
		zindex->set_enabled(true);
		zindex2->set_enabled(false);
	}
	else
	{
		playAnimation(S("elevator2_closed"));
		zindex->set_enabled(true);
		zindex2->set_enabled(false);
	}
	updateElevatorLogic();
}

void Waypoint_Outpost4_3::playSound(String soundName)
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

void Waypoint_Outpost4_3::clickAction2()
{
}

void Waypoint_Outpost4_3::clickAction0()
{
	cickedAlready = false;
	if (!GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		cickedAlready = true;
		playAnimation(S("elevator2_open"));
		GameDataController::gd->setObjective(S("outpost_elevator_open"), true);
	}
}

void Waypoint_Outpost4_3::closeDoorQuickAndFast()
{
	GameDataController::gd->setObjective(S("outpost_elevator_open"), false);
	updateElevatorLogic();
	playAnimation(S("elevator2_closed"));
}

void Waypoint_Outpost4_3::elevatorReady()
{
	PlayerController::pc->setBusy(false);
	PlayerController::wc->forceAnimationForAnimationEvent(S("action_stnd_n"));
	updateAll();
	closeDoorInFive();
	zindex->set_enabled(true);
	zindex2->set_enabled(false);
}

void Waypoint_Outpost4_3::closeDoorInFive()
{
	Invoke(S("closeDoorKindly"), 5.0f);
}

void Waypoint_Outpost4_3::lookAtIt()
{
}

void Waypoint_Outpost4_3::clickIt()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click2);
}

void Waypoint_Outpost4_3::updateElevatorLogic()
{
	if (GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("ClosedElevator"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		range = 0.0f;
		setCollider(1);
		actionMarker = actionRide;
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
		objectName = S("outpost_elevator_open");
		return;
	}
	GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
	GameObject::Find(S("ClosedElevator"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	if (GameDataController::gd->getObjective(S("outpost_elevator_powered")))
	{
		characterAnimationName = S("action1_e_animation");
		animationFlip = false;
		useCurrentDirection = false;
	}
	setCollider(0);
	actionType = Type::NormalAction;
	objectName = S("outpost_elevator");
	actionMarker = actionCall;
	range = 0.0f;
}

void Waypoint_Outpost4_3::closeDoorKindly()
{
	if (!GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		return;
	}
	if (PlayerController::wc->currentXY.x > 165.0f)
	{
		closeDoorInFive();
		return;
	}
	GameDataController::gd->setObjective(S("outpost_elevator_open"), false);
	updateElevatorLogic();
	playAnimation(S("elevator2_close"));
	if (PlayerController::wc->getFinalTarget().x >= 165.0f || PlayerController::wc->currentXY.x >= 165.0f)
	{
		PlayerController::wc->fullStop(true);
	}
}

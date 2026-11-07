#include "../game_all.h"

void LocationSiderealF3CElevator::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_elevator_closed");
	range = 1.0f;
	teleport = false;
	updateState();
}

void LocationSiderealF3CElevator::Update()
{
}

void LocationSiderealF3CElevator::whatOnClick0()
{
	if (GameDataController::gd->getObjective(S("sidereal_elevator_f3_open")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 20.0f;
	}
	else
	{
		characterAnimationName = S("action1_e");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
	}
}

void LocationSiderealF3CElevator::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_elevator_f3_open")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_elevator3")), true, false, false, 150);
		return;
	}
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_creak1);
	GameDataController::gd->setObjective(S("sidereal_elevator_f3_open"), true);
	updateState();
}

void LocationSiderealF3CElevator::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_elevator_f3_open")))
	{
		objectName = S("sidereal_elevator_3");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("f3c_elevator_overlay"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		objectName = S("sidereal_elevator_closed");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("f3c_elevator_overlay"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void LocationSiderealF3CElevator::clickAction2()
{
}

void LocationSiderealF3CElevator::clickAction0()
{
}

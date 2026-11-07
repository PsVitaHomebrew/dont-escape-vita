#include "../game_all.h"

void LocationSiderealF2CElevator::Start()
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

void LocationSiderealF2CElevator::Update()
{
}

void LocationSiderealF2CElevator::whatOnClick0()
{
	if (GameDataController::gd->getObjective(S("sidereal_elevator_f2_open")))
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

void LocationSiderealF2CElevator::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_elevator_f2_open")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_elevator2")), true, false, false, 150);
		return;
	}
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_creak1);
	GameDataController::gd->setObjective(S("sidereal_elevator_f2_open"), true);
	updateState();
}

void LocationSiderealF2CElevator::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_elevator_f2_open")))
	{
		objectName = S("sidereal_elevator_2");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		objectName = S("sidereal_elevator_closed");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void LocationSiderealF2CElevator::clickAction2()
{
}

void LocationSiderealF2CElevator::clickAction0()
{
}

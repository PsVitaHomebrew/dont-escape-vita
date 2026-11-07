#include "../game_all.h"

void LocationSiderealF3SComputer1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_computer1");
	range = 11.0f;
	teleport = false;
	updateState();
}

void LocationSiderealF3SComputer1::Update()
{
}

void LocationSiderealF3SComputer1::whatOnClick()
{
}

void LocationSiderealF3SComputer1::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_computer1")), true, false, false, 150);
}

void LocationSiderealF3SComputer1::updateState()
{
}

void LocationSiderealF3SComputer1::clickAction2()
{
}

void LocationSiderealF3SComputer1::clickAction0()
{
}

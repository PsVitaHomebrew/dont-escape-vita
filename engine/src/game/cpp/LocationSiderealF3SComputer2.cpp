#include "../game_all.h"

void LocationSiderealF3SComputer2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_computer2");
	range = 8000.0f;
	teleport = false;
	updateState();
}

void LocationSiderealF3SComputer2::Update()
{
}

void LocationSiderealF3SComputer2::whatOnClick()
{
}

void LocationSiderealF3SComputer2::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_computer2")), true, false, false, 150);
}

void LocationSiderealF3SComputer2::updateState()
{
}

void LocationSiderealF3SComputer2::clickAction2()
{
}

void LocationSiderealF3SComputer2::clickAction0()
{
}

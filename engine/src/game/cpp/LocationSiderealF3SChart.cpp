#include "../game_all.h"

void LocationSiderealF3SChart::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_chart");
	range = 8000.0f;
	teleport = false;
	updateState();
}

void LocationSiderealF3SChart::Update()
{
}

void LocationSiderealF3SChart::whatOnClick()
{
}

void LocationSiderealF3SChart::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_chart")), true, false, false, 150);
}

void LocationSiderealF3SChart::updateState()
{
}

void LocationSiderealF3SChart::clickAction2()
{
}

void LocationSiderealF3SChart::clickAction0()
{
}

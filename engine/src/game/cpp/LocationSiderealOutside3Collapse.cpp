#include "../game_all.h"

void LocationSiderealOutside3Collapse::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_side_building");
	range = 20.0f;
	teleport = false;
	updateState();
}

void LocationSiderealOutside3Collapse::Update()
{
}

void LocationSiderealOutside3Collapse::whatOnClick()
{
}

void LocationSiderealOutside3Collapse::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_back_collapsed")), true, false, false, 150);
}

void LocationSiderealOutside3Collapse::updateState()
{
}

void LocationSiderealOutside3Collapse::clickAction2()
{
}

void LocationSiderealOutside3Collapse::clickAction0()
{
}

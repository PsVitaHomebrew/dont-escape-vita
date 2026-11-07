#include "../game_all.h"

void LocationSiderealF3CCollapse::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_collapse1");
	range = 11.0f;
	teleport = false;
	updateState();
}

void LocationSiderealF3CCollapse::Update()
{
}

void LocationSiderealF3CCollapse::whatOnClick()
{
}

void LocationSiderealF3CCollapse::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_collapse1")), true, false, false, 150);
}

void LocationSiderealF3CCollapse::updateState()
{
}

void LocationSiderealF3CCollapse::clickAction2()
{
}

void LocationSiderealF3CCollapse::clickAction0()
{
}

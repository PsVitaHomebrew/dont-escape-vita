#include "../game_all.h"

void LocationSiderealF0S_Reception::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	range = 50.0f;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_reception_desk");
	actionType = Type::NormalAction;
}

void LocationSiderealF0S_Reception::clickAction()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_reception_desk"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void LocationSiderealF0S_Reception::updateState()
{
}

void LocationSiderealF0S_Reception::clickAction2()
{
}

void LocationSiderealF0S_Reception::clickAction0()
{
}

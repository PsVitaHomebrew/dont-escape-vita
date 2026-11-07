#include "../game_all.h"

void LocationSiderealF0S_Logo::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	range = 50.0f;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_logo");
	actionType = Type::NormalAction;
}

void LocationSiderealF0S_Logo::clickAction()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_logo"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void LocationSiderealF0S_Logo::updateState()
{
}

void LocationSiderealF0S_Logo::clickAction2()
{
}

void LocationSiderealF0S_Logo::clickAction0()
{
}

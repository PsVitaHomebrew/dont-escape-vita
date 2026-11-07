#include "../game_all.h"

void SiderealF1B_Calendar::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_calendar");
	actionType = Type::NormalAction;
}

void SiderealF1B_Calendar::clickAction()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_calendar1"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_calendar2"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void SiderealF1B_Calendar::updateState()
{
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	range = 50.0f;
	objectName = S("sidereal_calendar");
}

void SiderealF1B_Calendar::clickAction2()
{
}

void SiderealF1B_Calendar::clickAction0()
{
}

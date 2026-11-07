#include "../game_all.h"

void SiderealF2SPC1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_pc_off");
	actionType = Type::NormalAction;
}

void SiderealF2SPC1::clickAction()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_pc_off1"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_pc_off2"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_pc_off3"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void SiderealF2SPC1::updateState()
{
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	range = 50.0f;
	objectName = S("sidereal_pc_off");
}

void SiderealF2SPC1::clickAction2()
{
}

void SiderealF2SPC1::clickAction0()
{
}

#include "../game_all.h"

void SiderealF1B_Photocopier::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_photocopier");
	actionType = Type::NormalAction;
}

void SiderealF1B_Photocopier::clickAction()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_photocopier"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void SiderealF1B_Photocopier::updateState()
{
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	range = 50.0f;
	objectName = S("sidereal_photocopier");
}

void SiderealF1B_Photocopier::clickAction2()
{
}

void SiderealF1B_Photocopier::clickAction0()
{
}

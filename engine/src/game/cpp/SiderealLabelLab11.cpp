#include "../game_all.h"

void SiderealLabelLab11::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	range = 100.0f;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_lab11");
	actionType = Type::NormalAction;
}

void SiderealLabelLab11::clickAction()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_lab11"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void SiderealLabelLab11::updateState()
{
}

void SiderealLabelLab11::clickAction2()
{
}

void SiderealLabelLab11::clickAction0()
{
}

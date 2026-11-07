#include "../game_all.h"

void LocationOutpost5Ship::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship");
	actionType = Type::NormalAction;
}

void LocationOutpost5Ship::clickAction()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("outpost_ship_1"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("outpost_ship_2"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("outpost_ship_3"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("outpost_ship_4"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void LocationOutpost5Ship::updateState()
{
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	range = 50.0f;
}

void LocationOutpost5Ship::clickAction2()
{
}

void LocationOutpost5Ship::clickAction0()
{
}

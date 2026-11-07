#include "../game_all.h"

void LocationSiderealF3CAlarm::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_alarm1");
	range = 11.0f;
	teleport = false;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("rock"), GameStrings::getString(GameStrings::actions, S("sidereal_alarm_break")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rock2"), GameStrings::getString(GameStrings::actions, S("sidereal_alarm_break")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("sidereal_alarm_break")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("sidereal_alarm_break")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("sidereal_alarm_break")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("sidereal_alarm_break")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("shovel"), GameStrings::getString(GameStrings::actions, S("sidereal_alarm_break")), nullptr, String::Empty));
	updateState();
}

void LocationSiderealF3CAlarm::Update()
{
}

void LocationSiderealF3CAlarm::whatOnClick()
{
}

void LocationSiderealF3CAlarm::clickAction()
{
	PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_alarm1")));
	PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_alarm2")));
}

void LocationSiderealF3CAlarm::updateState()
{
}

void LocationSiderealF3CAlarm::clickAction2()
{
}

void LocationSiderealF3CAlarm::clickAction0()
{
}

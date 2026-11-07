#include "../game_all.h"

void LocationSiderealOutside2Lamp::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_streetlamp");
	range = 20.0f;
	teleport = false;
	updateState();
}

void LocationSiderealOutside2Lamp::Update()
{
}

void LocationSiderealOutside2Lamp::whatOnClick()
{
}

void LocationSiderealOutside2Lamp::clickAction()
{
	DialogueController::dc->quickDialogue(GingerActionController::getColor(), GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>(), S("sidereal_streetlamp"));
}

void LocationSiderealOutside2Lamp::updateState()
{
}

void LocationSiderealOutside2Lamp::clickAction2()
{
}

void LocationSiderealOutside2Lamp::clickAction0()
{
}

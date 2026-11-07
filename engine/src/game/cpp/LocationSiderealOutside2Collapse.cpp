#include "../game_all.h"

void LocationSiderealOutside2Collapse::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_entry_collapsed");
	range = 20.0f;
	teleport = false;
	updateState();
}

void LocationSiderealOutside2Collapse::Update()
{
}

void LocationSiderealOutside2Collapse::whatOnClick()
{
}

void LocationSiderealOutside2Collapse::clickAction()
{
	DialogueController::dc->quickDialogue(GingerActionController::getColor(), GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>(), S("sidereal_entry_closed"));
}

void LocationSiderealOutside2Collapse::updateState()
{
}

void LocationSiderealOutside2Collapse::clickAction2()
{
}

void LocationSiderealOutside2Collapse::clickAction0()
{
}

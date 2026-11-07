#include "../game_all.h"

void FirstEncounterHouse::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_stnd_e");
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("first_encounter");
}

void FirstEncounterHouse::clickAction()
{
}

void FirstEncounterHouse::updateState()
{
}

void FirstEncounterHouse::clickAction2()
{
}

void FirstEncounterHouse::clickAction0()
{
}

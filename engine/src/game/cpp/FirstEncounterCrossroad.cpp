#include "../game_all.h"

void FirstEncounterCrossroad::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_stnd_n");
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("first_encounter");
}

void FirstEncounterCrossroad::clickAction()
{
}

void FirstEncounterCrossroad::updateState()
{
}

void FirstEncounterCrossroad::clickAction2()
{
}

void FirstEncounterCrossroad::clickAction0()
{
}

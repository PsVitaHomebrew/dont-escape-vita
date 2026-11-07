#include "../game_all.h"

void BaseBathroomMirror::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bathroom_mirror");
	range = 2.0f;
}

void BaseBathroomMirror::clickAction()
{
	int num = Random::Range(1, 6);
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("bathroom_mirror") + num), true);
}

void BaseBathroomMirror::updateState()
{
	colliderManager->setCollider(0);
}

void BaseBathroomMirror::clickAction2()
{
}

void BaseBathroomMirror::clickAction0()
{
}

void BaseBathroomMirror::whatOnClick0()
{
}

void BaseBathroomMirror::whatOnClick()
{
}

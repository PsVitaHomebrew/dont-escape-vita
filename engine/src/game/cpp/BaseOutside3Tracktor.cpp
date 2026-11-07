#include "../game_all.h"

void BaseOutside3Tracktor::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tracktor");
	range = 100.0f;
}

void BaseOutside3Tracktor::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tracktor")), true);
}

void BaseOutside3Tracktor::updateState()
{
	colliderManager->setCollider(0);
}

void BaseOutside3Tracktor::clickAction2()
{
}

void BaseOutside3Tracktor::clickAction0()
{
}

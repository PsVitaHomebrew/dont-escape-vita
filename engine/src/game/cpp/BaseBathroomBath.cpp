#include "../game_all.h"

void BaseBathroomBath::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bathroom_bath");
	range = 50.0f;
}

void BaseBathroomBath::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("bathroom_bath")), true);
}

void BaseBathroomBath::updateState()
{
	colliderManager->setCollider(0);
}

void BaseBathroomBath::clickAction2()
{
}

void BaseBathroomBath::clickAction0()
{
}

void BaseBathroomBath::whatOnClick0()
{
}

void BaseBathroomBath::whatOnClick()
{
}

#include "../game_all.h"

void BarnFields::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_fields");
	range = 300.0f;
}

void BarnFields::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_fields")), true);
	PlayerController::wc->forceAnimation(S("stand_n"));
	PlayerController::wc->dir = WalkController::Direction::N;
}

void BarnFields::updateState()
{
	colliderManager->setCollider(0);
}

void BarnFields::clickAction2()
{
}

void BarnFields::clickAction0()
{
}

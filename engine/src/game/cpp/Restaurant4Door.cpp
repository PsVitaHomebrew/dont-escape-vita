#include "../game_all.h"

void Restaurant4Door::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_backdoor");
	range = 20.0f;
}

void Restaurant4Door::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_backdoor2")), true);
}

void Restaurant4Door::updateState()
{
}

void Restaurant4Door::whatOnClick()
{
}

void Restaurant4Door::clickAction2()
{
}

void Restaurant4Door::clickAction0()
{
}

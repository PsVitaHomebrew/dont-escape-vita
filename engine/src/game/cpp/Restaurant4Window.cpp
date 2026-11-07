#include "../game_all.h"

void Restaurant4Window::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_window");
	range = 20.0f;
}

void Restaurant4Window::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_window2")), true);
}

void Restaurant4Window::updateState()
{
}

void Restaurant4Window::whatOnClick()
{
}

void Restaurant4Window::clickAction2()
{
}

void Restaurant4Window::clickAction0()
{
}

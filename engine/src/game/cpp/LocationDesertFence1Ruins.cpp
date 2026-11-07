#include "../game_all.h"

void LocationDesertFence1Ruins::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tutorial_ruins");
	range = 8000.0f;
	teleport = false;
	updateState();
}

void LocationDesertFence1Ruins::Update()
{
}

void LocationDesertFence1Ruins::whatOnClick()
{
}

void LocationDesertFence1Ruins::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tutorial_ruins")), true, false, false, 150);
}

void LocationDesertFence1Ruins::updateState()
{
}

void LocationDesertFence1Ruins::clickAction2()
{
}

void LocationDesertFence1Ruins::clickAction0()
{
}

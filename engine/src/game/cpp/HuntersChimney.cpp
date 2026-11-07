#include "../game_all.h"

void HuntersChimney::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("hunters_chimney");
	range = 30.0f;
	teleport = false;
	updateState();
}

void HuntersChimney::Update()
{
}

void HuntersChimney::whatOnClick()
{
}

void HuntersChimney::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("hunters_chimney")), true, false, false, 150);
}

void HuntersChimney::updateState()
{
}

void HuntersChimney::clickAction2()
{
}

void HuntersChimney::clickAction0()
{
}

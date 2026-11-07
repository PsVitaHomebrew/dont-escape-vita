#include "../game_all.h"

void FuseboxFuse1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("source_good");
	range = 8000.0f;
	teleport = false;
	updateState();
}

void FuseboxFuse1::Update()
{
}

void FuseboxFuse1::whatOnClick()
{
}

void FuseboxFuse1::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("outpost_fuse_source")), true, false, false, 150);
}

void FuseboxFuse1::updateState()
{
}

void FuseboxFuse1::clickAction2()
{
}

void FuseboxFuse1::clickAction0()
{
}

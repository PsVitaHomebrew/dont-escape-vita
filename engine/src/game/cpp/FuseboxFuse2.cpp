#include "../game_all.h"

void FuseboxFuse2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("source_bad");
	range = 8000.0f;
	teleport = false;
	updateState();
}

void FuseboxFuse2::Update()
{
}

void FuseboxFuse2::whatOnClick()
{
}

void FuseboxFuse2::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("outpost_fuse_source")), true, false, false, 150);
}

void FuseboxFuse2::updateState()
{
}

void FuseboxFuse2::clickAction2()
{
}

void FuseboxFuse2::clickAction0()
{
}

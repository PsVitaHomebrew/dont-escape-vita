#include "../game_all.h"

void HuntersPicture::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("hunters_picture");
	range = 30.0f;
	teleport = false;
	updateState();
}

void HuntersPicture::Update()
{
}

void HuntersPicture::whatOnClick()
{
}

void HuntersPicture::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("hunters_picture")), true, false, false, 150);
}

void HuntersPicture::updateState()
{
}

void HuntersPicture::clickAction2()
{
}

void HuntersPicture::clickAction0()
{
}

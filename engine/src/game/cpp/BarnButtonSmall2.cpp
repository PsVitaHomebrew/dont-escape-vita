#include "../game_all.h"

void BarnButtonSmall2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_console_ground");
	teleport = true;
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
}

void BarnButtonSmall2::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_console_no_ground")), true, true);
}

void BarnButtonSmall2::updateAfterAnimation()
{
	updateState();
}

void BarnButtonSmall2::updateState()
{
	GetComponent<Animator>()->Play(S("b_small_off"), 0);
}

void BarnButtonSmall2::clickAction2()
{
}

void BarnButtonSmall2::clickAction0()
{
}

#include "../game_all.h"

void BarnButtonSmall::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_console_stnd_by");
	teleport = true;
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
}

void BarnButtonSmall::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_console_no_stnd_by")), true, true);
}

void BarnButtonSmall::updateAfterAnimation()
{
	updateState();
}

void BarnButtonSmall::updateState()
{
	if (GameDataController::gd->getObjective(S("barn_sprinklers_enabled")))
	{
		GetComponent<Animator>()->Play(S("b_small_off"), 0);
	}
	else
	{
		GetComponent<Animator>()->Play(S("b_small_blink"), 0);
	}
}

void BarnButtonSmall::clickAction2()
{
}

void BarnButtonSmall::clickAction0()
{
}

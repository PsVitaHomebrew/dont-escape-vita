#include "../game_all.h"

void BarnButtonSmall3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_console_air");
	teleport = true;
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
}

void BarnButtonSmall3::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_console_air")), true, true);
	if (!GameDataController::gd->getObjective(S("barn_sprinklers_enabled")))
	{
		GameDataController::gd->setObjective(S("barn_sprinklers_enabled"), true);
		GetComponent<Animator>()->Play(S("b_small_off_on"), 0);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
	}
}

void BarnButtonSmall3::updateAfterAnimation()
{
	updateAll();
}

void BarnButtonSmall3::updateState()
{
	if (GameDataController::gd->getObjective(S("barn_sprinklers_enabled")))
	{
		GetComponent<Animator>()->Play(S("b_small_on"), 0);
	}
	else
	{
		GetComponent<Animator>()->Play(S("b_small_off"), 0);
	}
}

void BarnButtonSmall3::clickAction2()
{
}

void BarnButtonSmall3::clickAction0()
{
}

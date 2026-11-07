#include "../game_all.h"

void BarnButtonX::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_console_reset");
	teleport = true;
	engineRun = SoundsManagerController::sm->engine_run;
	aS = gameObject->AddComponent<AudioSource>();
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) > 0 && GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		aS->set_clip(engineRun);
		aS->set_loop(true);
		aS->set_volume(0.25f);
		aS->Play();
	}
}

void BarnButtonX::clickAction()
{
	GameDataController::gd->setObjective(S("barn_sprinklers_b1"), false);
	GameDataController::gd->setObjective(S("barn_sprinklers_b2"), false);
	GameDataController::gd->setObjective(S("barn_sprinklers_b3"), false);
	GameDataController::gd->setObjective(S("barn_sprinklers_b4"), false);
	GameDataController::gd->setObjective(S("barn_sprinklers_b5"), false);
	GameDataController::gd->setObjective(S("barn_sprinklers_b6"), false);
	GameDataController::gd->setObjective(S("barn_sprinklers_b7"), false);
	GameDataController::gd->setObjective(S("barn_sprinklers_b8"), false);
	GetComponent<Animator>()->Play(S("b_x_press"), 0);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
}

void BarnButtonX::updateAfterAnimation()
{
	updateAll();
}

void BarnButtonX::updateState()
{
	GetComponent<Animator>()->Play(S("b_x_off"), 0);
}

void BarnButtonX::clickAction2()
{
}

void BarnButtonX::clickAction0()
{
}

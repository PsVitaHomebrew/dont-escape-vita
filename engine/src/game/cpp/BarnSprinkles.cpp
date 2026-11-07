#include "../game_all.h"

void BarnSprinkles::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kick_ne");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_sprinklers_disabled");
	setCollider(0);
	lights = gameObject->transform->Find(S("SprinklesLights"))->gameObject;
}

void BarnSprinkles::updateState()
{
	if (GameDataController::gd->getCurrentDay() > 1 || GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 2 || !GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		lights->GetComponent<Animator>()->Play(S("sprinkles_off"), 0);
		objectName = S("barn_sprinklers_disabled");
	}
	else if (!GameDataController::gd->getObjective(S("barn_sprinklers_enabled")))
	{
		lights->GetComponent<Animator>()->Play(S("sprinkles_lights"), 0);
		objectName = S("barn_sprinklers_enabled");
	}
	else
	{
		lights->GetComponent<Animator>()->Play(S("sprinkles_on"), 0);
		objectName = S("barn_sprinklers_set");
	}
}

void BarnSprinkles::whatOnClick()
{
	if (!GameDataController::gd->getObjective(S("base_discovered")))
	{
		characterAnimationName = S("action_stnd_n");
	}
	else if ((GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 2 && GameDataController::gd->getObjective(S("barn_pump_started"))) || usedItem != String::Empty)
	{
		characterAnimationName = S("action_n");
	}
	else
	{
		characterAnimationName = S("kick_ne");
	}
}

void BarnSprinkles::clickAction()
{
	if (!GameDataController::gd->getObjective(S("base_discovered")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pipe_first")));
		return;
	}
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 2 || !GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_sprinklers_no_power")), true);
	}
	else
	{
		if (GameDataController::gd->getCurrentDay() > 1)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_sprinklers_broken")));
			return;
		}
		PlayerController::pc->spawnName = S("BarnConsoleExit");
		CurtainController::cc->fadeOut(S("BarnConsole"), WalkController::Direction::W);
	}
	updateState();
	PlayerController::wc->forceDirection(WalkController::Direction::NE);
}

void BarnSprinkles::clickAction2()
{
}

void BarnSprinkles::clickAction0()
{
}

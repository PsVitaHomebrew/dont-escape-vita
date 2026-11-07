#include "../game_all.h"

void SiderealF1CVent::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_vent");
}

void SiderealF1CVent::clickAction2()
{
}

void SiderealF1CVent::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) != 15 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) != 40)
	{
		setCollider(-1);
		return;
	}
	setCollider(0);
	if (GameDataController::gd->getObjective(S("sidereal_vent_open")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 100.0f;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void SiderealF1CVent::clickAction()
{
	if (!GameDataController::gd->getObjective(S("sidereal_vent_open")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_thud2);
	}
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_vent_too_small")));
	GameDataController::gd->setObjective(S("sidereal_vent_open"), true);
	updateAll();
}

void SiderealF1CVent::clickAction0()
{
}

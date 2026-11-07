#include "../game_all.h"

void SiderealF1CDarkness::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_e");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_darkness");
	range = 20.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("lighter"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flamethrower"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flamethrower_empty"), String::Empty, nullptr, String::Empty));
}

void SiderealF1CDarkness::clickAction2()
{
}

void SiderealF1CDarkness::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) != 15 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) != 40)
	{
		setCollider(0);
	}
	else
	{
		setCollider(-1);
	}
}

void SiderealF1CDarkness::zapalniczka()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->flashlight);
}

void SiderealF1CDarkness::clickAction()
{
	if (usedItem != String::Empty)
	{
		zapalniczka();
		Invoke(S("zapalniczka"), 0.3f);
		Invoke(S("zapalniczka"), 0.8f);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_lighter_failed")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("too_dark")));
	}
}

void SiderealF1CDarkness::clickAction0()
{
}

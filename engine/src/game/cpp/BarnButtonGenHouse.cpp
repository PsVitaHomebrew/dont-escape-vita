#include "../game_all.h"

void BarnButtonGenHouse::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_generator_button_house");
	teleport = true;
	bbgo = GameObject::Find(S("ButtonOff"))->GetComponent<BarnButtonGenOff>();
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
}

void BarnButtonGenHouse::unlockIt()
{
	updateAll();
	PlayerController::pc->setBusy(false);
}

void BarnButtonGenHouse::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 1)
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
		PlayerController::pc->setBusy(true);
		Invoke(S("unlockIt"), 0.1f);
		GameDataController::gd->setObjectiveDetail(S("barn_pump_started"), 1);
		updateAll();
	}
}

void BarnButtonGenHouse::updateAfterAnimation()
{
	updateState();
}

void BarnButtonGenHouse::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void BarnButtonGenHouse::clickAction2()
{
}

void BarnButtonGenHouse::clickAction0()
{
}

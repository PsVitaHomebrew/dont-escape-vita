#include "../game_all.h"

void BarnButtonGenSprinklers::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_generator_button_sprinklers");
	teleport = true;
	bbgo = GameObject::Find(S("ButtonOff"))->GetComponent<BarnButtonGenOff>();
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
}

void BarnButtonGenSprinklers::unlockIt()
{
	PlayerController::pc->setBusy(false);
	updateAll();
}

void BarnButtonGenSprinklers::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 2)
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
		PlayerController::pc->setBusy(true);
		Invoke(S("unlockIt"), 0.1f);
		GameDataController::gd->setObjectiveDetail(S("barn_pump_started"), 2);
	}
}

void BarnButtonGenSprinklers::updateAfterAnimation()
{
	updateState();
}

void BarnButtonGenSprinklers::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 2)
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void BarnButtonGenSprinklers::clickAction2()
{
}

void BarnButtonGenSprinklers::clickAction0()
{
}
